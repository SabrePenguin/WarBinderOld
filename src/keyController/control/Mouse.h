#ifndef MOUSE_H
#define MOUSE_H
#include "Control.h"
class Mouse : public Control
{
	public:
		Mouse( std::string _mouse_id, std::string _local_name, bool _is_axis ) ;
	private:
		//The internal mouse button/axis id
		std::string mouse_id;
		//The local mouse name
		std::string local_mouse;
		//Indicates if the given id is an axis or not
		bool is_axis ;
};
#endif // !MOUSE_H