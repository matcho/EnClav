/* 
 * File:   EnClav.cpp
 * Author: mathias
 * 
 * Created on 13 mai 2010, 00:07
 *
 *
 *
 *
 * A FAIRE:
 * - écouter les événements Dbus pour savoir lorsqu'un clavier USB est connecté?
 *   (attention à la consommation de ressources si boucle)
 * - créer une classe JackMidi unique pour ouvrir plusieurs ports, détecter les
 *   ports, les connecter
 *
 *
 */

#include "EnClav.h"
#include "gui/Gui.h"
#include "carte/CarteClavier.h"
#include "sortie/SortieMIDI.h"

using namespace std;

// Emplacement par défaut des fichiers descripteurs de cartes de clavier
const char *EnClav::EMPLACEMENT_FICHIERS_CARTE = "/home/mathias/NetBeansProjects/EnClav/config/maps";

IMPLEMENT_APP(EnClav)

EnClav::EnClav() {

	this->clavs = new vector<Clavier*>();
	this->dc = new DetecteurClaviersProc();
}

EnClav::~EnClav() {
}

bool EnClav::OnInit() {

	cout << "coucou!" << endl;
	// Partie wxWidgets
	Gui* dialog = new Gui(this);
    dialog->Show();
    SetTopWindow(dialog);

	// Partie EnClav
	/*

	map<string,string>::iterator it;

	for (it = mapClav->begin (); it != mapClav->end (); ++it) {
		string dev = (*it).first;
		string name = (*it).second;
		cout << "Démarrage de la capture sur " << dev << " (" << name << ")" << endl;
		string jackName = "EnClav_" + name.substr(0,20);
		Clavier *c1 = new Clavier(dev, name, new CarteClavier(), new SortieMIDI(jackName.c_str()));
		clavs->push_back(c1);
		c1->start();
	}

	sleep(100);

	*/
    return true;
}

int EnClav::OnExit() {

	/*for (int j=0; j < this->clavs->size(); ++j) {
		if ((*this->clavs)[j] != 0) {
			cout << "++++ Interruption du clavier " << j << " ++++" << endl;
			(*this->clavs)[j]->cancel();
			(*this->clavs)[j]->closeClav();
		}
	}*/
	cout << "sortie propre" << endl;
}

void EnClav::DetectKbds(bool includePS2) {

	this->mapClav = this->dc->detect(includePS2);
}

/**
 * Retoune la liste des chemins absolus de fichiers descripteurs de carte présents
 * à l'emplacement par défaut
 */
vector<string> *EnClav::GetAvailableMaps() {

	vector<string> *descripteurs = new vector<string>();

	DIR *d = opendir(EMPLACEMENT_FICHIERS_CARTE);
	struct dirent *de = 0;

	if (d != NULL) {
		// Loop while not NULL
		while(de = readdir(d)) {
			if (de->d_name[0] != '.') {
				//string tmp = de->d_name;
				descripteurs->push_back(de->d_name);
				cout << "Fichier ajouté: " << de->d_name << endl;
			}
		}
		closedir(d);
	} else {
		cerr << "Erreur: impossible de lire le répertoire " << EMPLACEMENT_FICHIERS_CARTE << endl;
	}

	// Tri du vector par ordre alphabétique des string
	sort(descripteurs->begin(), descripteurs->end());

	return descripteurs;
}

Clavier *EnClav::CreateKbd(string dev, string name, string carte, string port) {

	string jackName = "EnClav_" + name.substr(0,20);
	Clavier *c = new Clavier(dev, name, new CarteClavier((EMPLACEMENT_FICHIERS_CARTE + string("/") + carte).c_str()), new SortieMIDI(jackName.c_str()));
	//this->clavs->push_back(c);

	return c;
}

/*void EnClav::DestroyKbd(string eventDev) {

	for (int j=0; j < this->clavs->size(); ++j) {
		if ((*this->clavs)[j] != 0) {
			if ((*this->clavs)[j]->getEventDev() == eventDev) {
				cout << "++++ Interruption du clavier " << j << "(" << eventDev << ") ++++" << endl;
				(*this->clavs)[j]->cancel();
				(*this->clavs)[j]->closeClav();
				delete (*this->clavs)[j];
			}
		}
	}
}*/