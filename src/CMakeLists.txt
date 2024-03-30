if(WXSET)
	target_compile_definitions(WarBinder
		PRIVATE
			WX_WIDGETS
	)
	add_executable(WarBinder WIN32 "WarBinder.cpp" )
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
	${SDL2}
	${UI_INCLUDE_DIRS}
) 

target_link_libraries(WarBinder
	PRIVATE
	Keybind
	userInterface
	SDL2::SDL2-static
)



##End of library insertion