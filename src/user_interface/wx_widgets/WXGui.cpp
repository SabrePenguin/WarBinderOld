#include "WXGui.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <memory>

wxBEGIN_EVENT_TABLE( testFrame, wxFrame )
EVT_MENU( wxID_EXIT, testFrame::OnExit )
EVT_MENU( wxID_ABOUT, testFrame::OnAbout )
wxEND_EVENT_TABLE()

WXGui::WXGui()
	: UserInterface( std::shared_ptr<KeyBindController>() ) 
{

}

WXGui::WXGui( std::shared_ptr<KeyBindController> _controller )
	: UserInterface( _controller )
{

}

bool WXGui::OnInit()
{
	testFrame* frame = new testFrame( "Test", wxPoint( 50, 50 ), wxSize( 450, 450 ) ) ;
	frame->Show( true ) ;
	return true ;
}

wxIMPLEMENT_APP_NO_MAIN(WXGui) ;

testFrame::testFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
	: wxFrame( NULL, wxID_ANY, title, pos, size )
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append( wxID_EXIT );
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append( wxID_ABOUT );
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to wxWidgets!" );
}

void testFrame::OnExit( wxCommandEvent& event )
{
    Close( true ) ;
}

void testFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox( "This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION );
}