add_library(Control)

target_sources ( Control
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/Control.h"
		"${CMAKE_CURRENT_LIST_DIR}/Key.h"
		"${CMAKE_CURRENT_LIST_DIR}/Mouse.h"
		"${CMAKE_CURRENT_LIST_DIR}/Joystick.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Key.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/Mouse.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/Joystick.cpp"
)

target_include_directories(Control
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)