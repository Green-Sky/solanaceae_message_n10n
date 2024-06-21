cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

add_library(plugin_message_n10n MODULE
	./plugin_message_n10n.cpp
)

target_link_libraries(plugin_message_n10n PUBLIC
	solanaceae_plugin
	solanaceae_message_n10n
)

set_target_properties(plugin_message_n10n PROPERTIES
	C_VISIBILITY_PRESET hidden
)
# probably not enough
target_compile_definitions(plugin_message_n10n PUBLIC ENTT_API_IMPORT)

