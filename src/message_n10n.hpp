#pragma once

#include <solanaceae/contact/fwd.hpp>
#include <solanaceae/message3/registry_message_model.hpp>

class MessageN10n : public RegistryMessageModelEventI {
	ContactStore4I& _cs;
	RegistryMessageModelI& _rmm;
	RegistryMessageModelI::SubscriptionReference _rmm_sr;

	public:
		MessageN10n(ContactStore4I& cs, RegistryMessageModelI& rmm);
		virtual ~MessageN10n(void);

	protected: // rmm
		bool onEvent(const Message::Events::MessageConstruct& e) override;

};
