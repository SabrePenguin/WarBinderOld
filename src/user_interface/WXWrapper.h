#ifndef WXWRAPPER_H
#define WXWRAPPER_H

#include "UserInterface.h"

class KeyBindController ;

class WXWrapper : public UserInterface
{
public:
	WXWrapper( std::shared_ptr<KeyBindController> _controller ) ;
	void controller_change_notify() ;
	int main_loop( int argc, char* argv[] ) ;
private:
};
#endif // !WXWRAPPER_H
