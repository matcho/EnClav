/* 
 * File:   SortieMIDI.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 21:48
 */

#ifndef _SORTIEMIDI_H
#define	_SORTIEMIDI_H

#include "../jack/JackMidi.h"

class SortieMIDI {
public:
	static const char *PACKAGE_NAME;

	SortieMIDI();
	SortieMIDI(const char *name);
	SortieMIDI(const SortieMIDI& orig);

	int noteOn(int notecode);
	int noteOff(int notecode);
	void pgChange(int pg, int bk);

	virtual ~SortieMIDI();
private:
	JackMidi *jm;
};

#endif	/* _SORTIEMIDI_H */

