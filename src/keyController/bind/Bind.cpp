#include <vector>
#include <string>
#include "Bind.h"
#include "Axis.h"
#include "KeyBind.h"
#include "../control/Control.h"

/**
 * @brief The constructor
 * @param _internal_id: The internal id of the bind, such as ID_AAM
 * @param _text_id: What will be displayed to the user
 * @param _mode: The gamemode that this belongs to
*/
Bind::Bind(std::string _internal_id, std::string _text_id, char _mode, bool _required) : 
	KeyBind( _mode, false, _required ), internal_id(_internal_id), text_id(_text_id)
{

}

Bind::~Bind()
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
void Bind::add_control( std::vector<Control*> _control_combo, controller _up )
{
	this->control.push_back( _control_combo );
}

/**
 * @brief Clears the current control for a fresh keyboard
*/
void Bind::reset()
{
	this->control.clear() ;
}

/**
 * @brief Searches through the control vector and removes all references to the key given
 * @param _key: The Control pointer to compare to
 * @param _up: Used to allow holding with Axis
 */
void Bind::remove_key( Control* _key, controller _up )
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
std::string Bind::get_local_name()
{
	return this->text_id ;
}

std::vector<std::vector<Control*>>* Bind::get_main_control()
{
	return &( this->control ) ;
}
