#pragma once

#include <solanaceae/message3/registry_message_model.hpp>

class MessageN10n : public RegistryMessageModelEventI {
	Contact3Registry& _cr;
	RegistryMessageModel& _rmm;

	public:
		MessageN10n(Contact3Registry& cr, RegistryMessageModel& rmm);
		virtual ~MessageN10n(void);

	protected: // rmm
		bool onEvent(const Message::Events::MessageConstruct& e) override;

};
