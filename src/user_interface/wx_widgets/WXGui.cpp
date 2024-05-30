#include "WXGui.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/splitter.h>
#include <memory>
#include <unordered_map>


//Include the crt to track any memory leaks
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include "KeyBind.h"
#include "Control.h"
#include "WXWrapper.h"
#include "WXKeyInput.h"

wxBEGIN_EVENT_TABLE( mainFrame, wxFrame )
EVT_MENU( wxID_EXIT, mainFrame::OnExit )
EVT_MENU( wxID_ABOUT, mainFrame::OnAbout )
wxEND_EVENT_TABLE()

WXGui::WXGui()
{

}

WXGui::WXGui( WXWrapper* _wrapper )
	: wrapper( _wrapper )
{

}


bool WXGui::OnInit()
{
	mainFrame* frame = new mainFrame( "WarBinder", wxDefaultPosition, wxDefaultSize, wrapper ) ;
	frame->Show( true ) ;
	frame->SetMinSize( wxSize( 700, 300 ) ) ;
	return true ;
}

wxIMPLEMENT_APP_NO_MAIN(WXGui) ;

//////////////////////////////////////////////////////////////////////////////////////////////

void mainFrame::on_button_clicked( wxCommandEvent& event )
{
	wxButton* button = dynamic_cast<wxButton*>( event.GetEventObject() ) ;
	if( !button )
		return ;

	KeyBind* data = static_cast<KeyBind*>( button->GetClientData() ) ;
	if( !data )
		return ;

	if( !data->is_axis() )
	{
		WXKeyInput* input = new WXKeyInput( this, "Test", data ) ;
		input->ShowModal() ;
		input->Destroy() ;
		//wxMessageBox( "A", "Popup A" ) ;
	}
	else
	{
		wxMessageBox( "B", "Popup B" ) ;
	}
}


mainFrame::mainFrame( const wxString& title, const wxPoint& pos, const wxSize& size, WXWrapper* _wrapper )
	: wxFrame( NULL, wxID_ANY, title, pos, size ), wrapper( _wrapper )
{
    //Create the bar
    this->create_bar() ;

    //Create the main grid
	wxBoxSizer* main_grid;
	main_grid = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* upper_bar;
	upper_bar = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* button_mode;
	button_mode = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* upper;
	upper = new wxBoxSizer( wxHORIZONTAL );

	wxButton* air = new wxButton( this, wxID_ANY, wxT( "Plane" ), wxDefaultPosition, wxDefaultSize, 0 );
	upper->Add( air, 0, wxALL, 5 );

	wxButton* tank = new wxButton( this, wxID_ANY, wxT( "Ground" ), wxDefaultPosition, wxDefaultSize, 0 );
	upper->Add( tank, 0, wxALL, 5 );

	wxButton* boat = new wxButton( this, wxID_ANY, wxT( "Naval" ), wxDefaultPosition, wxDefaultSize, 0 );
	upper->Add( boat, 0, wxALL, 5 );


	button_mode->Add( upper, 1, wxEXPAND, 5 );

	wxBoxSizer* lower;
	lower = new wxBoxSizer( wxHORIZONTAL );

	wxButton* heli = new wxButton( this, wxID_ANY, wxT( "Helicopter" ), wxDefaultPosition, wxDefaultSize, 0 );
	lower->Add( heli, 0, wxALL, 5 );

	wxButton* common = new wxButton( this, wxID_ANY, wxT( "Common" ), wxDefaultPosition, wxDefaultSize, 0 );
	lower->Add( common, 0, wxALL, 5 );

	wxButton* spectator = new wxButton( this, wxID_ANY, wxT( "Spectator" ), wxDefaultPosition, wxDefaultSize, 0 );
	lower->Add( spectator, 0, wxALL, 5 );


	button_mode->Add( lower, 1, wxEXPAND, 5 );


	upper_bar->Add( button_mode, 3, wxEXPAND, 5 );

	wxBoxSizer* button_type;
	button_type = new wxBoxSizer( wxHORIZONTAL );

	wxButton* simple = new wxButton( this, wxID_ANY, wxT( "Simple" ), wxDefaultPosition, wxDefaultSize, 0 );
	simple->SetMinSize( wxSize( 75, 50 ) );

	button_type->Add( simple, 0, wxALL, 5 );

	wxButton* advanced = new wxButton( this, wxID_ANY, wxT( "Advanced" ), wxDefaultPosition, wxDefaultSize, 0 );
	advanced->SetMinSize( wxSize( 75, 50 ) );

	button_type->Add( advanced, 0, wxALL, 5 );

	wxButton* real = new wxButton( this, wxID_ANY, wxT( "Real" ), wxDefaultPosition, wxDefaultSize, 0 );
	real->SetMinSize( wxSize( 75, 50 ) );

	button_type->Add( real, 0, wxALL, 5 );

	wxButton* full_real = new wxButton( this, wxID_ANY, wxT( "Full\nRealistic" ), wxDefaultPosition, wxDefaultSize, 0 );
	full_real->SetMinSize( wxSize( 75, 50 ) );

	button_type->Add( full_real, 0, wxALL, 5 );


	upper_bar->Add( button_type, 4, wxEXPAND, 5 );


	main_grid->Add( upper_bar, 2, wxEXPAND, 5 );

	wxBoxSizer* lower_bar;
	lower_bar = new wxBoxSizer( wxHORIZONTAL );

	////////////////////////////////////////////////////
	// Controls section

	wxBoxSizer* control_bar;
	control_bar = new wxBoxSizer( wxVERTICAL );

	wxScrolledWindow* scroll = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE | wxVSCROLL );
	scroll->SetScrollRate( 5, 5 );
	scroll->SetMinSize( wxSize( 250, 100 ) ) ;

	wxBoxSizer* scroll_sizer;
	scroll_sizer = new wxBoxSizer( wxVERTICAL );

	//Creation of the sections
	
	std::unordered_multimap<std::string, wxButton*> button_map ;
	auto map = wrapper->get_bind_map_pointer() ;
	for( auto iter = map->begin() ; iter != map->end() ; ++iter )
	{
		//Creat button with the local name and containing a pointer to itself
		auto controls = iter->second->get_control() ;
		std::string name = iter->second->get_local_name() + "\n";
		for( auto control_iter = controls->begin() ; control_iter != controls->end() ; ++control_iter )
		{
			for( auto control_inner = control_iter->begin() ; control_inner != control_iter->end() ; ++control_inner )
			{
				if( control_inner != control_iter->begin() )
				{
					name = name + ", " ;
				}
				name = name + ( *control_inner )->get_local_name() ;
			}
			if( control_iter != controls->begin() )
			{
				name = name + "; " ;
			}
		}
		wxButton* bind_button = new wxButton( scroll, wxID_ANY, name ) ;
		bind_button->SetClientData( iter->second ) ;
		bind_button->Bind( wxEVT_BUTTON, &mainFrame::on_button_clicked, this ) ;
		std::string section = iter->second->get_section() ;
		//button map already contains the section
		button_map.insert( { section, bind_button } ) ;
	}

	//Generate the sizers
	{
		std::string current_section = button_map.begin()->first ;
		wxBoxSizer* sizer = new wxBoxSizer( wxVERTICAL ) ;
		for( auto iter = button_map.begin() ; iter != button_map.end() ; ++iter )
		{
			if( current_section.compare( iter->first ) != 0 )
			{
				current_section = iter->first ;
				scroll_sizer->Add( sizer, 0, wxEXPAND, 5 ) ;
				sizer = new wxBoxSizer( wxVERTICAL ) ;
			}
			sizer->Add( iter->second, 0, wxALL, 5 ) ;
		}
		scroll_sizer->Add( sizer, 0, wxEXPAND, 5 ) ;
	}
	

	scroll->SetSizer( scroll_sizer );
	scroll->Layout();
	scroll_sizer->Fit( scroll );
	control_bar->Add( scroll, 1, wxEXPAND | wxALL, 5 );


	lower_bar->Add( control_bar, 3, wxEXPAND, 5 );

	//////////////////////////////////////////////

	//Control region
	wxBoxSizer* keyboard_area;
	keyboard_area = new wxBoxSizer( wxVERTICAL );

	wxNotebook* control_book = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	wxPanel* keyboard = new wxPanel( control_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL ) ;
	wxBoxSizer* cur_img;
	cur_img = new wxBoxSizer( wxVERTICAL );

	wxStaticBitmap* cur = new wxStaticBitmap( keyboard, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	cur_img->Add( cur, 0, wxALL, 5 );


	keyboard->SetSizer( cur_img );
	keyboard->Layout();
	cur_img->Fit( keyboard );
	control_book->AddPage( keyboard, wxT( "Keyboard" ), true );
	wxPanel* mouse = new wxPanel( control_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* cur_img1;
	cur_img1 = new wxBoxSizer( wxVERTICAL );

	wxStaticBitmap* cur1 = new wxStaticBitmap( mouse, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	cur_img1->Add( cur1, 0, wxALL, 5 );


	mouse->SetSizer( cur_img1 );
	mouse->Layout();
	cur_img1->Fit( mouse );
	control_book->AddPage( mouse, wxT( "Mouse" ), false );
	wxPanel* Controller = new wxPanel( control_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* cur_img2;
	cur_img2 = new wxBoxSizer( wxVERTICAL );

	wxStaticBitmap* cur2 = new wxStaticBitmap( Controller, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	cur_img2->Add( cur2, 0, wxALL, 5 );


	Controller->SetSizer( cur_img2 );
	Controller->Layout();
	cur_img2->Fit( Controller );
	control_book->AddPage( Controller, wxT( "Controller" ), false );

	keyboard_area->Add( control_book, 1, wxEXPAND | wxALL, 5 );


	lower_bar->Add( keyboard_area, 4, wxEXPAND, 5 );


	main_grid->Add( lower_bar, 3, wxEXPAND, 5 );


	this->SetSizer( main_grid );
	this->Layout();
	main_grid->Fit( this );

	this->Centre( wxBOTH );
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