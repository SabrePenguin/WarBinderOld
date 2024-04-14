#ifndef WX_GUI_H
#define WX_GUI_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <memory>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/statbmp.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <string>

class KeyBind ;
class WXWrapper ;

class WXGui : public wxApp
{
public:
	/**
	 * @brief WarBinder implementation of wxApp
	 */
	WXGui() ;
	WXGui( WXWrapper* _wrapper ) ;
	/**
	 * @brief The main logic startup
	 * @return Success or failure
	 */
	virtual bool OnInit() ;
private:
	WXWrapper* wrapper ; /* Used for communication. Do not delete, as it's shared and making this shared causes issues */
};

class mainFrame : public wxFrame
{
public:
	mainFrame( const wxString& title, const wxPoint& pos, const wxSize& size, WXWrapper* wrapper );
private:
	void OnExit( wxCommandEvent& event );
	void OnAbout( wxCommandEvent& event );
	void create_bar() ;
	void on_button_clicked( wxCommandEvent& event ) ;
	wxDECLARE_EVENT_TABLE();
	WXWrapper* wrapper ; /* Used for communication. Do not delete, as it's shared and making this shared causes issues */
};

#endif //WXGUI_H