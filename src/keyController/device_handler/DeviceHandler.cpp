#include <SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include "DeviceHandler.h"
#include "Device.h"
#include "UserInterface.h"

DeviceHandler::DeviceHandler()
{
}

/**
 * @brief Initialize SDL's game controller and joystick subsystem
 * @return 0 if successful, 1 otherwise
*/
int DeviceHandler::startup()
{
	if( SDL_Init( SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl ;
		return 1 ;
	}
	SDL_JoystickEventState( SDL_ENABLE ) ;
	SDL_GameControllerEventState( SDL_ENABLE ) ;
	return 0 ;
}

/**
 * @brief Adds devices to the game_controllers vector and returns a vector of Devices(?)
 * @return A vector of Devices(?)
*/
std::vector<Device> DeviceHandler::find_devices()
{
	std::vector<Device> device_list ;
	int joy_count = SDL_NumJoysticks() ;
	if( joy_count > 0 )
	{
		for( int iter = 0 ; iter < joy_count ; iter++ )
		{
			if( SDL_IsGameController( iter ) )
			{
				SDL_GameController* controller = SDL_GameControllerOpen( iter ) ;
				game_controllers.push_back( controller ) ;
			}
		}
	}
	return device_list ;
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

void DeviceHandler::add_device( int index )
{
	if( SDL_IsGameController( index ) )
	{
		SDL_GameController* controller = SDL_GameControllerOpen( index ) ;
		if( controller )
		{
			this->game_controllers.push_back( controller ) ;
		}
	}
}

void DeviceHandler::remove_device( int index )
{
	for( auto iter = game_controllers.begin() ; iter != game_controllers.end() ; iter++ )
	{
		if( SDL_JoystickInstanceID( SDL_GameControllerGetJoystick( *iter ) ) == index )
		{
			SDL_GameControllerClose( *iter ) ;
			iter = game_controllers.erase( iter ) ;
		}
	}
}