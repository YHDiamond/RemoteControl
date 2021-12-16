#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  SerialBT.begin("Car"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //Write data recieved over Bluetooth to UART - for debugging purposes
    return;
  }
}
