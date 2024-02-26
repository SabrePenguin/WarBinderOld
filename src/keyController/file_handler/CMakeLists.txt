add_library(FileHandler)

target_sources(FileHandler
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/reader.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/reader.cpp"
)

target_include_directories(FileHandler
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)