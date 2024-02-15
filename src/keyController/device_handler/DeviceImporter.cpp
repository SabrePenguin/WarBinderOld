#include <SDL.h>
#include <iostream>
#include <vector>
#include "Device.h"

int startup()
{
	if( SDL_Init( SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl ;
		return 1 ;
	}
	return 0 ;
}

std::vector<Device> find_devices()
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
				SDL_GameControllerClose( controller ) ;
			}
		}
	}
	return device_list ;
}

void shutdown()
{
	SDL_Quit() ;
}