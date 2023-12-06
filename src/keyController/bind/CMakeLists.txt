add_library(Bind)

target_sources ( Bind
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/Bind.h"
		"${CMAKE_CURRENT_LIST_DIR}/Axis.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Bind.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/Axis.cpp"
)

target_include_directories(Bind
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)