/* 
 * File:   DetecteurClaviers.cpp
 * Author: mathias
 * 
 * Created on 7 mai 2010, 23:50
 */

#include "DetecteurClaviers.h"

DetecteurClaviers::DetecteurClaviers() {
}

DetecteurClaviers::DetecteurClaviers(const DetecteurClaviers& orig) {
}

map<string,string> *DetecteurClaviers::detect(bool includePS2) {

	return 0;
}

map<string,string> *DetecteurClaviers::detect() {

	return this->detect(false);
}

DetecteurClaviers::~DetecteurClaviers() {
}