#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xC4, 0x4F, 0x33, 0x66, 0xCA, 0xC1};
//C4:4F:33:66:CA:C1

typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

struct_message myData;

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  pinMode(32, INPUT_PULLUP); //Set pin 32 as pullup for joystick button
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  WiFi.mode(WIFI_STA);
  Serial.println("WiFi MAC Address: " + WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onDataSent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  }

  
}

void loop() {
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
  strcpy(myData.a, basicString);
  myData.b = random(1,20);
  myData.c = 1.2;
  myData.d = false;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
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
