/***************************************************************************/
// File        [track.h]
// Author     [Erik Kuo]
// Synopsis   [Code used for tracking]
// Functions  [MotorWriting, tracking]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
extern int _Tp;
extern int ENA;
extern int ENB;
extern int IN1;
extern int IN2;
extern int IN3;
extern int IN4;
int value;

extern bool TCRT_detect();
/*===========================import variable===========================*/

// Write the voltage to motor.
void MotorWriting(int vL, int vR){
  if(vL >= 0 && vR >= 0){
    analogWrite(ENB, vL);
    analogWrite(ENA, vR);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
  }
  else if(vL < 0 && vR >= 0){
    analogWrite(ENB, -vL);
    analogWrite(ENA, vR);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if(vL >= 0 && vR < 0){
    analogWrite(ENB, vL);
    analogWrite(ENA, -vR);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else{
    analogWrite(ENB, -vL);
    analogWrite(ENA, -vR);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

}

// P control Tracking
void tracking(int l1,int l2,int l3,int r3,int r2,int r1)
{
    TCRT_detect();
    double value = 0.0;
    if((l1 + l2 + l3 + r1 + r2 + r3) == 0)value = 0;
    else value = -(2 * r3 + 1.5 * r2 + 1 * r1 - 1 * l1 - 1.5 * l2  - 2 * l3) / (r3 + r2 + r1 + l1 + l2 + l3);

    
    if(value < 0)
    {
        MotorWriting(160 - 30 * value, 160 + 30 * value);
        delay(3);
        MotorWriting(0, 0);
        delay(5);
    }
    else if(value > 0)
    {
        MotorWriting(160 - 30 * value, 160 + 30 * value);
        delay(3);
        MotorWriting(0, 0);
        delay(5);
    }
    else
    {
        MotorWriting(160, 160);
        delay(3);
        MotorWriting(0, 0);
        delay(5);
    }
    
}// tracking
