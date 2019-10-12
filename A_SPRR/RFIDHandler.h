/*
 * RFIDHandler.h
 *
 *  Created on: Oct 8, 2019
 *      Author: suhaimi
 */

#ifndef RFIDHANDLER_H_
#define RFIDHANDLER_H_

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         22           // Configurable, see typical pin layout above
#define SS_PIN          21          // Configurable, see typical pin layout above

class RFID_Handler {
public:
	RFID_Handler();
	virtual ~RFID_Handler();
	RFID_Handler(const BaseType_t xCoreID);
	void setup();
	static void loop(void * param);
};

struct CardUser {
	char isAvailable;
	MFRC522::Uid uid;
	String sUid;
};

extern struct CardUser curUser;
extern char rfidNakRead;

#endif /* RFIDHANDLER_H_ */
