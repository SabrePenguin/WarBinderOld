#ifndef BIND_H
#define BIND_H
#include <vector>
#include <string>
class Control;

class Bind
{
	public:
		Bind( std::string _internal_id, std::string _text_id, char _mode );
		void add_control(std::vector<Control*> _control_combo);
	private:
		//The internal id of the bind (THROTTLE_UP)
		std::string internal_id;
		//The local name of the bind
		std::string text_id;
		//The collection of vectors that make up the controls
		std::vector<std::vector<Control*>> control;
		//The gamemode character representation
		char mode ;
};


#endif