add_library(userInterface)

target_sources(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/UserInterface.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/ptui.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/ptui.h"
)

target_include_directories(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
)