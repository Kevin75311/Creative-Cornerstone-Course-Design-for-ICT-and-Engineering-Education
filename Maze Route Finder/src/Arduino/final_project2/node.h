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
        MotorWriting(120, 120);
    }
    MotorWriting(120, 120);
    delay(20);
    MotorWriting(0, 0);
}
void Asian_dance_king();
void Airfuck();

void advance()
{
    while(TCRT_detect())
    {
        MotorWriting(120, 120);
    }
    MotorWriting(120, 120);
    delay(20);
    MotorWriting(0, 0);
    delay(500);
    TCRT_detect();
    for(int i = 0; i < 10; i++)
    {
      if(i % 2 == 0)
      {
        for(int j = 0; j < 50 * i; j++)
        {
          MotorWriting(-160, 120);
          delay(5);
          MotorWriting(0,0);
          delay(5);
          TCRT_detect();
          if(l1 == 1 || r1 == 1)break;
        }
      }
      if(i % 2 == 1)
      {
        for(int j = 0; j < 50 * i; j++)
        {
          MotorWriting(120, -160);
          delay(5);
          MotorWriting(0,0);
          delay(5);
          TCRT_detect();
          if(l1 == 1 || r1 == 1)break;
        }
      }
    }   
    MotorWriting(0, 0);
    delay(500);    
}

void left_turn()
{
    black_to_white();
    for (int i=0;i<80;i++)
    {
      MotorWriting(-160, 70);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(-160, 70);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(500);
}
void right_turn()
{
    black_to_white();
    for (int i=0;i<80;i++)
    {
      MotorWriting(70, -160);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(70, -160);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(500);
}
void turn_around()
{
    MotorWriting(120, 120);
    delay(150);
    MotorWriting(0, 0);
    for (int i=0;i<80;i++)
    {
      MotorWriting(-160, 100);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    MotorWriting(0,0);
    TCRT_detect();
    while(l3 == 0 && l2 == 0 && l1 == 0 && r1 == 0 && r2 == 0 && r3 == 0){
        MotorWriting(-160, 100);
        delay(5);
        MotorWriting(0,0);
        delay(5);
        TCRT_detect();
    }
    MotorWriting(0, 0);
    delay(500);
}

void halt()
{
    //Serial.println("Halt!");
    byte* id = NULL;
    byte size = 0;
    //id = rfid(size);
    
    while(true)
    {
        //Serial.println("Read ID!");
        id = rfid(size);
        
        for(int i = 0;i < 40 ;i++)
        {
           MotorWriting(-120, -120);
           delay(7);
           MotorWriting(0, 0);
           delay(5);
        }
        while(!TCRT_detect())
        {
           airfucking(l1, l2, l3, r3, r2, r1);
        }
        
        
        if (size != 0) 
        {
          for (int i = 0; i < size; ++i) 
          {
            Serial.print(char(id[i]));
          }
          break;
        }
        
    }
     
    
    
    /*
    MotorWriting(-120, -120);
    delay(500);
    MotorWriting(0, 0);
    */
    
}
