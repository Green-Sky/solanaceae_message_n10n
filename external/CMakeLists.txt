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

if (NOT TARGET WinToast)
	FetchContent_Declare(WinToast_ext
		GIT_REPOSITORY https://github.com/mohabouje/WinToast.git
		GIT_TAG v1.3.1
	)
	FetchContent_MakeAvailable(WinToast_ext)
endif()

