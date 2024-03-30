// WarBinder.cpp : The entry point of the program. Controls basic loop logic.
//
#define SDL_MAIN_HANDLED
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <SDL.h>
#include <thread>
#include <memory>
#include "WarBinder.h"
#include "KeyBindController.h"
#include "UserInterface.h"
#include "ptui.h"
#ifdef WX_WIDGETS
	#include "WXWrapper.h"
	#include <wx/wxprec.h>
	//Use wxWidgets builtin because the regular has some conflicts with globals
	#ifdef __WXMSW__
		#include <wx/msw/msvcrt.h>      // redefines the new() operator 
	#endif
	#ifdef _MSC_VER
	#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
	#endif
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
	int i = 0 ;
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
			case SDL_CONTROLLERBUTTONDOWN:
				i++ ;
				break ;
			case SDL_CONTROLLERAXISMOTION:
				i++ ;
				std::cout << i << std::endl ;
				break ;
			case SDL_USEREVENT:
				active = false ;
				break ;
			}
		}
	}
}


int main( int argc, char* argv[] )
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc( 14299 ) ;
	//SDL_SetHint( SDL_HINT_JOYSTICK_THREAD, "1" );
	if( initialize() )
		return 1 ;
	{
		std::shared_ptr<KeyBindController> key1 = std::make_shared<KeyBindController>( "../../../../control_list.csv",
			"../../../../wt_bind_list.csv",
			"../../../../options.csv",
			"english" ) ;

		//TODO: Check proper file type
		key1.get()->import( "../../../../controller_settings.blk" ) ;
		//ptui
		/*
		
		//*/
		///*
		#ifdef WX_WIDGETS
		std::shared_ptr<UserInterface> user_interface = std::make_shared<WXWrapper>( key1 ) ;
		key1.get()->add_ui_observer( user_interface ) ;
		std::thread ui( &UserInterface::main_loop, user_interface, argc, argv ) ;
		#else
		std::shared_ptr<UserInterface> user_interface = std::make_shared<ptui>( key1 );
		key1.get()->add_ui_observer( user_interface ) ;
		std::thread ui( &UserInterface::main_loop, user_interface, argc, argv ) ;
		#endif
		//*/

		sdl_loop( key1 ) ;
		ui.join() ;
		key1.get()->clear_ui_observers() ;
	}

	return 0;
}
