/**
* Key.cpp: Defines the basic key type.
*/
#include <string>
#include <vector>
#include "Key.h"
#include "Control.h"
#include "../bind/KeyBind.h"

/**
 * @brief Modifier key constructor
 * @param _key_id: Key id
 * @param _local_key: Local key ("backspace", "a", "1")
 * @param _modifier: Modifier key, such as ctrl or alt
*/
Key::Key(std::string _key_id, std::string _local_key, bool _modifier) : 
	Control(), key_id( _key_id ), local_key( _local_key ), modifier_key( _modifier ) {
}

/**
 * @brief Adds a single Bind or Axis class to the internal vector
 * @param _bind : A single Bind that gets added to the vector
*/
void Key::add_bind( KeyBind* _bind )
{
	binds.push_back(_bind);
}

/**
 * @brief A method to check if the given bind has any internal conflicts (mode to mode)
 * @param _bind: The bind to check
 * @return True if the bind is good to use
*/
bool Key::check_conflict( KeyBind* _bind )
{
	for( std::vector<KeyBind*>::iterator it_bind = binds.begin() ; it_bind != binds.end() ; ++it_bind )
	{
		//Mode comparison. 'c' is common and should always be compared with
		char cur_mode = _bind->get_mode() ;
		if( cur_mode == (*it_bind)->get_mode() || cur_mode == 'c' )
			return false ;
	}
	return true ;
}

/**
 * @brief Enables or disables whether the key is a modifier key.
 * This enables using keys such as 'a' and 'z' like 'ctrl' and 'alt'
 * @param enable: Enable modifier key
 * @return The current state of the key
*/
bool Key::set_modifier(bool enable)
{
	return true;
}

std::string Key::get_id()
{
	return this->key_id;
}

bool Key::is_modifier()
{
	return this->modifier_key;
}

std::string Key::get_local_name()
{
	return this->local_key ;
}