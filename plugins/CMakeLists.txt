cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

add_library(plugin_message_n10n SHARED
	./plugin_message_n10n.cpp
)

target_link_libraries(plugin_message_n10n PUBLIC
	solanaceae_plugin
	solanaceae_message_n10n
)

