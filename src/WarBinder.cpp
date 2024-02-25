// WarBinder.cpp : The entry point of the program. Controls basic loop logic.
//
#define SDL_MAIN_HANDLED
#include "WarBinder.h"
#include "KeyBindController.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <SDL.h>
#include <thread>
#include "UserInterface.h"
#include "ptui.h"
#include <memory>


int initialize()
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl ;
		return 1 ;
	}
	return 0 ;
}

void sdl_loop( KeyBindController* key_controller )
{
	bool active = true ;

	SDL_Event event ;

	while( active )
	{
		if( SDL_WaitEvent( &event ) )
		{
			switch( event.type )
			{
			case SDL_CONTROLLERDEVICEADDED:
				std::cout << "Added device" << std::endl ;
				key_controller->notify_device( &event ) ;
				break ;
			case SDL_CONTROLLERDEVICEREMOVED:
				std::cout << "Removed device" << std::endl ;
				key_controller->notify_device( &event ) ;
				break ;
			case SDL_USEREVENT:
				std::cout << "Quitting SDL\n" ;
				active = false ;
				break ;
			}

		}
	}
}


int main()
{
	if( initialize() )
		return 1 ;

	KeyBindController key1("../../../../control_list.csv",
		"../../../../wt_bind_list.csv",
		"../../../../options.csv",
		"english");

	//TODO: Check proper file type
	key1.import( "../../../../controller_settings.blk" ) ;

	std::shared_ptr<UserInterface> user_interface = std::make_shared<ptui>();
	key1.add_ui_observer( user_interface ) ;
	std::cout << "Starting loop\n" ;

	std::thread ui( &UserInterface::main_loop, user_interface, &key1 ) ;
	sdl_loop( &key1 ) ;
	ui.join() ;
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
	_CrtDumpMemoryLeaks();
	return 0;
}