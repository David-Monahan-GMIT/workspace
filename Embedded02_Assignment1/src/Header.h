/*
 * Header.h
 *
 *  Created on: 20 Jan 2017
 *      Author: Dave
 */

#ifndef SRC_HEADER_H_
#define SRC_HEADER_H_

#include <string.h>

typedef struct {
	char name[20];
	float cTemp;	// Current Temperature
	float pTemp;	// Previous Temperature
	void *print;
}	TemperatureMonitor;

void printFunction();
}


#endif /* SRC_HEADER_H_ */
