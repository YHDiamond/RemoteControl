#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  SerialBT.begin("Car"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //Write data recieved over bluetooth to UART - for debugging purposes; in the final product the car will have no need to communicate back.
    return;
  }
    //char c = 'A';
    //SerialBT.write(c); //Write output to Bluetooth serial port
    //delay(100); //100ms delay to make output more human-readable. Will be removed or reduced eventually to reduce latency.
}


String format(int i) {
  String base = String(i);
  switch (base.length()) {
    case 1:
      return String("000") + base;
    case 2: 
      return String("00") + base;
    case 3: 
      return String("0") + base;
    default:
      return base;
  }
 
}
