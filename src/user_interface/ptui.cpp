#include <iostream>
#include <SDL.h>
#include <iomanip>
#include "ptui.h"
#include "KeyBindController.h"
#include "../keyController/bind/Axis.h"


ptui::ptui( std::shared_ptr<KeyBindController> _controller )
	: UserInterface( _controller )
{
}

void ptui::main_loop(  )
{
	bool active = true ;
	char in ;
	char data_type ;
	uint32_t threadType = SDL_RegisterEvents( 1 ) ;
	while( active )
	{
		std::cout << "\nEnter one of the following choices:" << std::endl ;
		std::cout << "D(isplay)" << std::endl;
		std::cout << "A(ssign)" << std::endl ;
		std::cout << "Q(uit)" << std::endl;
		std::cin >> in ;
		switch( in )
		{
			//Display information

		case 'A':
		case 'a':
			
			this->assign_key_to_bind( ) ;
			break ;

		case 'D':
		case 'd':
			std::cout << "\nEnter one of the following choices:\nK(eys)\nB(inds)" << std::endl ;
			std::cin >> data_type ;
			//Key information
			if( data_type == 'k' || data_type == 'K' )
			{
				auto data = this->controller.get()->get_key_details() ;
				for( auto element = data.begin() ; element != data.end() ; element++ )
				{
					std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
				}
				break ;
			}
			//Bind information
			else if( data_type == 'b' || data_type == 'B' )
			{
				auto data2 = this->controller.get()->get_bind_details() ;
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

void ptui::assign_key_to_bind( )
{
	std::string input_key ;
	std::string input_bind ;
	std::vector<std::string> key_list ;
	while( true )
	{
		std::cout << "Enter the key name to assign or hit one of the following\n(E)nd\n(Q)uit" << std::endl ;
		std::cin >> input_key ;
		if( input_key[ 0 ] == 'e' || input_key[ 0 ] == 'E' )
		{
			break ;
		}
		else if( input_key [0] == 'q' || input_key[ 0 ] == 'Q' )
		{
			std::cout << "Quitting" << std::endl ;
			return ;
		}
		if( this->controller.get()->check_key_exists( input_key ) )
			key_list.push_back( input_key ) ;
		else
			std::cout << "Key does not exist" << std::endl ;
	}
	std::cout << "Enter the bind name to assign:" << std::endl ;
	std::cin >> input_bind ;
	if( key_list.size() > 0 && this->controller.get()->check_bind_exists(input_bind) )
	{
		if( !this->controller.get()->check_bind_is_axis( input_bind ) )
		{
			//The controller is not axis, no further details required
			this->controller.get()->assign_key_to_bind( key_list, input_bind ) ;
		}
		else
		{
			char c ;
			enum controller direction ;
			std::cout << "This control is an axis. Please enter one of the following:" << std::endl ;
			std::cout << "I(ncrease)" << std::endl ;
			std::cout << "D(ecrease)" << std::endl ;
			std::cout << "R(eset)" << std::endl ;
			std::cin >> c ;
			switch( c )
			{
			case 'i':
			case 'I':
				direction = controller::INCREASE ;
				break ;
			case 'd':
			case 'D':
				direction = controller::DECREASE ;
				break ;
			case 'r':
			case 'R':
			default:
				direction = controller::RESET ;
				break ;
			}
			this->controller.get()->assign_key_to_axis( key_list, input_bind, direction ) ;
		}
	}
}