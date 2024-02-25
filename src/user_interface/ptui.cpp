#include "ptui.h"
#include "ptui.h"
#include <iostream>
#include <SDL.h>
#include "KeyBindController.h"


ptui::ptui()
	: UserInterface()
{

}

void ptui::main_loop( KeyBindController* key_controller )
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

void ptui::controller_change_notify()
{

}