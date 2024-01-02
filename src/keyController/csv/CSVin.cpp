#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <regex>

#include "CSVin.h"

/**
 * @brief Reads in the control_list.csv and selects the language, then returns a vector of keys
 * @param _filename: The name of the file to import
 * @param _language: The language to import
 * @return A vector of tuples in the <id, local_name, modifier> format
*/
std::vector<std::tuple<std::string, char, std::string, bool>> get_control( std::string _filename, std::string _language ) 
{
	std::vector<std::tuple<std::string, char, std::string, bool>> controls;
	{
		std::ifstream in_file(_filename);
		if( !in_file.is_open() )
			return controls;

		std::string in_string;
		std::string holder;
		std::string key_id;
		char c;
		char mode ;
		//Start base_index at -1 to allow for loop to work
		int base_index = -1 ;
		int local_index = 0 ;
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
					if( in_string.compare( _language ) == 0 )
					{
						header = !header ;
					}
					base_index++ ;
				}
				else if( local_index == 0 )
				{
					key_id = in_string ;
				}
				else if( local_index == 1 )
				{
					mode = in_string[0] ;
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
				local_index = 0 ;
				in_string = "" ;
				break ;

			default:
				//Runs if the ',' case determined the proper column
				if( correct_column ) 
				{
					correct_column = !correct_column ;
					bool modifier = ( c == 't' ) ;
					controls.push_back( { key_id, mode, holder, modifier } ) ;
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

/**
 * @brief A version of a csv parser that takes out only 2 pieces of information per row
 * @param _filename: The name of the file
 * @param _language: The language to use 
 * @return A vector of tuples with 5 parameters
*/
std::vector<std::tuple<std::string, char, std::string, bool, bool>> get_binds( std::string _filename, std::string _language )
{
	std::vector<std::tuple<std::string, char, std::string, bool, bool>> binds;
	{
		std::ifstream in_file( _filename );
		if( !in_file.is_open() )
			return binds;

		std::string in_string;
		std::string bind_id;
		char c;
		//Start base_index at -1 to allow for loop to work
		int base_index = -1 ;
		int local_index = 0 ;
		bool offset = false ;
		bool header = true ;
		bool axis = true ;
		char mode ;
		bool required ;

		while( in_file.good() )
		{
			in_file.get( c ) ;
			switch( c )
			{
			case '\n':
				offset = true ;
			case ',':
				if( header ) 
				{
					if( in_string.compare( _language ) == 0 )
						header = !header ;
					base_index++;
				}
				else if( local_index == 0 )
				{
					if( in_string.find("ID") == 0 )
						axis = false ;
					bind_id = in_string ;
				}
				else if( local_index == 1 )
				{
					mode = in_string[0] ;
				}
				else if( local_index == 2 )
				{
					required = 't' ==  in_string[0] ;
				}
				else if( local_index == base_index )
				{
					binds.push_back( { bind_id, mode, in_string, axis, required } ) ;
					bind_id = "" ;
					axis = true ; 
				}
				if( offset )
				{
					local_index = 0 ;
					offset = false ; 
				}
				else
				{
					local_index++ ;
				}
				in_string = "" ;
				break ;
			default:
				in_string += c ;
			}
		}
		in_file.close();
	}
	return binds ;
}