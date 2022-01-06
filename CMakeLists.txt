cmake_minimum_required(VERSION 3.8)
project(WickedSpaceFlight)

find_package(WickedEngine REQUIRED)

set (SOURCE_FILES
	stdafx.cpp
	WickedSpaceFlight.cpp
	WickedSpaceFlight.h
	stdafx.h
)

if (WIN32)
	list (APPEND SOURCE_FILES
		main_Windows.cpp
		main_Windows.h
		WickedSpaceFlight.rc
	)

	add_executable(WickedSpaceFlight WIN32 ${SOURCE_FILES})

	target_link_libraries(WickedSpaceFlight PUBLIC
		WickedEngine_Windows
	)
else()
	list (APPEND SOURCE_FILES
		main_SDL2.cpp
	)

	add_executable(WickedSpaceFlight ${SOURCE_FILES})

	target_link_libraries(WickedSpaceFlight PUBLIC
		WickedEngine::WickedEngine
	)
endif ()



if (MSVC)
	set_property(TARGET WickedSpaceFlight PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif ()

get_target_property(LIB_DXCOMPILER_LOCATION WickedEngine::dxcompiler IMPORTED_LOCATION)

# Copy content to build folder:
add_custom_command(
	TARGET WickedSpaceFlight POST_BUILD
	# Copy the shader library next to the executable
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LIB_DXCOMPILER_LOCATION}" "${CMAKE_CURRENT_BINARY_DIR}"
)
