/* 
 * File:   CarteClavier.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 21:47
 */

#ifndef _CARTECLAVIER_H
#define	_CARTECLAVIER_H

#include "../util/EnUtil.h"

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

class CarteClavier {

public:
	// Modificateurs pour calculer le scancode composé
	/*static const int MOD_LEFT_SHIFT;
	static const int MOD_RIGHT_SHIFT;
	static const int MOD_CAPS_LOCK;
	static const int MOD_LEFT_CTRL;
	static const int MOD_RIGHT_CTRL;
	static const int MOD_LEFT_ALT;
	static const int MOD_ALT_GR;
	static const int MOD_LEFT_WIN;
	static const int MOD_RIGHT_WIN;
	static const int MOD_NUM_LOCK;
	static const int MOD_SCROLL_LOCK;*/

	CarteClavier();
	CarteClavier(const CarteClavier& orig);
	CarteClavier(const char *chemin);

	void resetMap();
	void loadMap(const char *chemin);

	int getNote(int scancode);
	int getNoteMod(int scancode);
	int getActionMod(int scancode);

	// Énumération des actions hors notes
	enum actions_carte_t {
		AC_MUTE,
		AC_UNMUTE,
		AC_BANK_P,
		AC_BANK_M,
		AC_BANK_0,
		AC_PROGRAM_P,
		AC_PROGRAM_M,
		AC_PROGRAM_0,
		AC_VELOCITY_P,
		AC_VELOCITY_M,
		AC_VELOCITY_0,
		AC_NOTES_OFF
	};

	virtual ~CarteClavier();
private:
	void init();
	string *getInstruction(string instLine);
	void defineAction(int index, string action);
	int *tab;
	int *noteMods;
	int *actionMods;
};

#endif	/* _CARTECLAVIER_H */