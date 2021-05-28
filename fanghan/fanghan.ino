
//=============================================================================
#include <IRremote.h>//包含红外库  关键点
#include <Servo.h>
int RECV_PIN = A4;//端口声明
IRrecv irrecv(RECV_PIN);
decode_results results;//结构声明
int on = 0;//标志位
unsigned long last = millis();
char getstr; 
Servo myservo;
Servo myservo_bo;
int servopin=12;//设置舵机驱动脚到数字口2(笔）
int servopin_bo=2;//（波）
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;
long run_car = 0x00FF629D;//按键CH
long back_car = 0x00FFA857;//按键+
long left_car = 0x00FF22DD;//按键<<
long right_car = 0x00FFC23D;//按键>||
long stop_car = 0x00FF02FD;//按键>>|
long left_turn = 0x00ffE01F;//按键-
long right_turn = 0x00FF906F;//按键EQ
long square_run=0x00FF18E7;//按键2
long bluetooth=0x00FF42BD;//按钮7

//long chaoshengbo=0x00FF38C7；//按钮5

//==============================
int Echo = A1;  // Echo回声脚(P2.0)
int Trig =A0;  //  Trig 触发脚(P2.1)

int Front_Distance = 0;//
int Left_Distance = 0;
int Right_Distance = 0;

//==============================
int Left_motor_go=6;     //左电机前进(IN1)
int Left_motor_back=9;     //左电机后退(IN2)

int Right_motor_go=10;    // 右电机前进(IN3)
int Right_motor_back=5;    // 右电机后退(IN4)

int key=A2;//定义按键 A2 接口
int beep=A3;//定义蜂鸣器 A3 接口



void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
//  pinMode(13, OUTPUT);////端口模式，输出
  Serial.begin(9600);	//波特率9600
  pinMode(key,INPUT);//定义按键接口为输入接口
  pinMode(beep,OUTPUT);
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  irrecv.enableIRIn(); // Start the receiver
  pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
  pinMode(servopin_bo,OUTPUT);
}


int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int tempo = 300;
 
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(beep, HIGH);
    delayMicroseconds(tone);
    digitalWrite(beep, LOW);
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


void keysacn()//按键扫描
{
  int val;
  val=digitalRead(key);//读取数字7 口电平值赋给val
  while(!digitalRead(key))//当按键没被按下时，一直循环
  {
    val=digitalRead(key);//此句可省略，可让循环跑空
  }
  while(digitalRead(key))//当按键被按下时
  {
    delay(10);  //延时10ms
    val=digitalRead(key);//读取数字7 口电平值赋给val
    if(val==HIGH)  //第二次判断按键是否被按下
    {
      digitalWrite(beep,HIGH);    //蜂鸣器响
      while(!digitalRead(key))  //判断按键是否被松开
        digitalWrite(beep,LOW);   //蜂鸣器停止
    }
    else
      digitalWrite(beep,LOW);          //蜂鸣器停止
  }
}

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
  //Serial.println(Fdistance);         //显示距离
  //Distance = Fdistance;
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
   keysacn();     //调用按键扫描函数

  while(1)
  {
    front_detection();//测量前方距离
    if(Front_Distance < 30)//当遇到障碍物时
    {
      back(2);//后退减速
      brake(2);//停下来做测距
      left_detection();//测量左边距障碍物距离
     // Distance_display(Left_Distance);//液晶屏显示距离
      right_detection();//测量右边距障碍物距离
      //Distance_display(Right_Distance);//液晶屏显示距离
      if((Left_Distance < 30 ) &&( Right_Distance < 30 ))//当左右两侧均有障碍物靠得比较近
        spin_left(0.7);//旋转掉头
      else if(Left_Distance > Right_Distance)//左边比右边空旷
      {      
        left(3);//左转
        brake(1);//刹车，稳定方向
      }
      else//右边比左边空旷
      {
        right(3);//右转
        brake(1);//刹车，稳定方向
      }
    }
    else
    {
      run(10); //无障碍物，直行     
    }
  } 
}

void run(int time)     // 前进
{
   digitalWrite(Right_motor_go,HIGH);  // 右电机前进
   digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,100);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // 左电机前进
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,100);
  delay(time * 100);   //执行时间，可以调整 
}

void brake(int time)         //刹车，停车
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//执行时间，可以调整  
}

void left(int time)         //左转(左轮不动，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time*100);	//执行时间，可以调整 
}

void spin_left(int time)         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);	// 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,100); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整 
}

void right(int time)        //右转(右轮不动，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);//左电机前进
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,100);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整 
}

void spin_right(int time)        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,100);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);//左电机前进
  digitalWrite(Left_motor_back,HIGH);
 analogWrite(Left_motor_go,0); 
 analogWrite(Left_motor_back,100);//PWM比例0~255调速
  delay(time * 100);	//执行时间，可以调整
}

void back(int time)          //后退
{
  digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,150);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);  //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150);
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}

void dump(decode_results *results)
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) 
  {
    //Serial.println("Could not decode message");
    brake(10);
  } 
//串口打印，调试时可以打开，实际运行中会影响反应速度，建议屏蔽
/*
  else 
  {

    if (results->decode_type == NEC) 
    {
      Serial.print("Decoded NEC: ");
    } 
    else if (results->decode_type == SONY) 
    {
      Serial.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) 
    {
      Serial.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) 
    {
      Serial.print("Decoded RC6: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
    
  }
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 0; i < count; i++) 
  {
    if ((i % 2) == 1) 
    {
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else  
    {
      Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    Serial.print(" ");
  }
  Serial.println("");
*/
}
//-------------------------------------------//
void servopulse(int servopin,int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值舵机的范围是0.5MS到2.5MS 1.5MS 占空比是居中周期是20MS*/ 
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480 的脉宽值 这里的myangle就是0-180度  所以180*11+50=2480  11是为了换成90度的时候基本就是1.5MS
  digitalWrite(servopin,HIGH);//将舵机接口电平置高                                      90*11+50=1490uS  就是1.5ms
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数  这里调用的是微秒延时函数
  digitalWrite(servopin,LOW);//将舵机接口电平置低
 // delay(20-pulsewidth/1000);//延时周期内剩余时间  这里调用的是ms延时函数
  delay(20-(pulsewidth*0.001));//延时周期内剩余时间  这里调用的是ms延时函数
}

void draw_spin_left(int time)         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,170); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,110); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整   
}
void draw_run(int time)     // 前进
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // 左电机前进
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,200);
  delay(time * 100);   //执行时间，可以调整  
}

void draw_run_round(int time)     // 前进
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,200);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,LOW);  // 左电机前进
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,100);
  delay(time * 100);   //执行时间，可以调整  
}

void draw_brake(int time)  //刹车，停车
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  delay(time * 100);//执行时间，可以调整  
}
void draw_back(int time)          //后退
{
   digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,150);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);  //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,150);
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}

void down()
 {
    for(int i=1;i<=4;i++)
    {
      servopulse(servopin,100);
      delay(1000);
    }
 }

void up()
 {
     for(int i=1;i<=3;i++)
     {
        servopulse(servopin,30);
        delay(1000);
      }
 }

void drawTriangle(int time)
{
    brake(5);
     //for(int i=1;i<=3;i++)
     //{ 
      down();
      delay(2000);
      
      draw_run(10);
      draw_brake(10);
      
      up();
      delay(2000);

      draw_run(2.5);
      draw_brake(10);
      
      draw_spin_left(4);//3为正，4为三
      draw_brake(10);
     
      draw_back(3);
      draw_brake(10);
      //Serial.println(i);

      down();
      delay(2000);
      
      draw_run(10);
      draw_brake(10);
      
      up();
      delay(2000);

      draw_run(2.5);
      draw_brake(10);
      
      draw_spin_left(3.3);//3为正，4为三
      draw_brake(10);
     
      draw_back(3);
      draw_brake(10);
      //Serial.println(i);

      down();
      delay(2000);
      
      draw_run(10);
      draw_brake(10);
      
      up();
      delay(2000);

      draw_run(2.5);
      draw_brake(10);
      
      draw_spin_left(4);//3为正，4为三
      draw_brake(10);
     
      draw_back(3);
      draw_brake(10);
      //Serial.println(i);
    //
 
 
      delay(time*100);
}

void drawSquare(int time)
{
     brake(5);
     for(int i=1;i<=4;i++)
    {
      down();
      delay(2000);
      
      draw_run(6);
      draw_brake(10);
      
      up();
      delay(2000);

      draw_run(3.2);
      draw_brake(10);
      
      draw_spin_left(3);//3为正，4为三
      draw_brake(10);
     
      draw_back(3);
      draw_brake(10);
      Serial.println(i);
    }

   // brake(5000);
    delay(time*100);
}

void drawRound(int time)
{
    down();
    delay(2000);
    
    draw_run_round(70);
    draw_brake(10);

    up();
    delay(2000);

    draw_run(10);
    draw_brake(10);
    
    delay(time*100);
}


void blueTooth()
 {
    //playMusic();
   while(1)
   {
      getstr=Serial.read();
      if(getstr=='9')
      break;
      switch(getstr)
      {
        case 'A':        
        {
          Serial.println("go forward!"); 
          run(0);
          break;
        }

        case 'B':        
        {
          Serial.println("go back!"); 
          back(0);
          break;
        }

        case 'C':        
        {
          Serial.println("go left!"); 
          left(0);
          break;
        }

        case 'D':        
        {
          Serial.println("go right!"); 
          right(0);
          break;
        }

        case 'E':        
        {
          Serial.println("Stop!"); 
          brake(0); 
          break;
        }

        case 'F':        
        {
          Serial.println("Stop!"); 
          brake(0); 
          break;
        }

        case '1':        
        {
          Serial.println("square");
          drawSquare(50);
          break;
        }

        case '2':        
        {
          Serial.println("triangle");
          drawTriangle(50);
          break;
        }

        case '3':        
        {
          Serial.println("Round");
          drawRound(50);
          break;
        }

        case '4':
        {
          Serial.println("Bo");
          chaoshengbo();
          break;
        }

        case '5':
        {
          
        }

       
        
      }   
  }
 }


  


void loop()
{ 
  if (irrecv.decode(&results)) //调用库函数：解码
  {
    // If it's been at least 1/4 second since the last
    // IR received, toggle the relay
    if (millis() - last > 250) //确定接收到信号
    {
      on = !on;//标志位置反
      digitalWrite(13, on ? HIGH : LOW);//板子上接收到信号闪烁一下led
      dump(&results);//解码红外信号
    }
    if (results.value == run_car )//按键CH
      {
        run(10);
        brake(10);
       }//前进
    if (results.value == back_car )//按键+
      {
        back(10);//后退
        brake(10);
      }
    if (results.value == left_car )//按键<<
      {
        left(10);//左转
        brake(10);
      }
    if (results.value == right_car )//按键>||
      {
        right(10);//右转
        brake(10);
      }
    if (results.value == stop_car )//按键>>|
      brake(10);//停车
    if (results.value == left_turn )//按键-
      {
        spin_left(10);//左旋转
        brake(10);
      }
    if (results.value == right_turn )//按键EQ
      {
        spin_right(10);//右旋转
        brake(10);
      }
    if( results.value == bluetooth)
    {
       blueTooth();
      // drawRound(50);
      // drawSquare(50);
       //drawTriangle(50);
    }
    last = millis();      
    irrecv.resume(); // Receive the next value
  }
  else
  {
    
  }
}



