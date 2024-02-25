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


int initialize()
{
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl ;
		return 1 ;
	}
	return 0 ;
}

/**
 * @brief 
 * @param key_controller 
*/
void ui_loop( KeyBindController* key_controller )
{
	
	bool active = true ;
	char in ;
	char data_type ;
	uint32_t threadType = SDL_RegisterEvents( 1 ) ;
	while( active )
	{
		std::cout << "\nEnter one of the following choices:\nD(isplay)\nQ(uit)\n" << std::endl ;
		std::cin >> in ;
		switch( in )
		{
			//Display information
		case 'D':
		case 'd':
			std::cout << "\nEnter one of the following choices:\nK(eys)\nB(inds)\n" << std::endl ;
			std::cin >> data_type ;
			//Key information
			if( data_type == 'k' )
			{
				auto data = key_controller->get_key_details() ;
				for( auto element = data.begin() ; element != data.end() ; element++ )
				{
					std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
				}
				break ;
			}
			//Bind information
			else if( data_type == 'b' )
			{
				auto data2 = key_controller->get_bind_details() ;
				for( auto element = data2.begin() ; element != data2.end() ; element++ )
				{
					std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
				}
			}
			break ;

			//Quit the loop
		case 'Q':
		case 'q':

			std::cout << "Qutting UI\n" ;
			if( threadType != ( ( uint32_t )-1 ) )
			{
				SDL_Event threadInterrupt ;
				SDL_zero( threadInterrupt ) ;
				threadInterrupt.type = threadType ;
				threadInterrupt.user.data1 = nullptr ;
				threadInterrupt.user.data2 = nullptr ;
				SDL_PushEvent( &threadInterrupt ) ;
			}
			active = false ;
			break ;

			//Repeat
		default:
			break ;
		}
	}
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
	//Start testing
	if( initialize() )
		return 1 ;
	//SDL_SetHint( SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1" );

	//end testing
	std::cout << "Starting Program" << std::endl;
	KeyBindController key1("../../../../control_list.csv",
		"../../../../wt_bind_list.csv",
		"../../../../options.csv",
		"english");

	//TODO: Check proper file type
	key1.import( "../../../../controller_settings.blk" ) ;

	UserInterface* user_interface = new ptui();

	std::cout << "Starting loop\n" ;

	std::thread ui( ui_loop, &key1 ) ;
	//std::thread sdl( sdl_loop, &key1 ) ;
	sdl_loop( &key1 ) ;
	ui.join() ;
	//sdl.join() ;
	//SDL_Quit() ;
	delete user_interface ;
	return 0;
}
