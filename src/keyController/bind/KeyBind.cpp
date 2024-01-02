#include "KeyBind.h"

KeyBind::KeyBind( char _mode ) :
	mode( _mode ), required( true )
{

}

/**
 * @brief Adds a vector of keys to the current Bind.
 * @param _control_combo : vector of implemented Control classes
*/
void KeyBind::add_control( std::vector<Control*> _control_combo )
{
	this->control.push_back( _control_combo );
}