#ifndef DEVICE_HANDLER_H
#define DEVICE_HANDLER_H
#include <vector>
#include <SDL.h>
#include <memory>
#include <string>
class Device ;
class UserInterface ;

class DeviceHandler
{
public:
	DeviceHandler() ;
	/**
	* @brief Adds devices to the game_controllers vector and returns a vector of Devices(?)
	* @return A vector of Devices(?)
	*/
	std::vector<Device> find_devices() ;
	/**
	 * @brief Clears everything
	 */
	void shutdown() ;
	/**
	* @brief Adds a ui observer to be notified
	* @param _ui: The ui to be added.
	*/
	void add_ui_observer( std::shared_ptr<UserInterface> _ui ) ;
	/**
	* @brief Informs this that a device change has occurred and that it must notify the UI
	* @param con_event: A detach or attach of a controller
	*/
	std::string device_change( SDL_Event* con_event ) ;
	void clear_ui_observers() ;
private:
	void remove_device( SDL_JoystickID _controller ) ;
	/**
	* @brief Adds a controller to the DeviceHandler vector.
	* @param device_index: The index to add
	*/
	std::string add_device( int index ) ;
	/**
	* @brief Converted version of SDL2's example find_device function
	* @param _dev_id: The game controller's id
	* @return The pointer of the item. Will return nullptr if it isn't in the list
	*/
	SDL_GameController* find_device( SDL_JoystickID _joy_id ) ;
	/*The observer for the ui. Made a vector in case of wierd stuff.*/
	std::vector<std::shared_ptr<UserInterface>> ui_observer ;
	std::vector<SDL_GameController*> game_controllers ;
	int num_controllers ; 
};

#endif // !DEVICE_HANDLER_H