#include <esp_now.h>
#include <esp_mac.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// #define SONAR_TRIG_P  18
// #define SONAR_ECHO_P  19
#define WHEEL_EN_A 9
#define WHEEL_EN_B 4
#define WHEEL_L_P1 8
#define WHEEL_L_P2 7
#define WHEEL_R_P1 6
#define WHEEL_R_P2 5
#define SERVO_R_PIN 11
#define SERVO_L_PIN 10
#define AUTO_PIN 1

Servo servo_r;
Servo servo_l;

float servo_angle;
float servo_speed;

uint8_t data[250];

void recieve_data(uint8_t* mac, uint8_t* incoming_data, uint8_t data_len){
  memcpy(&data, incoming_data, data_len);
  Serial.println(data[4]);
}

void setup() {
  Serial.begin(115200);
  // pinMode(SONAR_TRIG_P, OUTPUT);
  // pinMode(SONAR_ECHO_P, INPUT); 

  pinMode(WHEEL_EN_A, OUTPUT);
  pinMode(WHEEL_EN_B, OUTPUT);

  pinMode(WHEEL_L_P1, OUTPUT); 
  pinMode(WHEEL_L_P2, OUTPUT); 
  pinMode(WHEEL_R_P1, OUTPUT); 
  pinMode(WHEEL_R_P2, OUTPUT);

  pinMode(AUTO_PIN, OUTPUT);

  servo_r.attach(SERVO_R_PIN, 500, 2400);
  servo_l.attach(SERVO_L_PIN, 500, 2400);

  servo_angle = 0;
  servo_speed = 0.5;

  uint8_t mac_addr[6];
  esp_err_t response = esp_base_mac_addr_get(mac_addr);
  if(response == ESP_OK){
    Serial.println("Robot's Mac address: ");
    Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  }
  else{
    Serial.println("Failed to get mac address");
  }

  WiFi.mode(WIFI_STA);
  esp_now_init();

  esp_now_register_recv_cb(
    esp_now_recv_cb_t(recieve_data)
  );
}

// long sonarDuration;   
// float distanceCm;

void loop() {
  if(digitalRead(AUTO_PIN)){
    autonomous();
    return;
  }
  servo_r.write(servo_angle);
  servo_l.write(servo_angle);

  // forward
  if(data[0]){
    move_forward();
  }
  // backward
  else if(data[1]){
    move_backward();
  }
  // turn left
  else if(data[2]){
    turn_left();
  }
  // turn right
  else if(data[3]){
    turn_right();
  }
  // action 1
  else if(data[4]){
    do_action_1();
  }
  // action 2
  else if(data[5]){
    do_action_2();
  }
  else{
    stop();
  }
}

void do_action_1(){
  Serial.println("performing action 1...");
  if(servo_angle < 180){
    servo_angle += servo_speed;
  }
}

void do_action_2(){
  Serial.println("performing action 2...");
  if(servo_angle > 0){
    servo_angle -= servo_speed;
  }
}

void stop(){
  Serial.println("stopping...");
  digitalWrite(WHEEL_EN_A, LOW);
  digitalWrite(WHEEL_EN_B, LOW);
  digitalWrite(WHEEL_L_P1, LOW);
  digitalWrite(WHEEL_L_P2, LOW);
  digitalWrite(WHEEL_L_P1, LOW);
  digitalWrite(WHEEL_R_P2, LOW);
}

void turn_left(){
  Serial.println("turning left...");
  digitalWrite(WHEEL_EN_A, HIGH);
  digitalWrite(WHEEL_EN_B, HIGH);

  digitalWrite(WHEEL_L_P1, HIGH);
  digitalWrite(WHEEL_L_P2, LOW);

  digitalWrite(WHEEL_R_P1, HIGH);
  digitalWrite(WHEEL_R_P2, LOW);
}

void turn_right(){
  Serial.println("turning right...");
  digitalWrite(WHEEL_EN_A, HIGH);
  digitalWrite(WHEEL_EN_B, HIGH);

  digitalWrite(WHEEL_L_P1, LOW);
  digitalWrite(WHEEL_L_P2, HIGH);

  digitalWrite(WHEEL_R_P1, LOW);
  digitalWrite(WHEEL_R_P2, HIGH);
}

void move_forward(){
  Serial.println("moving forward...");
  digitalWrite(WHEEL_EN_A, HIGH);
  digitalWrite(WHEEL_EN_B, HIGH);

  digitalWrite(WHEEL_L_P1, LOW);
  digitalWrite(WHEEL_L_P2, HIGH);

  digitalWrite(WHEEL_R_P1, HIGH);
  digitalWrite(WHEEL_R_P2, LOW);
}

void move_backward(){
  Serial.println("moving backward...");
  digitalWrite(WHEEL_EN_A, HIGH);
  digitalWrite(WHEEL_EN_B, HIGH);

  digitalWrite(WHEEL_L_P1, HIGH);
  digitalWrite(WHEEL_L_P2, LOW);

  digitalWrite(WHEEL_R_P1, LOW);
  digitalWrite(WHEEL_R_P2, HIGH);
}

void autonomous(){
  digitalWrite(WHEEL_EN_A, HIGH);
  digitalWrite(WHEEL_EN_B, HIGH);

  digitalWrite(WHEEL_L_P1, LOW);
  digitalWrite(WHEEL_L_P2, HIGH);

  delay(5000);

  stop();

  move_forward();

  delay(1000);
}