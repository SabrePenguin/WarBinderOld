#include <SDL.h>
#include "SDLKeyInput.h"


void new_window()
{
	SDL_Window* window = SDL_CreateWindow( "Key Input", 400, 200, 0 ) ;
	SDL_Surface* surface = SDL_GetWindowSurface( window ) ;

	SDL_FillSurfaceRect( surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) ) ;
	SDL_UpdateWindowSurface( window ) ;
	SDL_Event e; 
	bool quit = false; 
	while( quit == false ) 
	{ 
		SDL_PumpEvents();
		while( SDL_PeepEvents( &e, 1, SDL_GETEVENT, SDL_EVENT_QUIT, SDL_EVENT_QUIT ) ) 
		{
			if( e.type == SDL_EVENT_QUIT ) 
				quit = true; 
		}
	}
	SDL_DestroyWindow( window ) ;
}