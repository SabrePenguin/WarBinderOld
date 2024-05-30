#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class KeyBind ;

class WXKeyInput : public wxDialog
{
public:
	WXKeyInput(wxWindow* parent, const wxString& name, KeyBind* keybind ) ;
};