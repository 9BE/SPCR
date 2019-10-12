/*
 * SpiffsHandler.h
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#ifndef SPIFFSHANDLER_H_
#define SPIFFSHANDLER_H_

#include "Arduino.h"

class SpiffsHandler {
public:
	SpiffsHandler();
	virtual ~SpiffsHandler();
	String readFromSpiffs(String filename);
private:
	void startup();

	char readMtypeFromSpiffs();
	void writeToSpiffs(char * data, String filename);
};

extern SpiffsHandler iniSPIFFS;
#endif /* SPIFFSHANDLER_H_ */
