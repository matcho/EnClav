/* 
 * File:   EnUtil.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 13:50
 */

#ifndef _ENUTIL_H
#define	_ENUTIL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class EnUtil {
public:
	EnUtil();
	EnUtil(const EnUtil& orig);

	static vector<string> *split(string haystack, string needle, bool keepLastPart);
	static bool stringMapContains(map<string,string> *carte, string value);

	virtual ~EnUtil();
private:

};

#endif	/* _ENUTIL_H */

