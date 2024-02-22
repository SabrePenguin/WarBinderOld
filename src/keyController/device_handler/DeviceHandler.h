#ifndef DEVICE_HANDLER_H
#define DEVICE_HANDLER_H
#include <vector>
#include <SDL.h>
#include <memory>
class Device ;
class UserInterface ;

class DeviceHandler
{
public:
	DeviceHandler() ;
	int startup() ;
	std::vector<Device> find_devices() ;
	void shutdown() ;
	void add_ui_observer( UserInterface* _ui ) ;
	void device_change( SDL_Event* con_event ) ;
	void remove_device( int index ) ;
	void add_device( int index ) ;
private:
	/*The observer for the ui. Made a vector in case of wierd stuff.*/
	std::vector<std::shared_ptr<UserInterface>> ui_observer ;
	std::vector<SDL_GameController*> game_controllers ;
};

#endif // !DEVICE_HANDLER_H