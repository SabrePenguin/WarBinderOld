#ifndef WX_GUI_H
#define WX_GUI_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <memory>

class WXGui : public wxApp
{
public:
	WXGui() ;
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