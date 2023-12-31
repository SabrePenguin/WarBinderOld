/**
* Key.cpp: Defines the basic key type.
*/
#include <string>
#include <vector>
#include "Key.h"
#include "Control.h"
#include "../bind/Bind.h"

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
void Key::add_bind(Bind* _bind)
{
	binds.push_back(_bind);
}

/**
 * @brief Sets the representative key to the actual key in the system (ie. A, enter, backspace)
 * @param local_key: The local key in terms of a string to allow other keys
 * @return Whether the addition was successful
*/
bool Key::set_local_key(std::string local_key)
{
	return true;
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