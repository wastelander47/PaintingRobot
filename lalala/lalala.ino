#include <IRremote.h>
IRsend irsend;//发射红外线的借口默认接为3口，故不用声明
IRrecv irrecv(RECV_PIN);
int RECV_PIN=2;//在2口接收红外线
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
irrecv.enableIRIn();

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(3,HIGH);
State=analogRead(RECV_PIN);
if(State == HIGH);
{walk(in1,in2);
walk(in3,in4);}
else
{stopper(in1,in2);
stopper(in3,in4);}
}
