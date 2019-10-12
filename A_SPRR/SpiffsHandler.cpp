/*
 * SpiffsHandler.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#include "SpiffsHandler.h"

SpiffsHandler iniSPIFFS;

extern uint8_t mType;
extern String mID;

SpiffsHandler::SpiffsHandler() {
	// TODO Auto-generated constructor stub
//	iniSPIFFS = this;
//	startup();
}

SpiffsHandler::~SpiffsHandler() {
	// TODO Auto-generated destructor stub
}

void SpiffsHandler::startup() {
	mType = iniSPIFFS.readMtypeFromSpiffs();
	mID = iniSPIFFS.readFromSpiffs("/mID");
	log_i("SPIFFS ready");
}

String SpiffsHandler::readFromSpiffs(String filename) {

	return "1";
}

char SpiffsHandler::readMtypeFromSpiffs() {

	return 3;
}

void SpiffsHandler::writeToSpiffs(char* data, String filename) {
}
