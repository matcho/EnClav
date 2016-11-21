/* 
 * File:   SortieMIDI.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 21:48
 */

#include "SortieMIDI.h"

#include <iostream>

using namespace std;

const char *SortieMIDI::PACKAGE_NAME = "EnClav";

SortieMIDI::SortieMIDI() {

	this->jm = new JackMidi(PACKAGE_NAME);
}

SortieMIDI::SortieMIDI(const char *name) {

	this->jm = new JackMidi(name);
}

SortieMIDI::SortieMIDI(const SortieMIDI& orig) {
}

int SortieMIDI::noteOn(int notecode) {

	//int	nVelocity = 80;

	this->jm->queue_new_message(MIDI_NOTE_ON, notecode, 80);
	cout << "++++ NOTE ON ++++" << endl;

	return 0;
}

int SortieMIDI::noteOff(int notecode) {

	this->jm->queue_new_message(MIDI_NOTE_OFF, notecode, 80);
	cout << "++++ NOTE OFF ++++" << endl;

	return 0;
}

void SortieMIDI::pgChange(int bk, int pg) {

	this->jm->send_program_change(bk, pg);
}

SortieMIDI::~SortieMIDI() {

	cout << "destruction de SortieMIDI" << endl;
	delete this->jm;
}