/* 
 * File:   EnUtil.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 13:50
 */

#include <vector>

#include "EnUtil.h"

using namespace std;

EnUtil::EnUtil() {
}

EnUtil::EnUtil(const EnUtil& orig) {
}

vector<string> *EnUtil::split(string haystack, string needle, bool keepLastPart) {

	size_t found, prec = 0;
	string tmp;
	vector<string> *res = new vector<string>();

	found = haystack.find(needle,0);
	// Découpage en rondelles tant qu'on trouve le motif
	while (found != string::npos) {

		if (prec > 0) prec += needle.length();
		tmp = haystack.substr(prec,(found-prec));
		res->push_back(tmp);
		//cout << "ligne ajoutée: " << tmp << endl;

		prec = found;
		found = haystack.find(needle,found+1);
	}
	// Conservation de la dernière partie?
	if (keepLastPart) {
		prec += needle.length();
		tmp = haystack.substr(prec,(haystack.length()-prec));
		res->push_back(tmp);
		//cout << "ligne ajoutée: " << tmp << endl;
	}

	return res;
}

bool EnUtil::stringMapContains(map<string,string> *carte, string value) {

    bool found = false;
    map<string,string>::iterator it = carte->begin();

    while(it != carte->end()) {
        found = (it->second == value);
        if(found)
                break;
        ++it;
    }
    return found;
}

EnUtil::~EnUtil() {
}