/* 
 * File:   DetecteurClaviers.h
 * Author: mathias
 *
 * Created on 7 mai 2010, 23:50
 */

#ifndef _DETECTEURCLAVIERS_H
#define	_DETECTEURCLAVIERS_H

#include <map>
#include <string>

using namespace std;

class DetecteurClaviers {

public:
	DetecteurClaviers();
	DetecteurClaviers(const DetecteurClaviers& orig);

	virtual map<string,string> *detect(bool includePS2);

	map<string,string> *detect();

	virtual ~DetecteurClaviers();
private:

};

#endif	/* _DETECTEURCLAVIERS_H */