#include "./message_n10n.hpp"

#include <solanaceae/message3/components.hpp>

MessageN10n::MessageN10n(RegistryMessageModel& rmm) : _rmm(rmm) {
}

MessageN10n::~MessageN10n(void) {
}

bool MessageN10n::onEvent(const Message::Events::MessageConstruct& e) {
	if (!e.e.all_of<Message::Components::MessageText>()) {
		return false;
	}

	return false;
}

