/* 
 * File:   BarreClavier.cpp
 * Author: mathias
 * 
 * Created on 15 mai 2010, 13:24
 */

#include "BarreClavier.h"

using namespace std;

BarreClavier::BarreClavier(
		wxWindow *parent,
		string clavTitle,
		string devName,
		EnClav *app
	) : wxToolBar(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL) {

	// Attributs
	this->clavTitle = clavTitle;
	this->devName = devName;
	this->app = app;
	this->bank = 0;
	this->prog = 0;
	this->capturing = false;
	this->velocity = 90;
	this->carte = "";
	this->outPort = "";
	this->c = 0;

	wxString lctt = wxString(devName.c_str(), wxConvUTF8);
	wxString lcte = wxString(clavTitle.c_str(), wxConvUTF8);

	// Construction wxWidgets
	this->start_button = new wxButton( this, wxID_ANY, wxT("▶"), wxDefaultPosition, wxSize( 36,-1 ), 0 );
	start_button->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	start_button->SetToolTip( wxT("Démarrer la capture") );
	this->AddControl( start_button );
	this->AddSeparator();

	this->label_clav = new wxStaticText( this, wxID_ANY, lcte, wxPoint( -1,-1 ), wxSize(220,-1), 0 );
	label_clav->Wrap( -1 );
	label_clav->SetToolTip(lctt);
	this->AddControl( label_clav );
	this->AddSeparator();

	this->slider_velo = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 100,-1 ), wxSL_HORIZONTAL );
	slider_velo->SetToolTip(wxT("Volume relatif") );
	this->AddControl( slider_velo );
	this->AddSeparator();

	wxArrayString select_carteChoices;
	this->select_carte = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, select_carteChoices, 0 );
	select_carte->SetSelection( 0 );
	select_carte->SetToolTip( wxT("Carte de clavier") );
	select_carte->SetSize(140, select_carte->GetSize().y);
	this->AddControl( select_carte );
	this->AddSeparator();

	this->label_pg = new wxStaticText( this, wxID_ANY, wxT("Pg "), wxDefaultPosition, wxDefaultSize, 0 );
	label_pg->Wrap( -1 );
	this->AddControl( label_pg );
	this->spin_pg = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	spin_pg->SetToolTip( wxT("Program (MIDI)") );
	this->AddControl( spin_pg );
	this->AddSeparator();

	this->label_bk = new wxStaticText( this, wxID_ANY, wxT("Bk "), wxDefaultPosition, wxDefaultSize, 0 );
	label_bk->Wrap( -1 );
	this->AddControl( label_bk );
	this->spin_bk = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 10, 0 );
	spin_bk->SetToolTip( wxT("Bank (MIDI)") );
	this->AddControl( spin_bk );
	this->AddSeparator();

	wxArrayString select_portChoices;
	this->select_port = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, select_portChoices, 0 );
	select_port->SetSelection( 0 );
	select_port->SetToolTip( wxT("Port de sortie Jack") );

	this->AddControl( select_port );
	this->Realize();

	// Connect Events
	start_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BarreClavier::OnButtonStartCaptureClick ), NULL, this );
	select_carte->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BarreClavier::OnChoiceCarteSelected ), NULL, this );
	select_port->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BarreClavier::OnChoicePortSelected ), NULL, this );
	spin_pg->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler( BarreClavier::OnSpinPgUpdated ), NULL, this );
	spin_bk->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler( BarreClavier::OnSpinBkUpdated ), NULL, this );
}

// Event handlers implementations
void BarreClavier::OnButtonStartCaptureClick( wxCommandEvent& event ) {

	if (! this->capturing) {
		cout << "Start Capture" << endl;
		// Créer un clavier
		string map = std::string(this->select_carte->GetStringSelection().mb_str(wxConvUTF8));
		this->c = this->app->CreateKbd(this->devName, this->clavTitle, map);
		// Lui définir une sortie Jack et la carte choisie
		// Démarrer la capture
		this->c->start();
		// Envoyer les evts Jack de connexion au port, de changement de Pg, Bk
		this->UpdatePgBk();
		// Griser les widgets
		//this->GriserWidgets();
		// Modifier l'apparence du bouton
		this->start_button->SetToolTip(wxT("Stopper la capture"));
		this->start_button->SetLabel(wxT("■"));
		// Capture en cours!
		this->capturing = true;
	} else {
		cout << "Stop Capture" << endl;
		// Stopper le clavier
		this->c->cancel();
		// Dézinguage du Clavier
		//this->app->DestroyKbd(this->c->getEventDev());
		delete this->c;
		// Dégriser les widgets
		//this->DegriserWidgets();
		// Modifier l'apparence du bouton
		this->start_button->SetToolTip(wxT("Démarrer la capture"));
		this->start_button->SetLabel(wxT("▶"));
		// Capture terminée!
		this->capturing = false;
	}
}

void BarreClavier::OnChoiceCarteSelected( wxCommandEvent& event ) {

	cout << "Choice Carte" << endl;
}

void BarreClavier::OnChoicePortSelected( wxCommandEvent& event ) {

	cout << "Choice Port" << endl;
}

void BarreClavier::OnSpinPgUpdated( wxCommandEvent& event ) {

	cout << "Spin Pg: " << this->spin_pg->GetValue() << endl;
	this->prog = this->spin_pg->GetValue();
	this->UpdatePgBk();
}

void BarreClavier::OnSpinBkUpdated( wxCommandEvent& event ) {

	cout << "Spin Bk: " << this->spin_bk->GetValue() << endl;
	this->bank = this->spin_bk->GetValue();
	this->UpdatePgBk();

}

void BarreClavier::UpdatePgBk() {

	cout << "updating ports/bank" << endl;
	if (this->c != 0) {
		this->c->getSortie()->pgChange(this->prog, this->bank);
	}
}

void BarreClavier::SetMapList(vector<string> *maps) {

	for (int i=0; i < maps->size(); ++i) {
		wxString opt = wxString(maps->at(i).c_str(), wxConvUTF8);
		this->select_carte->Append(opt);
	}
	//cout << "nb options: " << this->select_carte->GetCount() << endl;
	if (this->select_carte->GetCount() > 0) {
		this->select_carte->SetSelection(0);
	}
}

void BarreClavier::GriserWidgets() {

	this->select_carte->Disable();
	this->select_port->Disable();
	//this->spin_bk->Disable();
	//this->spin_pg->Disable();
	this->slider_velo->Disable();
}

void BarreClavier::DegriserWidgets() {

	this->select_carte->Enable();
	this->select_port->Enable();
	//this->spin_bk->Enable();
	//this->spin_pg->Enable();
	this->slider_velo->Enable();
}

BarreClavier::~BarreClavier() {

	// Disconnect Events
	start_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BarreClavier::OnButtonStartCaptureClick ), NULL, this );
	select_carte->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BarreClavier::OnChoiceCarteSelected ), NULL, this );
	select_port->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( BarreClavier::OnChoicePortSelected ), NULL, this );
	spin_pg->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler( BarreClavier::OnSpinPgUpdated ), NULL, this );
	spin_bk->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxCommandEventHandler( BarreClavier::OnSpinBkUpdated ), NULL, this );
}
