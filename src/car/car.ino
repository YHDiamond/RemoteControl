#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int x;
  int y;
  bool button;
} struct_message;

struct_message myData;

void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  int x = myData.x;
  int y = myData.y;
  bool buttonState = myData.button;
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("; Y: ");
  Serial.print(y);
  Serial.print("; Button: ");
  Serial.println(buttonState);

// < and > are reversed because the potentiometer reading is low at the top and high at the bottom.
//  if (y < forward_threshold) {
  //PWM both motors at maximum forward speed
//}

//  if (y > reverse_threshold) {
  //PWM both motors at maximum reverse speed
//}

//  if (buttonState == true) {
  //Do something fun
//}

}

void setup() {
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(17,OUTPUT);
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);

//  while (true) {
//    digitalWrite(19, HIGH);
//    delay(100);
//    digitalWrite(19, LOW);
//    delay(100);
//    digitalWrite(18, HIGH);
//    delay(100);
//    digitalWrite(18, LOW);
//    delay(100);
//    digitalWrite(5, HIGH);
//    delay(100);
//    digitalWrite(5, LOW);
//    delay(100);
//    digitalWrite(17, HIGH);
//    delay(100);
//    digitalWrite(17, LOW);
//    delay(100);
  }
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("WiFi MAC Address: " + WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {

  }
