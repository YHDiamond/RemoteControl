#include <esp_now.h>
#include <WiFi.h>

#define Y_LOW 1700
#define Y_HIGH 2000

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
  Serial.print(buttonState);
  byte power;
  if (y <= Y_LOW) {
    power = map(y, 0, Y_LOW, 255, 0);

    digitalWrite(19, LOW);
    analogWrite(18, power);
    digitalWrite(5, LOW);
    analogWrite(17, power);
  } else if (y >= Y_HIGH) {
    power = map(y, Y_HIGH, 4096, 0, 255);
    analogWrite(19, power);
    digitalWrite(18, LOW);
    analogWrite(5, power);
    digitalWrite(17, LOW);
  } else {
    digitalWrite(19, LOW);
    digitalWrite(18, LOW);
    digitalWrite(5, LOW);
    digitalWrite(17, LOW);   
  }
  Serial.print("; Power: ");
  Serial.println(power);

  
// < and > are reversed because the potentiometer reading is low at the top and high at the bottom.
//  if (y < forward_threshold) {
  //PWM both motors at maximum forward speed
//}

//  if (y > reverse_threshold) {
  //PWM both motors at maximum reverse speed
//}

//  if (buttonState == true) {
  //Do something fun
//}z

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
