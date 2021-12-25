#include <ESP32_Servo.h>
#include <analogWrite.h>
#include <esp_now.h>
#include <WiFi.h>

#define servoPin 4

//Threshold values for Y axis dead zone
#define Y_LOW 1700
#define Y_HIGH 2000
Servo servo;
//struct with data to be recieved
typedef struct struct_message {
  int x;
  int y;
  bool button;
} struct_message;
struct_message myData;

void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  //When data is recieved, store it in local variables x, y, and buttonState
  int x = myData.x;
  int y = myData.y;
  bool buttonState = myData.button;
  //Print recieved data to serial port. For debugging only; will be removed to reduce latency in final product.
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("; Y: ");
  Serial.print(y);
  Serial.print("; Button: ");
  Serial.print(buttonState);

  //Convert recieved Y axis data to an 8-bit value, and write the value to the respective H-bridge pins
  byte power = 0;
  if (y <= Y_LOW) {
    power = map(y, 0, Y_LOW, 255, 0);
    analogWrite(19, LOW);
    analogWrite(18, power);
    analogWrite(5, LOW);
    analogWrite(17, power);
  } else if (y >= Y_HIGH) {
    power = map(y, Y_HIGH, 4096, 0, 255);
    analogWrite(19, power);
    analogWrite(18, LOW);
    analogWrite(5, power);
    analogWrite(17, LOW);
  }
  //Write 8-bit power value to serial port. For debugging only; will be removed to reduce latency in the final product.
  Serial.print("; Power: ");
  Serial.print(power);

  //Extra reassurance that if the joystick is in the center and not being moved, that the motors will not spin.
  if (power == 0) {
    analogWrite(19, LOW);
    analogWrite(18, LOW);
    analogWrite(5, LOW);
    analogWrite(17, LOW);
  }
 
  byte position = 90;
  if (x <= Y_LOW) {
    position = map(x, 0, Y_LOW, 0, 90);
  } else if (x >= Y_HIGH) {
    position = map(x, Y_HIGH, 4096, 90, 180);
  }
  servo.write(position);
  Serial.print("; ServPos: ");
  Serial.println(position);

}

//Because of the way the ESPNOW protocol works, the connection is always maintained and the method never completes. Thus, there is no need for a loop method, only a setup method.
void setup() {
  //Define pins for the H-bridge connections and set them to low, because some of them start high.
  pinMode(19, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(17,OUTPUT);
  digitalWrite(19, LOW);
  digitalWrite(18, LOW);
  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
  servo.attach(servoPin);
  //Open debug serial port. Will be removed in the final product.
  Serial.begin(115200);

  //Set the Wifi chipset mode to station, return the MAC address on the serial port, and initialize ESPNOW.
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("WiFi MAC Address: " + WiFi.macAddress());
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //Execute callback function onDataRecv when data is recieved
  esp_now_register_recv_cb(onDataRecv);
}


//Loop method does nothing but needs to be declared.
void loop() {
  
}
