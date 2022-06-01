#include<Arduino.h>
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid
#define SS_PIN 5
#define RST_PIN 17 
const int ipaddress[4] = {103, 97, 67, 25};

byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);
void readRFID(void );
void printDec(byte *buffer, byte bufferSize);
void printHex(byte *buffer, byte bufferSize);

void loop() {
 readRFID();
}
void setup() {

 Serial.begin(115200);
 Serial.println(F("Initialize System"));

 SPI.begin();
 rfid.PCD_Init();
 Serial.print(F("Reader :"));
 rfid.PCD_DumpVersionToSerial();
}

void readRFID(void ) { 

 for (byte i = 0; i < 6; i++) {
   key.keyByte[i] = 0xFF;
 }
 if ( ! rfid.PICC_IsNewCardPresent())
   return;

 if (  !rfid.PICC_ReadCardSerial())
   return;

 for (byte i = 0; i < 4; i++) {
   nuidPICC[i] = rfid.uid.uidByte[i];
 }
 Serial.print(F("RFID In dec: "));
 printDec(rfid.uid.uidByte, rfid.uid.size);
 Serial.println();

 rfid.PICC_HaltA();

 rfid.PCD_StopCrypto1();
}

void printHex(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], HEX);
 }
}

void printDec(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], DEC);
 }
}