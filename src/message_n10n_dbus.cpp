#include "./message_n10n.hpp"

#include <solanaceae/contact/contact_store_i.hpp>

#include <solanaceae/message3/components.hpp>
#include <solanaceae/contact/components.hpp>

#include <dbus-cxx.h>
#include <org_freedesktop_NotificationsProxy.h>

#include <iostream>
#include <stdexcept>

// global state
static std::shared_ptr<DBus::Dispatcher> g_dispatcher = nullptr;
static std::shared_ptr<DBus::Connection> g_connection = nullptr;
static std::shared_ptr<DBus::ObjectProxy> g_object = nullptr;
static std::shared_ptr<org_freedesktop_NotificationsProxy> g_notifications_proxy = nullptr;

MessageN10n::MessageN10n(ContactStore4I& cs, RegistryMessageModelI& rmm) : _cs(cs), _rmm(rmm), _rmm_sr(_rmm.newSubRef(this)) {
	//WinToastLib::WinToast::instance()->setAppName(L"Tomato");
	//const auto aumi = WinToastLib::WinToast::configureAUMI(L"green", L"solanaceae", L"solanaceae_message_n10n", L"20240517");


	g_dispatcher = DBus::StandaloneDispatcher::create();
	if (!g_dispatcher) {
		throw std::runtime_error("failed to create dbus dispatcher");
	}

	g_connection = g_dispatcher->create_connection(DBus::BusType::SESSION);
	if (!g_connection) {
		throw std::runtime_error("failed to connect to dbus session");
	}

	g_object = g_connection->create_object_proxy("org.freedesktop.Notifications", "/org/freedesktop/Notifications");
	if (!g_object) {
		throw std::runtime_error("failed to create the dbus proxy object");
	}

	g_notifications_proxy = org_freedesktop_NotificationsProxy::create();
	if (!g_notifications_proxy) {
		throw std::runtime_error("failed to create the dbus notification proxy interface");
	}
	if (!g_object->add_interface(g_notifications_proxy)) {
		throw std::runtime_error("failed to bind the dbus notification proxy interface to the proxy object");
	}

	auto server_info = g_notifications_proxy->GetServerInformation();
	std::cout << "MN10N: connected to dbus notification server '" << std::get<0>(server_info.m_data) << "'\n";

	auto server_caps = g_notifications_proxy->GetCapabilities();
	std::cout << "MN10N: server provides caps: ";
	for (const auto& it : server_caps) {
		std::cout << it << ", ";
	}
	std::cout << "\n";

	_rmm_sr.subscribe(RegistryMessageModel_Event::message_construct);
}

MessageN10n::~MessageN10n(void) {
	// inverse shutdown
	// TODO: use raii instead
	g_notifications_proxy = nullptr;
	g_object = nullptr;
	g_connection = nullptr;
	g_dispatcher = nullptr;
}

bool MessageN10n::onEvent(const Message::Events::MessageConstruct& e) {
	std::cout << "MN10N: message constructed called\n";

	if (!e.e.all_of<
		Message::Components::MessageText,
		Message::Components::ContactFrom,
		Message::Components::ContactTo
	>()) {
		return false;
	}

	const auto& text = e.e.get<Message::Components::MessageText>().text;
	if (text.empty()) {
		return false;
	}

	const auto sender_c = e.e.get<Message::Components::ContactFrom>().c;

	const auto& cr = _cs.registry();

	if (cr.all_of<Contact::Components::TagSelfStrong>(sender_c)) {
		return false;
	}
	if (!cr.all_of<
		Contact::Components::Name
	>(sender_c)) {
		return false;
	}

	std::string title {
		cr.get<Contact::Components::Name>(sender_c).name
	};

	if (title.empty()) {
		return false;
	}

	// callsig: https://specifications.freedesktop.org/notification/latest/protocol.html#id-1.10.3.3.4
	// hints: https://specifications.freedesktop.org/notification/latest/hints.html
	try {
		g_notifications_proxy->Notify(
			"tomato",
			0,
			"", // app icon (type?)
			title,
			text,
			{}, // actions
			{ // hints
				{"category", "im.received"},
			},
			-1 // expire_timeout
		);
	} catch (...) {
		std::cerr << "MN10N error: notification failed!\n";
	}

	return false;
}
