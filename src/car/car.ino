#include <WiFi.h>

void setup() {
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("WiFi MAC Address: " + WiFi.macAddress());
}

void loop() {

  }
