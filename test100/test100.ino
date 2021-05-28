#include <Servo.h>
#include <IRremote.h>  // 使用IRRemote函数库

Servo myservo;//定义舵机变量名
const int irReceiverPin = 2;  // 红外接收器的 OUTPUT 引脚接在 PIN2 接口 定义irReceiverPin变量为PIN2接口
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置
int ena=
int enb=
int in1=
int in2=
int in3=
int in4=
int len;
int wid;
int val1=; //PWM值120度
int val2=; //300度
int val3=; //90度
int t=?; //小车走1cm需要多久

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
  analogWrite(enb,val);
  walk(in3,in4);
  walk(in2,in1);  
}
void turnright(int val)
{
  analogWrite(ena,val);
  walk(in1,in2);
  walk(in4,in3);  
}
void drawtri()
{
  myservo.write(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(3000);
  turnright(val1);
  delay(1000);
  walk(in1,in2);
  walk(in3,in4);
  delay(3000);
  turnright(val2);
  delay(1000);
  walk(in1,in2);
  walk(in3,in4);
  delay(3000);
  turnright(val1);
  delay(1000);
}
void drawcir()
{
  myservo.write(0);
  walk(in1,in2);
  stopper(in3,in4);
  delay(4000); //time needs change
}
void drawrect(int l,int w)
{
  myservo.write(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(w*t);
  turnright(val3);
  delay(1000);
  walk(in1,in2);
  walk(in3,in4);
  delay(l*t);
  turnright(val3);
  delay(1000);
  walk(in1,in2);
  walk(in3,in4);
  delay(w*t);
  turnright(val3);
  delay(1000);
  walk(in1,in2);
  walk(in3,in4);
  delay(l*t);
  turnright(val3);
  delay(1000);
}
int number(int ircode)
{
  switch (ircode)
  {
    case  0xFF6897:
      return 1;
    case 0xFF9867:
      return 2;
    case 0xFFB04F:
      return 3; 
    case 0xFF30CF:
      return 4;  
    case 0xFF18E7:
      return 5; 
    case 0xFF7A85:
      return 6; 
    case 0xFF10EF:
      return 7; 
    case 0xFF38C7:
      return 8; 
    case 0xFF5AA5:
      return 9;  
  }
}
void setup() 
{ 
  myservo.attach(9);//定义舵机数字接口9
  Serial.begin(9600); 
  irrecv.enableIRIn();   // 启动红外解码
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT); 
  pinMode(in4,OUTPUT);
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT); 
  //下面程序开始时让控制端都为高电平，电机保持不动。 
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,HIGH); 
  digitalWrite(in3,HIGH); 
  digitalWrite(in4,HIGH); 
}
void loop()
{
  myservo.write(45);
  if (irrecv.decode(&results)) {   // 解码成功，把数据放入results变量中          
    switch (results.value)
    {
      case 0xFF6897:
        drawtri();
        break;
      case 0xFF9867:
        drawcir();
        break;
      case 0xFFB04F:
        irrecv.resume();
        while(1)
        {
          if (irrecv.decode(&results))
          { 
            len=number(results.value);
            Serial.print("len=");
            Serial.println(len);
            break;
          }
        }
        delay(600);
        irrecv.resume();
        while (1)
        {
          if (irrecv.decode(&results)) 
          {
            wid=number(results.value); 
            Serial.print("wid=");
            Serial.println(wid);
            break;
          }
        }
        drawrect(len,wid);
        break;
      case 0xFF629D:
        walk(in1,in2);
        walk(in3,in4)
        break;
      case 0xFFA857:
        walk(in2,in1);
        walk(in4,in3);
        break;
      case 0xFF22DD:
        turnleft(val3);
        break;
      case 0xFFC23D:
        turnright(val3);
        break;
      case 0xFF02FD:
        stopper(in1,in2);
        stopper(in3,in4);
        warnlight();
        break;
      default: 
        warnlight(); 
    }
    irrecv.resume();    // 继续等待接收下一组信号
}
