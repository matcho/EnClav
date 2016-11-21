#include "EnClavAbout.h"

const char *EnClavAbout::EMPLACEMENT_ABOUT_HTML = "/home/mathias/NetBeansProjects/EnClav/config/about.html";

EnClavAbout::EnClavAbout( wxWindow* parent )
:
EnClavAboutBase( parent ) {

	wxString chem = wxString(EMPLACEMENT_ABOUT_HTML, wxConvUTF8);
	this->html_page->LoadFile(wxFileName(/*AppData()->GetApplicationPath() + wxFILE_SEP_PATH + wxT("resources/about.html")*/chem));
}

void EnClavAbout::OnClose( wxCloseEvent& event ) {
	this->Close();
}

void EnClavAbout::OnButtonFermerClick( wxCommandEvent& event ) {
	this->Close();
}