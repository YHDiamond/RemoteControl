#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  pinMode(32, INPUT_PULLUP); //Set pin 32 as pullup for joystick button
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  SerialBT.begin("CarRemote"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); //Write data recieved over bluetooth to UART - for debugging purposes; in the final product the car will have no need to communicate back.
    return;
  }
  String total = "";  
  int x = analogRead(34); //Initialize pin 34 for analog read of joystick x potentiometer
  int y = analogRead(35); //Initialize pin 35 for analog read of joystick y potentiometer
  int b = digitalRead(32); //Initialize pin 32 for digital read of joystick button.

//Concatenate output
  total = total + format(x);
  total = total + format(y);
  total = total + b;
  char basicString[9] = {};
  total.toCharArray(basicString, 10);
  for (int i = 0; i <= 8; i++) {
    SerialBT.write(basicString[i]); //Write output to Bluetooth serial port
  }
  SerialBT.write('\n');
  delay(100); //100ms delay to make output more human-readable. Will be removed or reduced eventually to reduce latency.
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
