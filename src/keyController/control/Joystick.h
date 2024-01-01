#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "Control.h"
class Joystick : public Control
{
public:
	Joystick( std::string _joystick_id, std::string _local_name, bool _is_axis ) ;
private:
	//The internal mouse button/axis id
	std::string joystick_id;
	//The local mouse name
	std::string local_joy;
	//Indicates if the given id is an axis or not
	bool is_axis ;
};
#endif // !JOYSTICK_H