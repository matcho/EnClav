///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __EnClavGuiBase__
#define __EnClavGuiBase__

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
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_BUTTON_REFRESH_JACK 1000
#define wxID_CB_INCLUDE_PS2 1001
#define wxID_BUTTON_DETECT_CL 1002
#define wxID_SLIDER_GLOBAL_VELOCITY 1003

///////////////////////////////////////////////////////////////////////////////
/// Class EnClavGuiBase
///////////////////////////////////////////////////////////////////////////////
class EnClavGuiBase : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* barreMenu;
		wxMenu* mFichier;
		wxMenu* mEdition;
		wxMenu* mAide;
		wxToolBar* m_toolBar1;
		wxButton* butRefreshJack;
		wxCheckBox* cbInclurePS2;
		wxButton* butDetectCl;
		wxStaticText* lbVelocite;
		wxSlider* slGlobalVelocity;
		wxScrolledWindow* scrListeclaviers;
		wxStatusBar* barreStatut;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnMenuQuitter( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMenuPreferences( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnMenuApropos( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnButtonRefreshJackClick( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnCbIncludePS2Check( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnButtonDetectClClick( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		EnClavGuiBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("EnClav GUI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 807,371 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~EnClavGuiBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class EnClavAboutBase
///////////////////////////////////////////////////////////////////////////////
class EnClavAboutBase : public wxDialog 
{
	private:
	
	protected:
		wxHtmlWindow* html_page;
		wxButton* button_fermer;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnButtonFermerClick( wxCommandEvent& event ){ event.Skip(); }
		
	
	public:
		EnClavAboutBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("À propos d'EnClav"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,400 ), long style = wxDEFAULT_DIALOG_STYLE );
		~EnClavAboutBase();
	
};

#endif //__EnClavGuiBase__
