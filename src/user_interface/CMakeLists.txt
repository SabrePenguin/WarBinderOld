add_library(userInterface)

target_sources(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/UserInterface.h"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/ptui.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/ptui.h"
		"${CMAKE_CURRENT_LIST_DIR}/UserInterface.cpp"
)

target_include_directories(userInterface
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}"
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/"
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/control/"
		"${CMAKE_CURRENT_LIST_DIR}/../keyController/bind/"
		"${SDL2}"
)

target_link_libraries(userInterface
	PRIVATE
	SDL2::SDL2-static
)