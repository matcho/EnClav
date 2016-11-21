/* 
 * File:   Disposition105.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 21:33
 */

#ifndef _DISPOSITION105_H
#define	_DISPOSITION105_H

class Disposition105 {
public:

	// Codes des LED
	static const int LED_NUM;
	static const int LED_CAP;
	static const int LED_SCR;

	Disposition105();
	Disposition105(const Disposition105& orig);
	virtual ~Disposition105();
private:

};

#endif	/* _DISPOSITION105_H */

