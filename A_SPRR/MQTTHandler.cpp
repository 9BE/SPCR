/*
 * MQTTHandler.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#include "MQTTHandler.h"

/**
 * Data to send :
 * 	1- Machine ID -> 6 alphanumeric
 * 	2- Machine Type -> 1 digit number (1=Reload, 2=POS, 3=Library, 4=Attendance)
 * 	3- CardID -> 4 hex
 * Format data to send :
 * 	"MachineID,MachineType,CardID,Amount"
 *
 * Example :
 * 	"112233,4,43FEC927,0.00
 */

DataToSend dataToSend;
MQTT_Handler::MQTT_Handler() {
	// TODO Auto-generated constructor stub

}

MQTT_Handler::~MQTT_Handler() {
	// TODO Auto-generated destructor stub
}

void MQTT_Handler::hantar() {
	String data = "";
	data.concat(dataToSend.MachineID);
	data.concat(",");
	data.concat(dataToSend.MachineType);
	data.concat(",");
	data.concat(dataToSend.CardID);
	data.concat(",");
	data.concat(dataToSend.Amount);
	log_i("HANTARING DATA ---------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>>>");
	Serial.println(data);
}
