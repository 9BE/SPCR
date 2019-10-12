/*
 * RFIDHandler.cpp
 *
 *  Created on: Oct 8, 2019
 *      Author: suhaimi
 */

#include "RFIDHandler.h"

RFID_Handler *iniRFID;
TaskHandle_t rfidReaderLoopTaskHandle = NULL;

CardUser curUser;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

char rfidNakRead = 0;

RFID_Handler::RFID_Handler() {
	// TODO Auto-generated constructor stub
	iniRFID = this;
	setup();
	xTaskCreatePinnedToCore(loop, "readerTask", 8192, NULL, 1, &rfidReaderLoopTaskHandle, 0);

}

RFID_Handler::~RFID_Handler() {
	// TODO Auto-generated destructor stub
	log_i("RFID destruct");
	vTaskDelete(rfidReaderLoopTaskHandle);
}

RFID_Handler::RFID_Handler(const BaseType_t xCoreID) {
	iniRFID = this;
	setup();
	xTaskCreatePinnedToCore(loop, "readerTask", 8192, NULL, 1, &rfidReaderLoopTaskHandle, xCoreID);
}

void RFID_Handler::setup() {
	SPI.begin();                                                  // Init SPI bus
	mfrc522.PCD_Init();                                              // Init MFRC522 card
	mfrc522.PCD_DumpVersionToSerial();
	log_i("READY TO READ MIFARE PICC");    //shows in serial that it is ready to read
}

void RFID_Handler::loop(void* param) {
	while(1) {

		if (rfidNakRead) {
//			log_i("rfidNakRead ================= %u" , millis());
			if (mfrc522.PICC_IsNewCardPresent()) {
				log_i("===========>>>>>>>>>><<<<<<<<<<<<<===========");
				log_i("**Card Detected:**");
				if (mfrc522.PICC_ReadCardSerial()) {
					mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));
					curUser.isAvailable = 1;
					curUser.uid = mfrc522.uid;
					log_i();
					curUser.sUid = "";
					for (int i=0; i<mfrc522.uid.size; i++) {
						if (mfrc522.uid.uidByte[i] < 0x10) curUser.sUid.concat("0");
						curUser.sUid.concat(String(mfrc522.uid.uidByte[i], HEX));
					}

					curUser.sUid.toUpperCase();


					Serial.println(curUser.sUid);

					mfrc522.PICC_HaltA(); // Halt the PICC before stopping the encrypted session.
					mfrc522.PCD_StopCrypto1();
				}
			}
		}



		delay(50);
	}
}


