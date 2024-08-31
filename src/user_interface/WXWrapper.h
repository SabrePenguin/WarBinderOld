#ifndef WXWRAPPER_H
#define WXWRAPPER_H

#include "UserInterface.h"
#include <unordered_map>
#include <string>

class KeyBindController ;
class KeyBind ;

class WXWrapper : public UserInterface
{
public:
	WXWrapper( std::shared_ptr<KeyBindController> _controller ) ;
	void controller_change_notify() ;
	int main_loop( int argc, char* argv[] ) ;
	std::unordered_map<std::string, KeyBind*>* get_bind_map_pointer() ;
private:
};
#endif // !WXWRAPPER_H
