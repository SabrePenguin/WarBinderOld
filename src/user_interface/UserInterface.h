#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H
#include <memory>

class KeyBindController ;

class UserInterface
{
public:
//Gets updated through an update()
//Call Binder, which then calls relevant controller. May get assigned here instead.
//DeviceHandler is a notifier, which notifies this that the controller is gone.
//Model contains SDL loop
//Gets information by calling relevant controller. Will be assigned here.

	UserInterface( std::shared_ptr<KeyBindController> _controller );
	// Informs the UI that the controllers been added or removed
	virtual void controller_change_notify() {} ;
	// Runs the main logic
	virtual int main_loop( int argc, char* argv[] ) { return  0 ; } ;
protected:
	// The primary controllers
	std::shared_ptr<KeyBindController> controller ;
};

#endif // !USER_INTERFACE_H