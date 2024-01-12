#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include "reader.h"

typedef std::vector<std::tuple<std::string, std::vector<std::string>>> t_keys ;
typedef std::tuple<t_keys, std::vector<Imported_Axis>> t_return ;
/**
 * @brief A method to import a file given either by the user or on startup
 * @param _filename: The name of the file to import
 * @return A vector of tuples in the order of bind name (ie. fire_AAM) and the ids assigned (ie. 44)
*/
t_keys import_controls( std::string _filename )
{
	std::ifstream in_file( _filename ) ;
	t_keys pairs;
	std::vector<Imported_Axis> axis_details ;

	if( !in_file.is_open() )
		return pairs;

	//Import setup
	char c ;
	std::vector<std::string> key_holder ;
	std::string in_string ;
	std::string bind_id ;
	std::string control_id ;
	bool hotkeys = false ;
	bool axes = false ;
	bool keys_added = false ;
	int braceLevel = 0 ;
	Imported_Axis empty = {
		"", "", false, false, false, 0,0,0,0,0
	};
	Imported_Axis t_axis = empty ;

	while( in_file.good() ) {
		in_file.get( c ) ;

		switch( c )
		{
			case '\n':
				if( hotkeys && braceLevel == 3 )
				{
					//The controls are guaranteed to only use this as the separator
					size_t pos = in_string.find( "=" ) ;
					control_id = in_string.substr( pos + 1 ) ;
					//Search for the different types
					if( in_string.find( "keyboardKey" ) == 0 )
					{
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
				else if( axes && braceLevel == 3 )
				{
					size_t pos = in_string.find( "=" ) ;
					control_id = in_string.substr( pos + 1 ) ;
					//Variable amount of information. Yay.
					if( in_string.find( "axisId" ) == 0 )
					{
						t_axis.axis = control_id ;
					}
					else if( in_string.find( "mouseAxisId" ) == 0 )
					{
						t_axis.axis = control_id ;
					}
					else if( in_string.find( "innerDeadzone" ) == 0 )
					{
						t_axis.dead_zone = std::stof( control_id ) ;
					}
					else if( in_string.find( "kMul" ) == 0 )
					{
						t_axis.multiplier = std::stof( control_id ) ;
					}
					else if( in_string.find( "relSens" ) == 0 )
					{
						t_axis.relSens = std::stof( control_id ) ;
					}
					else if( in_string.find( "relStep" ) == 0 )
					{
						t_axis.relStep = std::stof( control_id ) ;
					}
					else if( in_string.find( "relative" ) == 0 )
					{
						t_axis.relative = control_id[ 0 ] == 'y' ;
					}
					keys_added = true ;
				}
				in_string = "" ;
				break ;

			case '{':
				if( !hotkeys && in_string.find( "hotkeys" ) == 0 )
				{
					hotkeys = true ;
				}
				else if( !axes && in_string.find( "axes" ) == 0 )
				{
					axes = true ;
				}
				else if( ( hotkeys || axes ) && braceLevel == 2 )
				{
					bind_id = in_string ;
					if( axes )
						t_axis.name = bind_id ;
				}
				in_string = "" ;
				braceLevel++ ;
				break ;
				
			case '}':
				if( hotkeys && braceLevel == 2 ) {
					hotkeys = false ;
				}
				else if( axes && keys_added )
				{
					axis_details.push_back( t_axis ) ;
					t_axis = empty ;
					keys_added = false ;
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