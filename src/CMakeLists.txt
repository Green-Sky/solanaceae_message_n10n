cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_message_n10n
	./message_n10n.hpp
)

target_include_directories(solanaceae_message_n10n PUBLIC .)
target_compile_features(solanaceae_message_n10n PUBLIC cxx_std_17)
target_link_libraries(solanaceae_message_n10n PUBLIC
	solanaceae_message3
)

if (WIN32)
	target_link_libraries(solanaceae_message_n10n PUBLIC
		WinToast
	)
	target_sources(solanaceae_message_n10n PRIVATE
		./message_n10n_wintoast.cpp
	)
elseif(APPLE)
	message(FATAL_ERROR "Apple platforms is not supported")
elseif(ANDROID)
	message(FATAL_ERROR "Android is not supported")
else() # assume dbus
	add_subdirectory(dbus)

	target_link_libraries(solanaceae_message_n10n PUBLIC
		dbus-cxx
		dbus_notifications
	)
	target_sources(solanaceae_message_n10n PRIVATE
		./message_n10n_dbus.cpp
	)
endif()

########################################

