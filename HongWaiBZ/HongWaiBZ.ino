//循迹小车Arduino 程序：
//基于慧净电子ARDUINO智能小车、小白龟机器人、蓝牙智能车、HL-1智能小车
//配套视频教程下载网站：
//http://www.hjmcu.com
//http://www.hlmcu.com
//交流论坛：http://hjdz.haotui.com
//交流QQ：1526248688
// 免费结缘：5星好评赠送18个资料包，追加评价后再加送20G资料，网上网盘下载
// 视频教程：本小车配套详细视频教程，有需要请到慧净网站免费下载
// R是右(right),L是左(left)	  小车对着自己看时 分的左右
int MotorRight1=14; //A0 IN1
int MotorRight2=15; //A1 IN2
int MotorLeft1=16;  //A2 IN3
int MotorLeft2=17;  //A3 IN4

int MotorRPWM=5;  //PWM  5
int MotorLPWM=3;  //PWM 3
const int SensorLeft = 12;      //左感測器輸入腳
const int SensorRight = 13;     //右感測器輸入腳
int SL;    //左感測器狀態
int SR;    //右感測器狀態

void setup()
{  
  Serial.begin(9600);
  pinMode(MotorRight1, OUTPUT);  // 腳位 14 (PWM)
  pinMode(MotorRight2, OUTPUT);  // 腳位 15 (PWM)
  pinMode(MotorLeft1,  OUTPUT);  // 腳位 16 (PWM) 
  pinMode(MotorLeft2,  OUTPUT);  // 腳位 17 (PWM)
  
  pinMode(MotorLPWM,  OUTPUT);  // 腳位 3 (PWM) 
  pinMode(MotorRPWM,  OUTPUT);  // 腳位 5 (PWM)
  
  pinMode(SensorLeft, INPUT); //定義左感測器
  pinMode(SensorRight, INPUT); //定義右感測器
}

void loop() 
 {
 SL = digitalRead(SensorLeft);
 SR = digitalRead(SensorRight);
       if (SL == HIGH&&SR==HIGH)//  前進
   { 
             digitalWrite(MotorRight1,LOW);//IN1 右电机 高电平反转
             digitalWrite(MotorRight2,HIGH);//IN2 右电机 高电平正转
             analogWrite(MotorRPWM,130); //0---100--250
             
             digitalWrite(MotorLeft1,HIGH);//IN3 左电机 高电平正转
             digitalWrite(MotorLeft2,LOW);//IN4 左电机 高电平反转
             analogWrite(MotorLPWM,130);
           

         }      
       
       else // R是右(right),L是左(left)	  小车对着自己看时 分的左右
      {  
         if (SL == HIGH & SR == LOW)//  快速左轉 
        {  
            delay(1);
             digitalWrite(MotorRight1,LOW);//IN1 右电机 高电平反转
             digitalWrite(MotorRight2,HIGH);//IN2 右电机 高电平正转
             analogWrite(MotorRPWM,200);
             
             digitalWrite(MotorLeft1,LOW);//IN3 左电机 高电平正转
             digitalWrite(MotorLeft2,LOW);//IN4 左电机 高电平反转
             analogWrite(MotorLPWM,0);
        }
         else if (SR == HIGH & SL == LOW) //  快速右轉
        {  
          delay(1); 
             digitalWrite(MotorRight1,LOW);//IN1 右电机 高电平反转
             digitalWrite(MotorRight2,LOW);//IN2 右电机 高电平正转
             analogWrite(MotorRPWM,0);
             
             digitalWrite(MotorLeft1,HIGH);//IN3 左电机 高电平正转
             digitalWrite(MotorLeft2,LOW);//IN4 左电机 高电平反转
             analogWrite(MotorLPWM,200);
          
        }
         else //  停止
        {    
        digitalWrite(MotorRight1,LOW);
        digitalWrite(MotorRight2,LOW);
        analogWrite(MotorRPWM,0);
        digitalWrite(MotorLeft1,LOW);
        digitalWrite(MotorLeft2,LOW);;
        analogWrite(MotorLPWM,0);
        }}}

