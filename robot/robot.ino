// #define SONAR_TRIG_P  18
// #define SONAR_ECHO_P  19
#define SERVO_EN_A 9
#define SERVO_EN_B 4
#define SERVO_L_P1 8
#define SERVO_L_P2 7
#define SERVO_R_P1 6
#define SERVO_R_P2 5

uint8_t data[250];

void recieve_data(uint8_t* mac, uint8_t* incoming_data, uint8_t data_len){
  memcpy(&data, incoming_data, data_len)
  for(int i = 0; i < data_len; i++){
    Serial.println("New Recieved Data: ")
    Serial.println(myData[i]);
  }
}

void setup() {
  Serial.begin(115200);
  // pinMode(SONAR_TRIG_P, OUTPUT);
  // pinMode(SONAR_ECHO_P, INPUT); 

  pinMode(SERVO_EN_A, OUTPUT);
  pinMode(SERVO_EN_B, OUTPUT);

  pinMode(SERVO_L_P1, OUTPUT); 
  pinMode(SERVO_L_P2, OUTPUT); 
  pinMode(SERVO_R_P1, OUTPUT); 
  pinMode(SERVO_R_P2, OUTPUT);

  WiFi.mode(WIFI_STA);

  esp_now_register_recv_cb(
    esp_now_recv_cb_t(recieve_data)
  );
}

// long sonarDuration;   
// float distanceCm;

void loop() {
  turnLeft(1000);
  delay(2000);
  turnRight(1000); 
  delay(2000);

  // digitalWrite(SONAR_TRIG_P, LOW);
  // delayMicroseconds(2);
  // digitalWrite(SONAR_TRIG_P, HIGH);
  // delayMicroseconds(10);
  // digitalWrite(SONAR_TRIG_P, LOW);
   
  // // Read echo time
  // sonarDuration = pulseIn(SONAR_TRIG_P, HIGH);
   
  // // Convert time to distance (speed of sound = 0.034 cm/µs)
  // distanceCm = sonarDuration * 0.034 / 2;
   
  // // Display distance on serial monitor
  // Serial.print("Distance: ");
  // Serial.print(distanceCm);
  // Serial.println(" cm");
}

void stop(){
  Serial.println("stopping...");
  digitalWrite(SERVO_EN_A, LOW);
  digitalWrite(SERVO_EN_B, LOW);
  digitalWrite(SERVO_L_P1, LOW);
  digitalWrite(SERVO_L_P2, LOW);
  digitalWrite(SERVO_L_P1, LOW);
  digitalWrite(SERVO_R_P2, LOW);
}

void turnLeft(float duration){
  Serial.println("turning left...");
  digitalWrite(SERVO_EN_A, HIGH);
  digitalWrite(SERVO_EN_B, HIGH);

  digitalWrite(SERVO_L_P1, HIGH);
  digitalWrite(SERVO_L_P2, LOW);

  digitalWrite(SERVO_R_P1, LOW);
  digitalWrite(SERVO_R_P2, HIGH);

  delay(duration);

  stop();
}

void turnRight(float duration){
  Serial.println("turning right...");
  digitalWrite(SERVO_EN_A, HIGH);
  digitalWrite(SERVO_EN_B, HIGH);

  digitalWrite(SERVO_L_P1, LOW);
  digitalWrite(SERVO_L_P2, HIGH);

  digitalWrite(SERVO_R_P1, HIGH);
  digitalWrite(SERVO_R_P2, LOW);

  delay(duration);

  stop();
}
