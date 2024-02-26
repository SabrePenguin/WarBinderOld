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


#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


int initialize()
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl ;
		return 1 ;
	}
	return 0 ;
}

void sdl_loop( std::shared_ptr<KeyBindController> key_controller )
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
				key_controller->notify_device( &event ) ;
				break ;
			case SDL_CONTROLLERDEVICEREMOVED:
				key_controller->notify_device( &event ) ;
				break ;
			case SDL_USEREVENT:
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
	{
		std::shared_ptr<KeyBindController> key1 = std::make_shared<KeyBindController>( "../../../../control_list.csv",
			"../../../../wt_bind_list.csv",
			"../../../../options.csv",
			"english" ) ;

		//TODO: Check proper file type
		key1.get()->import( "../../../../controller_settings.blk" ) ;

		std::shared_ptr<UserInterface> user_interface = std::make_shared<ptui>(key1);
		key1.get()->add_ui_observer( user_interface ) ;

		std::thread ui( &UserInterface::main_loop, user_interface, key1 ) ;
		sdl_loop( key1 ) ;
		ui.join() ;
	}
	//_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
	//_CrtDumpMemoryLeaks();
	return 0;
}
