add_library(Keybind "KeyBindController.cpp")

##Library insertion
add_subdirectory(control)
add_subdirectory(binds)

target_link_libraries(Keybind
	PRIVATE
	Control
	Binds
)

target_include_directories(Keybind PRIVATE "control")
##End of library insertion

target_sources(Keybind
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}/KeyBindController.cpp"
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/KeyBindController.h"
		
)

target_include_directories(Keybind
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}
)