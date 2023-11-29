add_executable(WarBinder "WarBinder.cpp")

##Library insertion
add_subdirectory(keyController)

target_link_libraries(WarBinder
	PRIVATE
	Keybind
)

target_include_directories(Keybind PRIVATE "keyController")
##End of library insertion