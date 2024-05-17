#include "./message_n10n.hpp"

#include <solanaceae/message3/components.hpp>


MessageN10n::MessageN10n(RegistryMessageModel& rmm) : _rmm(rmm) {
	// Register WinToast App User Model
	WinToastLib::WinToast::instance()->setAppName(L"Tomato");
	const auto aumi = WinToastLib::WinToast::configureAUMI(L"green", L"solanaceae", L"solanaceae_message_n10n", L"20240517");
	WinToastLib::WinToast::instance()->setAppUserModelId(aumi);

	// Initialize WinToast
	if (!WinToastLib::WinToast::instance()->initialize()) {
		std::wcout << L"Error, could not initialize the lib!" << std::endl;
	} else {
		_rmm.subscribe(this, RegistryMessageModel_Event::message_construct);
	}
}

MessageN10n::~MessageN10n(void) {
}

bool MessageN10n::onEvent(const Message::Events::MessageConstruct& e) {
	std::cout << "message constructed called\n";

	/*
	if (!e.e.all_of<Message::Components::MessageText>()) {
		return false;
	}
	*/

	auto templ = WinToastLib::WinToastTemplate(WinToastLib::WinToastTemplate::Text02);
	templ.setTextField(L"title", WinToastLib::WinToastTemplate::FirstLine);
	templ.setTextField(L"subtitle", WinToastLib::WinToastTemplate::SecondLine);

	WinToastLib::WinToast::WinToastError error;
	const auto toast_id = WinToastLib::WinToast::instance()->showToast(templ, this, &error);
	if (toast_id < 0) {
		std::wcout << L"Error: Could not launch your toast notification! " << error << std::endl;
	}

	return false;
}

void MessageN10n::toastActivated(void) const {
	// action
	std::cout << "action called\n";
}

void MessageN10n::toastActivated(int actionIndex) const {
	// action
	std::cout << "action called\n";
}

void MessageN10n::toastDismissed(WinToastDismissalReason) const {
}

void MessageN10n::toastFailed(void) const {
}