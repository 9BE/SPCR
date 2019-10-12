/*
 * KeypadHandler.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#include "KeypadHandler.h"

Keypad_Handler * iniKeypad;

TaskHandle_t keypadTask = NULL;

String keyPressed = "";

Keypad_Handler::Keypad_Handler() {
	// TODO Auto-generated constructor stub
	iniKeypad = this;
	log_i("KEYPAD READY");
	xTaskCreatePinnedToCore(loop, "keypadTask", 2048, NULL, 1, &keypadTask, 0);
}

Keypad_Handler::~Keypad_Handler() {
	// TODO Auto-generated destructor stub
	log_i("KEYPAD DESTRUCT");
	vTaskDelete(keypadTask);
}

Keypad_Handler::Keypad_Handler(const BaseType_t xCoreID) {
	iniKeypad = this;
	log_i("KEYPAD READY");
	xTaskCreatePinnedToCore(loop, "keypadTask", 2048, NULL, 1, &keypadTask, xCoreID);
}

void Keypad_Handler::loop(void* param) {
	while(1) {
		if (Serial.available()) {
			while (Serial.available()) {
				keyPressed.concat((char) Serial.read());
			}
		}

//		delay(10);
//		keyPressed = "";
		delay(100);
	}
}

