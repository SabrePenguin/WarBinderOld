#ifndef KEYBIND_H
#define KEYBIND_H
#include <vector>

class Control ;

class KeyBind
{
	public:
		KeyBind(char _mode) ;
		void add_control( std::vector<Control*> _control_combo );
	protected:
		//The collection of vectors that make up the controls
		std::vector<std::vector<Control*>> control;
		//The gamemode character representation
		char mode ;
		//Whether the given control is required to play the game (ie. Fire guns)
		bool required ;
};

#endif // !KEYBIND_H