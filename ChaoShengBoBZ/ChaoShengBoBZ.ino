//基于慧净电子ARDUINO智能小车、小白龟机器人、蓝牙智能车、HL-1智能小车
//配套视频教程下载网站：http://www.hjmcu.com  
//http://www.hlmcu.com
//交流论坛：http://hjdz.haotui.com
//交流QQ群：264506746
//超声波智能避障车程序（ARDUINO）
//    L = 左
//    R = 右
//    F = 前
//    B = 後

#include <Servo.h> 
int pinLB=15;     // 定義15腳位 左後
int pinLF=14;     // 定義14腳位 左前

int pinRB=16;    // 定義16腳位 右前
int pinRF=17;    // 定義17腳位 右後

int MotorRPWM=3;
int MotorLPWM=5;

int inputPin = 9;  // 定義超音波信號接收腳位
int outputPin =8;  // 定義超音波信號發射腳位

int Fspeedd = 0;      // 前速
int Rspeedd = 0;      // 右速
int Lspeedd = 0;      // 左速
int directionn = 0;   // 前=8 後=2 左=4 右=6 
Servo myservo;        // 設 myservo
int delay_time = 500; // 伺服馬達轉向後的穩定時間

int Fgo = 8;         // 前進
int Rgo = 6;         // 右轉
int Lgo = 4;         // 左轉
int Bgo = 2;         // 倒車

void setup()
 {
  Serial.begin(9600);     // 定義馬達輸出腳位 
  pinMode(pinLB,OUTPUT); // 腳位 8 (PWM)
  pinMode(pinLF,OUTPUT); // 腳位 9 (PWM)
  pinMode(pinRB,OUTPUT); // 腳位 10 (PWM) 
  pinMode(pinRF,OUTPUT); // 腳位 11 (PWM)
  
  pinMode(MotorLPWM,  OUTPUT);  // 腳位 3 (PWM) 
  pinMode(MotorRPWM,  OUTPUT);  // 腳位 5 (PWM)
  
  pinMode(inputPin, INPUT);    // 定義超音波輸入腳位
  pinMode(outputPin, OUTPUT);  // 定義超音波輸出腳位   

  myservo.attach(10);    // 定義伺服馬達輸出第10腳位(PWM)
 }
void advance(int a)     // 前進
    {
     digitalWrite(pinRB,HIGH);  // 使馬達（右後）動作
     digitalWrite(pinRF,LOW);  
     analogWrite(MotorRPWM,140);//左右马达速度不同时可修改参数
     digitalWrite(pinLB,HIGH);  // 使馬達（左後）動作
     digitalWrite(pinLF,LOW);   
     analogWrite(MotorLPWM,150);//左右马达速度不同时可修改参数
     delay(a * 50);     
    }

void right(int b)        //右轉(單輪)
    {
     digitalWrite(pinRB,LOW);   //使馬達（右後）動作
     digitalWrite(pinRF,HIGH);
     analogWrite(MotorRPWM,200);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
     delay(b * 100);
    }
void left(int c)         //左轉(單輪)
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,LOW);   //使馬達（左後）動作
     digitalWrite(pinLF,HIGH);
     analogWrite(MotorLPWM,200);
     delay(c * 100);
    }

void turnR(int d)        //右轉(雙輪)
    {
     digitalWrite(pinRB,LOW);  //使馬達（右後）動作
     digitalWrite(pinRF,HIGH);
     analogWrite(MotorRPWM,130);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);  //使馬達（左前）動作
     analogWrite(MotorLPWM,130);
     delay(d * 50);
    }
    
void turnL(int e)        //左轉(雙輪)
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW);   //使馬達（右前）動作
     analogWrite(MotorRPWM,130);
     digitalWrite(pinLB,LOW);   //使馬達（左後）動作
     digitalWrite(pinLF,HIGH);
     analogWrite(MotorLPWM,130);
     delay(e * 50);
    }    
void stopp(int f)         //停止
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
     delay(f * 50);
    }
    
void back(int g)          //後退
    {

     digitalWrite(pinRB,LOW);  //使馬達（右後）動作
     digitalWrite(pinRF,HIGH);
     analogWrite(MotorRPWM,150);
     digitalWrite(pinLB,LOW);  //使馬達（左後）動作
     digitalWrite(pinLF,HIGH);
     analogWrite(MotorLPWM,120);
     delay(g * 100);     
    }
    
void detection()        //測量3個角度(0.90.179)
    {      
      int delay_time = 150;   // 伺服馬達轉向後的穩定時間
      ask_pin_F();            // 讀取前方距離
      
     if(Fspeedd < 10)         // 假如前方距離小於10公分
      {
      stopp(1);               // 清除輸出資料 
      back(3);                // 後退 0.3秒
      }
           
      if(Fspeedd < 25)         // 假如前方距離小於25公分
      {
        stopp(10);               // 清除輸出資料 
        ask_pin_L();            // 讀取左方距離
        delay(delay_time);      // 等待伺服馬達穩定
        ask_pin_R();            // 讀取右方距離  
        delay(delay_time);      // 等待伺服馬達穩定  
        
     
        if(Lspeedd < Fspeedd)   //假如 左邊距離小於前邊距離
        {
         directionn = Fgo;      //向前走
        }
        
       if(Rspeedd < Fspeedd)   //假如 右邊距離小於前邊距離
        {
         directionn =  Fgo;      //向前走
        } 
        
      if(Lspeedd > Rspeedd)   //假如 左邊距離大於右邊距離
        {
         directionn = Rgo;      //向左走
        }
        
        if(Lspeedd < Rspeedd)   //假如 左邊距離小於右邊距離
        {
         directionn = Lgo;      //向右走
        } 

        if (Lspeedd < 15 && Fspeedd < 15)   //假如 左邊距離和前方距離皆小於15公分
        {

         directionn = Lgo;      //向右走 
        } 
        
        if (Rspeedd < 15 && Fspeedd < 15)   //假如 右邊距離和前方距離和皆小於15公分
        {

         directionn = Rgo;      //向左走   
        } 

        if (Lspeedd < 15 && Rspeedd < 15)   //假如 左邊距離和右邊距離皆小於15公分
        {

         directionn = Bgo;      //向後走        
        }          
      }
      
      else                      //假如前方不小於(大於)25公分     
      {
        directionn = Fgo;        //向前走     
      }
     
    }    
void ask_pin_F()   // 量出前方距離 
    {
      myservo.write(90);
      digitalWrite(outputPin, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);    // 維持超聲波發射低電壓
      float Fdistance = pulseIn(inputPin, HIGH);  // 讀差相差時間
      Fdistance= Fdistance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      Serial.print("F distance:");      //輸出距離（單位：公分）
      Serial.println(Fdistance);         //顯示距離
      Fspeedd = Fdistance;              // 將距離 讀入Fspeedd(前速)
    }  
 void ask_pin_L()   // 量出左邊距離 
    {
      myservo.write(5);
      delay(delay_time);
      digitalWrite(outputPin, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);    // 維持超聲波發射低電壓
      float Ldistance = pulseIn(inputPin, HIGH);  // 讀差相差時間
      Ldistance= Ldistance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      Serial.print("L distance:");       //輸出距離（單位：公分）
      Serial.println(Ldistance);         //顯示距離
      Lspeedd = Ldistance;              // 將距離 讀入Lspeedd(左速)
    }  
void ask_pin_R()   // 量出右邊距離 
    {
      myservo.write(177);
      delay(delay_time);
      digitalWrite(outputPin, LOW);   // 讓超聲波發射低電壓2μs
      delayMicroseconds(2);
      digitalWrite(outputPin, HIGH);  // 讓超聲波發射高電壓10μs，這裡至少是10μs
      delayMicroseconds(10);
      digitalWrite(outputPin, LOW);    // 維持超聲波發射低電壓
      float Rdistance = pulseIn(inputPin, HIGH);  // 讀差相差時間
      Rdistance= Rdistance/5.8/10;       // 將時間轉為距離距离（單位：公分）
      Serial.print("R distance:");       //輸出距離（單位：公分）
      Serial.println(Rdistance);         //顯示距離
      Rspeedd = Rdistance;              // 將距離 讀入Rspeedd(右速)
    }  
    
void loop()
 {
    myservo.write(90);  //讓伺服馬達回歸 預備位置 準備下一次的測量
    detection();        //測量角度 並且判斷要往哪一方向移動
      
   if(directionn == 2)  //假如directionn(方向) = 2(倒車)             
   {
     back(8);                    //  倒退(車)
     turnL(2);      //些微向左方移動(防止卡在死巷裡)
     
     Serial.print(" Reverse ");   //顯示方向(倒退)
   }
   if(directionn == 6)           //假如directionn(方向) = 6(右轉)    
   {
     back(1); 
     turnR(6);                   // 右轉
     Serial.print(" Right ");    //顯示方向(左轉)
   }
   if(directionn == 4)          //假如directionn(方向) = 4(左轉)    
   {  
     back(1);      
     turnL(6);                  // 左轉
     Serial.print(" Left ");     //顯示方向(右轉)   
   }  
   if(directionn == 8)          //假如directionn(方向) = 8(前進)      
   { 
    advance(1);                 // 正常前進  
    Serial.print(" Advance ");   //顯示方向(前進)
    Serial.print("   ");    
   }
 }


