#include <solanaceae/plugin/solana_plugin_v1.h>

#include "message_n10n.hpp"

#include <iostream>

static std::unique_ptr<MessageN10n> g_mn10n = nullptr;

constexpr const char* plugin_name = "MessageN10n";

extern "C" {

SOLANA_PLUGIN_EXPORT const char* solana_plugin_get_name(void) {
	return plugin_name;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_get_version(void) {
	return SOLANA_PLUGIN_VERSION;
}

SOLANA_PLUGIN_EXPORT uint32_t solana_plugin_start(struct SolanaAPI* solana_api) {
	std::cout << "PLUGIN " << plugin_name << " START()\n";

	if (solana_api == nullptr) {
		return 1;
	}

	try {
		auto* cr = PLUG_RESOLVE_INSTANCE_VERSIONED(Contact3Registry, "1");
		auto* rmm = PLUG_RESOLVE_INSTANCE(RegistryMessageModel);

		// static store, could be anywhere tho
		// construct with fetched dependencies
		g_mn10n = std::make_unique<MessageN10n>(*cr, *rmm);

		// register types
		PLUG_PROVIDE_INSTANCE(MessageN10n, plugin_name, g_mn10n.get());
	} catch (const ResolveException& e) {
		std::cerr << "PLUGIN " << plugin_name << " " << e.what << "\n";
		return 2;
	}

	return 0;
}

SOLANA_PLUGIN_EXPORT void solana_plugin_stop(void) {
	std::cout << "PLUGIN " << plugin_name << " STOP()\n";

	g_mn10n.reset();
}

SOLANA_PLUGIN_EXPORT float solana_plugin_tick(float) {
	//return g_rpbot->tick(delta);
	return 1000.f;
}

} // extern C

