/*
 * Displayhandler.cpp
 *
 *  Created on: Oct 9, 2019
 *      Author: suhaimi
 */

#include "Displayhandler.h"

//***********************************************************************************
/* # IF OLED 0.96inch
 * | 			| Character count			|
 * | Size		| Landscape 	| Potrait	|
 * |			| X		| Y		|			|
 * | 10 (10x13)	| 		| 		|			|
 * | 16 (16x19)	| 		| 		|			|
 * | 24 (24x28)	| 		| 		|			|
 */
//***********************************************************************************
/* # IF TFT 1.8inch
 * | 			| Character count			|
 * | Size		| Landscape 	| Potrait	|
 * |			| X		| Y		|			|
 * | 1 (6x8)	| 26	| 16	|			|
 * | 2 (12x16)	| 13	| 8		|			|
 * | 3 (18x24)	| 8		| 4		|			|
 */
//***********************************************************************************
/*	# IF TFT 3.2inch
 * | 			| Character count				|
 * | Size		| Landscape 	| Potrait		|
 * |			| X		| Y		| X		| Y		|
 * | 1 (6x8)	| 		| 		| 40	| 40	|
 * | 2 (12x16)	| 		|		| 20	| 20	|
 * | 3 (18x24)	| 		|		| 13	| 13	|
 */
//***********************************************************************************

//define pins of TFT screen
#define DIS_CS     15
#define DIS_RST    22
#define DIS_DC     13
#define DIS_CLK   18
#define DIS_MOSI   23

SSD1306Spi display(DIS_RST, DIS_DC, DIS_CS); // @suppress("Abstract class cannot be instantiated")
OLEDDisplayUi ui ( &display );
#define sW_1 		128
#define sH_1 		64

Adafruit_ST7735 tft_18 = Adafruit_ST7735(DIS_CS, DIS_DC, DIS_RST);
#define sW_18		160
#define sH_18		128

Adafruit_ILI9341 tft_32 = Adafruit_ILI9341(DIS_CS, DIS_DC, 2);
#define sW_32		320 // 160
#define sH_32		240 // 128
//***********************************************************************************

float p = 3.1415926;

Display_handler * iniDisplay;
TaskHandle_t displayTask = NULL;

Page page;

extern int topupDenomSize;
extern int topupDenom[];
extern String amount;

uint8_t OLED_TYPE = 0;

uint64_t masaBatt = 0;

struct StatusBar statusBar;

Display_handler::Display_handler() {
	// TODO Auto-generated constructor stub
	iniDisplay = this;
	setup();
	xTaskCreatePinnedToCore(loop, "keypadTask", 2048, NULL, 1, &displayTask, 0);
}

Display_handler::~Display_handler() {
	// TODO Auto-generated destructor stub
}

Display_handler::Display_handler(const BaseType_t xCoreID) {
	iniDisplay = this;
	setup();
	xTaskCreatePinnedToCore(loop, "keypadTask", 2048, NULL, 1, &displayTask, xCoreID);
}



void Display_handler::setup() {
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);

	if (OLED_TYPE == 1) {
		ui = &display;
		ui.init();
		display.flipScreenVertically();
	}else if (OLED_TYPE == 2) {					// >>>>>>>>>>>>>>>>. OLED_TYPE == 2
		tft_18.initR(INITR_BLACKTAB);//initialize a ST7735S chip, black tab
		tft_18.setRotation(1);
		iniDisplay->drawLine("Initializing", ST7735_BLUE, 2, center, 0);
		delay(1000);
		tft_18.fillScreen(ST7735_BLACK);
	}
	else if (OLED_TYPE == 3) {				// OLED_TYPE == 3
		tft_32.begin();
		tft_32.fillScreen(ILI9341_BLACK); //large block of text
		tft_32.setRotation(1);
		iniDisplay->drawLine("Initializing", ILI9341_BLUE, 2, center, 0);
		delay(1000);
		tft_32.fillScreen(ILI9341_BLACK);
	}

	iniDisplay->drawHeader();
	delay(50);



	
//	page.curPageNum = main;
//	page.update = true;
}

void Display_handler::loop(void* param) {
	while(1) {
		if (page.update) {
			iniDisplay->updateDisplay();
			page.update = false;
		}

		if (millis() - masaBatt >= 1000) {
			masaBatt = millis();
			iniDisplay->drawBattery(70);
			iniDisplay->drawWiFi(0);
		}
		delay(50);
	}
}

void Display_handler::drawWiFi(char ada) {
	if (OLED_TYPE == 1) {

	}else if (OLED_TYPE == 2) {

	}else if (OLED_TYPE == 3) {
		if (ada == 0) {
			tft_32.drawLine(3, 1, 9, 1, ILI9341_DARKGREY);
			tft_32.drawLine(0, 4, 3, 1, ILI9341_DARKGREY);
			tft_32.drawLine(9, 1, 12, 4, ILI9341_DARKGREY);

			tft_32.drawLine(4, 4, 8, 4, ILI9341_DARKGREY);
			tft_32.drawLine(2, 6, 4, 4, ILI9341_DARKGREY);
			tft_32.drawLine(8, 4, 10, 6, ILI9341_DARKGREY);

			tft_32.drawLine(5, 7, 7, 7, ILI9341_DARKGREY);
			tft_32.drawLine(4, 8, 5, 7, ILI9341_DARKGREY);
			tft_32.drawLine(7, 7, 8, 8, ILI9341_DARKGREY);

			tft_32.drawPixel(6, 10, ILI9341_DARKGREY);

//			tft_32.drawLine(1, 9, 10, 0, ILI9341_DARKGREY);
//			tft_32.drawLine(2, 9, 11, 0, ILI9341_DARKGREY);
		}else if (ada == 1) {
			tft_32.drawLine(3, 1, 9, 1, ILI9341_WHITE);
			tft_32.drawLine(0, 4, 3, 1, ILI9341_WHITE);
			tft_32.drawLine(9, 1, 12, 4, ILI9341_WHITE);

			tft_32.drawLine(4, 4, 8, 4, ILI9341_WHITE);
			tft_32.drawLine(2, 6, 4, 4, ILI9341_WHITE);
			tft_32.drawLine(8, 4, 10, 6, ILI9341_WHITE);

			tft_32.drawLine(5, 7, 7, 7, ILI9341_WHITE);
			tft_32.drawLine(4, 8, 5, 7, ILI9341_WHITE);
			tft_32.drawLine(7, 7, 8, 8, ILI9341_WHITE);

			tft_32.drawPixel(6, 10, ILI9341_WHITE);

			tft_32.drawLine(1, 9, 10, 0, ILI9341_WHITE);
			tft_32.drawLine(2, 9, 11, 0, ILI9341_WHITE);
		}else if (ada == 2) {
			tft_32.drawLine(3, 1, 9, 1, ILI9341_WHITE);
			tft_32.drawLine(0, 4, 3, 1, ILI9341_WHITE);
			tft_32.drawLine(9, 1, 12, 4, ILI9341_WHITE);

			tft_32.drawLine(4, 4, 8, 4, ILI9341_WHITE);
			tft_32.drawLine(2, 6, 4, 4, ILI9341_WHITE);
			tft_32.drawLine(8, 4, 10, 6, ILI9341_WHITE);

			tft_32.drawLine(5, 7, 7, 7, ILI9341_WHITE);
			tft_32.drawLine(4, 8, 5, 7, ILI9341_WHITE);
			tft_32.drawLine(7, 7, 8, 8, ILI9341_WHITE);

			tft_32.drawPixel(6, 10, ILI9341_WHITE);
		}


//		tft_32.fillRect(sW_32-36, 0, 36, 10, ILI9341_BLACK);
//		tft_32.drawRect(sW_32-11, 1, 10, 7, ILI9341_WHITE);
//		tft_32.drawLine(sW_32-1, 3, sW_32-1, 5, ILI9341_WHITE);
//		tft_32.fillRect(sW_32-11, 1, battery/10, 7, ILI9341_WHITE);
//
//		tft_32.setCursor(sW_32-30, 1);
//		if (battery == 100) tft_32.setCursor(sW_32-36, 1);
//		tft_32.setTextColor(ILI9341_WHITE);
//		tft_32.setTextSize(1);
//		tft_32.print(battery);
//		tft_32.print("%");
	}
}


void Display_handler::drawBattery(uint8_t battery) {
	if (OLED_TYPE == 1) {

	}else if (OLED_TYPE == 2) {

	}else if (OLED_TYPE == 3) {
		tft_32.fillRect(sW_32-36, 0, 36, 11, ILI9341_BLACK);
		tft_32.drawRect(sW_32-11, 1, 10, 8, ILI9341_WHITE);
		tft_32.drawLine(sW_32-1, 3, sW_32-1, 6, ILI9341_WHITE);
		tft_32.fillRect(sW_32-11, 1, battery/10, 8, ILI9341_WHITE);

		tft_32.setCursor(sW_32-30, 1);
		if (battery == 100) tft_32.setCursor(sW_32-36, 1);
		tft_32.setTextColor(ILI9341_WHITE);
		tft_32.setTextSize(1);
		tft_32.print(battery);
		tft_32.print("%");
	}
}

void Display_handler::updateDisplay() {
	log_i("PAGE :: %d", page.curPageNum);

	uint8_t size = 2;
	uint8_t spacing = 42;
	uint16_t color = 0;

	if (OLED_TYPE == 1) {
		display.fillRect(0, 21, sW_1, sH_1-19);
		spacing = 21;
		size = 1;

	}else if (OLED_TYPE == 2) {
		size = 1;
		spacing = 24;
		color = ST7735_WHITE;
		tft_18.fillRect(0, spacing, sW_18, sH_18-spacing, ST7735_BLACK);
	}else if (OLED_TYPE == 3) {
		size = 2;
		spacing = 42;
		color = ILI9341_WHITE;
		tft_32.fillRect(0, spacing, sW_32, sH_32-spacing, ILI9341_BLACK);
	}
	
	
	switch(page.curPageNum) {
		case main:

			iniDisplay->drawLine("MENU UTAMA", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);

//			iniDisplay->drawMenuLine("1","TAMBAH NILAI", color, size, left, spacing);
//			spacing += (10*size);
//
//			iniDisplay->drawMenuLine("2","PEMBAYARAN", color, size, left, spacing);
//			spacing += (10*size);
//
//			iniDisplay->drawMenuLine("3","PERPUSTAKAAN", color, size, left, spacing);
//			spacing += (10*size);
//
//			iniDisplay->drawMenuLine("4", "KEHADIRAN", color, size, left, spacing);

			break;
		case reload:

			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);

			for(int i=0; i<topupDenomSize; i++) {
				iniDisplay->drawMenuLine(String(i+1), " RM " + String(topupDenom[i]) + ".00", color, size, left, spacing);
				spacing += (10*size);
			}

			break;
		case pos:

			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("Sila masukkan jumlah", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("RM " + amount, color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawMenuLine("*"," Padam", color, size, left, spacing);
			iniDisplay->drawMenuLine("#"," Teruskan", color, size, right, spacing);

			break;
		case library:
		case attendance:

			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("Sentuh kad pada pengimbas", color, size, center, spacing);

			break;
		case reload2:
		case pos2:
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("RM " + amount, color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("Sentuh kad pada pengimbas", color, size, center, spacing);

			break;
		case success:
			iniDisplay->drawLine("", color, size, center, spacing);
			spacing += (10*size);
			iniDisplay->drawLine("BERJAYA!!!", color, size, center, spacing);
			break;
	}
}

int16_t Display_handler::getcursorXpos(uint8_t s, int len, int align, int sWidth, uint16_t sMultiplier) {
	int16_t res = 0;
	switch (align) {
		case left:
			res = 0;
			break;
		case center:
			res = s * sMultiplier;
			res = res * len;
			res = sWidth - res;
			res /= 2;
			break;
		case right:
			res = s * sMultiplier;
			res = res * len;
			res = sWidth - res;
			break;
	}

	return res;
}

void Display_handler::drawLine(String text, uint16_t color, uint8_t s,
		uint8_t align, uint8_t spacing) {

	if (OLED_TYPE == 1) {
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_10);
		display.drawString(iniDisplay->getcursorXpos(s, text.length(), align, sW_1, 10), spacing+(spacing/10*4), text);

	}else if (OLED_TYPE == 2) {				// OLED_TYPE == 2
		tft_18.setCursor(iniDisplay->getcursorXpos(s, text.length(), align, sW_18, 6)+1, spacing);
		tft_18.setTextColor(color);
		tft_18.setTextSize(s);
		tft_18.print(text);
	}else if (OLED_TYPE == 3) {			// OLED_TYPE == 3
		tft_32.setCursor(iniDisplay->getcursorXpos(s, text.length(), align, sW_32, 6)+1, spacing);
		tft_32.setTextColor(color);
		tft_32.setTextSize(s);
		tft_32.print(text);
	}

}

void Display_handler::drawMenuLine(String num, String text, uint16_t color, uint8_t s,
		uint8_t align, uint8_t spacing) {

	if (OLED_TYPE == 1) {
		display.fillRect(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_1, 10), spacing+(spacing/10*4)-1, 10, 13);

		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_10);
		display.drawString(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_1, 10), spacing+(spacing/10*4), num);
		display.drawString(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_1, 10)+13, spacing+(spacing/10*4), text);

	}else if (OLED_TYPE == 2) {				// OLED_TYPE == 2

		tft_18.fillRect(iniDisplay->getcursorXpos(s, text.length()+(s*6), align, sW_18, 6), spacing-1, s*6, s*8, ST7735_WHITE);

		tft_18.setCursor(iniDisplay->getcursorXpos(s, text.length(), align, sW_18, 6)+1, spacing);
		tft_18.setTextColor(ST7735_BLACK);
		tft_18.setTextSize(s);
		tft_18.print(num);

		tft_18.setCursor(iniDisplay->getcursorXpos(s, text.length(), align, sW_18, 6)+(s*6*2), spacing);
		tft_18.setTextColor(color);
		tft_18.setTextSize(s);
		tft_18.print(text);

	}else if (OLED_TYPE == 3) {			// OLED_TYPE == 3

		tft_32.fillRect(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_32, 6), spacing-1, s*6, s*8, ILI9341_WHITE);

		tft_32.setCursor(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_32, 6)+1, spacing);
		tft_32.setTextColor(ILI9341_BLACK);
		tft_32.setTextSize(s);
		tft_32.print(num);

		tft_32.setCursor(iniDisplay->getcursorXpos(s, text.length()+num.length(), align, sW_32, 6)+(s*6), spacing);
		tft_32.setTextColor(color);
		tft_32.setTextSize(s);
		tft_32.print(text);

	}

}

void Display_handler::drawHeader() {
	String header = "";
	switch (page.curPageNum) {
		case reload:
			header = "TAMBAH NILAI";
			break;
		case pos:
			header = "PEMBAYARAN";
			break;
		case library:
			header = "PERPUSTAKAAN";
			break;
		case attendance:
			header = "KEHADIRAN";
			break;
		default:
			header = "default";
			break;
	}

	if (OLED_TYPE == 1) {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_CENTER);
		display.setFont(ArialMT_Plain_16);
		display.drawString((sW_1/2), 5, header);
	}else if (OLED_TYPE == 2) {				// OLED_TYPE == 2

		tft_18.fillRect(0, 11, sW_18, 14, ST7735_MAGENTA);

		tft_18.setCursor(iniDisplay->getcursorXpos(2, header.length(), center, sW_18, 6), 15);
		tft_18.setTextColor(ST7735_BLACK);
		tft_18.setTextSize(2);

		tft_18.print(header);

	}else if (OLED_TYPE == 3) {			// OLED_TYPE == 3

		tft_32.fillRect(0, 11, sW_32, 30, ILI9341_MAGENTA);

		tft_32.setCursor(iniDisplay->getcursorXpos(3, header.length(), center, sW_32, 6), 15);
		tft_32.setTextColor(ILI9341_BLACK);
		tft_32.setTextSize(3);

		tft_32.print(header);


	}
}





