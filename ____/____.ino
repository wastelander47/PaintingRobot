int in1=9;
int in2=6;
int in3=5;
int in4=3;
void walk(int pin1,int pin2)//当in1=0,in2=1,正转；in1=1,in2=0,反转；
{ 
  digitalWrite(pin1,LOW); 
  digitalWrite(pin2,HIGH); 
} 
void stopper(int pin1,int pin2)//紧急制动，实际就是将电机两个端短接了 
{  
  digitalWrite(pin1,HIGH); 
  digitalWrite(pin2,HIGH); 
} 
void turnleft(int val)
{
  //analogWrite(enb,val);
  walk(in3,in4);
  walk(in2,in1);  
}
void turnright(int val)
{
  //analogWrite(ena,val);
  walk(in1,in2);
  walk(in4,in3);  
}
void setup() {
  // put your setup code here, to run once:
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT); 
  pinMode(in4,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  walk(in1,in2);
  walk(in3,in4);
  delay(3000);
}
