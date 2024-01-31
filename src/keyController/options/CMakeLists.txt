add_library(Opts)

target_sources(Opts
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/Options.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Options.cpp"
)

target_include_directories(Opts
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)