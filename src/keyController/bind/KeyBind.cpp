#include "KeyBind.h"

KeyBind::KeyBind( char _mode, bool _axis, bool _required, std::string _local_name, std::string _internal_id) :
	mode( _mode ), axis( _axis ), required( true ), local_id( _local_name ), internal_id( _internal_id )
{

}

KeyBind::~KeyBind()
{
	for( auto iter = control.begin() ; iter != control.end() ; iter++ )
	{
		//No need to delete, controls are deleted by hand
		iter->clear() ;
	}
	control.clear() ;
}

/**
 * @brief Adds a vector of keys to the current Bind.
 * @param _control_combo : vector of implemented Control classes
*/
void KeyBind::add_control( std::vector<Control*> _control_combo )
{
	this->control.push_back( _control_combo );
}

/**
 * @brief Clears the current control for a fresh keyboard
*/
void KeyBind::reset()
{
	this->control.clear() ;
}

/**
 * @brief Searches through the control vector and removes all references to the key given
 * @param _key: The Control pointer to compare to
 * @param _up: Used to allow holding with Axis
 */
void KeyBind::remove_key( Control* _key, controller _up )
{
	for( auto inner_vector = control.begin() ; inner_vector != control.end() ; inner_vector++ )
	{
		for( auto comp_control = inner_vector->begin() ; comp_control != inner_vector->end() ; comp_control++ )
		{
			if( *comp_control == _key )
			{
				inner_vector->erase( comp_control ) ;
			}
		}
		if( inner_vector->size() == 0 )
		{
			control.erase( inner_vector ) ;
		}
	}
}

/**
 * @brief Get the text id of the Bind
 * @return The text id
*/
std::string KeyBind::get_local_name()
{
	return this->local_id ;
}

char KeyBind::get_mode() 
{
	return this->mode ;
}

bool KeyBind::is_axis()
{
	return this->axis ;
}

std::vector<std::vector<Control*>>* KeyBind::get_control()
{
	return &this->control ;
}