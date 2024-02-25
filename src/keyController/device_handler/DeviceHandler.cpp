#include <SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include "DeviceHandler.h"
#include "Device.h"
#include "UserInterface.h"

DeviceHandler::DeviceHandler() :
	num_controllers( 0 )
{
}

/**
 * @brief Adds devices to the game_controllers vector and returns a vector of Devices(?)
 * @return A vector of Devices(?)
*/
std::vector<Device> DeviceHandler::find_devices()
{
	std::vector<Device> device_list ;
	for( int iter = 0 ; iter < SDL_NumJoysticks() ; iter++ )
	{
		if( SDL_IsGameController( iter ) )
		{
			add_device( iter ) ;
		}
	}
	return device_list ;
}

/**
 * @brief Converted version of SDL2's example find_device function
 * @param _dev_id: The game controller's id
 * @return The pointer of the item. Will return nullptr if it isn't in the list
*/
SDL_GameController* DeviceHandler::find_device( SDL_JoystickID _dev_id )
{
	//Loop through devices. Uses vector instead of array.
	for( auto iter = game_controllers.begin() ; iter != game_controllers.end() ; iter++ )
	{
		if( _dev_id == SDL_JoystickInstanceID( SDL_GameControllerGetJoystick( *iter ) ) )
		{
			return *iter ;
		}
	}
	return nullptr ;
}

/**
 * @brief Adds a controller to the DeviceHandler vector.
 * @param device_index: The index to add
*/
void DeviceHandler::add_device( int device_index )
{
	SDL_JoystickID controller_id = SDL_JoystickGetDeviceInstanceID( device_index ) ;
	// Check if controller id exists
	if( controller_id < 0 )
		return ;

	//Check if this exists in the list. If it does, quit this function as we don't need it.
	if( find_device( controller_id ) )
		return ;


	SDL_GameController* controller = SDL_GameControllerOpen( device_index ) ;
	// Check if controller was created
	if( !controller )
		return ;
	game_controllers.push_back( controller ) ;
}

void DeviceHandler::remove_device( SDL_JoystickID _controller )
{
	SDL_GameController* control_p = find_device( _controller ) ;

	// Check for nullptr
	if( !control_p )
		return ;

	//Search through vector
	for( auto iter = game_controllers.begin() ; iter != game_controllers.end() ; iter++ )
	{
		//Erase item
		if( *iter == control_p )
		{
			game_controllers.erase( iter ) ;
			return ;
		}
	}
}

/**
 * @brief Clears everything from this
*/
void DeviceHandler::shutdown()
{
	for( auto iter = this->game_controllers.begin() ; iter != this->game_controllers.end() ; iter++ )
	{
		SDL_GameControllerClose( ( *iter ) ) ;
	}
	SDL_Quit() ;
}

/**
 * @brief Adds a ui observer to be notified
 * @param _ui: The ui to be added.
*/
void DeviceHandler::add_ui_observer( UserInterface* _ui )
{
	this->ui_observer.push_back( std::shared_ptr<UserInterface>( _ui ) ) ;
}


/**
 * @brief Informs this that a device change has occurred and that it must notify the UI
 * @param con_event: A detach or attach of a controller
*/
void DeviceHandler::device_change( SDL_Event* con_event )
{
	if( con_event->type == SDL_CONTROLLERDEVICEADDED || con_event->type == SDL_JOYDEVICEADDED )
	{
		this->add_device( con_event->cdevice.which ) ;
	}
	else if( con_event->type == SDL_CONTROLLERDEVICEREMOVED || con_event->type == SDL_JOYDEVICEREMOVED )
	{
		this->remove_device( con_event->cdevice.which ) ;
	}
	for( auto iter = this->ui_observer.begin() ; iter != this->ui_observer.end() ; iter++ )
	{
		iter->get()->controller_change_notify() ;
	}
}