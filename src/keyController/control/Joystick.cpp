#include "Joystick.h"
#include "Joystick.h"

Joystick::Joystick( std::string _joystick_id, std::string _local_name, bool _is_axis ) :
	Control(), is_axis( _is_axis ), local_joy( _local_name ), joystick_id( _joystick_id )
{

}

void Joystick::add_bind( KeyBind* _bind )
{
	this->binds.push_back( _bind ) ;
}
