#ifndef WX_GUI_H
#define WX_GUI_H
#include "UserInterface.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <memory>

class KeyBindController ;

class WXGui : public UserInterface, public wxApp
{
public:
	WXGui() ;
	WXGui( std::shared_ptr<KeyBindController> _controller ) ;
	void controller_change_notify() {} ;
	void main_loop() {} ;

	virtual bool OnInit() ;

private:
	
};

class testFrame : public wxFrame
{
public:
	testFrame( const wxString& title, const wxPoint& pos, const wxSize& size );
private:
	void OnExit( wxCommandEvent& event );
	void OnAbout( wxCommandEvent& event );
	wxDECLARE_EVENT_TABLE();
};

#endif //WXGUI_H