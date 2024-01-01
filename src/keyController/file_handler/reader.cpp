#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include "reader.h"

/**
 * @brief A method to import a file given either by the user or on startup
 * @param _filename: The name of the file to import
 * @return A vector of tuples in the order of bind name (ie. fire_AAM) and the ids assigned (ie. 44)
*/
std::vector<std::tuple<std::string, std::vector<std::string>>> import_controls( std::string _filename )
{
	std::ifstream in_file( _filename ) ;
	std::vector<std::tuple<std::string, std::vector<std::string>>> pairs;

	if( !in_file.is_open() )
		return pairs;

	//Import setup
	char c ;
	std::vector<std::string> key_holder ;
	std::string in_string ;
	std::string bind_id ;
	std::string control_id ;
	bool hotkeys = false ;
	bool keys_added = false ;
	int braceLevel = 0 ;

	while( in_file.good() ) {
		in_file.get( c ) ;

		switch( c )
		{
			case '\n':
				if( hotkeys && braceLevel == 3 )
				{
					//The controls are guaranteed to only use this as the separator
					size_t pos = in_string.find( "=" ) ;
					//Search for the different types
					if( in_string.find( "keyboardKey" ) == 0 )
					{
						control_id = in_string.substr( pos + 1 ) ;
						key_holder.push_back( control_id ) ;
						keys_added = true ;
					}
					else if( in_string.find( "mouseButton" ) == 0 )
					{
						//TODO
						keys_added = true ;
					}
					else if( in_string.find( "joyButton" ) == 0 )
					{
						//TODO
						keys_added = true ;
					}
						
				}
				in_string = "" ;
				break ;

			case '{':
				if( !hotkeys && in_string.find( "hotkeys" ) == 0 )
				{
					hotkeys = true ;
				}
				else if ( hotkeys && braceLevel == 2 )
				{
					bind_id = in_string ;
				}
				in_string = "" ;
				braceLevel++ ;
				break ;
				
			case '}':
				if( hotkeys && braceLevel == 2 ) {
					hotkeys = false ;
				}
				//Else if to prevent excssive calculations
				else if( keys_added == true )
				{
					pairs.push_back( {bind_id, key_holder} ) ;
					key_holder.clear() ;
					keys_added = false ;
				}
				braceLevel-- ;
				break ;

			//Clear whitespace
			case '\t':
			case ' ':
				break;
			
			default:
				in_string += c ;
				break;
		}
	}
	in_file.close() ;
	return pairs ;
}