#include "Device.h"

Device::Device( bool _connected, std::string _name, std::string _device_id, 
	int _axes_offset, int _button_offset, int _button_count, int _axes_count, std::string _type )
	: connected( _connected ), name( _name ), device_id( _device_id ), axes_offset( _axes_offset ), 
	button_offset( _button_offset ), button_count( _button_count ), axes_count( _axes_count ),
	type( _type )
{
}

void Device::set_connected( bool _c )
{
	connected = _c ;
}

bool Device::get_connected()
{
	return connected ;
}

void Device::set_name( std::string _n )
{
	name = _n ;
}

void Device::set_id( std::string _i )
{
	device_id = _i ;
}

void Device::set_axes_offset( int _a )
{
	axes_offset = _a ;
}

void Device::set_axes_count( int _a )
{
	axes_count = _a ;
}

void Device::set_button_offset( int _b )
{
	button_offset = _b ;
}

void Device::set_button_count( int _b )
{
	button_count = _b ;
}

void Device::set_type( std::string _t )
{
}
