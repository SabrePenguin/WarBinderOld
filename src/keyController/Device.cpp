#include "Device.h"

Device::Device( bool _connected, std::string _name, std::string _device_id, 
	int _axes_offset, int _button_offset, int _button_count, int _axes_count, std::string _type )
	: connected( _connected ), name( _name ), device_id( _device_id ), axes_offset( _axes_offset ), 
	button_offset( _button_offset ), button_count( _button_count ), axes_count( _axes_count ),
	type( _type )
{
}