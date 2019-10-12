#include "Arduino.h"
#include "RFIDHandler.h"
#include "SpiffsHandler.h"
#include "KeypadHandler.h"
#include "Displayhandler.h"
#include "MQTTHandler.h"

RFID_Handler *rfidHandler;
//SpiffsHandler * spiffsHandler;
Keypad_Handler * keypadHandler;
Display_handler * displayHandler;
MQTT_Handler * nyamuk;

/**
 * mType is machine type
 * 0 = default
 * 1 = Reload
 * 2 = POS
 * 3 = Library
 * 4 = Attendance
 */
uint8_t mType = 3;

String mID = "A9B8C7";

int topupDenom[5] = {5,10,30,50,100};
int topupDenomSize = sizeof(topupDenom) / sizeof(topupDenom[0]);

uint64_t rfidTime = 0;

String amount = "0.00";

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here

	Serial.begin(921600);
	delay(500);
	log_i("MULAI . . .");
	if (mType == reload || mType == pos) {OLED_TYPE = 3;
		rfidNakRead = 0;
	}
	else if (mType == library || mType == attendance) {
		OLED_TYPE = 3;
		rfidNakRead = 1;
	}
	//	spiffsHandler = new SpiffsHandler;

	page.curPageNum = (PageNumber) mType;
	page.update = true;

	rfidHandler = new RFID_Handler(0);
	keypadHandler = new Keypad_Handler(1);
	displayHandler = new Display_handler(0);


	log_i("%d", page.curPageNum);
}

String masukkanAmount(String keyAsal, String keyIN)
{
	String res = keyAsal;

	// let keyPressed = 1
	res.concat(keyIN); // 0.001
	res.remove(res.indexOf('.'), 1); // 0001
	for (int k=0; k<keyIN.length(); k++) {
		if (res.charAt(0) == '0') res.remove(0,1); // 001
		else break;
	}
//	int i = res.indexOf('0');
//	while (i==0) {
//		res.remove(0,1); // 001
//		i = res.indexOf('0');
//		if (i<0 || i>0) break;
//	}
//	if (res.charAt(0) == '0') res.remove(0,1); // 001
	String temp = res.substring(res.length() - 2); // temp = 01
	res.remove(res.length() - 2); // 0
	res.concat("."); // 0.
	res.concat(temp); // 0.01

	return res;
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	if (keyPressed != "") {
		if (keyPressed == "***") {  // tekan "*" lebih 3 saat
			page.curPageNum = main;
			page.update = true;
			mType = 0;
			rfidNakRead = 0;
			amount = "";
		}else {
//			if (page.curPageNum == main) {
//				page.curPageNum = (PageNumber) keyPressed.toInt();
//				page.update = true;
//				mType = keyPressed.toInt();
//
//				if (page.curPageNum == attendance || page.curPageNum == library) {
//					log_i("Please touch card on reader");
//					rfidNakRead = 1;
//					rfidTime = millis();
//				}
//
//				if (page.curPageNum == pos) {
//					amount = "0.00";
//				}
//
//				// TODO : display designated page
//			}else
			if (page.curPageNum == reload) {
				amount = masukkanAmount(amount, String(topupDenom[keyPressed.toInt()-1]) + "00");
				log_i("RELOAD :: %d", amount);
				Serial.println(amount);
				log_i("Please touch card on reader");

				page.curPageNum = reload2;
				page.update = true;
				rfidNakRead = 1;
				rfidTime = millis();
				// TODO : display designated page
			}else if (page.curPageNum == pos) {

				if (keyPressed == "#") {
					page.curPageNum = pos2;
					page.update = true;
					rfidNakRead = 1;
					rfidTime = millis();

					log_i("PAY :: %s", amount);
					Serial.println(amount);
					log_i("Please touch card on reader");
				} else if (keyPressed == "*"){
					if (amount == "0.00") {
						page.curPageNum = main;
						page.update = true;
						mType = 0;
						rfidNakRead = 0;
//						amount = "";
					}else {
						amount = "0.00";
						page.curPageNum = pos;
						page.update = true;
					}
				}else {
					amount = masukkanAmount(amount, keyPressed);

					page.curPageNum = pos;
					page.update = true;

					log_i("PAY :: %s", amount);
					Serial.println(amount);
				}



				// TODO : display designated page
			}
		}

		keyPressed = "";
		log_i("RFID Ready to read == %d", rfidNakRead);
	}

	if (rfidNakRead) {
		if (curUser.isAvailable) {
			dataToSend.MachineID = mID;
			dataToSend.MachineType = String(mType);
			dataToSend.CardID = curUser.sUid;
			dataToSend.Amount = amount;
			nyamuk->hantar();
			page.curPageNum = success;
			page.update = true;
			rfidNakRead = 0;
			curUser.isAvailable = false;
			amount = "0.00";

			delay(1000);

			page.curPageNum = (PageNumber) mType;
			page.update = true;
			if (mType == library || mType == attendance) {
				rfidNakRead = 1;
			}

		}else if (millis() - rfidTime >= 10000) {

			if (mType == reload || mType == pos) {
				page.curPageNum = (PageNumber) mType;
				page.update = true;
				rfidNakRead = 0;
				amount = "0.00";
			}

		}

	}

	delay(10);
}















