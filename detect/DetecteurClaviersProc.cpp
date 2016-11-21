/* 
 * File:   DetecteurClaviersProc.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 00:09
 */

#include "DetecteurClaviersProc.h"
#include "../util/EnUtil.h"

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

const char *DetecteurClaviersProc::PROC_BUS_INPUT_DEVICES = "/proc/bus/input/devices";

DetecteurClaviersProc::DetecteurClaviersProc() {
}

DetecteurClaviersProc::DetecteurClaviersProc(const DetecteurClaviersProc& orig) {
}

map<string,string> *DetecteurClaviersProc::detect(bool includePS2) {

	map<string,string> *carte = new map<string,string>();
	string dev, devName, devPhysical, devHandlers, eventDev;
	vector<string> *devs, *lines;
	bool cond;

	ifstream pbid(PROC_BUS_INPUT_DEVICES, ios::in);

	if (pbid) {
		// Lecture du contenu du fichier
		stringstream buffer;
		buffer << pbid.rdbuf();

		// Découpage par périphérique
		devs = EnUtil::split(buffer.str(),"\n\n",false);

		for (int i=0; i<devs->size(); ++i) {
			dev = devs->at(i);
			lines = EnUtil::split(dev,"\n",true);
			// Récupération des lignes d'infos
			devName = lines->at(1);
			devName = devName.substr(9,devName.length()-10);
			devPhysical = lines->at(2);
			devHandlers = lines->at(5);
			// Calcul de la condition
			//cond = devHandlers.contains("kbd"); // marche pas :-(
			cond = (devName.find("eyboard") != string::npos);
			if (! includePS2) {
				cond = (cond && (devPhysical.find("usb") != string::npos));
			}
			// Extraction des liens considérés
			if (cond) {
				// Récupération du périphérique eventX
				eventDev = "/dev/input/" + devHandlers.substr(devHandlers.length()-7,6);
				// Conservation de la première occurence du nom?
				if (! EnUtil::stringMapContains(carte, devName)) {
					(*carte)[eventDev] = devName;
				}
			}
		}

		// Fermeture du fichier
		pbid.close();
	} else {
		cerr << "Erreur: impossible de lire le fichier " << PROC_BUS_INPUT_DEVICES << endl;
	}

	return carte;
}

DetecteurClaviersProc::~DetecteurClaviersProc() {
}