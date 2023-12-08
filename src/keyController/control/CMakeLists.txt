add_library(Control)

target_sources ( Control
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/Control.h"
		"${CMAKE_CURRENT_LIST_DIR}/Key.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Key.cpp"
)

target_include_directories(Control
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)