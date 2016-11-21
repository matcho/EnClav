/* 
 * File:   KbdScan.cpp
 * Author: mathias
 * 
 * Created on 8 mai 2010, 17:52
 */

#include "KbdScan.h"

KbdScan::KbdScan() {
}

KbdScan::KbdScan(const KbdScan& orig) {
}

KbdScan::~KbdScan() {
}

int KbdScan::openKbd(const char *chemin) {

	/* Ouverture de l' "input event" */
	this->fd = open(chemin,O_RDWR);
	if (! this->fd) {
		perror("ouverture");
		return 1;
	}

	/* C'est la fête du slip */
	ioctl(this->fd, EVIOCGRAB, 1);

	return 0;
}

int KbdScan::readEvent(struct input_event *evt) {

	if(read(this->fd, evt, sizeof(*evt))<0) {
		perror("lecture");
		return 1;
	}
}

void KbdScan::closeKbd() {

	close(this->fd);
}

void KbdScan::setLED(int led, int mode) {

	struct input_event ledevt;

	ledevt.type = EV_LED;
	ledevt.code = led;
	ledevt.value = mode;

	write(this->fd, &ledevt, sizeof(ledevt));
}