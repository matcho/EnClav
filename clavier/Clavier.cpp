/* 
 * File:   Clavier.cpp
 * Author: mathias
 * 
 * Created on 7 mai 2010, 23:18
 */

#include "Clavier.h"
#include "KbdScan.h"
#include "../disposition/Disposition105.h"

#include <OpenThreads/Thread>
#include <cmath>
#include <iostream>

// Constantes des scancodes pour un clavier 105 touches bateau
const int Clavier::D105_ERROR = 0;
const int Clavier::D105_ESC = 1;
const int Clavier::D105_1 = 2;
const int Clavier::D105_2 = 3;
const int Clavier::D105_3 = 4;
const int Clavier::D105_4 = 5;
const int Clavier::D105_5 = 6;
const int Clavier::D105_6 = 7;
const int Clavier::D105_7 = 8;
const int Clavier::D105_8 = 9;
const int Clavier::D105_9 = 10;
const int Clavier::D105_0 = 11;
const int Clavier::D105_DEG = 12;
const int Clavier::D105_PLUS = 13;
const int Clavier::D105_BACKSPACE = 14;
const int Clavier::D105_TAB = 15;
const int Clavier::D105_A = 16;
const int Clavier::D105_Z = 17;
const int Clavier::D105_E = 18;
const int Clavier::D105_R = 19;
const int Clavier::D105_T = 20;
const int Clavier::D105_Y = 21;
const int Clavier::D105_U = 22;
const int Clavier::D105_I = 23;
const int Clavier::D105_O = 24;
const int Clavier::D105_P = 25;
const int Clavier::D105_CIRC = 26;
const int Clavier::D105_DOLLAR = 27;
const int Clavier::D105_RETURN = 28;
const int Clavier::D105_LEFT_CTRL = 29;
const int Clavier::D105_Q = 30;
const int Clavier::D105_S = 31;
const int Clavier::D105_D = 32;
const int Clavier::D105_F = 33;
const int Clavier::D105_G = 34;
const int Clavier::D105_H = 35;
const int Clavier::D105_J = 36;
const int Clavier::D105_K = 37;
const int Clavier::D105_L = 38;
const int Clavier::D105_M = 39;
const int Clavier::D105_UGRAVE = 40;
const int Clavier::D105_SQUARE = 41;
const int Clavier::D105_LEFT_SHIFT = 42;
const int Clavier::D105_STAR = 43;
const int Clavier::D105_W = 44;
const int Clavier::D105_X = 45;
const int Clavier::D105_C = 46;
const int Clavier::D105_V = 47;
const int Clavier::D105_B = 48;
const int Clavier::D105_N = 49;
const int Clavier::D105_COMMA = 50;
const int Clavier::D105_SEMICOLON = 51;
const int Clavier::D105_COLON = 52;
const int Clavier::D105_EXCLAM = 53;
const int Clavier::D105_RIGHT_SHIFT = 54;
const int Clavier::D105_KP_STAR = 55;
const int Clavier::D105_LEFT_ALT = 56;
const int Clavier::D105_SPACE = 57;
const int Clavier::D105_CAPS_LOCK = 58;
const int Clavier::D105_F1 = 59;
const int Clavier::D105_F2 = 60;
const int Clavier::D105_F3 = 61;
const int Clavier::D105_F4 = 62;
const int Clavier::D105_F5 = 63;
const int Clavier::D105_F6 = 64;
const int Clavier::D105_F7 = 65;
const int Clavier::D105_F8 = 66;
const int Clavier::D105_F9 = 67;
const int Clavier::D105_F10 = 68;
const int Clavier::D105_NUM_LOCK = 69;
const int Clavier::D105_SCROLL_LOCK = 70;
const int Clavier::D105_KP_7 = 71;
const int Clavier::D105_KP_8 = 72;
const int Clavier::D105_KP_9 = 73;
const int Clavier::D105_KP_MINUS = 74;
const int Clavier::D105_KP_4 = 75;
const int Clavier::D105_KP_5 = 76;
const int Clavier::D105_KP_6 = 77;
const int Clavier::D105_KP_PLUS = 78;
const int Clavier::D105_KP_1 = 79;
const int Clavier::D105_KP_2 = 80;
const int Clavier::D105_KP_3 = 81;
const int Clavier::D105_KP_0 = 82;
const int Clavier::D105_KP_DOT = 83;
const int Clavier::D105_INF_SUP = 86;
const int Clavier::D105_F11 = 87;
const int Clavier::D105_F12 = 88;
const int Clavier::D105_KP_RETURN = 96;
const int Clavier::D105_RIGHT_CTRL = 97;
const int Clavier::D105_KP_SLASH = 98;
const int Clavier::D105_PRINT_SCREEN = 99;
const int Clavier::D105_ALT_GR = 100;
const int Clavier::D105_ORIGIN = 102;
const int Clavier::D105_AR_UP = 103;
const int Clavier::D105_P_PAGE = 104;
const int Clavier::D105_AR_LEFT = 105;
const int Clavier::D105_AR_RIGHT = 106;
const int Clavier::D105_END = 107;
const int Clavier::D105_AR_DOWN = 108;
const int Clavier::D105_N_PAGE = 109;
const int Clavier::D105_INSERT = 110;
const int Clavier::D105_DEL = 111;
const int Clavier::D105_PAUSE = 119;
const int Clavier::D105_LEFT_WIN = 125;
const int Clavier::D105_RIGHT_WIN = 126;
const int Clavier::D105_CONTEXT = 127;
//const int Clavier::D105_SUN = 666;

Clavier::Clavier() {
}

Clavier::Clavier(const Clavier& orig) {
}

Clavier::Clavier(string eventDev) {

	Clavier(eventDev, eventDev, new CarteClavier(), new SortieMIDI());
}

Clavier::Clavier(string eventDev, string devName, CarteClavier *carte, SortieMIDI *sortie) {

	this->eventDev = eventDev;
	this->devName = devName;
	this->carte = carte;
	this->sortie = sortie;
	this->ks = new KbdScan();
	this->noteOffset = 0;

	/*this->ModAltGrOn = 0;
	this->ModLeftAltOn = 0;
	this->ModLeftCtrlOn = 0;
	this->ModLeftShiftOn = 0;
	this->ModLeftWinOn = 0;
	this->ModRightCtrlOn = 0;
	this->ModRightShiftOn = 0;
	this->ModRightWinOn = 0;*/
	this->ModCapsLockOn = 0;
	this->ModNumLockOn = 0;
	this->ModScrollLockOn = 0;
}

void Clavier::run() {

	// Scancode calculé à chaque tour
	//int scancode = 0;
	// Note calculée à chaque tour par la carte
	//int notecode = 0;
	// Code casté en int à chaque tour
	int intCode = 0;
	// Valeur castée en int à chaque tour
	int intValue = 0;
	// Code d'action de carte
	//int actionCode = 0;

	// Structure d'événement d'entrée
	struct input_event ie;

	// Ouverture du clavier matériel en mode lecture d'événements
	//cout << "ouverture de [" << this->eventDev.c_str() << "]" << endl;
	this->ks->openKbd(this->eventDev.c_str());
	//cout << "ouvert: " << endl;

	// Désactivation de toutes les LED
	this->ks->setLED(Disposition105::LED_CAP, 0);
	this->ks->setLED(Disposition105::LED_NUM, 0);
	this->ks->setLED(Disposition105::LED_SCR, 0);

	// Boucle sur la lecture d'événements
	while(true) {
		// Lectue d'un événement
		this->ks->readEvent(&ie);

		// Casting des valeurs
		intValue = (int)ie.value;
		intCode = (int)ie.code;

		// Types d'événements
		if (ie.type == 1) {
			cout << "DEV: " << this->devName << endl;
			// Affichage debug
			switch(intValue) {
				case 1:
					cout << "Touche enfoncée:" << endl;
					break;
				case 0:
					cout << "Touche relâchée:" << endl;
					break;
				case 2:
					cout << "Touche maintenue:" << endl;
					break;
				default:
					cout << "Événement inconnu:" << endl;
					break;
			}

			// D'abord: modificateur persistant ou autre?
			switch(intCode) {
				// Si modificateur persistant, (des)activation de la modification
				// et (des)activation de la LED sur le clavier
				case D105_CAPS_LOCK: {
					if (intValue == 1) { // appui de la touche
						short md = (short) ((this->ModCapsLockOn + 1) % 2);
						this->ModCapsLockOn = md;
						this->ks->setLED(Disposition105::LED_CAP, md);
						// Activation du modificateur défini par la carte
						this->noteOffsetsAndActions(md, intCode);
					}
				} break;
				case D105_NUM_LOCK: { // appui de la touche
					if (intValue == 1) {
						short md = (short) ((this->ModNumLockOn + 1) % 2);
						this->ModNumLockOn = md;
						this->ks->setLED(Disposition105::LED_NUM, md);
						// Activation du modificateur défini par la carte
						this->noteOffsetsAndActions(md, intCode);
					}
				} break;
				case D105_SCROLL_LOCK: { // appui de la touche
					if (intValue == 1) {
						short md = (short) ((this->ModScrollLockOn + 1) % 2);
						this->ModScrollLockOn = md;
						this->ks->setLED(Disposition105::LED_SCR, md);
						// Activation du modificateur défini par la carte
						this->noteOffsetsAndActions(md, intCode);
					}
				} break;
				default: {
					// Si rien de persistant, comportement ponctuel par défaut
					this->noteOffsetsAndActions(intValue, intCode);
				}
			}

			// Si le scancode est un modificateur ou un spécial, action spécifique.
			// Sinon, action de "note"
			/*switch (intCode) {
				// Si spécial -> ??

				// Si modificateur persistant, (des)activation de la modification
				// et (des)activation de la LED sur le clavier
				case D105_CAPS_LOCK: {
					if (intValue == 1) { // appui de la touche
						short md = (short) ((this->ModCapsLockOn + 1) % 2);
						this->ModCapsLockOn = md;
						this->ks->setLED(Disposition105::LED_CAP, md);
					}
				} break;
				case D105_NUM_LOCK: { // appui de la touche
					if (intValue == 1) {
						short md = (short) ((this->ModNumLockOn + 1) % 2);
						this->ModNumLockOn = md;
						this->ks->setLED(Disposition105::LED_NUM, md);
					}
				} break;
				case D105_SCROLL_LOCK: { // appui de la touche
					if (intValue == 1) {
						short md = (short) ((this->ModScrollLockOn + 1) % 2);
						this->ModScrollLockOn = md;
						this->ks->setLED(Disposition105::LED_SCR, md);
					}
				} break;

				// Si modificateur temporaire, activation de la modification
				// à l'appui de la touche, désactivation au relâchement
				case D105_LEFT_SHIFT: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_LEFT_SHIFT))) {
						if (intValue == 1) { // appui de la touche
							this->ModLeftShiftOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModLeftShiftOn = 0;
						}
					}
				} break;
				case D105_RIGHT_SHIFT: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_RIGHT_SHIFT))) {
						if (intValue == 1) { // appui de la touche
							this->ModRightShiftOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModRightShiftOn = 0;
						}
					}
				} break;
				case D105_LEFT_CTRL: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_LEFT_CTRL))) {
						if (intValue == 1) { // appui de la touche
							this->ModLeftCtrlOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModLeftCtrlOn = 0;
						}
					}
				} break;
				case D105_RIGHT_CTRL: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_RIGHT_CTRL))) {
						if (intValue == 1) { // appui de la touche
							this->ModRightCtrlOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModRightCtrlOn = 0;
						}
					}
				} break;
				case D105_LEFT_ALT: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_LEFT_ALT))) {
						if (intValue == 1) { // appui de la touche
							this->ModLeftAltOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModLeftAltOn = 0;
						}
					}
				} break;
				case D105_ALT_GR: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_ALT_GR))) {
						if (intValue == 1) { // appui de la touche
							this->ModAltGrOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModAltGrOn = 0;
						}
					}
				} break;
				case D105_LEFT_WIN: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_LEFT_WIN))) {
						if (intValue == 1) { // appui de la touche
							this->ModLeftWinOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModLeftWinOn = 0;
						}
					}
				} break;
				case D105_RIGHT_WIN: {
					if (this->carte->isModEnabled(this->mlog(Clavier::MOD_RIGHT_WIN))) {
						if (intValue == 1) { // appui de la touche
							this->ModRightWinOn = 1;
						} else if (intValue == 0) { // relâchement de la touche
							this->ModRightWinOn = 0;
						}
					}
				} break;

				// Action par défaut (touche de "note")
				default: {
					// Calcul du scancode en fonction des modificateurs en cours
					scancode = this->calculScancode(&ie);
					cout << "+ scancode calculé: " << scancode << endl;
					// Récupération de la note en fonction de la this->carte
					if (this->carte == 0) {
						cerr << "CarteClavier non définie (null)" << endl;
						notecode = 0;
					} else {
						notecode = this->carte->getNote(scancode);
						cout << "+ note d'après la carte: " << notecode << endl;
						// Jeu de la note par l'instrument
						if (this->sortie == 0) {
							cerr << "Sortie MIDI non définie (null)" << endl;
						} else {
							if (intValue == 1) {
								this->sortie->noteOn(notecode);
							} else if (intValue == 0) {
								this->sortie->noteOff(notecode);
							}
						}
					}
				}
			}*/
			cout << endl;
			// Affichage de l'événement
			//ks.dispEvt(ie);
		}
	}
}

void Clavier::noteOffsetsAndActions(int intValue, int intCode) {

	// Addition des modificateurs
	if (intValue == 1) { // appui de la touche
		this->noteOffset += this->carte->getNoteMod(intCode);
	}

	int actionCode = this->carte->getActionMod(intCode);
	// Si le scancode est un modificateur ou un spécial, action spécifique.
	// Sinon, action de "note"
	switch(actionCode) {
		case 1: {
			cout << "action 1!" << endl;
		} break;
		case 2: {
			cout << "action 2!" << endl;
		} break;
		case 3: {
			cout << "action 3!" << endl;
		} break;
		// Aucun code d'action: joue une note
		case 0:
		default: {
			cout << "note!" << endl;
			this->joueNote(intCode, intValue);
		}
	}
	// Soustraction des modificateurs
	if (intValue == 0) { // relâchement de la touche
		this->noteOffset -= this->carte->getNoteMod(intCode);
	}
	// Protection pourrie?
	//if (this->noteOffset < 0) this->noteOffset = 0;
}

void Clavier::joueNote(int intCode, int intValue) {

	// Affichage debug
	string str = "";
	if (this->ModNumLockOn == 1) str += "N_LOCK + ";
	if (this->ModCapsLockOn == 1) str += "C_LOCK + ";
	if (this->ModScrollLockOn == 1) str += "S_LOCK + ";
	cout << "AP: " << str << intCode << endl;
	cout << "OFFSET: " << this->noteOffset << endl;

	// Calcul de la note depuis la carte
	int scancode = this->noteOffset + intCode;
	cout << "SCAN: " << scancode << endl;
	int notecode;

	if (this->carte == 0) {
		cerr << "CarteClavier non définie (null)" << endl;
		notecode = 0;
	} else {
		notecode = this->carte->getNote(scancode);
		cout << "+ note d'après la carte: " << notecode << endl;
		// Jeu de la note par l'instrument
		if (this->sortie == 0) {
			cerr << "Sortie MIDI non définie (null)" << endl;
		} else {
			if (intValue == 1) {
				this->sortie->noteOn(notecode);
			} else if (intValue == 0) {
				this->sortie->noteOff(notecode);
			}
		}
	}
}

int Clavier::calculScancode(int code) {

	string str = "";
	if (this->ModNumLockOn == 1) str += "N_LOCK + ";
	if (this->ModCapsLockOn == 1) str += "C_LOCK + ";
	if (this->ModScrollLockOn == 1) str += "S_LOCK + ";
	/*if (this->ModLeftShiftOn == 1) str += "L_SHIFT + ";
	if (this->ModRightShiftOn == 1) str += "R_SHIFT + ";
	if (this->ModLeftCtrlOn == 1) str += "L_CTRL + ";
	if (this->ModRightCtrlOn == 1) str += "R_CTRL + ";
	if (this->ModLeftAltOn == 1) str += "L_ALT + ";
	if (this->ModAltGrOn == 1) str += "R_ALT + ";
	if (this->ModLeftWinOn == 1) str += "L_WIN + ";
	if (this->ModRightWinOn == 1) str += "R_WIN + ";*/

	//cout << "AP: " << str << code << endl;

	/*int cs = (int) (ie->code
		+ (MOD_LEFT_SHIFT  * this->ModLeftShiftOn)
		+ (MOD_RIGHT_SHIFT * this->ModRightShiftOn)
		+ (MOD_CAPS_LOCK   * this->ModCapsLockOn)
		+ (MOD_LEFT_CTRL   * this->ModLeftCtrlOn)
		+ (MOD_RIGHT_CTRL  * this->ModRightCtrlOn)
		+ (MOD_LEFT_ALT    * this->ModLeftAltOn)
		+ (MOD_ALT_GR      * this->ModAltGrOn)
		+ (MOD_LEFT_WIN    * this->ModLeftWinOn)
		+ (MOD_RIGHT_WIN   * this->ModRightWinOn)
		+ (MOD_NUM_LOCK    * this->ModNumLockOn)
		+ (MOD_SCROLL_LOCK * this->ModScrollLockOn)
	);*/

	return 0; //cs;
}

int Clavier::mlog(int mod) {

	return log2(mod) - 6;
}

void Clavier::disptime(long t1, long t2, string mess) {

	long t = t2-t1;
	cout << mess << ": " << t << "(" << (t/1000) << "ms)" << endl;
}

void Clavier::closeClav() {

	if (this->ks != 0) {
		cout << "closing kbd scan" << endl;
		this->ks->closeKbd();
	}
}

Clavier::~Clavier() {

	cout << "destruction du clavier" << endl;
	this->closeClav();

	delete this->ks;
	delete this->sortie;
	delete this->carte;
}