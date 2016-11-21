/* 
 * File:   CarteClavier.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 21:47
 */

#include "CarteClavier.h"

using namespace std;

// Valeur des modificateurs pour calculer le scancode composé
/*const int Clavier::MOD_LEFT_SHIFT = 128;
const int Clavier::MOD_RIGHT_SHIFT = 256;
const int Clavier::MOD_CAPS_LOCK = 512;
const int Clavier::MOD_LEFT_CTRL = 1024;
const int Clavier::MOD_RIGHT_CTRL = 2048;
const int Clavier::MOD_LEFT_ALT = 4096;
const int Clavier::MOD_ALT_GR = 8192;
const int Clavier::MOD_LEFT_WIN = 16384;
const int Clavier::MOD_RIGHT_WIN = 32768;
const int Clavier::MOD_NUM_LOCK = 65536;
const int Clavier::MOD_SCROLL_LOCK = 131072;*/

CarteClavier::CarteClavier() {

	this->init();
}

CarteClavier::CarteClavier(const CarteClavier& orig) {
}

/**
 * Construit un carte de clavier à partir d'un fichier de description
 */
CarteClavier::CarteClavier(const char *chemin) {

	this->init();
	this->loadMap(chemin);
}

/**
 * Initialisation à effectuer dans les différents constructeurs
 */
void CarteClavier::init() {

	this->tab = new int[262144];
	this->noteMods = new int[128];
	this->actionMods = new int[128];

	// Tous les modificateurs inactifs par défaut
	for (int i=0; i < 128; ++i) {
		noteMods[i] = 0;
		actionMods[i] = 0;
	}

	// Carte moisie de test
	for (int i=0; i < 128; ++i) {
		tab[i] = i;
	}
}

/**
 * Recharge les paramètres par défaut de la carte
 */
void CarteClavier::resetMap() {

	this->init();
}

/**
 * Lit un fichier de description de carte et charge les valeurs de 'tab', 'noteMods' et 'actionMods'
 */
void CarteClavier::loadMap(const char* chemin) {

	//map<string,string> *carte = new map<string,string>();
	string bloc, blocName;
	vector<string> *blocs, *lines;

	ifstream mf(chemin, ios::in);

	if (mf) {
		cout << "Chargement du fichier de carte " << chemin << endl;
		// Lecture du contenu du fichier
		stringstream buffer;
		buffer << mf.rdbuf();

		// Découpage par bloc de commandes
		blocs = EnUtil::split(buffer.str(),"\n\n",true);

		for (int i=0; i<blocs->size(); ++i) {
			bloc = blocs->at(i);
			//cout << "BLOC:\n" << bloc << endl << endl;
			// Découpage par lignes
			lines = EnUtil::split(bloc,"\n",true);

			// Récupération du nom du bloc
			blocName = lines->at(0);
			//cout << "BlocName: " << blocName << endl;

			if (blocName.compare("[ACTIONS]") == 0) {
				//cout << "Bloc Actions!" << endl;
				for (int j=1; j < lines->size(); ++j) {
					//cout << "++ action[" << j << "] : " << lines->at(j) << endl;
					if ((lines->at(j)[0] != '\0') && (lines->at(j)[0] != '#')) {
						string *pair = this->getInstruction(lines->at(j));
						//cout << "A:" << pair[0] << ", B:" << pair[1] << endl;
						this->defineAction(atoi(pair[0].c_str()), pair[1]);
					}

				}
			} else if (blocName.compare("[MODS]") == 0) {
				//cout << "Bloc Mods!" << endl;
				for (int j=1; j < lines->size(); ++j) {
					//cout << "++ mods[" << j << "] : " << lines->at(j) << endl;
					if ((lines->at(j)[0] != '\0') && (lines->at(j)[0] != '#')) {
						string *pair = this->getInstruction(lines->at(j));
						// Affectation du modificateur de notes
						this->noteMods[atoi(pair[0].c_str())] = atoi(pair[1].c_str());
					}
				}
			} else if (blocName.compare("[NOTES]") == 0) {
				//cout << "Bloc Notes!" << endl;
				for (int j=1; j < lines->size(); ++j) {
					//cout << "ligne: " << lines->at(j) << ", char: " << lines->at(j)[0] << endl;
					//cout << "++ notes[" << j << "] : " << lines->at(j) << endl;
					if ((lines->at(j)[0] != '\0') && (lines->at(j)[0] != '#')) {
						string *pair = this->getInstruction(lines->at(j));
						// Affectation de la note à la carte
						this->tab[atoi(pair[0].c_str())] = atoi(pair[1].c_str());
					}
				}
			} else {
				cerr << "Type de bloc inconnu!" << endl;
			}
		}
		// Fermeture du fichier
		mf.close();
	} else {
		cerr << "Erreur: impossible de lire le fichier " << chemin << endl;
	}
}

/**
 * Découpe une ligne d'instruction du descripteur de carte et retourne la paire
 * de string de part et d'autre du séparateur ':'
 */
string *CarteClavier::getInstruction(string instLine) {

	vector<string> *inst = EnUtil::split(EnUtil::split(instLine,"\t",false)->at(0),":",true);

	string *pair = new string[2];
	pair[0] = inst->at(0);
	pair[1] = inst->at(1);

	return pair;
}

/**
 * Affecte à l'index reçu la valeur entière de l'enum correspondant à l'action reçue
 */
void CarteClavier::defineAction(int index, string action) {

	if (action.compare("MUTE") == 0)
		this->actionMods[index] = AC_MUTE;
	else if (action.compare("UNMUTE") == 0)
		this->actionMods[index] = AC_UNMUTE;
	else if (action.compare("BANK+") == 0)
		this->actionMods[index] = AC_BANK_P;
	else if (action.compare("BANK-") == 0)
		this->actionMods[index] = AC_BANK_M;
	else if (action.compare("BANK0") == 0)
		this->actionMods[index] = AC_BANK_0;
	else if (action.compare("PROGRAM+") == 0)
		this->actionMods[index] = AC_PROGRAM_P;
	else if (action.compare("PROGRAM-") == 0)
		this->actionMods[index] = AC_PROGRAM_M;
	else if (action.compare("PROGRAM0") == 0)
		this->actionMods[index] = AC_PROGRAM_0;
	else if (action.compare("VELOCITY+") == 0)
		this->actionMods[index] = AC_VELOCITY_P;
	else if (action.compare("VELOCITY-") == 0)
		this->actionMods[index] = AC_VELOCITY_M;
	else if (action.compare("VELOCITY0") == 0)
		this->actionMods[index] = AC_VELOCITY_0;
	else if (action.compare("NOTESOFF") == 0)
		this->actionMods[index] = AC_NOTES_OFF;
	else
		this->actionMods[index] = -1;
}

int CarteClavier::getNote(int scancode) {

	cout << "SC: " << scancode << " (taille: 262144)" << endl;
	return this->tab[scancode];
}

int CarteClavier::getNoteMod(int scancode) {

	return this->noteMods[scancode];
}

int CarteClavier::getActionMod(int scancode) {

	return this->actionMods[scancode];
}

CarteClavier::~CarteClavier() {
}