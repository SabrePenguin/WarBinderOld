#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <SDL_system.h>
class KeyBind ;

class WXKeyInput : public wxDialog
{
public:
	WXKeyInput(wxWindow* parent, const wxString& name, KeyBind* keybind ) ;
	~WXKeyInput() ;
private:
	void start_addition( wxCommandEvent& event ) ;
	void onSize( wxCommandEvent& event ) ;
	SDL_Window* window ;
};

class WXReadIn : public wxDialog
{
public:
	WXReadIn( wxWindow* parent, const wxString& name, KeyBind* keybind ) ;
	~WXReadIn() ;
};