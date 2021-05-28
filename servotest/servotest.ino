#include <Servo.h>

Servo myservo;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(0);
  delay(3000);
  myservo.write(45);
  delay(3000);
}
