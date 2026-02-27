cmake_minimum_required(VERSION 3.9...3.24 FATAL_ERROR)

add_library(dbus_notifications
	./org_freedesktop_NotificationsProxy.h
	./org_freedesktop_NotificationsProxy.cpp
	# TODO: add portal
)

target_include_directories(dbus_notifications PUBLIC .)
target_compile_features(dbus_notifications PUBLIC cxx_std_17)

target_link_libraries(dbus_notifications PUBLIC
	dbus-cxx
)

