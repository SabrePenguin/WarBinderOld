## This fun if statement is for switching between UIs. You shouldn't have to mess with it, but
## I'm unfamiliar with CMake, so feel free to make it better.
if(WXSET)
	message(STATUS "Enabled wxWidgets")
	add_executable(WarBinder WIN32 "WarBinder.cpp" )
	target_compile_definitions(WarBinder
		PRIVATE
			WX_WIDGETS
	)
else()
	message(STATUS "Enabled PTUI")
	add_executable(WarBinder "WarBinder.cpp" )
endif()
##Library insertion
add_subdirectory(keyController)
add_subdirectory(user_interface)

target_include_directories(Keybind 
	PRIVATE 
	"keyController"
	"user_interface"
	${SDL3}
	${UI_INCLUDE_DIRS}
) 

target_link_libraries(WarBinder
	PRIVATE
	Keybind
	userInterface
	SDL3::SDL3-static
)