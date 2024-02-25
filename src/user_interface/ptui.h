#ifndef PTUI_H
#define PTUI_H
#include "UserInterface.h"
class ptui : public UserInterface
{
public:
	ptui() ;
	void main_loop( KeyBindController* _controller ) ;
	void controller_change_notify() ;
};

#endif // !PTUI_H
