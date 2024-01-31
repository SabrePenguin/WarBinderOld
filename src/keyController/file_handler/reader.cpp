#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include "reader.h"

//TODO: Limit maximum character size
/**
 * @brief A method to import a file given either by the user or on startup
 * @param _filename: The name of the file to import
 * @return A vector of tuples in the order of bind name (ie. fire_AAM) and the ids assigned (ie. 44)
*/
t_return import_controls( std::string _filename )
{
	std::ifstream in_file( _filename ) ;
	t_return return_values ;
	t_keys pairs;
	t_import_axis axis_details ;
	t_options params_list ;
	t_options settings_list;
	t_device device_list ;


	if( !in_file.is_open() )
		return return_values;

	//Import setup
	char c ;
	Key_Type key_type ;
	t_buttons key_holder ;
	std::string in_string ;
	std::string bind_id ;
	std::string control_id ;
	std::string opt_id ;
	bool hotkeys = false ;
	bool axes = false ;
	bool keys_added = false ;
	bool settings = false ;
	bool params = false ;
	bool device = false ;
	int braceLevel = 0 ;
	Imported_Axis empty = {
		Key_Type::CONTROLLER, "", "", false, false, false, 0,0,0,0,0
	};
	Imported_Axis t_axis = empty ;
	Device_Data empty_device = {
		false, "", "", "", 0, 0, 0, 0
	};
	Device_Data st_device = empty_device ;

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
						key_holder.push_back( { Key_Type::KEYBOARD, control_id } ) ;
						keys_added = true ;
					}
					else if( in_string.find( "mouseButton" ) == 0 )
					{
						key_holder.push_back( { Key_Type::MOUSE, control_id } ) ;
						keys_added = true ;
					}
					else if( in_string.find( "joyButton" ) == 0 )
					{
						key_holder.push_back( { Key_Type::CONTROLLER, control_id } ) ;
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
						t_axis.axis_type = Key_Type::CONTROLLER ;
						t_axis.axis = control_id ;
					}
					else if( in_string.find( "mouseAxisId" ) == 0 )
					{
						t_axis.axis_type = Key_Type::MOUSE ;
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
				else if( device && braceLevel == 3 )
				{
					size_t pos = in_string.find( "=" ) ;
					control_id = in_string.substr( pos + 1 ) ;
					//Variable amount of information. Yay.
					if( in_string.find( "connected" ) == 0 )
					{
						st_device.connected = control_id[ 0 ] == 'n' ;
					}
					else if( in_string.find( "devId" ) == 0 )
					{
						st_device.device_id = control_id.substr( 1, control_id.size() -2 ) ;
					}
					else if( in_string.find( "name" ) == 0 )
					{
						st_device.name = control_id.substr( 1, control_id.size() - 2 ) ;
					}
					else if( in_string.find( "axesOffset" ) == 0 )
					{
						st_device.axes_offset = std::stoi( control_id ) ;
					}
					else if( in_string.find( "buttonsOffset" ) == 0 )
					{
						st_device.button_offset = std::stoi( control_id ) ;
					}
					else if( in_string.find( "buttonsCount" ) == 0 )
					{
						st_device.button_offset = std::stoi( control_id ) ;
					}
					else if( in_string.find( "axesCount" ) == 0 )
					{
						st_device.axes_count = std::stoi( control_id ) ;
					}
					keys_added = true ;
				}
				else if( params && braceLevel == 2 && in_string.size() > 0 )
				{
					size_t pos = in_string.find( ":" ) ;
					control_id = in_string.substr( pos + 1 ) ;
					opt_id = in_string.substr( 0, pos ) ;
					params_list.push_back( {opt_id, control_id[0], control_id.substr( 2 )} ) ;
				}
				else if( settings && braceLevel == 1 && in_string.size() > 0 )
				{
					size_t pos = in_string.find( ":" ) ;
					control_id = in_string.substr( pos + 1 ) ;
					opt_id = in_string.substr( 0, pos ) ;
					params_list.push_back( { opt_id, control_id[ 0 ], control_id.substr( 2 ) } ) ;
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
				else if( !params && in_string.find( "params" ) == 0 )
				{
					params = true ;
				}
				else if( !settings && in_string.find( "settings" ) == 0 )
				{
					settings = true ;
				}
				else if( !device && in_string.find( "deviceMapping" ) == 0 )
				{
					device = true ;
				}
				else if( ( hotkeys || axes ) && braceLevel == 2 )
				{
					bind_id = in_string ;
					if( axes )
						t_axis.name = bind_id ;
				}
				else if( device && braceLevel == 3 )
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
				else if( axes && braceLevel == 2 )
				{
					axes = false ;
				}
				else if( params && braceLevel == 2 )
				{
					params = false ;
				}
				else if( settings && braceLevel == 1 )
				{
					settings = false ;
				}
				else if( device && braceLevel == 2 )
				{
					device = false ;
				}
				else if( axes && keys_added )
				{
					axis_details.push_back( t_axis ) ;
					t_axis = empty ;
					keys_added = false ;
				}
				else if( device && keys_added )
				{
					st_device.type = bind_id ;
					device_list.push_back( st_device ) ;
					st_device = empty_device ;
					keys_added = false ;
				}
				//Else if to prevent excssive calculations
				else if( keys_added )
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
				//Known bug source. Names of devices do not properly import due to space stripping
				break;
			
			default:
				in_string += c ;
				break;
		}
	}
	in_file.close() ;
	return_values = {pairs, axis_details, params_list, device_list, settings_list} ;
	return return_values ;
}