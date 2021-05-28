void blootooth() 
{ 
  char val;
  while(1)
  {
    val = Serial.read();
    if(val!=-1)
       {
          switch(val)
           {
             case 'A':
             walk(in1,in2);
             walk(in3,in4);
             delay(50);
             break; 
             case 'B':
             walk(in1,in2);
             walk(in3,in4);
             delay(50);
             break;
             case 'C':
             turnleft(val3);
             break;
            delay(50);
             break; 
             case 'D':
             turnright(val3);
             delay(50);
             break;  
             case 'F':
            stopper(in1,in2);
            stopper(in3,in4);
            warnlight();
            break;
            default: 
            warnlight(); 
           }
       }
  }
}
