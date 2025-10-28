#include <esp_now.h>
#include <WiFi.h>
#include <esp_err.h>

#define RIGHT 1
#define TOP 2
#define LEFT 4
#define BOT 5
#define ACTION_1 21
#define ACTION_2 47

// robot mac address here
uint8_t robot_mac[] = {0x80, 0xb5, 0x4e, 0xe3, 0x1d, 0x54};
esp_now_peer_info_t peer_connection;

// custom data package object to send to robot
typedef struct{
  bool forward;
  bool backward;
  bool turn_left;
  bool turn_right;
  bool action_1;
  bool action_2;
} data_package;

// creating data packages
data_package new_data;
data_package prev_data;

void setup(){
  Serial.begin(115200);
  
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(TOP, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(BOT, INPUT_PULLUP);
  pinMode(ACTION_1, INPUT_PULLUP);
  pinMode(ACTION_2, INPUT_PULLUP);

  WiFi.mode(WIFI_MODE_STA);
  esp_now_init();

  // initializing peer connection and assigning robot mac
  memcpy(peer_connection.peer_addr, robot_mac, 6);
  peer_connection.channel = 0;
  peer_connection.encrypt = false;
  peer_connection.ifidx = WIFI_IF_STA;

  esp_now_add_peer(&peer_connection);
}

void loop(){
  new_data.forward = !digitalRead(TOP);
  new_data.backward = !digitalRead(BOT);
  new_data.turn_left = !digitalRead(LEFT);
  new_data.turn_right = !digitalRead(RIGHT);
  new_data.action_1 = !digitalRead(ACTION_1);
  new_data.action_2 = !digitalRead(ACTION_2);

  if(
    new_data.forward != prev_data.forward ||
    new_data.backward != prev_data.backward ||
    new_data.turn_left != prev_data.turn_left ||
    new_data.turn_right != prev_data.turn_right ||
    new_data.action_1 != prev_data.action_1 ||
    new_data.action_2 != prev_data.action_2
  ){
    memcpy(&prev_data, &new_data, sizeof(&new_data));
    esp_err_t response = esp_now_send(robot_mac, (uint8_t*)&new_data, sizeof(new_data));
    if(response == ESP_OK){
      Serial.println("Data sent successfully");
    }
    else{
      Serial.println(response);
    }
  }

  delay(50);
}
