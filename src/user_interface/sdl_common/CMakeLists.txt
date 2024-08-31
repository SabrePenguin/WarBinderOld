#This CMake controls the common input ui created in SDL

add_library(sdl_common_gui)

target_sources(sdl_common_gui
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/SDLKeyInput.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/SDLKeyInput.cpp"
)

target_include_directories(sdl_common_gui
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
	PRIVATE
		${SDL3}
)

target_link_libraries(sdl_common_gui
	SDL3::SDL3-static
)