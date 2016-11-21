///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 17 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "EnClavGuiBase.h"

///////////////////////////////////////////////////////////////////////////

EnClavGuiBase::EnClavGuiBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 238, 238, 238 ) );
	
	barreMenu = new wxMenuBar( 0 );
	mFichier = new wxMenu();
	wxMenuItem* miQuitter;
	miQuitter = new wxMenuItem( mFichier, wxID_ANY, wxString( wxT("Quitter") ) , wxEmptyString, wxITEM_NORMAL );
	mFichier->Append( miQuitter );
	
	barreMenu->Append( mFichier, wxT("Fichier") );
	
	mEdition = new wxMenu();
	wxMenuItem* miPreferences;
	miPreferences = new wxMenuItem( mEdition, wxID_ANY, wxString( wxT("Préférences") ) , wxEmptyString, wxITEM_NORMAL );
	mEdition->Append( miPreferences );
	
	barreMenu->Append( mEdition, wxT("Édition") );
	
	mAide = new wxMenu();
	wxMenuItem* miApropos;
	miApropos = new wxMenuItem( mAide, wxID_ANY, wxString( wxT("À propos d'EnClav") ) , wxEmptyString, wxITEM_NORMAL );
	mAide->Append( miApropos );
	
	barreMenu->Append( mAide, wxT("?") );
	
	this->SetMenuBar( barreMenu );
	
	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY ); 
	butRefreshJack = new wxButton( m_toolBar1, wxID_BUTTON_REFRESH_JACK, wxT("Actualiser les ports Jack "), wxDefaultPosition, wxDefaultSize, 0 );
	butRefreshJack->SetToolTip( wxT("Détecter la liste des ports de sortie Jack disponibles") );
	
	m_toolBar1->AddControl( butRefreshJack );
	m_toolBar1->AddSeparator();
	cbInclurePS2 = new wxCheckBox( m_toolBar1, wxID_CB_INCLUDE_PS2, wxT("Inclure PS2"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
	cbInclurePS2->SetValue(true);
	
	cbInclurePS2->SetToolTip( wxT("Inclure les claviers PS2 dans la détection") );
	
	m_toolBar1->AddControl( cbInclurePS2 );
	butDetectCl = new wxButton( m_toolBar1, wxID_BUTTON_DETECT_CL, wxT("Détecter les claviers "), wxDefaultPosition, wxDefaultSize, 0 );
	butDetectCl->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	butDetectCl->SetToolTip( wxT("Détecter les claviers matériels connectés") );
	
	m_toolBar1->AddControl( butDetectCl );
	m_toolBar1->AddSeparator();
	lbVelocite = new wxStaticText( m_toolBar1, wxID_ANY, wxT("Vélocité"), wxDefaultPosition, wxDefaultSize, 0 );
	lbVelocite->Wrap( -1 );
	m_toolBar1->AddControl( lbVelocite );
	slGlobalVelocity = new wxSlider( m_toolBar1, wxID_SLIDER_GLOBAL_VELOCITY, 64, 0, 127, wxDefaultPosition, wxSize( 200,-1 ), wxSL_HORIZONTAL );
	slGlobalVelocity->SetToolTip( wxT("Ajuster le volume (vélocité) global") );
	
	m_toolBar1->AddControl( slGlobalVelocity );
	m_toolBar1->Realize();
	
	wxBoxSizer* lytMain;
	lytMain = new wxBoxSizer( wxVERTICAL );
	
	scrListeclaviers = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	scrListeclaviers->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	scrListeclaviers->SetSizer( bSizer3 );
	scrListeclaviers->Layout();
	bSizer3->Fit( scrListeclaviers );
	lytMain->Add( scrListeclaviers, 1, wxALL|wxEXPAND, 5 );
	
	this->SetSizer( lytMain );
	this->Layout();
	barreStatut = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	// Connect Events
	this->Connect( miQuitter->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuQuitter ) );
	this->Connect( miPreferences->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuPreferences ) );
	this->Connect( miApropos->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuApropos ) );
	butRefreshJack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnButtonRefreshJackClick ), NULL, this );
	cbInclurePS2->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnCbIncludePS2Check ), NULL, this );
	butDetectCl->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnButtonDetectClClick ), NULL, this );
}

EnClavGuiBase::~EnClavGuiBase()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuQuitter ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuPreferences ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EnClavGuiBase::OnMenuApropos ) );
	butRefreshJack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnButtonRefreshJackClick ), NULL, this );
	cbInclurePS2->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnCbIncludePS2Check ), NULL, this );
	butDetectCl->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavGuiBase::OnButtonDetectClClick ), NULL, this );
}

EnClavAboutBase::EnClavAboutBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	html_page = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	bSizer4->Add( html_page, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	button_fermer = new wxButton( this, wxID_ANY, wxT("Fermer"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( button_fermer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	this->SetSizer( bSizer4 );
	this->Layout();

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EnClavAboutBase::OnClose ) );
	button_fermer->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavAboutBase::OnButtonFermerClick ), NULL, this );
}

EnClavAboutBase::~EnClavAboutBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( EnClavAboutBase::OnClose ) );
	button_fermer->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EnClavAboutBase::OnButtonFermerClick ), NULL, this );
}
