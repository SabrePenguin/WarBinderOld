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

void initialize()
{

}

void sdl_loop(KeyBindController* key_controller)
{ 
	bool active = true ;

	SDL_Event cur_event ;
	while( active )
	{
		if( SDL_WaitEvent( &cur_event ) )
		{
			switch( cur_event.type )
			{
			case SDL_JOYDEVICEADDED:
			case SDL_CONTROLLERDEVICEADDED:
				key_controller->notify_device( &cur_event ) ;
				break ;
			case SDL_JOYDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMOVED:
				key_controller->notify_device( &cur_event ) ;
				break ;
			case SDL_USEREVENT:
				std::cout << "Evented" ;
				active = false ;
				break ;
			}
			
		}
		/*while( SDL_PollEvent(&cur_event) != 0 )
		{
			if( cur_event.type == SDL_JOYDEVICEADDED )
			{
				key_controller->notify_device( &cur_event ) ;
			}
			else if( cur_event.type == SDL_JOYDEVICEREMOVED )
			{
				key_controller->notify_device( &cur_event ) ;
			}
		}
		*/
	}
}

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

int main()
{
	
	std::cout << "Starting Program" << std::endl;
	KeyBindController key1("../../../../control_list.csv",
		"../../../../wt_bind_list.csv",
		"../../../../options.csv",
		"english");
	//TODO: Check proper file type
	key1.import( "../../../../controller_settings.blk" ) ;
	initialize() ;
	std::cout << "Starting loop\n" ;
	
	

	std::thread ui( ui_loop, &key1 ) ;
	std::thread sdl( sdl_loop, &key1 ) ;
	
	ui.join() ;
	sdl.join() ;

	return 0;
}
