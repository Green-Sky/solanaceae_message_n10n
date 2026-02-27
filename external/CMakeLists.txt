cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(FetchContent)

if (NOT TARGET solanaceae_message3)
	FetchContent_Declare(solanaceae_message3
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_message3.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_message3)
endif()

if (NOT TARGET solanaceae_plugin)
	FetchContent_Declare(solanaceae_plugin
		GIT_REPOSITORY https://github.com/Green-Sky/solanaceae_plugin.git
		GIT_TAG master
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(solanaceae_plugin)
endif()

if (WIN32)
	if (NOT TARGET WinToast)
		FetchContent_Declare(WinToast_ext
			GIT_REPOSITORY https://github.com/mohabouje/WinToast.git
			GIT_TAG v1.3.1
		)
		FetchContent_MakeAvailable(WinToast_ext)
	endif()
elseif(APPLE)
	message(FATAL_ERROR "Apple platforms is not supported")
elseif(ANDROID)
	message(FATAL_ERROR "Android is not supported")
else() # assume dbus

	# TODO: find dbus-cxx


	# requires sigc/sigc++-3.0
	# nixpkg libsigcxx30
	# with tools requires expat, dbus, popt
	set(ENABLE_TOOLS OFF CACHE INTERNAL "")
	set(BUILD_TESTING OFF CACHE INTERNAL "")
	FetchContent_Declare(dbus-cxx
		GIT_REPOSITORY https://github.com/Green-Sky/dbus-cxx.git
		GIT_TAG cmake_static
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(dbus-cxx)
endif()



