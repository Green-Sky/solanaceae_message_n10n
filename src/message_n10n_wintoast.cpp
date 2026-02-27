#include "./message_n10n.hpp"

#include <solanaceae/contact/contact_store_i.hpp>

#include <solanaceae/message3/components.hpp>
#include <solanaceae/contact/components.hpp>

#include <wintoastlib.h>

#include <locale>
#include <codecvt>

class OurHandler : public WinToastLib::IWinToastHandler {
	public:
		virtual ~OurHandler(void) override {
		}

	protected: // wintoast
		void toastActivated(void) const override {
			std::cout << "action called\n";
		}

		void toastActivated(int actionIndex) const override {
			std::cout << "action called\n";
		}

		void toastActivated(const char* response) const override {
			std::cout << "action called\n";
		}

		void toastDismissed(WinToastDismissalReason state) const override {
		}

		void toastFailed(void) const override {
		}
};


MessageN10n::MessageN10n(ContactStore4I& cs, RegistryMessageModelI& rmm) : _cs(cs), _rmm(rmm), _rmm_sr(_rmm.newSubRef(this)) {
	// Register WinToast App User Model
	WinToastLib::WinToast::instance()->setAppName(L"Tomato");
	const auto aumi = WinToastLib::WinToast::configureAUMI(L"green", L"solanaceae", L"solanaceae_message_n10n", L"20240517");
	WinToastLib::WinToast::instance()->setAppUserModelId(aumi);

	// Initialize WinToast
	if (!WinToastLib::WinToast::instance()->initialize()) {
		std::wcout << L"Error, could not initialize the lib!" << std::endl;
	} else {
		_rmm_sr.subscribe(RegistryMessageModel_Event::message_construct);
	}
}

MessageN10n::~MessageN10n(void) {
}

bool MessageN10n::onEvent(const Message::Events::MessageConstruct& e) {
	std::cout << "message constructed called\n";

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

	auto templ = WinToastLib::WinToastTemplate(WinToastLib::WinToastTemplate::Text02);
	templ.setTextField(
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.from_bytes(
			title
		),
		WinToastLib::WinToastTemplate::FirstLine
	);
	templ.setTextField(
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>{}.from_bytes(
			text
		),
		WinToastLib::WinToastTemplate::SecondLine
	);

	WinToastLib::WinToast::WinToastError error;
	const auto toast_id = WinToastLib::WinToast::instance()->showToast(templ, new OurHandler, &error);
	if (toast_id < 0) {
		std::wcout << L"Error: Could not launch your toast notification! " << error << std::endl;
	}

	return false;
}
