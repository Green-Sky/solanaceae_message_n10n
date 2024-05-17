#pragma once

#include <solanaceae/message3/registry_message_model.hpp>

class MessageN10n : public RegistryMessageModelEventI {
	RegistryMessageModel& _rmm;

	public:
		MessageN10n(RegistryMessageModel& rmm);
		virtual ~MessageN10n(void);

	protected: // rmm
		bool onEvent(const Message::Events::MessageConstruct& e) override;
};

