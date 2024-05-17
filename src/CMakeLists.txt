cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_message_n10n
	./message_n10n.hpp
	./message_n10n.cpp
)

target_include_directories(solanaceae_message_n10n PUBLIC .)
target_compile_features(solanaceae_message_n10n PUBLIC cxx_std_17)
target_link_libraries(solanaceae_message_n10n PUBLIC
	solanaceae_message3
)

########################################

