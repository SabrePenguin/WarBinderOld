add_library(CSV)

target_sources(CSV
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/CSVin.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/CSVin.cpp"
)

target_include_directories(CSV
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)