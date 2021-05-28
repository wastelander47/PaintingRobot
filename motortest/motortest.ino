//#include <Servo.h>

//Servo myservo;//定义舵机变量名
int in3=5;//右轮
int in4=3;
int in1=10;//左轮
int in2=9;
int val0=15;//
int val1=120;//walk
int val2=90;//画三角调整后退时的速度
int val3=150;//画圆时的差速
int val4=250;//画圆时的速度

int servopin=11;    //定义舵机接口数字接口7 也就是舵机的橙色信号线。

void servopulse(int angle)//定义一个脉冲函数
{
  int pulsewidth=(angle*11)+500;  //将角度转化为500-2480的脉宽值
  digitalWrite(servopin,HIGH);    //将舵机接口电平至高
  delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
  digitalWrite(servopin,LOW);     //将舵机接口电平至低
  delayMicroseconds(20000-pulsewidth);
}
void writeangle(int angle)
{
  for(int i=0;i<50;i++)  //发送50个脉冲
    servopulse(angle);   //引用脉冲函数
}
void stepback()
{
  walk(in2,in1);
  walk(in4,in3);
}
void walk(int pin1,int pin2)//当in1=1,in2=0,正转；in1=0,in2=1,反转；
{ 
  digitalWrite(pin1,HIGH); 
  digitalWrite(pin2,LOW);
  if ((pin1==in3)||(pin1==in4))
    analogWrite(pin1,val1);
  else 
    analogWrite(pin1,val1-val0);
} 
void stopper(int pin1,int pin2)//紧急制动，实际就是将电机两个端短接了 
{  
  digitalWrite(pin1,HIGH); 
  digitalWrite(pin2,HIGH); 
} 
void turnleft()
{
  walk(in2,in1);  
  walk(in3,in4);  
}
void turnright()
{
  walk(in4,in3);  
  walk(in1,in2);  
}
void drawtri()
{
  for (int i=1;i<=2;i++)
  {
    writeangle(0);
    walk(in1,in2);
    walk(in3,in4);
    delay(1000);
    writeangle(40);
    stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
    walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,val2-val0);
    analogWrite(in3,val2);
    delay(100);
    turnright();
    delay(390);
    stepback();
    analogWrite(in2,val2);
    analogWrite(in4,val2); 
    delay(200);  
  }
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(1000);
  writeangle(40);
  stopper(in1,in2);
  stopper(in3,in4);
  delay(500);
  turnright();
  delay(400);
  stepback();
  analogWrite(in2,val2);
  analogWrite(in4,val2); 
  delay(250); 
}
void drawcir(int val)
{
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  analogWrite(in3,val);
  analogWrite(in1,val-val0-val3);
  delay(2000); //time needs change
}
void setup() {
  // put your setup code here, to run once:
  //myservo.attach(11);
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT); 
  pinMode(in4,OUTPUT);
  pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
}

void loop() {
  writeangle(40);
  //myservo.write(45);
  // put your main code here, to run repeatedly:
  //walk(in1,in2);
  //walk(in3,in4);
  //analogWrite(in3,230);
  //analogWrite(in4,0); 
  //delay(2000);
  //stopper(in1,in2);
  //stopper(in3,in4);
  //delay(2000);
  //turnleft(95);
  //delay(1000);
  //stopper(in1,in2);
  //stopper(in3,in4);
  //delay(3000);*/
  drawcir(val4);
  stopper(in1,in2);
  stopper(in3,in4);
  delay(3000);
}
