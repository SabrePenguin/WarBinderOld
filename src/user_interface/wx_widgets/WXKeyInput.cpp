#include "WXKeyInput.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <string>
#include "KeyBind.h"
#include "Control.h"

WXKeyInput::WXKeyInput( wxWindow* parent, const wxString& name, KeyBind* keybind )
	: wxDialog(parent, -1, name)
{
	wxBoxSizer* stack = new wxBoxSizer( wxVERTICAL ) ;
	wxBoxSizer* main_control = new wxBoxSizer( wxHORIZONTAL ) ;
	auto controls = keybind->get_control() ;
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

	main_control->Add( newControl, 0 ) ;
	main_control->Add( confirm, 0 ) ;
	stack->Add( main_control, 0 ) ;
	SetSizer( stack ) ;
}