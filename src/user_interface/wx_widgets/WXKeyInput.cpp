#include "WXKeyInput.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <string>
#include "KeyBind.h"
#include "Control.h"
#include <SDL_system.h>

WXKeyInput::WXKeyInput( wxWindow* parent, const wxString& name, KeyBind* keybind )
	: wxDialog(parent, -1, name)
{
	wxBoxSizer* stack = new wxBoxSizer( wxVERTICAL ) ;
	wxBoxSizer* main_control = new wxBoxSizer( wxHORIZONTAL ) ;
	auto controls = keybind->get_control() ;
	Bind( wxEVT_SIZE, &WXKeyInput::OnSize, this );
	for( auto iter = controls->begin() ; iter != controls->end() ; ++iter )
	{
		std::string name ;
		for( auto control_data = iter->begin() ; control_data != iter->end() ; ++control_data )
		{
			if( control_data != iter->begin() )
			{
				name = name + ", " ;
			}
			name = name + ( *control_data )->get_local_name() ;
		}
		wxButton* button = new wxButton( this, wxID_ANY, name ) ;
		stack->Add( button, 0 ) ;
	}
	wxButton* confirm = new wxButton( this, wxID_OK, "Confirm" ) ;
	/// TODO: Fire event here where we wait until key is lifted
	wxButton* newControl = new wxButton( this, wxID_ANY, "Add new combo" ) ;
	newControl->Bind( wxEVT_BUTTON, &WXKeyInput::start_addition, this) ;

	main_control->Add( newControl, 0 ) ;
	main_control->Add( confirm, 0 ) ;
	stack->Add( main_control, 0 ) ;
	SetSizer( stack ) ;

	SDL_PropertiesID props = SDL_CreateProperties() ;
	//SDL_SetBooleanProperty( props, SDL_PROP_WINDOW_CREATE_MENU_BOOLEAN, true ) ;
	//SDL_SetProperty( props, SDL_PROP_WINDOW_CREATE_PARENT_POINTER, parent->GetHWND() ) ;
	SDL_SetProperty( props, SDL_PROP_WINDOW_CREATE_WIN32_HWND_POINTER, GetHandle() ) ;

	window = SDL_CreateWindowWithProperties( props )  ;
}

void WXKeyInput::onSize( wxCommandEvent& event )
{
	Update() ;
	Refresh() ;
}

WXKeyInput::~WXKeyInput()
{
	if( window )
		SDL_DestroyWindow( window ) ;
}

void WXKeyInput::start_addition( wxCommandEvent& event )
{

	//data->add_control() ;
}

WXReadIn::WXReadIn( wxWindow* parent, const wxString& name, KeyBind* keybind )
	: wxDialog( parent, -1, name )
{
}

WXReadIn::~WXReadIn()
{

}