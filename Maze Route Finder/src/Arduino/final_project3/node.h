/***************************************************************************/
// File        [node.h]
// Author     [Erik Kuo, Joshua Lin]
// Synopsis   [Code for managing car movement when encounter a node]
// Functions  [/* add on yout own! */]
// Modify     [2020/03/027 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <string.h>

/*===========================import variable===========================*/
int extern r1, l1, r2, l2, r3, l3;
int extern _Tp;
byte* id = NULL;
byte size = 0;
/*===========================import variable===========================*/

// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.
bool TCRT_detect()
{
    r3 = digitalRead(R3);
    r2 = digitalRead(R2);
    r1 = digitalRead(R1);
    l1 = digitalRead(L1);
    l2 = digitalRead(L2);
    l3 = digitalRead(L3);
    
    if(r1 == 1 && r2 == 1 && l1 == 1 && l2 == 1)return true;
    return false;
}

void black_to_white()
{
    while(TCRT_detect())
    {
        MotorWriting(90, 90);
    }
    MotorWriting(90, 90);
    delay(100);
    MotorWriting(0, 0);
}

void advance()
{
    black_to_white();
    // delay(100);
    TCRT_detect();
    bool goodsway = false;
    for(int j = 0; j < 50; j++)
    {
      MotorWriting(-170, 120);
      delay(5);
      MotorWriting(0,0);
      delay(5);
      TCRT_detect();
      if(l2 == 1 || l1 == 1 || r1 == 1 || r2 == 1)
      {
        break;
        goodsway = true;
      }
    }
    delay(200);
    TCRT_detect();
    while(goodsway == false && l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(80, -170);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(200);
}

void left_turn()
{
    black_to_white();
    for (int i=0;i<80;i++)
    {
      MotorWriting(-170, 80);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(-170, 80);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(200);
}
void right_turn()
{
    black_to_white();
    for (int i=0;i<80;i++)
    {
      MotorWriting(80, -170);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(80, -170);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(200);
}
void turn_around()
{
    MotorWriting(120, 120);
    delay(150);
    MotorWriting(0, 0);
    for (int i=0;i<60;i++)
    {
      MotorWriting(-170, 100);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    MotorWriting(0,0);
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(-170, 100);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(200);
}

void halt()
{
    //Serial.println("Halt!");
    
    //id = rfid(size);
    
    while(true)
    {
        //Serial.println("Read ID!");
        id = rfid(size);
                
        for(int i = 0;i < 40 ;i++)
        {
           //id = rfid(size);
           MotorWriting(-120, -120);
           delay(7);
           MotorWriting(0, 0);
           delay(5);
        }
        while(!TCRT_detect())
        {
           //id = rfid(size);
           airfucking(l1, l2, l3, r3, r2, r1);
        }
        
        
        if (size != 0) 
        {
          for (int i = 0; i < size; ++i) 
          {
            Serial.print(char(id[i]));
          }
          *id = NULL;
          size = 0;
          break;
        }
        
    }
     
    
    
    /*
    MotorWriting(-120, -120);
    delay(500);
    MotorWriting(0, 0);
    */
    
}
