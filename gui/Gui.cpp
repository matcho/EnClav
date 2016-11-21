/* 
 * File:   Gui.cpp
 * Author: mathias
 * 
 * Created on 14 mai 2010, 12:49
 */

#include "Gui.h"

Gui::Gui(EnClav *app) : EnClavGui((wxWindow*)0) {

	this->app = app;
	this->mapBarClav = new map<string,BarreClavier*>();
	this->incPS2 = true;
	this->globalVelocity = 90;
	// Détection des cartes de clavier
	this->avMaps = this->app->GetAvailableMaps();
}

void Gui::OnMenuQuitter( wxCommandEvent& event ) {
	this->app->Exit();
}

void Gui::OnMenuPreferences( wxCommandEvent& event ) {
	cout << "Menu Préférences!" << endl;
}

void Gui::OnMenuApropos( wxCommandEvent& event ) {
	cout << "Menu À Propos!" << endl;
	EnClavAbout *ea = new EnClavAbout(this);
	//ea->CenterOnParent();
	ea->ShowModal();
	ea->Destroy();
}

void Gui::OnButtonRefreshJackClick( wxCommandEvent& event ) {
	// TODO: Implement OnButtonRefreshJackClick
	cout << "Refresh Jack GUI !" << endl;
}

void Gui::OnCbIncludePS2Check( wxCommandEvent& event ) {
	// TODO: Implement OnCbIncludePS2Check
	cout << "Include PS2 GUI !" << endl;
	this->incPS2 = this->cbInclurePS2->IsChecked();
}

/**
 * Détection des claviers. TODO: conserver les BarreClavier déjà en place lors
 * du rafraîchissement
 *
 */
void Gui::OnButtonDetectClClick( wxCommandEvent& event ) {
	// Détecter les claviers
	this->app->DetectKbds(this->incPS2);

	// Vider le sizer
	this->scrListeclaviers->GetSizer()->Clear(true);
	// Vider la carte de barres claviers
	this->mapBarClav->clear();

	// Créer et ajouter les barre d'outils une par une au sizer et à la carte
	map<string,string>::iterator it;
	for (it = this->app->mapClav->begin (); it != this->app->mapClav->end (); ++it) {
		string dev = (*it).first;
		string name = (*it).second;
		cout << "Ajout du clavier " << dev << " (" << name << ")" << endl;
		// Nom du clavier (tronqué à 30 caractères)
		string clavName;
		if (name.size() > 30) {
			clavName = name.substr(0,28).append("...");
		} else {
			clavName = name.substr(0,30);
		}
		// Création de la barre d'outils clavier
		BarreClavier *barClav =  new BarreClavier(this->scrListeclaviers, clavName, dev, this->app);
		barClav->SetMapList(this->avMaps);
		// Ajout au sizer
		this->scrListeclaviers->GetSizer()->Add(barClav, 0, wxEXPAND, 5);
		// TODO Rafraîchir l'affichage!!

		// Ajout à la carte
		(* this->mapBarClav) [dev] = barClav;
	}

	// Ajustement de la taille de la fenêtre principale
	this->Layout();
}

BarreClavier *Gui::CreerBarreClavier() {

	return 0;
}

Gui::~Gui() {
}