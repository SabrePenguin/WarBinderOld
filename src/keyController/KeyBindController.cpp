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
#include "Axis.h"
#include "CSVin.h"
#include "reader.h"
#include "KeyBind.h"
#include "Device.h"
#include "DeviceHandler.h"



#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

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
	for (auto iterator = this->system_keys.begin(); iterator != this->system_keys.end(); ++iterator) 
	{
		//std::cout << "Deleting " << iterator->first << std::endl ;
		delete iterator->second ;
	}
	this->system_keys.clear();
	for (auto iterator = this->system_binds.begin(); iterator != this->system_binds.end(); ++iterator)
	{
		//std::cout << "Deleting " << iterator->first << std::endl ;
		delete iterator->second ;
	}
	this->system_binds.clear();
	//Pointers automatically clear, unlike above's circular relationship
	device_list.clear() ;
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
	// Prevent memory leak from overwriting the previous value with this key
	std::string key_id = "key" ;
	if( this->system_keys.find( key_id+_key_id ) != this->system_keys.end() )
	{
		return ;
	}
	Control* new_key = new Key(_key_id, _local_key, _modifier);
	//delete new_key ;
	this->system_keys.insert({ key_id+_key_id , new_key});
}

/**
 * @brief Adds a controller button
 * @param _key_id: The internal id. Can be anything as long as it matches Gaijin's internal id.
 * @param _local_key 
*/
void KeyBindController::add_new_joystick(std::string _key_id, std::string _local_key)
{
	std::string key_id = "controller" ;
	if( this->system_keys.find( key_id + _key_id ) != this->system_keys.end() )
	{
		return ;
	}
	Control* new_joystick = new Joystick( _key_id, _local_key, false ) ;
	//delete new_joystick ;
	this->system_keys.insert( { key_id + _key_id, new_joystick } ) ;
}

void KeyBindController::add_new_controller_axis( std::string _key_id, std::string _local_key )
{
	std::string key_id = "controller_axis" ;
	if( this->system_keys.find( key_id + _key_id ) != this->system_keys.end() )
	{
		return ;
	}
	Control* new_con_axis = new Joystick( _key_id, _local_key, true ) ;
	//delete new_con_axis ;
	this->system_keys.insert( { key_id + _key_id, new_con_axis } ) ;
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
		//Memory leak protection
		if( this->system_binds.find( _internal_id ) != this->system_binds.end() )
		{
			return ;
		}
		new_bind = new KeyBind( _mode, _is_axis, _required, _local_id, _internal_id ) ;
		//delete new_bind ;
		this->system_binds.insert( { _internal_id, new_bind } ) ;
	}
	else
	{

		// If it doesn't exist, it's fine
		// This has the side effect of protecting the memory
		auto temp = this->system_binds.find( _internal_id ) ;
		if( temp == this->system_binds.end() )
		{
			KeyBind* bind_one ;
			KeyBind* bind_two ;
			//This ugly section is for the new Axis type of three objects
			if( _internal_id.find( "_rangeSet" ) != std::string::npos )
			{
				new_bind = new AxisReset( _internal_id, _local_id, _mode, _required ) ;
				size_t cutoff = _internal_id.find_last_of( "_" ) ;
				if( cutoff != std::string::npos )
					_internal_id.erase( cutoff ) ;
				bind_one = new AxisChange( _internal_id + "_rangeMin", _local_id, _mode, _required) ;
				bind_two = new AxisChange( _internal_id + "_rangeMax", _local_id, _mode, _required) ;
			}
			else if( _internal_id.find( "_rangeMin" ) != std::string::npos )
			{
				bind_one = new AxisChange( _internal_id, _local_id, _mode, _required ) ;
				size_t cutoff = _internal_id.find_last_of( "_" ) ;
				if( cutoff != std::string::npos )
					_internal_id.erase( cutoff ) ;
				new_bind = new AxisReset( _internal_id + "_rangeSet", _local_id, _mode, _required ) ;
				bind_two = new AxisChange( _internal_id + "_rangeMax", _local_id, _mode, _required ) ;
			}
			else
			{
				bind_two = new AxisChange( _internal_id, _local_id, _mode, _required ) ;
				size_t cutoff = _internal_id.find_last_of( "_" ) ;
				if( cutoff != std::string::npos )
					_internal_id.erase( cutoff ) ;
				new_bind = new AxisReset( _internal_id + "_rangeSet", _local_id, _mode, _required ) ;
				bind_one = new AxisChange( _internal_id + "_rangeMin", _local_id, _mode, _required ) ;
			}
			//Circular reference to allow for easy comm
			bind_one->add_other_controls( new_bind, bind_two ) ;
			bind_two->add_other_controls( new_bind, bind_one ) ;
			new_bind->add_other_controls( bind_one, bind_two ) ;
			//insert them all
			this->system_binds.insert( { _internal_id + "_rangeSet", new_bind } ) ;
			this->system_binds.insert( { _internal_id + "_rangeMin", bind_one } ) ;
			this->system_binds.insert( { _internal_id + "_rangeMax", bind_two } ) ;
		}
		else
		{
			//This will only sometimes set the local right. If the local name is missing from the .csv,
			//this will fail to set the local name
			temp->second->set_local_name( _local_id ) ;
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
		auto check = this->system_binds.find( name ) ;
		//This if statement is very annoying, but I need it for update protection (no nulls)
		if( check != this->system_binds.end() )
		{
			KeyBind* existing_bind = check->second;
			t_buttons bound_keys = std::get<1>( *iter ) ;
			std::vector<Control*> key_list ;
			std::string control_type ;
			Key_Type key_type ;
			for( t_buttons::iterator single = bound_keys.begin() ; single != bound_keys.end() ; ++single )
			{
				key_type = std::get<0>( *single ) ;
				control_type = check_type( key_type ) ;
				auto find_key = this->system_keys.find( control_type + std::get<1>( *single ) ) ;
				if( find_key != this->system_keys.end() )
				{
					find_key->second->add_bind( existing_bind ) ;
					key_list.push_back( find_key->second ) ;
				}
			}
			if( key_list.size() )
			{
				existing_bind->add_control( key_list ) ;
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
		this->device_list.insert({iter->name, std::make_shared<Device>(
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
		auto check = this->system_binds.find( iter->name ) ;
		if( check != this->system_binds.end() )
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

/**
 * @brief Gets the internal map with all the binds
 * @return A pointer to the map. Returns reference due to size.
 */
std::unordered_map<std::string, KeyBind*>* KeyBindController::get_binds_map()
{
	return &( this->system_binds ) ;
}

/**
 * @brief Gets the internal map with all the controls
 * @return A pointer to the map. Returns reference due to size.
 */
std::unordered_map<std::string, Control*>* KeyBindController::get_controls_map()
{
	return &( this->system_keys ) ;
}

int KeyBindController::find_pos( std::string name, char ch )
{
	int pos = name.find_first_of( ch ) ;
	return pos ;
}

void KeyBindController::notify_device( SDL_Event* cur_event )
{
	std::string result = device_handler.get()->device_change( cur_event ) ;
	int pos = 0 ;
	std::string name ;
	if( result.length() > 0 )
	{
		//Remove guid
		pos = find_pos( result, ',' ) ;
		result = result.substr(pos) ;
		//Remove name
		pos = find_pos( result, ',' ) ;
		name = result.substr( 0, pos ) ;
		result = result.substr( pos ) ;
		std::string a ;
		std::string b ;
		//while( result.length() > 0 )
		{
			pos = find_pos( result, ',' ) ;

			pos = find_pos( result, ',' ) ;

			pos = find_pos( result, ',' ) ;
		}
	}
}

/**
 * @brief Adds a ui observer to the device handler
 * @param _user_interface: The User Interface to add as an observer
*/
void KeyBindController::add_ui_observer( std::shared_ptr<UserInterface> _user_interface )
{
	device_handler.get()->add_ui_observer( _user_interface ) ;
}

/**
 * @brief Clears the observer to allow the release of the circular references
*/
void KeyBindController::clear_ui_observers()
{
	device_handler.get()->clear_ui_observers() ;
}

/**
 * @brief Checks if the given key exists
 * @param _key_id: The key to search for
 * @return True if the key exists
*/
bool KeyBindController::check_key_exists( std::string _key_id )
{
	if( this->system_keys.find( _key_id ) != this->system_keys.end() )
		return true ;
	return false ;
}

/**
 * @brief Checks if the given bind exists
 * @param _bind_id: The bind to search for
 * @return True if the bind exists
*/
bool KeyBindController::check_bind_exists( std::string _bind_id )
{
	if( this->system_binds.find( _bind_id ) != this->system_binds.end() )
		return true ;
	return false ;
}

/**
 * @brief Checks if the requested bind is an axis bind
 * @param _key_id: The key to check
 * @return True if it is an axis
*/
bool KeyBindController::check_bind_is_axis( std::string _bind_id )
{
	return this->system_binds.find( _bind_id )->second->is_axis() ;
}

//TODO. Multi-key additions

/**
 * @brief Assigns the given key to a bind based on the input strings
 * @param _key_id_list: The key to assign to
 * @param _bind_id: The bind to assign to
 * @return True if the bind assignment successful
*/
void KeyBindController::assign_key_to_bind( std::vector<std::string> _key_id_list, std::string _bind_id )
{
	//Create a list for storage
	std::vector<Control*> control_list ;
	//Loop through and add all the controls
	for( auto iter = _key_id_list.begin() ; iter != _key_id_list.end() ; iter++ )
	{
		control_list.push_back( this->system_keys.find( *iter )->second ) ;
	}
	auto bind = this->system_binds.find( _bind_id )->second ;
	//Insert the keys into the bind
	bind->add_control( control_list ) ;
	//Insert the bind into the keys
	for( auto iter = control_list.begin() ; iter != control_list.end() ; iter++ )
	{
		(*iter)->add_bind( bind ) ;
	}
}

/**
 * @brief Assigns the given key to the specified axis.
 * @param _key_id_list: The string key id to add
 * @param _axis_id: The string axis id to add to
 * @param _which: The direction (reset, increase, decrease)
 */
void KeyBindController::assign_key_to_axis( std::vector<std::string> _key_id_list, std::string _axis_id )
{
	std::vector<Control*> control_list ;
	for( auto iter = _key_id_list.begin() ; iter != _key_id_list.end() ; iter++ )
	{
		control_list.push_back( this->system_keys.find( *iter )->second ) ;
	}
	auto bind = this->system_binds.find( _axis_id )->second ;
	bind->add_control( control_list ) ;
	for( auto iter = control_list.begin() ; iter != control_list.end() ; iter++ )
	{
		( *iter )->add_bind( bind ) ;
	}
}

/**
 * @brief Assigns the given bind to a key.
 * @return True if the assignment was successful
*/
bool KeyBindController::assign_bind_to_key()
{
	return false ;
}
