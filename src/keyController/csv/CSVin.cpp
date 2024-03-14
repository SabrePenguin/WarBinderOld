#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <regex>

#include "CSVin.h"


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
					++base_index ;
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
				++local_index ;
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
					++base_index ;
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
					++local_index ;
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


std::vector<std::tuple<std::string, char, std::string, float, float, bool, std::list<std::string>>> 
	get_options( std::string _filename, std::string _language )
{
	std::vector<std::tuple<std::string, char, std::string, float, float, bool, std::list<std::string>>> t_options ;
	{
		std::ifstream in_file( _filename ) ;
		if( !in_file.is_open() )
			return t_options ;
		//Control variables
		char c ;
		bool header = true ;
		std::string in_string ;
		//Options information
		std::string internal_name ;
		char o_type ;
		std::string local_name ;
		float base_value ;
		float max_value ;
		bool parameter = false ;
		std::list<std::string> options ;
		//Location variables
		int column = 0 ;
		int option_col = 0 ;
		int lang_col = 0 ;

		while( in_file.good() )
		{
			c = in_file.get() ;
			switch( c )
			{
			case '\n':
				if( header )
					header = false ;
				else
				{
					parameter = in_string[ 0 ] == 't' ;
					t_options.push_back( {internal_name, o_type, local_name, base_value, max_value, parameter, options} ) ;
				}
				column = 0 ;
				option_col = 0 ;
				in_string = "" ;
				break ;
			case ',':
				if( header )
				{
					if( in_string.compare( _language ) == 0 )
					{
						lang_col = column ;
					}
				}
				else if( column == 0 )
				{
					internal_name = in_string ;
				}
				else if( column == 1 )
				{
					o_type = in_string[ 0 ] ;
				}
				else if( column == 2 )
				{
					base_value = std::stof( in_string ) ;
				}
				else if( column == 3 )
				{
					max_value = std::stof( in_string ) ;
				}
				++column ;
				in_string = "";
				break ;
			case '/':
				if( column == lang_col )
				{
					//Default language option (ie. "invert y axis" or "Mouse control mode")
					if( option_col == 0 )
					{
						local_name = in_string ;
					}
					//Adds extra options to list
					else
					{
						options.push_back( in_string ) ;
					}
					in_string = "" ;
					++option_col ;
				}
				break ;
			default:
				in_string += c ;
			}
		}
	}
	return t_options ;
}