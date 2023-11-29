add_library(Keybind "")

##Library insertion
add_subdirectory(control)

target_link_libraries(Keybind
	PRIVATE
	Control
)

target_include_directories(Keybind PRIVATE "control")
##End of library insertion

target_sources(Keybind
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/KeyBindController.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/Bind.cpp"
		"${CMAKE_CURRENT_LIST_DIR}/Bind.h"
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/KeyBindController.h"
		
)

target_include_directories(Keybind
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)