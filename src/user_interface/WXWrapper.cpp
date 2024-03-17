#include "WXWrapper.h"
#include "WXGui.h"
#include <SDL.h>

//Include this here because it handles some of the pointers
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

WXWrapper::WXWrapper( std::shared_ptr<KeyBindController> _controller )
	: UserInterface( _controller )
{
}

int WXWrapper::main_loop( int argc, char* argv[] )
{
	wxApp::SetInstance( new WXGui() ) ;
	wxEntryStart( argc, argv ) ;
	wxTheApp->CallOnInit() ;
	wxTheApp->OnRun() ;
	//wxTheApp->Exit() ;
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