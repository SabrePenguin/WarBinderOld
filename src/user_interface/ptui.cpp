#include "ptui.h"
#include <iostream>
#include <SDL.h>
#include <iomanip>
#include "KeyBindController.h"


ptui::ptui( std::shared_ptr<KeyBindController> _controller )
	: UserInterface(), controller( _controller )
{
}

void ptui::main_loop( std::shared_ptr<KeyBindController> key_controller )
{
	bool active = true ;
	char in ;
	char data_type ;
	uint32_t threadType = SDL_RegisterEvents( 1 ) ;
	while( active )
	{
		for( int i =0 ; i < 60 ; i++ )
			std::cout << "\n" ;
		std::cout << "Enter one of the following choices:" << line_one << std::endl ;
		std::cout << "D(isplay)" << line_two << std::endl;
		std::cout << "Q(uit)" << line_three << std::endl;
		std::cin >> in ;
		switch( in )
		{
			//Display information
		case 'D':
		case 'd':
			for( int i = 0 ; i < 60 ; i++ )
				std::cout << "\n" ;
			std::cout << "Enter one of the following choices:\nK(eys)\nB(inds)" << std::endl ;
			std::cin >> data_type ;
			//Key information
			if( data_type == 'k' || data_type == 'K' )
			{
				auto data = key_controller.get()->get_key_details() ;
				for( auto element = data.begin() ; element != data.end() ; element++ )
				{
					std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
				}
				break ;
			}
			//Bind information
			else if( data_type == 'b' || data_type == 'B' )
			{
				auto data2 = key_controller.get()->get_bind_details() ;
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

void ptui::controller_change_notify()
{

}