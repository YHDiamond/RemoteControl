// Serial communication with Bluetooth HM-10
// Uses serial monitor for communication with Bluetooth HM-10
//
//  Arduino to HM-10 connections
//  Arduino pin 2 (TX) to voltage divider then to HM-10 RX
//  Arduino pin 3 to HM-10 TX
//  Connect GND from the Arduiono to GND on the HM-10
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay the command to the HM-10


// Library to make a Software UART
#include <SoftwareSerial.h>

#define RX 2
#define TX 3

#define BAUDRATE 9600

char c = ' ';
boolean new_line = true;

// Instantiation of a Software UART
SoftwareSerial HM10(RX, TX); // (RX, TX)

void setup() {  

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);
  
  // HM-10 default speed in AT command mode
  HM10.begin(BAUDRATE);
  Serial.println("HM10 serial started at 9600");
  
  Serial.println("Enter AT commands:");
}

void loop() {
  HM10.listen();
  while (HM10.available() > 0) {
    char c = HM10.read();
    Serial.println(c);
  }
  if (Serial.available()) {
    delay(10);
    HM10.write(Serial.read());
  }
}
