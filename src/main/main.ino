#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
//int x = IO32;

  // initialize digital pins for Bluetooth Tx and Rx
  // initialize analog pins for joystick x and y

  //Whatever code we need to use to interface with the Bluetooth module
}

void loop() {
  // put your main code here, to run repeatedly:
void setup() {
  pinMode(32, INPUT_PULLUP);
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(Serial.read());
    return;
  }
  
  String total = "";
  int x = analogRead(34);
  int y = analogRead(35);
  int b = digitalRead(32);
  total = total + format(x);
  total = total + format(y);
  total = total + b;
  char basicString[8] = {};
  total.toCharArray(basicString, 9);
  for (int i = 0; i < 9; i++) {
    SerialBT.write(basicString[i]);
  }
  SerialBT.write('\n');
  //SerialBT.write(basicString);
  delay(100);
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
