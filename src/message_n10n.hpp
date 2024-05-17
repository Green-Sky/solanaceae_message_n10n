#pragma once

#include <solanaceae/message3/registry_message_model.hpp>

#include <wintoastlib.h>

class MessageN10n : public RegistryMessageModelEventI, public WinToastLib::IWinToastHandler {
	RegistryMessageModel& _rmm;

	public:
		MessageN10n(RegistryMessageModel& rmm);
		virtual ~MessageN10n(void);

	protected: // rmm
		bool onEvent(const Message::Events::MessageConstruct& e) override;

	protected: // wintoast
		void toastActivated(void) const override;
		void toastActivated(int actionIndex) const override;
		void toastDismissed(WinToastDismissalReason state) const override;
		void toastFailed(void) const override;
};
