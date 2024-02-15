// WarBinder.cpp : The entry point of the program.
//

#include "WarBinder.h"
#include "KeyBindController.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

void initialize()
{

}

void program_loop(KeyBindController* key_controller)
{
	bool active = true ;
	char in ;
	char data_type ;
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
	program_loop( &key1 ) ;
	
	return 0;
}
