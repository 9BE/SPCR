/*
 * KeypadHandler.h
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#ifndef KEYPADHANDLER_H_
#define KEYPADHANDLER_H_

#include "Arduino.h"

class Keypad_Handler {
public:
	Keypad_Handler();
	Keypad_Handler(const BaseType_t xCoreID);
	virtual ~Keypad_Handler();
private:
	static void loop(void * param);
};

extern String keyPressed;

#endif /* KEYPADHANDLER_H_ */
