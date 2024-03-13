#ifndef PTUI_H
#define PTUI_H
#include "UserInterface.h"
#include <string>

class KeyBindController ;

class ptui : public UserInterface
{
public:
	ptui( std::shared_ptr<KeyBindController> _controller ) ;
	void main_loop(  ) ;
	void controller_change_notify() ;

private:
	void assign_key_to_bind( ) ;
	void display_keys_from_bind() ;
	void display_binds_from_key() ;
	void tester() ;
};

#endif // !PTUI_H
