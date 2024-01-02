#ifndef KEYBIND_H
#define KEYBIND_H
#include <vector>

class Control ;

class KeyBind
{
	public:
		KeyBind(char _mode, bool _axis) ;
		virtual void add_control( std::vector<Control*> _control_combo, bool _up ) { return ; };
	protected:
		//Unfortunate type check
		bool axis ;
		//The gamemode character representation
		char mode ;
		//Whether the given control is required to play the game (ie. Fire guns)
		bool required ;
};

#endif // !KEYBIND_H