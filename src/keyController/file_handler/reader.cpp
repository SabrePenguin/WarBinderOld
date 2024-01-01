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
	std::string key_id ;
	std::string data ;
	bool hotkeys = false ;
	int braceLevel = 0 ;

	while( in_file.good() ) {
		in_file.get( c ) ;

		switch( c )
		{
			case '\n':
				if( hotkeys )
				{
					data = in_string ;
				}
				in_string = "" ;
				break ;

			case '{':
				if( !hotkeys && in_string.find( "hotkeys" ) == 0 )
				{
					hotkeys = true ;
				}
				else if ( hotkeys )
				{
					key_id = in_string ;
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