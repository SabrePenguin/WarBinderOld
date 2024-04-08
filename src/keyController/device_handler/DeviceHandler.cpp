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
	SDL_GameControllerAddMappingsFromFile("../../../../third_party/gamecontrollerdb.txt") ;
	//SDL_GameControllerAddMapping("a:b0,b:b1,back:b6,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,dpup:h0.1,guide:b8,leftshoulder:b4,leftstick:b9,lefttrigger:a2,leftx:a0,lefty:a1,rightshoulder:b5,rightstick:b10,righttrigger:a5,rightx:a3,righty:a4,start:b7,x:b2,y:b3,platform:Windows,") ;
}


SDL_GameController* DeviceHandler::find_device( SDL_JoystickID _dev_id )
{
	//Loop through devices. Uses vector instead of array.
	for( auto iter = game_controllers.begin() ; iter != game_controllers.end() ; ++iter )
	{
		if( _dev_id == SDL_JoystickInstanceID( SDL_GameControllerGetJoystick( *iter ) ) )
		{
			return *iter ;
		}
	}
	return nullptr ;
}


std::string DeviceHandler::add_device( int device_index )
{
	std::string mapping ;
	SDL_JoystickID controller_id = SDL_JoystickGetDeviceInstanceID( device_index ) ;
	// Check if controller id exists
	if( controller_id < 0 )
		return mapping ;

	//Check if this exists in the list. If it does, quit this function as we don't need it.
	if( find_device( controller_id ) )
		return mapping ;


	SDL_GameController* controller = SDL_GameControllerOpen( device_index ) ;
	// Check if controller was created
	if( !controller )
		return mapping ;

	mapping = SDL_GameControllerMapping( controller ) ;
	int button_count = SDL_JoystickNumButtons( SDL_GameControllerGetJoystick( controller ) ) ;
	game_controllers.push_back( controller ) ;
	++num_controllers ;
	return mapping ;
}

void DeviceHandler::remove_device( SDL_JoystickID _controller )
{
	SDL_GameController* control_p = find_device( _controller ) ;

	// Check for nullptr
	if( !control_p )
		return ;

	//Search through vector
	for( auto iter = game_controllers.begin() ; iter != game_controllers.end() ; ++iter )
	{
		//Erase item
		if( *iter == control_p )
		{
			game_controllers.erase( iter ) ;
			--num_controllers ;
			return ;
		}
	}
}


void DeviceHandler::shutdown()
{
	for( auto iter = this->game_controllers.begin() ; iter != this->game_controllers.end() ; ++iter )
	{
		SDL_GameControllerClose( ( *iter ) ) ;
	}
	SDL_Quit() ;
}


void DeviceHandler::add_ui_observer( std::shared_ptr<UserInterface> _ui )
{
	this->ui_observer.push_back( _ui ) ;
}


std::string DeviceHandler::device_change( SDL_Event* con_event )
{
	std::string result ;
	if( con_event->type == SDL_CONTROLLERDEVICEADDED || con_event->type == SDL_JOYDEVICEADDED )
	{
		result = this->add_device( con_event->cdevice.which ) ;
	}
	else if( con_event->type == SDL_CONTROLLERDEVICEREMOVED || con_event->type == SDL_JOYDEVICEREMOVED )
	{
		this->remove_device( con_event->cdevice.which ) ;
	}
	for( auto iter = this->ui_observer.begin() ; iter != this->ui_observer.end() ; ++iter )
	{
		iter->get()->controller_change_notify() ;
	}

	return result ;
}


void DeviceHandler::clear_ui_observers()
{
	ui_observer.clear() ;
}