#include <string>
#include <fstream>
#include "reader.h"


void import_controls( std::string _filename )
{
	std::ifstream in_file( _filename ) ;

	if( !in_file.is_open() )
		return ;

	char c ;
	std::string in_string ;
	std::string bind_id ;
	std::string control_id ;
	std::string data ;
	bool hotkeys = false ;
	int braceLevel = 0 ;

	while( in_file.good() ) {
		in_file.get( c ) ;

		switch( c )
		{
			case '\n':
				if( hotkeys && braceLevel == 3 )
				{
					//The controls are guaranteed to only use this as the separator
					int pos = in_string.find( "=" ) ;
					//Search for the different types
					if( in_string.find( "keyboardKey" ) == 0 )
					{
						control_id = in_string.substr( pos + 1 ) ;
					}
					else if( in_string.find( "mouseButton" ) == 0 )
					{
						//TODO
					}
					else if( in_string.find( "joyButton" ) == 0 )
					{
						//TODO
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
}