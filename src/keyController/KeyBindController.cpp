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


/**
 * @brief Imports the files and converts them to objects
 * @param _controlfile: The file of the controls and their names
 * @param _bindfile: The file of all the keys and their local ids and counterparts
 * @param _language: The language in the file. Used to find local ids.
*/
KeyBindController::KeyBindController(std::string _controlfile, std::string _bindfile, std::string _language) : 
	language(_language) 
{
	std::vector<std::tuple<std::string, char, std::string, bool>> controls = get_control( _controlfile, _language ) ;
	std::vector<std::tuple<std::string, bool, std::string>> binds = get_binds( _bindfile, _language ) ;
	for( auto iterator = controls.begin() ; iterator != controls.end() ; ++iterator )
	{
		//Position zero has the internal name
		//Position two has the local name
		//Position three determines if it's a modifier
		//Position one is the gamemode control
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
		//Position one controls if it's an axis
		this->add_new_bind(
			std::get<0>( *iterator ),
			std::get<2>( *iterator ),
			std::get<1>( *iterator )
		) ;
	}
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
 * @param _gamemode 
*/
void KeyBindController::add_key(std::string _key_id, std::string _local_key, bool _modifier, char _gamemode)
{
	//Technically can be put in one line, but reduces readability
	Key* new_key = new Key(_key_id, _local_key, _modifier, _gamemode);
	this->system_keys.insert({ _key_id, new_key });
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
 * @brief Adds either an Axis or Bind pointer.
 * @param _internal_id: The internal id of the bind name.
 * @param _local_id: The local name of the bind. (ie. "Throttle Up")
 * @param _axis: Determines if the given bind needs to be an axis or regular button
*/
void KeyBindController::add_new_bind(std::string _internal_id, std::string _local_id, bool _axis)
{
	Bind* new_bind ;
	if( !_axis )
		new_bind = new Bind( _internal_id, _local_id ) ;
	else
		new_bind = new Axis( _internal_id, _local_id ) ;
	this->p_binds.insert({ _local_id, new_bind }) ;
}

/**
 * @brief Sets the language of the keybind controller.
 * @param _language: The language to be used. Must match a language in the csv files.
*/
void KeyBindController::set_language(std::string _language)
{
	this->language = _language;
}
