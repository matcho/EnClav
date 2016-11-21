/* 
 * File:   DetecteurClaviersProc.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 00:09
 */

#ifndef _DETECTEURCLAVIERSPROC_H
#define	_DETECTEURCLAVIERSPROC_H

#include "DetecteurClaviers.h"

class DetecteurClaviersProc : DetecteurClaviers {
public:
	static const char *PROC_BUS_INPUT_DEVICES;

	DetecteurClaviersProc();
	DetecteurClaviersProc(const DetecteurClaviersProc& orig);

	map<string,string> *detect(bool includePS2);

	virtual ~DetecteurClaviersProc();
private:

};

#endif	/* _DETECTEURCLAVIERSPROC_H */

