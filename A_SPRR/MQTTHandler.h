/*
 * MQTTHandler.h
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#ifndef MQTTHANDLER_H_
#define MQTTHANDLER_H_

#include "Arduino.h"

class MQTT_Handler {
public:
	MQTT_Handler();
	virtual ~MQTT_Handler();
	void hantar();
};

struct DataToSend {
	String MachineID;
	String MachineType;
	String CardID;
	String Amount;
};

extern struct DataToSend dataToSend;

#endif /* MQTTHANDLER_H_ */
