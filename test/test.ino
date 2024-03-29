                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      #include <IRremote.h>  // 使用IRRemote函数库

const int irReceiverPin = 2;  // 红外接收器的 OUTPUT 引脚接在 PIN2 接口 定义irReceiverPin变量为PIN2接口
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;    // 定义results变量为红外结果存放位置
int in3=6;//右轮
int in4=5;
int in1=10;//左轮
int in2=9;
int val0=15;//左轮快，调整差速
int val1=120;//walk
int val2=90;//画三角调整后退时的速度
int val3=150;//画圆时的差速
int val4=250;//画圆时的速度
int val5=180;
int servopin=11;    //定义舵机接口数字接口11 也就是舵机的橙色信号线
int servopin_bo=7;
int angle=40;  //舵机抬笔角度
int len;
int wid;
int t=100; //矩形的单位时间
int voice=3;  //蜂鸣器
int led=8; //LED灯
int Echo = A1;  // Echo回声脚(P2.0)
int Trig =A0;  //  Trig 触发脚(P2.1)
int Front_Distance = 0;//
int Left_Distance = 0;
int Right_Distance = 0;

//--------------------------------蓝牙模式-------------------------------//
void bluetooth() 
{ 
  char val;
  while(1)
  {
    if (Serial.available())
    {
      val = Serial.read();
      if(val=='E') break;
      else
        switch (val)
        {
          case 'T':  //1
            Serial.println("Triangle"); 
            digitalWrite(led,HIGH);
            drawtri();
            stopper(in1,in2);
            stopper(in3,in4);
            break;
          case 'C':  //2
            Serial.println("Circle"); 
            digitalWrite(led,HIGH);
            drawcir(val4);
            stopper(in1,in2);
            stopper(in3,in4);
            break;
          case 'Z':  //3
            Serial.println("Square"); 
            digitalWrite(led,HIGH);
            drawrect(6,6);
            stopper(in1,in2);
            stopper(in3,in4);
            break;
          case 'J':  //4
            Serial.println("Rectangle"); 
            digitalWrite(led,HIGH);
            drawrect(15,10);
            stopper(in1,in2);
            stopper(in3,in4);
            break;
          case 'M':  //5
            Serial.println("Music"); 
            digitalWrite(led,HIGH);
            playMusic();
          case 'W':  //上
          {
            Serial.println("Go forward!"); 
            digitalWrite(led,HIGH);
            walk(in1,in2);
            walk(in3,in4);
            break;
          }
          case 'B':  //下
            Serial.println("Go back!"); 
            digitalWrite(led,HIGH);
            stepback(val1);
            break;
          case 'L':  //左
            Serial.println("Turn left!"); 
            digitalWrite(led,HIGH);
            turnleft();
            break;
          case 'R':  //右
            Serial.println("Turn right!"); 
            digitalWrite(led,HIGH);
            turnright();
            break;
          case 'S':  //OK制停
            Serial.println("Stop!"); 
            stopper(in1,in2);
            stopper(in3,in4);
            twinkle(1);
            break;
          case 'Q':
            Serial.println("Lift the pen!");
            writeangle(40);
            break;
          case 'D':
            Serial.println("Put down the pen!");
            writeangle(0);
            break;
          case 'U':
            Serial.println("Ultrasonic obstacle avoidance mode!"); 
            twinkle(3);
//            chaoshengbo();
            break;
        }
    }
  }
}

//--------------------------------蜂鸣器播放音乐-------------------------------//
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(voice, HIGH);
    delayMicroseconds(tone);
    digitalWrite(voice, LOW);
    delayMicroseconds(tone);
  }
} 
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
 
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
void playMusic(){
   for (int i = 0; i < length; i++) {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); // rest
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   // pause between notes
   delay(tempo / 2); 
 }
}

//--------------------------------控制舵机-------------------------------//
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

//--------------------------------小车运动-------------------------------//
void walk(int pin1,int pin2)//当in1=1,in2=0,正转；in1=0,in2=1,反转；
{ 
  digitalWrite(pin1,HIGH); 
  digitalWrite(pin2,LOW);
  if ((pin1==in3)||(pin1==in4))
    analogWrite(pin1,val1);
  else 
    analogWrite(pin1,val1-val0);
} 
void stepback(int val)
{
  walk(in2,in1);
  walk(in4,in3);
  analogWrite(in2,val);
  analogWrite(in4,val);
}
void stopper(int pin1,int pin2)//紧急制动，实际就是将电机两个端短接了 
{  
  digitalWrite(pin1,HIGH); 
  digitalWrite(pin2,HIGH); 
} 
void left(int tim)
{
  stopper(in1,in2);
  walk(in3,in4);
  analogWrite(in3,100);
  delay(tim*100);
}
void right(int tim)
{
  stopper(in3,in4);
  walk(in1,in2);
  analogWrite(in1,100);
  delay(tim*100);
}
void turnleft()
{
  walk(in3,in4);
  walk(in2,in1);  
}
void turnright()
{
  walk(in1,in2);
  walk(in4,in3);  
}

//--------------------------------小车画图-------------------------------//
void drawtri()
{
  for (int i=1;i<=2;i++)
  {
    writeangle(0);
    walk(in1,in2);
    walk(in3,in4);
    //analogWrite(in1,val5-val0);
    //analogWrite(in3,val5);
    delay(700);
    stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
    writeangle(40);
    walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
    //walk(in1,in2);
    //walk(in3,in4);
    //analogWrite(in1,val2-val0);
    //analogWrite(in3,val2);
    //delay(100);
    turnright();
    //analogWrite(in1,val5-val0);
    //analogWrite(in3,val5);
    if (i==1)
     delay(470);
    else delay(480);
    stepback(val2);
    delay(360);  
    stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  }
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  //analogWrite(in1,val5-val0);
  //analogWrite(in3,val5);
  delay(700);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(40);
  walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
  turnright();
  //analogWrite(in1,val5-val0);
  //analogWrite(in3,val5);
  delay(470);
  stepback(val2);
  delay(360); 
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
}
void drawcir(int val)
{
  writeangle(0);
  stopper(in1,in2);
  walk(in3,in4);
  analogWrite(in3,val);
  //analogWrite(in1,val-val0-val3);
  delay(2000); //time needs change
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
   writeangle(40);
}
void drawrect(int l,int w)
{
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(w*t);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(40);
  walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
  turnright();
  delay(350);
  stepback(val1);
  delay(330);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(l*t);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(40);
  walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
  turnright();
  delay(350);
  stepback(val1);
  delay(330);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(w*t);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(40);
  walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
  turnright();
  delay(350);
  stepback(val1);
  delay(330);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(0);
  walk(in1,in2);
  walk(in3,in4);
  delay(l*t);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
  writeangle(40);
  walk(in1,in2);
    walk(in3,in4);
    analogWrite(in1,120-val0);
    analogWrite(in3,120);
    delay(370);
  turnright();
  delay(350);
  stepback(val1);
  delay(330);
  stopper(in1,in2);
    stopper(in3,in4);
    delay(500);
}

//--------------------------------红外译码-------------------------------//
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

//--------------------------------蜂鸣器报警-------------------------------//
void warn()
{
  for (int i=1;i<=2;i++)
  {
     digitalWrite(voice,HIGH);
     delay(500);
     digitalWrite(voice,LOW);
     delay(500);
  }
}

//--------------------------------LED灯闪烁-------------------------------//
void twinkle(int tim)
{
  for (int i=1;i<=tim;i++)
  {
    digitalWrite(led,HIGH);
    delay(500);
    digitalWrite(led,LOW);
    delay(500);
    digitalWrite(led,HIGH);
  }
}

//--------------------------------超声波避障-------------------------------//
float Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  //Serial.print("Distance:");      //输出距离（单位：厘米）
  Serial.println(Fdistance);         //显示距离
  //Distance = Fdistance
  return Fdistance;
}  
void front_detection()
{
  //此处循环次数减少，为了增加小车遇到障碍物的反应速度
  for(int i=0;i<=5;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    //Serial.println("www");
    servopulse(servopin_bo,90);//模拟产生PWM
  }
  Front_Distance = Distance_test();
  //Serial.print("Front_Distance:");      //输出距离（单位：厘米）
 // Serial.println(Front_Distance);         //显示距离
 //Distance_display(Front_Distance);
}
void left_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin_bo,175);//模拟产生PWM
  }
  Left_Distance = Distance_test();
  //Serial.print("Left_Distance:");      //输出距离（单位：厘米）
  //Serial.println(Left_Distance);         //显示距离
}
void right_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin_bo,5);//模拟产生PWM
  }
  Right_Distance = Distance_test();
  //Serial.print("Right_Distance:");      //输出距离（单位：厘米）
  //Serial.println(Right_Distance);         //显示距离
}
void chaoshengbo()
{
  irrecv.resume(); 
  while(1)
  {
    if (irrecv.decode(&results))
      if (results.value==0xFF02FD) break;
    front_detection();//测量前方距离
    if(Front_Distance < 30)//当遇到障碍物时
    {
      stepback(val1);//后退减速
      delay(200);
      stopper(in1,in2);//停下来做测距
      stopper(in3,in4);
      delay(200);
      left_detection();//测量左边距障碍物距离
     // Distance_display(Left_Distance);//液晶屏显示距离
      right_detection();//测量右边距障碍物距离
      //Distance_display(Right_Distance);//液晶屏显示距离
      if((Left_Distance < 30 ) &&( Right_Distance < 30 ))//当左右两侧均有障碍物靠得比较近
      {
        turnleft();//旋转掉头
        analogWrite(in2,100);
        analogWrite(in3,100);
        delay(70);
      }
      else if(Left_Distance > Right_Distance)//左边比右边空旷
      {      
        left(3);//左转
        stopper(in1,in2);//刹车，稳定方向
        stopper(in3,in4);
        delay(100);
      }
      else//右边比左边空旷
      {
        right(3);//右转
        stopper(in1,in2);//刹车，稳定方向
        stopper(in3,in4);
        delay(100);
      }
    }
    else
    {
      walk(in1,in2);//无障碍物，直行 
      walk(in3,in4);
      analogWrite(in1,80-val0);
      analogWrite(in3,80);
      delay(400);    
    }
  } 
}

//--------------------------------主程序-------------------------------//
void setup() 
{ 
  Serial.begin(9600); 
  irrecv.enableIRIn();   // 启动红外解码
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT); 
  pinMode(in4,OUTPUT);
  pinMode(voice,OUTPUT);
  pinMode(led,OUTPUT); 
  pinMode(servopin,OUTPUT);
  pinMode(servopin_bo,OUTPUT);
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  //下面程序开始时让控制端都为高电平，电机保持不动。 
  //digitalWrite(in1,HIGH); 
  //digitalWrite(in2,HIGH); 
  //digitalWrite(in3,HIGH); 
  //digitalWrite(in4,HIGH); 
}
void loop()
{
  digitalWrite(led,LOW);
  writeangle(40);
  if (irrecv.decode(&results)) {   // 解码成功，把数据放入results变量中        
    Serial.println(results.value,HEX);  
    switch (results.value)
    {
      case 0xFF6897:  //1
        digitalWrite(led,HIGH);
        drawtri();
        stopper(in1,in2);
        stopper(in3,in4);
        break;
      case 0xFF9867:  //2
        digitalWrite(led,HIGH);
        drawcir(val4);
        stopper(in1,in2);
        stopper(in3,in4);
        break;
      case 0xFFB04F:  //3
        digitalWrite(led,HIGH);
        drawrect(6,6);
        stopper(in1,in2);
        stopper(in3,in4);
        break;
      case 0xFF30CF:  //4
        digitalWrite(led,HIGH);
        drawrect(15,10);
        stopper(in1,in2);
        stopper(in3,in4);
        break;
      case 0xFF18E7:  //5
        digitalWrite(led,HIGH);
        playMusic();
      case 0xFF629D:  //上
        digitalWrite(led,HIGH);
        walk(in1,in2);
        walk(in3,in4);
        break;
      case 0xFFA857:  //下
        digitalWrite(led,HIGH);
        stepback(val1);
        break;
      case 0xFF22DD:  //左
        digitalWrite(led,HIGH);
        turnleft();
        break;
      case 0xFFC23D:  //右
        digitalWrite(led,HIGH);
        turnright();
        break;
      case 0xFF02FD:  //OK制停
        stopper(in1,in2);
        stopper(in3,in4);
        twinkle(1);
        break;
      case 0xFF42BD:  //*
        twinkle(2);
        bluetooth();
        break;
      case 0xFF52AD:  //#
        twinkle(3);
//        chaoshengbo();
        break;
      case 0xFFFFFFFF:
        break;
      default: 
        warn(); 
    }
    irrecv.resume();    // 继续等待接收下一组信号
  }
}
