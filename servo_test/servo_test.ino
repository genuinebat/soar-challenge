#include <ESP32Servo.h>

#define S_PIN 10

Servo s;

void setup(){
  Serial.begin(115200);
  s.attach(S_PIN, 500, 2400);
}

void loop(){
  Serial.write("turning to 180");
  s.write(180);
  delay(2000);
  Serial.write("turning to 0");
  s.write(0);
  delay(2000);
}