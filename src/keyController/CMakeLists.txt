add_library(Keybind)

##Library insertion
add_subdirectory(control)
add_subdirectory(bind)
add_subdirectory(csv)
add_subdirectory(file_handler)

target_link_libraries(Keybind
	PRIVATE
	Control
	Bind
	CSV
	FileHandler
)

target_include_directories(Keybind PRIVATE "control" "bind" "csv" "file_handler")
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