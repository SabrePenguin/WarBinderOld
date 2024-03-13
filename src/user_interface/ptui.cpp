#include <iostream>
#include <SDL.h>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <string>
#include "Control.h"
#include "KeyBind.h"
#include "ptui.h"
#include "KeyBindController.h"


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
		std::cout << "R(emove)" << std::endl ;
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
				this->display_binds_from_key() ;
				break ;
			}
			//Bind information
			else if( data_type == 'b' || data_type == 'B' )
			{
				this->display_keys_from_bind() ;
			}
			break ;

		case 'r':
		case 'R':
			tester() ;
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
		this->controller.get()->assign_key_to_bind( key_list, input_bind ) ;
	}
}

void ptui::display_binds_from_key()
{
	const auto keys = this->controller.get()->get_controls_map() ;
	std::cout << "Total key count: " << keys->size() << std::endl ;
	for( auto iter = keys->begin() ; iter != keys->end() ; ++iter )
	{
		std::cout << "----------------------------------------" << std::endl ;
		const auto binds = iter->second->get_binds() ;
		for( auto sub_iter = binds->begin() ; sub_iter != binds->end() ; ++sub_iter )
		{
			std::cout << "\n" << ( *sub_iter )->get_local_name() << " - ";
		}
		std::cout << iter->second->get_local_name() << std::endl ;
	}
}

void ptui::display_keys_from_bind()
{
	const auto binds = this->controller.get()->get_binds_map() ;
	std::cout << "Total bind count: " << binds->size() << std::endl ;
	for( auto iter = binds->begin() ; iter != binds->end() ; ++iter )
	{
		std::cout << "----------------------------------------" << std::endl ;

		const auto keys = iter->second->get_control() ;
		for( auto sub_iter = keys->begin() ; sub_iter != keys->end() ; ++sub_iter )
		{
			for( auto sub2_iter = sub_iter->begin() ; sub2_iter != sub_iter->end() ; ++sub2_iter )
			{
				std::cout << ( *sub2_iter )->get_local_name() << ", " ;
			}
			std::cout << "\n------" << std::endl ;
			
		}
		std::cout << iter->second->get_local_name() << std::endl;
	}
}

void ptui::tester()
{
	const auto controls = this->controller.get()->get_controls_map() ;
	const auto binds = this->controller.get()->get_binds_map() ;
	auto temp = controls->find("key1") ;
	auto bind_temp = binds->find( "throttle_rangeMin" ) ;
	//if( temp != controls->end() )
	if( bind_temp != binds->end() )
	{
		auto key_list = bind_temp->second->get_control() ;
		for( auto iter = key_list->begin() ; iter != key_list->end() ; ++iter )
		{
			bind_temp->second->remove_key_combo( &*iter ) ;
			break ;
		}
	//	temp->second->remove_bind( bind_temp ) ;
	//	temp->second->remove_all_binds() ;
	}
}