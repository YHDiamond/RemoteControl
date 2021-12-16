#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  SerialBT.begin("Car"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {

  // TODO:
  // - Pair both ESP32s together
  // - Actually store the data recieved from the remote instead of just pushing it out of the UART
  // - Write a parser for recieved joystick data

  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //Write data recieved over Bluetooth to UART - for debugging purposes
    return;
  }
}
