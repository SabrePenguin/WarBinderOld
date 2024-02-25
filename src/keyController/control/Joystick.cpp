#include <string>
#include "Joystick.h"

Joystick::Joystick( std::string _joystick_id, std::string _local_name, bool _is_axis ) :
	Control(), is_axis( _is_axis ), local_joy( _local_name ), joystick_id( _joystick_id )
{

}

Joystick::~Joystick()
{
}

void Joystick::add_bind( KeyBind* _bind )
{
	this->binds.push_back( _bind ) ;
}

std::string Joystick::get_local_name()
{
	return this->local_joy ;
}