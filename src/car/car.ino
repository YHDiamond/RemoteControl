#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int x;
  int y;
  bool button;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("X: ");
  Serial.print(myData.x);
  Serial.print("; Y: ");
  Serial.print(myData.y);
  Serial.print("; Button: ");
  Serial.println(myData.button);
}

void setup() {
  Serial.begin(115200); //Open serial port at 115200 baud for Bluetooth transmission
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("WiFi MAC Address: " + WiFi.macAddress());
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

  }
