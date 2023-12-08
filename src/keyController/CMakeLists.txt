add_library(Keybind)

##Library insertion
add_subdirectory(control)
add_subdirectory(bind)

target_link_libraries(Keybind
	PRIVATE
	Control
	Bind
)

target_include_directories(Keybind PRIVATE "control" "bind")
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