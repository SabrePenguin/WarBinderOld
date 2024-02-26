#ifndef PTUI_H
#define PTUI_H
#include "UserInterface.h"
#include <string>

class KeyBindController ;

class ptui : public UserInterface
{
public:
	ptui( std::shared_ptr<KeyBindController> _controller ) ;
	void main_loop( std::shared_ptr<KeyBindController> _controller ) ;
	void controller_change_notify() ;

private:
	std::string line_one ;
	std::string line_two ;
	std::string line_three ;
	std::shared_ptr<KeyBindController> controller ;
};

#endif // !PTUI_H
