add_executable(WarBinder WIN32 "WarBinder.cpp" )
##Library insertion
add_subdirectory(keyController)
add_subdirectory(user_interface)

target_include_directories(Keybind 
	PRIVATE 
	"keyController"
	"user_interface"
	${SDL2}
	${wxWidgets_SOURCE_DIR}/include
)

target_link_libraries(WarBinder
	PRIVATE
	Keybind
	userInterface
	SDL2::SDL2-static
)

##End of library insertion