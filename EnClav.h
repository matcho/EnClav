/* 
 * File:   EnClav.h
 * Author: mathias
 *
 * Created on 13 mai 2010, 00:07
 */

#ifndef _ENCLAV_H
#define	_ENCLAV_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include <wx/wx.h>
#include <dirent.h>

#include "clavier/Clavier.h"
#include "detect/DetecteurClaviersProc.h"

using namespace std;

class EnClav : public wxApp {

public:
	EnClav();
	virtual ~EnClav();
	virtual bool OnInit();
	virtual int OnExit();

	static const char *EMPLACEMENT_FICHIERS_CARTE;

	void DetectKbds(bool includePS2);
	vector<string> *GetAvailableMaps();
	Clavier *CreateKbd(string dev, string name, string carte = "", string port = "");
	//void DestroyKbd(string eventDev);

	vector<Clavier*> *clavs;
	DetecteurClaviersProc *dc;
	map<string,string> *mapClav;
};

DECLARE_APP(EnClav)

#endif	/* _ENCLAV_H */