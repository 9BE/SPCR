/*
 * Displayhandler.h
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#ifndef DISPLAYHANDLER_H_
#define DISPLAYHANDLER_H_

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "Adafruit_ILI9341.h"
#include <SSD1306Spi.h>
#include <OLEDDisplayUi.h>
#include <SPI.h>
#include "SpiffsHandler.h"

class Display_handler {
public:
	Display_handler();
	virtual ~Display_handler();
	Display_handler(const BaseType_t xCoreID);
private:
	void setup();
	static void loop(void * param);
	void updateDisplay();
	int16_t getcursorXpos(uint8_t s, int len, int align, int sWidth, uint16_t sMultiplier);
	void drawLine(String text, uint16_t color, uint8_t s, uint8_t align, uint8_t spacing);
	void drawMenuLine(String num, String text, uint16_t color, uint8_t s, uint8_t align, uint8_t spacing);
	void drawHeader();
	void drawBattery(uint8_t battery);
	void drawWiFi(char ada);
};

enum Alignment {
	left,
	right,
	center
};

enum PageNumber{
	main,
	reload,
	pos,
	library,
	attendance,
	reload2,
	pos2,
	success
};

struct Page{
	bool update;
	PageNumber curPageNum;
};

struct StatusBar {
	uint16_t network;
	bool internet;
	String masa;
	uint8_t battery;
};

extern struct Page page;
extern uint8_t OLED_TYPE;
extern struct StatusBar statusBar;

#endif /* DISPLAYHANDLER_H_ */
