#include "WXGui.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/splitter.h>
#include <memory>

//Include the crt to track any memory leaks
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

wxBEGIN_EVENT_TABLE( mainFrame, wxFrame )
EVT_MENU( wxID_EXIT, mainFrame::OnExit )
EVT_MENU( wxID_ABOUT, mainFrame::OnAbout )
wxEND_EVENT_TABLE()

WXGui::WXGui()
{

}


bool WXGui::OnInit()
{
	mainFrame* frame = new mainFrame( "Test", wxDefaultPosition, wxDefaultSize ) ;
	frame->Show( true ) ;
	return true ;
}

wxIMPLEMENT_APP_NO_MAIN(WXGui) ;

//////////////////////////////////////////////////////////////////////////////////////////////

mainFrame::mainFrame( const wxString& title, const wxPoint& pos, const wxSize& size )
	: wxFrame( NULL, wxID_ANY, title, pos, size )
{
    this->create_bar() ;

    /*
    wxPanel* panel_top = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 200, 100 ) ) ;
    panel_top->SetBackgroundColour( wxColor( 100, 100, 100 ) ) ;
    wxPanel* panel_bottom = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 200, 100 ) )  ;
    panel_bottom->SetBackgroundColour( wxColor( 100, 200, 0 ) ) ;


    wxSplitterWindow* split = new wxSplitterWindow( panel_bottom, wxID_ANY, wxDefaultPosition, wxDefaultSize ) ;
    wxPanel* panel_bottom_l = new wxPanel( split, wxID_ANY, wxDefaultPosition, wxSize( 100, 100 ) ) ;
    panel_bottom_l->SetBackgroundColour( wxColor( 100, 100, 200 ) ) ;
    wxPanel* panel_bottom_r = new wxPanel( split, wxID_ANY, wxDefaultPosition, wxSize( 100, 100 ) ) ;
    panel_bottom_r->SetBackgroundColour( wxColor( 0, 100, 200 ) ) ;


    split->SplitVertically( panel_bottom_l, panel_bottom_r ) ;
    split->SetMinimumPaneSize( 100 ) ;
    split->SetSashGravity( 0.5 ) ;

    wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL ) ;
    sizer->Add( panel_top, 1, wxEXPAND ) ;
    wxBoxSizer* size_bottom = new wxBoxSizer( wxHORIZONTAL ) ;
    size_bottom->Add( panel_bottom, 1, wxEXPAND ) ;
    //size_bottom->Add( panel_bottom_r, 0, wxEXPAND ) ;
    //sizer->Add( panel_bottom, 1, wxEXPAND ) ;
    sizer->Add( size_bottom, 1, wxEXPAND ) ;
    this->SetSizerAndFit( sizer ) ;
    */
}

void mainFrame::OnExit( wxCommandEvent& event )
{
    Close( true ) ;
}

void mainFrame::OnAbout( wxCommandEvent& event )
{
    wxMessageBox( "This is a program that uses wxWidgets for a small, native implementation",
        "About WarBinder", wxOK | wxICON_INFORMATION );
}

void mainFrame::create_bar()
{
    //Create the File menu
    wxMenu* menuFile = new wxMenu ;
    menuFile->Append( wxID_EXIT ) ;
    wxMenuItem* import = new wxMenuItem( menuFile, wxID_ANY, "Import" ) ;
    menuFile->Append( import ) ;
    wxMenuItem* save = new wxMenuItem( menuFile, wxID_ANY, "Save" ) ;
    menuFile->Append( save ) ;

    //Create the Edit menu
    wxMenu* edit = new wxMenu() ;
    wxMenuItem* item = new wxMenuItem( edit, wxID_ANY, "Item" ) ;
    edit->Append( item ) ;

    //Create the Preferences menu
    wxMenu* prefs = new wxMenu() ;
    wxMenuItem* lang = new wxMenuItem( prefs, wxID_ANY, "Language") ;
    prefs->Append( lang ) ;

    //Create the help menu
    wxMenu* menuHelp = new wxMenu ;
    menuHelp->Append( wxID_ABOUT ) ;
    wxMenuItem* help = new wxMenuItem( prefs, wxID_ANY, "Help" ) ;
    menuHelp->Append( help ) ;

    //Append the wxMenu items to the Menubar
    wxMenuBar* menuBar = new wxMenuBar ;
    menuBar->Append( menuFile, "&File" ) ;
    menuBar->Append( edit, "&Edit" ) ;
    menuBar->Append( prefs, "&Preferences" ) ;
    menuBar->Append( menuHelp, "&Help" ) ;
    SetMenuBar( menuBar ) ;
}