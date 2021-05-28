#include <Stepper.h>
#define STEPS 200
Stepper stepper(STEPS, 4,5,8,6);
Stepper stepper1(STEPS,9,10,12,13);
int v1=60;
int v2=60;
void setup() {
  stepper.setSpeed(v1);
  stepper1.setSpeed(v2);
}
void walk(){
   for(int i=0;i<=STEPS;i++){
   stepper.step(1);
   //delay(500);
   stepper1.step(1);
  }
  delay(500);
}
void stepback(){
   for(int i=0;i<=STEPS;i++){
   stepper.step(-1);
   stepper1.step(-1);
  }
}
void stopper(){
   stepper.step(0);
   stepper1.step(0);
  }


void turnleft(){
  for(int i=0;i<=STEPS;i++){
   stepper.step(1);
   stepper1.step(2);
  }
}
void turnright(){
  for(int i=0;i<=STEPS;i++){
   stepper.step(2);
   stepper1.step(1);
  }
}
void drawtri(){
  for(int i=1;i<=2;i++){
    walk();
    stopper();
   //之后的左转还要像左转一样现调，画矩形，圆形同理
  }
}
void loop() {
  // put your main code here, to run repeatedly:
walk();
 
 
 
 //等等其他功能
}
