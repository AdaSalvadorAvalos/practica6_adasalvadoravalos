Materiales:
· MÓDULO LECTOR RFID RC522
· ESP32
· TARJETA
· LLAVERO

Presentación:
En esta práctica hemos usado los buses SPI, concretamente en esta hemos pasado un tag (una tarjeta) que tiene la capacidad de enviar información al lector.
El SPI  consta de mínimo 3 líneas: MOSI: comunicació maestro-esclavo, MISO:comunicación esclavo-maestro, SCK:señal de reloj
Añade una línea adicional por cada esclavo, aunque estas se pueden poner en cascada.
Aquí el esclavo sí puede comenzar la comunicación siempre que el maestro lo indique (LOW:inicia eclavo, HIGH: inicia maestro)
Utilizaremos la conexión por defecto:
HSPI	GPIO 13	GPIO 12	GPIO 14	GPIO 15

```
#include<Arduino.h>
//librerias
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid
//Definimos unas constantes
#define SS_PIN 5 //pin para la SS (SDA) del RC522
#define RST_PIN 17 //pin que usa como reset el RC522
const int ipaddress[4] = {103, 97, 67, 25};
//creamos otras variables que usaremos
byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN); //creamos un objeto para el RC522
void readRFID(void );
void printDec(byte *buffer, byte bufferSize);
void printHex(byte *buffer, byte bufferSize);

void loop() {
 readRFID();
}
void setup() {
 //Iniciamos La comunicacion serial a 115200
 Serial.begin(115200);
 Serial.println(F("Initialize System")); //println por la terminal
 //iniciamos el bus SPI
 SPI.begin();
 rfid.PCD_Init(); //inciamos el objeto MFRC522
 Serial.print(F("Reader :")); //lo mostramos por pantalla
 rfid.PCD_DumpVersionToSerial();
}

void readRFID(void ) { /* función readRFID */
 ////leemos la carta RFID
 for (byte i = 0; i < 6; i++) {
   key.keyByte[i] = 0xFF;
 }
 // Busca una nueva carta
 if ( ! rfid.PICC_IsNewCardPresent())
   return;
 // verifica si el NUID ha sido leído
 if (  !rfid.PICC_ReadCardSerial())
   return;
 // y lo guarda en un vector nuidPICC
 for (byte i = 0; i < 4; i++) {
   nuidPICC[i] = rfid.uid.uidByte[i];
 }
 Serial.print(F("RFID In dec: "));
 printDec(rfid.uid.uidByte, rfid.uid.size);
 Serial.println();
 // Detiene el PICCvoid printDec(byte *buffer, byte bufferSize)
 rfid.PICC_HaltA();
 // detiene la encriptación de PCD
 rfid.PCD_StopCrypto1();
}
/**
rutina de ayuda para pasar de una matriz de bytes en hexadecimales a serial
*/
void printHex(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], HEX);
 }
}
/**
 rutina de ayuda para pasar de una matriz de bytes en decimales a serial
*/
void printDec(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], DEC);
 }
}

```
En el video añadido se puede ver la salida:
