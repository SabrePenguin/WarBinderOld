#include "Mouse.h"

Mouse::Mouse( std::string _mouse_id, std::string _local_name, bool _is_axis ) :
	Control(), is_axis( _is_axis ), local_mouse( _local_name ), mouse_id( _mouse_id )
{

}