#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <memory>
#include <SDL.h>
#include "KeyBindController.h"
#include "Control.h"
#include "Key.h"
#include "Joystick.h"
#include "Bind.h"
#include "Axis.h"
#include "CSVin.h"
#include "reader.h"
#include "KeyBind.h"
#include "Device.h"
#include "DeviceHandler.h"


// The purpose of this file is to be the surface level file that users
//

/**
 * @brief Imports the files and converts them to objects
 * @param _controlfile: The file of the controls and their local names
 * @param _bindfile: The file of all the binds and their names
 * @param _language: The language in the file. Used to find local ids.
*/
KeyBindController::KeyBindController(std::string _controlfile, std::string _bindfile, std::string _optfile, std::string _language) : 
	language(_language) 
{
	// SDL2 initialization. Run first to check for errors.
	device_handler = std::make_unique<DeviceHandler>() ;

	// Import all the files
	file_handler = std::make_unique<Reader>() ;
	std::vector<std::tuple<std::string, char, std::string, bool>> controls = get_control( _controlfile, _language ) ;
	std::vector<std::tuple<std::string, char, std::string, bool, bool>> binds = get_binds( _bindfile, _language ) ;
	auto options = get_options( _optfile, _language ) ;

	// Add data to internal structures
	for( auto iterator = controls.begin() ; iterator != controls.end() ; ++iterator )
	{
		//Position zero has the internal name
		//Position two has the local name
		//Position three determines if it's a modifier
		//Position one is the type control
		this->add_key( 
			std::get<0>( *iterator ), 
			std::get<2>( *iterator ), 
			std::get<3>( *iterator ), 
			std::get<1>( *iterator )
		) ;
	}

	for( auto iterator = binds.begin() ; iterator != binds.end() ; ++iterator )
	{
		//Position zero has the internal name
		//Position two has the local name
		//Position three controls if it's an axis
		//Position one controls its mode
		//Position four is whether the bind is required to play
		this->add_new_bind(
			std::get<0>( *iterator ),
			std::get<2>( *iterator ),
			std::get<1>( *iterator ),
			std::get<3>( *iterator ),
			std::get<4>( *iterator )
		) ;
	}
	// Run a scan for any controllers
	device_handler->find_devices() ;
}


/**
 * @brief Destroys the pointers by hand due to being unable to use smart pointers effectively.
*/
KeyBindController::~KeyBindController() 
{
	for (auto iterator = this->system_keys.begin(); iterator!= this->system_keys.end(); ++iterator) 
	{
		delete(iterator->second);
	}
	this->system_keys.clear();
	for (auto iterator = this->p_binds.begin(); iterator != this->p_binds.end(); ++iterator)
	{
		delete(iterator->second);
	}
	this->p_binds.clear();
	device_handler->shutdown() ;
}

/**
 * @brief Adds a key pointer to the KeyBindController vector
 * @param _key_id: The internal id. Can be anything, so long as it matches Gaijin's internal id. (ie: 1, button_1)
 * @param _local_key: The local name. Can be anything
 * @param _modifier: Whether the key is a modifier such as "ctrl" or "alt"
 * @param _type: The type of control (key, mouse, controller) 
*/
void KeyBindController::add_key(std::string _key_id, std::string _local_key, bool _modifier, char _type)
{
	//Technically can be put in one line, but reduces readability
	Control* new_key = new Key(_key_id, _local_key, _modifier);
	this->system_keys.insert({ "key"+_key_id, new_key});
}

/**
 * @brief Adds a controller button
 * @param _key_id: The internal id. Can be anything as long as it matches Gaijin's internal id.
 * @param _local_key 
*/
void KeyBindController::add_new_joystick(std::string _key_id, std::string _local_key)
{
	Control* new_joystick = new Joystick( _key_id, _local_key, false ) ;
	this->system_keys.insert( { "controller" + _key_id, new_joystick } ) ;
}

void KeyBindController::add_new_controller_axis( std::string _key_id, std::string _local_key )
{
	Control* new_con_axis = new Joystick( _key_id, _local_key, true ) ;
	this->system_keys.insert( { "controller_axis" + _key_id, new_con_axis } ) ;
}

/**
 * @brief Adds a Bind pointer.
 * @param _internal_id: The internal id of the bind name.
 * @param _local_id: The local name of the bind. (ie. "Throttle Up")
 * @param _axis: Determines if the given bind needs to be an axis or regular button
*/
void KeyBindController::add_new_bind(std::string _internal_id, std::string _local_id, char _mode, bool _is_axis, bool _required)
{
	KeyBind* new_bind ;
	if( !_is_axis )
	{
		new_bind = new Bind( _internal_id, _local_id, _mode, _required ) ;
		this->p_binds.insert( { _internal_id, new_bind } ) ;
	}
	else
	{
		controller up = this->check_string( _internal_id ) ;

		size_t cutoff = _internal_id.find_last_of( "_" ) ;
		//HERE
		if( cutoff != std::string::npos )
			_internal_id.erase( cutoff ) ;
		new_bind = new Axis( _internal_id, _local_id, _mode, up, _required ) ;
		if( this->p_binds.find( _internal_id ) == this->p_binds.end())
			this->p_binds.insert( { _internal_id, new_bind } ) ;
		else
		{
			KeyBind* existing_bind = this->p_binds.find( _internal_id )->second ;
			existing_bind->add_second_bind( _local_id, up ) ;
		}
	}
}

/**
 * @brief Sets the language of the keybind controller.
 * @param _language: The language to be used. Must match a language in the csv files.
*/
void KeyBindController::set_language(std::string _language)
{
	this->language = _language;
}

/**
 * @brief A method to check whether the given axis control is an increase, decrease, or reset
 * @param _name: The string to check
 * @return A controller enum value
*/
controller KeyBindController::check_string( std::string _name )
{
	if( _name.find( "_rangeMax" ) != std::string::npos )
		return controller::INCREASE ;
	else if( _name.find( "_rangeMin" ) != std::string::npos )
		return controller::DECREASE ;
	return controller::RESET ;
}

/**
 * @brief A method to check whether the given button is on the keyboard, mouse, or a controller
 * @param t_key: The enum to check
 * @return A string
*/
std::string KeyBindController::check_type( Key_Type t_key )
{
	if( t_key == Key_Type::KEYBOARD )
		return "key" ;
	else if( t_key == Key_Type::MOUSE )
		return "mouse" ;
	return "controller" ;
}

/**
 * @brief Imports the control file. Must be a .blk file and must follow Gaijin's format
 * @param _filename 
*/
void KeyBindController::import( std::string _filename )
{
	t_return data = file_handler->import_controls( _filename ) ;
	t_keys keys = std::get<0>( data ) ;
	int i = 0 ;
	for( t_keys::iterator iter = keys.begin() ; iter != keys.end() ; ++iter )
	{
		std::string name = std::get<0>( *iter ) ;
		controller up = this->check_string( name ) ;
		name.erase( name.find_last_of( "_" ) ) ;
		auto check = this->p_binds.find( name ) ;
		//This if statement is very annoying, but I need it for update protection (no nulls)
		if( check != this->p_binds.end() )
		{
			KeyBind* existing_bind = check->second;
			t_buttons bound_keys = std::get<1>( *iter ) ;
			std::vector<Control*> key_list ;
			std::string control_type ;
			Key_Type key_type ;
			//Import, then run a check. That way avoid unneeded calls
			for( t_buttons::iterator single = bound_keys.begin() ; single != bound_keys.end() ; ++single )
			{
				key_type = std::get<0>( *single ) ;
				control_type = check_type( std::get<0>( *single ) ) ;
				auto find_key = this->system_keys.find( control_type + std::get<1>( *single ) ) ;
				if( find_key != this->system_keys.end() )
				{
					find_key->second->add_bind( existing_bind ) ;
					key_list.push_back( find_key->second ) ;
				}
			}
			if( key_list.size() )
			{
				existing_bind->add_control( key_list, up ) ;
			}
		}
	}
	//Import the controllers before the axes
	t_device devices = std::get<3>( data ) ;
	int total_buttons = 1 ;
	int total_axes = 1 ;
	for( t_device::iterator iter = devices.begin() ; iter != devices.end() ; ++iter )
	{
		auto check = this->device_list.find( (*iter).name ) ;
		bool enabled = iter->connected ;
		//If it exists, remove everything of the device and replace so that it's easier
		if( check != this->device_list.end() )
		{
			enabled = check->second->get_connected() ;
			this->device_list.erase( check ) ;
		}
		this->device_list.insert( { iter->name, std::make_shared<Device>(
			enabled,
			iter->name,
			iter->device_id,
			iter->axes_offset,
			iter->button_offset,
			iter->button_count,
			iter->axes_count,
			iter->type
		) } );
		total_buttons += iter->button_count ;
		total_axes += iter->axes_count ;
		
	}
	std::string front = "controller" ;
	//Add missing buttons.
	for( int button_number = 1 ; button_number <= total_buttons ; button_number++ )
	{
		auto find_button = this->system_keys.find( front + std::to_string( button_number ) ) ;
		if( find_button == this->system_keys.end() )
		{
			add_new_joystick( std::to_string( button_number ), front + std::to_string( button_number ) ) ;
		}
	}
	//Erase the extra stuff
	auto find_button = this->system_keys.find( front + std::to_string( ++total_buttons ) ) ;
	while( find_button != this->system_keys.end() )
	{
		this->system_keys.erase( find_button ) ;
		find_button = this->system_keys.find( front + std::to_string( ++total_buttons ) ) ;
	}
	front = "controller_axis" ;
	//Now time to add the missing axes
	for( int axes_number = 1 ; axes_number <= total_axes ; axes_number++ )
	{
		auto find_axes = this->system_keys.find( front + std::to_string( axes_number ) ) ;
		if( find_axes == this->system_keys.end() )
		{
			add_new_controller_axis( std::to_string( axes_number ), front + std::to_string( axes_number ) ) ;
		}
	}
	//Erase the extra axes
	auto find_axes = this->system_keys.find( front + std::to_string( ++total_axes ) ) ;
	while( find_axes != this->system_keys.end() )
	{
		this->system_keys.erase( find_axes ) ;
		find_axes = this->system_keys.find( front + std::to_string( ++total_axes ) ) ;
	}

	//Now run to get the axes
	t_import_axis axes = std::get<1>( data ) ;
	for( t_import_axis::iterator iter = axes.begin() ; iter != axes.end() ; ++iter )
	{
		auto check = this->p_binds.find( iter->name ) ;
		if( check != this->p_binds.end() )
		{
			//Insert a pointer to the data by dereferencing the iterator and then getting the address of the struct
			check->second->add_data( &*iter ) ;
			std::string control_type = check_type( iter->axis_type ) ;
			if( iter->axis.length() > 0 )
			{
				control_type = control_type + "_axis" ;
			}
			auto existing_control = this->system_keys.find( control_type + iter->axis ) ;
			if( existing_control != this->system_keys.end() )
			{
				existing_control->second->add_bind( check->second ) ;
				check->second->add_axis( existing_control->second ) ;
			}
			i++ ;
		}
	}
	return ;
}

std::vector<std::tuple<std::string, std::string>> KeyBindController::get_key_details()
{
	std::vector<std::tuple<std::string, std::string>> key_strings ;
	for( auto iter = this->system_keys.begin() ; iter != this->system_keys.end() ; iter++ )
	{
		key_strings.push_back( { iter->first, iter->second->get_local_name() } ) ;
	}
	return key_strings ;
}


/**
 * @brief Temp string output
 * @return String vector data
*/
std::vector<std::tuple<std::string, std::string>> KeyBindController::get_bind_details()
{
	std::vector<std::tuple<std::string, std::string>> bind_strings ;
	for( auto iter = this->p_binds.begin() ; iter != this->p_binds.end() ; iter++ )
	{
		if( iter->second->is_axis() )
		{
			std::vector<std::string> axis_names = iter->second->get_axis_names() ;
			for( auto axis_iter = axis_names.begin() ; axis_iter != axis_names.end() ; axis_iter++ )
			{
				bind_strings.push_back( { iter->first, ( *axis_iter ) } ) ;
			}
		}
		else
		{
			bind_strings.push_back( { iter->first, iter->second->get_local_name() } ) ;
		}
	}
	return bind_strings ;
}

void KeyBindController::notify_device( SDL_Event* cur_event )
{
	device_handler.get()->device_change( cur_event ) ;
}