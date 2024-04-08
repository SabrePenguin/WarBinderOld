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

#ifdef WX_WIDGETS

#endif

#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

// The purpose of this file is to be the surface level file that users
//


KeyBindController::KeyBindController(std::string _controlfile, std::string _bindfile, std::string _optfile, std::string _language) : 
	language(_language), buttons_locked( true )
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
}



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


void KeyBindController::set_language(std::string _language)
{
	this->language = _language;
	//TODO
}


std::string KeyBindController::check_type( Key_Type t_key )
{
	if( t_key == Key_Type::KEYBOARD )
		return "key" ;
	else if( t_key == Key_Type::MOUSE )
		return "mouse" ;
	return "controller" ;
}


void KeyBindController::import( std::string _filename )
{
	t_return data = file_handler->import_controls( _filename ) ;
	t_keys keys = std::get<0>( data ) ;
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

	/*
	//Import the controllers before the axes
	t_device devices = std::get<3>( data ) ;
	int total_buttons = 1 ;
	int total_axes = 1 ;
	for( t_device::iterator iter = devices.begin() ; iter != devices.end() ; ++iter )
	{
		//TODO: Ask user if they want to try matching controllers. Mainly because War Thunder gets info from another method.
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
	for( int button_number = 1 ; button_number <= total_buttons ; ++button_number )
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
	for( int axes_number = 1 ; axes_number <= total_axes ; ++axes_number )
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
	*/
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
		}
	}
	return ;
}


std::unordered_map<std::string, KeyBind*>* KeyBindController::get_binds_map()
{
	return &( this->system_binds ) ;
}


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
		//Remove the GUID
		result.erase( 0, result.find_first_of( ',' )+1 ) ;
		pos = result.find_first_of( ',' ) ;
		if( result[ 0 ] != '*' )
		{
			name = result.substr( 0, pos ) ;
		}
		else
		{
			#ifdef WX_WIDGETS
			//Run an SDL event to call the observer
			#else
			std::cin >> name ; //Due to parallel threads, a space must be added at the start
			#endif
		}
		result.erase( 0, pos + 1 ) ;
		int middle ;
		while( result.length() > 0 )
		{
			//a = axis
			//h = button
			//b = button
			pos = result.find_first_of( ',' ) ;
			middle = result.find_first_of( ':' ) ;
			if( pos == std::string::npos )
			{
				pos = result.length() - 1 ;
			}
			if( result[ middle+1 ] == 'b' )
			{

			}
			else if( result[ middle+1 ] == 'h' )
			{

			}
			else if( result[ middle+1 ] == 'a' )
			{

			}
			result.erase( 0, pos+1 ) ;
		}
	}
}


void KeyBindController::add_ui_observer( std::shared_ptr<UserInterface> _user_interface )
{
	device_handler.get()->add_ui_observer( _user_interface ) ;
}


void KeyBindController::clear_ui_observers()
{
	device_handler.get()->clear_ui_observers() ;
}


bool KeyBindController::check_key_exists( std::string _key_id )
{
	if( this->system_keys.find( _key_id ) != this->system_keys.end() )
		return true ;
	return false ;
}


bool KeyBindController::check_bind_exists( std::string _bind_id )
{
	if( this->system_binds.find( _bind_id ) != this->system_binds.end() )
		return true ;
	return false ;
}


bool KeyBindController::check_bind_is_axis( std::string _bind_id )
{
	return this->system_binds.find( _bind_id )->second->is_axis() ;
}


void KeyBindController::assign_key_to_bind( std::vector<std::string> _key_id_list, std::string _bind_id )
{
	//Create a list for storage
	std::vector<Control*> control_list ;
	//Loop through and add all the controls
	for( auto iter = _key_id_list.begin() ; iter != _key_id_list.end() ; ++iter )
	{
		control_list.push_back( this->system_keys.find( *iter )->second ) ;
	}
	auto bind = this->system_binds.find( _bind_id )->second ;
	//Insert the keys into the bind
	bind->add_control( control_list ) ;
	//Insert the bind into the keys
	for( auto iter = control_list.begin() ; iter != control_list.end() ; ++iter )
	{
		(*iter)->add_bind( bind ) ;
	}
}

void KeyBindController::remove_bind( Control* _control, KeyBind* _bind )
{
	//Temporary until I figure out how the UI sends information to here
	_control->remove_bind( _bind ) ;
}


void KeyBindController::remove_all_binds( Control* _control )
{
	_control->remove_all_binds() ;
}


void KeyBindController::remove_key( KeyBind* _bind, Control* _key )
{
	_bind->remove_key( _key ) ;
}


void KeyBindController::remove_single_key( KeyBind* _bind, std::vector<Control*>* _key_combo, Control* _key )
{
	_bind->remove_single_key( _key_combo, _key ) ;
}


void KeyBindController::remove_key_combo( KeyBind* _bind, std::vector<Control*>* _key_combo )
{
	_bind->remove_key_combo( _key_combo ) ;
}


void KeyBindController::remove_all_keys( KeyBind* _bind )
{
	_bind->remove_all_keys() ;
}


void KeyBindController::add_single_key( KeyBind* _bind, std::vector<Control*>* _key_combo, Control* _key )
{
	_bind->add_single_key( _key_combo, _key ) ;
}

void KeyBindController::set_lock( SDL_Event* _event )
{
	for( auto iter = this->button_combo.begin() ; iter != this->button_combo.end() ; iter++ )
	{
		// If this program's id is equal to the internal id of the event
		// and if any of the second equal the event button which was released.
		if( iter->first == _event->gbutton.which && iter->second == _event->gbutton.button )
		{
			this->buttons_locked.store( true ) ;
		}
	}
	this->buttons_locked.store( false ) ;
}
bool KeyBindController::get_lock()
{
	return this->buttons_locked.load() ;
}