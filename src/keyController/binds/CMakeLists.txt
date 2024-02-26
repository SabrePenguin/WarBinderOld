add_library(Binds)

target_sources ( Binds
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/Bind.h"
		"${CMAKE_CURRENT_LIST_DIR}/Bind.cpp"
)

target_include_directories(Binds
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)