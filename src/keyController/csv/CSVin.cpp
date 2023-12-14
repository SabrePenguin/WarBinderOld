#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <regex>

#include "CSVin.h"

const int BUFFER_SIZE = 100;

std::vector<std::tuple<std::string, std::string, bool>> get_control(std::string _filename, std::string _language)
{
	std::vector<std::tuple<std::string, std::string, bool>> controls;
	{
		std::ifstream in_file(_filename);
		if( !in_file.is_open() )
			return controls;

		std::string in_string;
		std::string holder;
		std::string key_id;
		char c;
		std::regex language(_language) ;
		//Start base_index at -1 to allow for loop to work
		int base_index = -1 ;
		size_t local_index = 0 ;
		bool header = true ;
		bool correct_column = false ;

		while( in_file.good() )
		{
			in_file.get(c) ;
			switch( c )
			{
			case ',':
				//Runs once for the header to find the index
				if( header )
				{
					if( std::regex_match( in_string, language ) )
					{
						header = !header ;
					}
					base_index++ ;
				}
				if( local_index == 0 )
				{
					key_id = in_string ;
				}
				//Proper column, setup for next column being true or false modifier. Can be elseif because of how the file works
				else if( local_index == base_index ) 
				{
					holder = in_string ;
					correct_column = true ;
				}

				in_string = "" ;
				local_index++ ;
				break ;

			case '\n':
				in_string = "" ;
				local_index = 0 ;
				break ;

			default:
				//Runs if the ',' case determined the proper column
				if( correct_column ) 
				{
					correct_column = !correct_column ;
					bool modifier = ( c == 'f' ) ;
					controls.push_back( { key_id, holder, modifier } ) ;
					key_id = "";
					holder = "";
				}
				in_string += c ;
			}
		}
		in_file.close();
	}
	return controls;
}