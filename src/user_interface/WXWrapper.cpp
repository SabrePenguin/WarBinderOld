#include "WXWrapper.h"
#include "WXGui.h"
#include <SDL.h>
#include <SDL_system.h>
#include <unordered_map>
#include <string>
//TODO: Remove?
//Include this here because it handles some of the pointers
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include "KeyBindController.h"

WXWrapper::WXWrapper( std::shared_ptr<KeyBindController> _controller )
	: UserInterface( _controller )
{
}

int WXWrapper::main_loop( int argc, char* argv[] )
{
	wxApp::SetInstance( new WXGui( this ) ) ;
	wxEntryStart( argc, argv ) ;
	wxTheApp->CallOnInit() ;

	wxFrame* mainFrame = dynamic_cast< wxFrame* >( wxTheApp->GetTopWindow() ) ;
	if( !mainFrame )
		return 1 ;


	SDL_PropertiesID props = SDL_CreateProperties() ;
	SDL_SetProperty( props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, mainFrame->GetHandle() ) ;

	SDL_Window* sdlWindow = SDL_CreateWindowWithProperties( props )  ;

	if( !sdlWindow )
	{
		return 1 ;
	}

	wxTheApp->OnRun() ;
	//wxTheApp->Exit() ;
	SDL_DestroyWindow( sdlWindow ) ;
	wxEntryCleanup() ;


	uint32_t threadType = SDL_RegisterEvents( 1 ) ;
	if( threadType != ( ( uint32_t )-1 ) )
	{
		SDL_Event threadInterrupt ;
		SDL_zero( threadInterrupt ) ;
		threadInterrupt.type = threadType ;
		threadInterrupt.user.data1 = nullptr ;
		threadInterrupt.user.data2 = nullptr ;
		SDL_PushEvent( &threadInterrupt ) ;
	}
	return 0 ;
}

void WXWrapper::controller_change_notify()
{

}

std::unordered_map<std::string, KeyBind*>* WXWrapper::get_bind_map_pointer()
{
	return this->controller.get()->get_binds_map() ;
}