/* 
 * File:   KbdScan.h
 * Author: mathias
 *
 * Created on 8 mai 2010, 17:52
 */

#ifndef _KBDSCAN_H
#define	_KBDSCAN_H

#include <linux/input.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

class KbdScan {
public:
	KbdScan();
	KbdScan(const KbdScan& orig);

	int openKbd(const char *chemin);
	int readEvent(struct input_event *evt);
	void closeKbd();
	void setLED(int led, int mode);

	virtual ~KbdScan();
private:
	int fd;
};

#endif	/* _KBDSCAN_H */

