#include "KeyBind.h"

KeyBind::KeyBind( char _mode, bool _axis, bool _required) :
	mode( _mode ), axis( _axis ), required( true )
{

}

KeyBind::~KeyBind()
{

}

char KeyBind::get_mode() 
{
	return this->mode ;
}

bool KeyBind::is_axis()
{
	return this->axis ;
}