#include "KeyBind.h"
#include "Control.h"

KeyBind::KeyBind( char _mode, bool _axis, bool _required, std::string _local_name, std::string _internal_id) :
	mode( _mode ), axis( _axis ), required( _required ), local_id( _local_name ), internal_id( _internal_id ), is_reset( false )
{

}

KeyBind::~KeyBind()
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
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
void KeyBind::remove_key( Control* _key )
{
	for( auto inner_vector = control.begin() ; inner_vector != control.end() ; )
	{
		for( auto control_pointer = inner_vector->begin() ; control_pointer != inner_vector->end() ; )
		{
			if( *control_pointer == _key )
			{
				control_pointer = inner_vector->erase( control_pointer ) ;
			}
			else
			{
				++control_pointer ;
			}
		}

		if( inner_vector->size() == 0 )
		{
			inner_vector = control.erase( inner_vector ) ;
		}
		else
		{
			++inner_vector ;
		}
	}
}

/**
 * @brief Removes the given vector of Controls from the list of available controls
 * @param _key_combo: Pointer to the vector to remove
 */
void KeyBind::remove_key_combo( std::vector<Control*>* _key_combo )
{
	for( auto iter = control.begin() ; iter != control.end() ; ++iter )
	{
		if( *iter == *_key_combo )
		{
			// Call each Control individually and remove this KeyBind from it
			for( auto remove_control = iter->begin() ; remove_control != iter->end() ; ++remove_control )
			{
				( *remove_control )->call_remove_bind( this ) ;
			}
			control.erase( iter ) ;
			break ;
		}
	}
}

void KeyBind::remove_all_keys()
{
	for( auto iter = control.begin() ; iter != control.end() ; )
	{
		for( auto remove_control = iter->begin() ; remove_control != iter->end() ; ++remove_control )
		{
			( *remove_control )->call_remove_bind( this ) ;
		}
		iter = control.erase( iter ) ;
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

void KeyBind::set_local_name( std::string _name )
{
	this->local_id = _name ;
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