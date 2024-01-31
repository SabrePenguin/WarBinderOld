#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "KeyBindController.h"
#include "Control.h"
#include "Key.h"
#include "Bind.h"
#include "Axis.h"
#include "CSVin.h"
#include "reader.h"
#include "KeyBind.h"


/**
 * @brief Imports the files and converts them to objects
 * @param _controlfile: The file of the controls and their local names
 * @param _bindfile: The file of all the binds and their names
 * @param _language: The language in the file. Used to find local ids.
*/
KeyBindController::KeyBindController(std::string _controlfile, std::string _bindfile, std::string _language) : 
	language(_language) 
{
	std::vector<std::tuple<std::string, char, std::string, bool>> controls = get_control( _controlfile, _language ) ;
	std::vector<std::tuple<std::string, char, std::string, bool, bool>> binds = get_binds( _bindfile, _language ) ;
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
	set_language( _language ) ;
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
 * @brief Adds a generic control type
 * @param _key_id: The internal id. Can be anything as long as it matches Gaijin's internal id.
 * @param _local_key 
*/
void KeyBindController::add_new_control(std::string _key_id, std::string _local_key)
{
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
		_internal_id.erase( cutoff ) ;
		int un = 1;
		//this->p_binds.find() ;
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

controller KeyBindController::check_string( std::string _name )
{
	controller up ;
	if( _name.find( "_rangeMax" ) != std::string::npos )
		up = controller::INCREASE ;
	else if( _name.find( "_rangeMin" ) != std::string::npos )
		up = controller::DECREASE ;
	else
		up = controller::RESET ;
	return up ;
}

/**
 * @brief Imports the file. Must be a .blk file and must follow Gaijin's format
 * @param _filename 
*/
void KeyBindController::import( std::string _filename )
{
	t_return data = import_controls( _filename ) ;
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
				if( key_type == Key_Type::KEYBOARD )
					control_type = "key" ;
				else if( key_type == Key_Type::MOUSE )
					control_type = "mouse" ;
				else
					control_type = "joystick" ;
				auto find_key = this->system_keys.find( control_type + std::get<1>( *single ) ) ;
				if( find_key != this->system_keys.end() )
				{
					(*find_key).second->add_bind( existing_bind ) ;
					key_list.push_back( (*find_key).second ) ;
					i++ ;
				}
				i++ ;
			}
			if( key_list.size() )
			{
				existing_bind->add_control( key_list, up ) ;
			}
			
			//this->system_keys.find(bound_keys) ;
			i++ ;
		}
	}
	t_import_axis temp2 = std::get<1>( data ) ;
	return ;
}