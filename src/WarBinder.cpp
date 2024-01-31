// WarBinder.cpp : The entry point of the program.
//

#include "WarBinder.h"
#include "KeyBindController.h"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main()
{
	cout << "Starting Program" << endl;
	KeyBindController key1("../../../../control_list.csv",
		"../../../../wt_bind_list.csv",
		"../../../../options.csv",
		"english");
	//TODO: Check proper file type
	key1.import( "../../../../controller_settings.blk" ) ;
	auto data = key1.get_key_details() ;
	for( auto element = data.begin() ; element != data.end() ; element++ )
	{
		std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
	}
	auto data2 = key1.get_bind_details() ;
	for( auto element = data2.begin() ; element != data2.end() ; element++ )
	{
		std::cout << "Local name: " << std::get<0>( *element ) << ", internal id: " << std::get<1>( *element ) << std::endl ;
	}
	return 0;
}
