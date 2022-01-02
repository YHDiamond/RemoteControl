#include <esp_now.h>
#include <WiFi.h>

//Store the MAC address of the car that we need to send data to
uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x5F, 0x1E, 0x94};

//struct with data to be sent
typedef struct struct_message {
  int x;
  int y;
  bool button;
} struct_message;
struct_message myData;

//Return on serial whether data packet was sent successfully. I'm not exactly sure how the esp_now library works, and this method may call another method with its input parameters. The Serial statements are for debugging and will be removed.
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  //Set pin 32 as pulled up input for the joystick's button.
  pinMode(32, INPUT_PULLUP);

  //Open debug serial port. Will be removed in the final product.
  //Serial.begin(115200);

  //Set the WiFi chipset mode to station
  WiFi.mode(WIFI_STA);

  //Return MAC address on serial port. For debugging purposes; will be removed in the final product.
  //Serial.println("WiFi MAC Address: " + WiFi.macAddress());

  //Initialize ESPNOW
  esp_now_init();

  //Register onDataSent as callback function
  esp_now_register_send_cb(onDataSent);

  //Create a peerinfo object with information about how and where the data is being sent
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  int x = analogRead(34); //Read joystick X potentiometer
  int y = analogRead(35); //Read of joystick Y potentiometer
  int b = digitalRead(32); //Read joystick button state

  //Concatenate output
  myData.x = x;
  myData.y = y;
  myData.button = !b;

  //Send data
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(50);
}
