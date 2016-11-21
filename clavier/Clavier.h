/* 
 * File:   Clavier.h
 * Author: mathias
 *
 * Created on 7 mai 2010, 23:18
 */

#ifndef _CLAVIER_H
#define	_CLAVIER_H

#include <string>
#include <OpenThreads/Thread>

#include "../carte/CarteClavier.h"
#include "../sortie/SortieMIDI.h"
#include "KbdScan.h"

using namespace std;

class Clavier : public OpenThreads::Thread {

public:
	// Constantes des scancodes pour un clavier 105 touches bateau
	static const int D105_ERROR;
	static const int D105_ESC;
	static const int D105_1;
	static const int D105_2;
	static const int D105_3;
	static const int D105_4;
	static const int D105_5;
	static const int D105_6;
	static const int D105_7;
	static const int D105_8;
	static const int D105_9;
	static const int D105_0;
	static const int D105_DEG;
	static const int D105_PLUS;
	static const int D105_BACKSPACE;
	static const int D105_TAB;
	static const int D105_A;
	static const int D105_Z;
	static const int D105_E;
	static const int D105_R;
	static const int D105_T;
	static const int D105_Y;
	static const int D105_U;
	static const int D105_I;
	static const int D105_O;
	static const int D105_P;
	static const int D105_CIRC;
	static const int D105_DOLLAR;
	static const int D105_RETURN;
	static const int D105_LEFT_CTRL;
	static const int D105_Q;
	static const int D105_S;
	static const int D105_D;
	static const int D105_F;
	static const int D105_G;
	static const int D105_H;
	static const int D105_J;
	static const int D105_K;
	static const int D105_L;
	static const int D105_M;
	static const int D105_UGRAVE;
	static const int D105_SQUARE;
	static const int D105_LEFT_SHIFT;
	static const int D105_STAR;
	static const int D105_W;
	static const int D105_X;
	static const int D105_C;
	static const int D105_V;
	static const int D105_B;
	static const int D105_N;
	static const int D105_COMMA;
	static const int D105_SEMICOLON;
	static const int D105_COLON;
	static const int D105_EXCLAM;
	static const int D105_RIGHT_SHIFT;
	static const int D105_KP_STAR;
	static const int D105_LEFT_ALT;
	static const int D105_SPACE;
	static const int D105_CAPS_LOCK;
	static const int D105_F1;
	static const int D105_F2;
	static const int D105_F3;
	static const int D105_F4;
	static const int D105_F5;
	static const int D105_F6;
	static const int D105_F7;
	static const int D105_F8;
	static const int D105_F9;
	static const int D105_F10;
	static const int D105_NUM_LOCK;
	static const int D105_SCROLL_LOCK;
	static const int D105_KP_7;
	static const int D105_KP_8;
	static const int D105_KP_9;
	static const int D105_KP_MINUS;
	static const int D105_KP_4;
	static const int D105_KP_5;
	static const int D105_KP_6;
	static const int D105_KP_PLUS;
	static const int D105_KP_1;
	static const int D105_KP_2;
	static const int D105_KP_3;
	static const int D105_KP_0;
	static const int D105_KP_DOT;
	static const int D105_INF_SUP;
	static const int D105_F11;
	static const int D105_F12;
	static const int D105_KP_RETURN;
	static const int D105_RIGHT_CTRL;
	static const int D105_KP_SLASH;
	static const int D105_PRINT_SCREEN;
	static const int D105_ALT_GR;
	static const int D105_ORIGIN;
	static const int D105_AR_UP;
	static const int D105_P_PAGE;
	static const int D105_AR_LEFT;
	static const int D105_AR_RIGHT;
	static const int D105_END;
	static const int D105_AR_DOWN;
	static const int D105_N_PAGE;
	static const int D105_INSERT;
	static const int D105_DEL;
	static const int D105_PAUSE;
	static const int D105_LEFT_WIN;
	static const int D105_RIGHT_WIN;
	static const int D105_CONTEXT;

	Clavier();
	Clavier(const Clavier& orig);
	Clavier(string eventDev);
	Clavier(string eventDev, string devName, CarteClavier *carte, SortieMIDI *sortie);

	virtual void run();
	int calculScancode(int code);
	void joueNote(int intCode, int intValue);
	void noteOffsetsAndActions(int intValue, int intCode);
	int mlog(int mod);
	void disptime(long t1, long t2, string mess);
	void closeClav();

	string getDevName() const {
		return devName;
	}

	string getEventDev() const {
		return eventDev;
	}

	CarteClavier* getCarte() const {
		return carte;
	}

	KbdScan* getKs() const {
		return ks;
	}

	SortieMIDI* getSortie() const {
		return sortie;
	}

	virtual ~Clavier();
private:
	string devName;
	string eventDev;
	CarteClavier *carte;
	SortieMIDI *sortie;
	KbdScan *ks;
	int noteOffset;

	/*short ModLeftShiftOn;
	short ModRightShiftOn;
	short ModLeftCtrlOn;
	short ModRightCtrlOn;
	short ModLeftAltOn;
	short ModAltGrOn;
	short ModLeftWinOn;
	short ModRightWinOn;*/
	short ModCapsLockOn;
	short ModNumLockOn;
	short ModScrollLockOn;
};

#endif	/* _CLAVIER_H */

