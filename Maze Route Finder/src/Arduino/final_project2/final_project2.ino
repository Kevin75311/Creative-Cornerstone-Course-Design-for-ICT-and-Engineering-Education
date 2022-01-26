/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Halt_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/
// for BlueTooth
#include<SoftwareSerial.h>
// for RFID
#include <SPI.h>
#include <MFRC522.h>

/*===========================define pin & create module object================================*/
// BlueTooth
SoftwareSerial BT(0, 1);   // TX,RX on bluetooth module, 請按照自己車上的接線寫入腳位
#define RST_PIN    9  
#define SS_PIN    10
// L298N, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define MotorR_I1      7 //定義 I1 接腳（右）
#define MotorR_I2      4 //定義 I2 接腳（右）
#define MotorL_I3      3 //定義 I3 接腳（左）
#define MotorL_I4      2 //定義 I4 接腳（左）
#define MotorL_PWML    5 //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR    6 //定義 ENB (PWM調速) 接腳
// 循線模組, 請按照自己車上的接線寫入腳位
int IN1 = MotorR_I1;
int IN2 = MotorR_I2;
int IN3 = MotorL_I3;
int IN4 = MotorL_I4;
int ENA = MotorL_PWML;
int ENB = MotorR_PWMR;

enum TCRT{
  R3 = A5, //右3
  R2 = A4, //右2
  R1 = A3, //右1
  L1 = A2, //左1
  L2 = A1, //左2
  L3 = A0  //左3
};

 
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN      9        // 讀卡機的重置腳位
#define SS_PIN       10       // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
/*===========================define pin & create module object===========================*/

/*===========================declare function prototypes===========================*/

/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void setup()
{
   //bluetooth initialization
   BT.begin(9600);
   //Serial window
   Serial.begin(9600);
   //RFID initial
   SPI.begin();
   mfrc522.PCD_Init();
   //L298N pin
   pinMode(MotorR_I1,   OUTPUT);
   pinMode(MotorR_I2,   OUTPUT);
   pinMode(MotorL_I3,   OUTPUT);
   pinMode(MotorL_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   //tracking pin
   pinMode(R1, INPUT); 
   pinMode(R2, INPUT);
   pinMode(R3, INPUT);
   pinMode(L1, INPUT);
   pinMode(L2, INPUT);
   pinMode(L3, INPUT);
#ifdef DEBUG
  //Serial.println("Start!");
#endif
}// setup

// Import header files
#include "RFID.h"
#include "track.h"
#include "bluetooth.h"
#include "node.h"

// initalize parameter
// for start and end
bool _start = false;
// variables for 循線模組
int r2=0,r1=0,r3=0,l3=0,l1=0,l2=0;
// variable for motor power
int _Tp=90;

// enum for bluetooth message, reference in bluetooth.h line 2
BT_CMD _cmd = NOTHING;

void loop()
{
  _cmd = ask_BT();

  //reading RFID   
 
  // Car moving part
  if(_cmd == START) _start = true;
  else if(_cmd == END) _start = false;
  if (_start)
  {
    if(_cmd == TURN_RIGHT) right_turn();
    else if(_cmd == ADVANCE) advance();
    else if(_cmd == TURN_LEFT) left_turn();
    else if(_cmd == U_TURN) turn_around();
    else if(_cmd == HALT) halt();
    TCRT_detect();
    while(!TCRT_detect())
    {
        //Serial.println("track");
        if (TCRT_detect()) break;
        tracking(l1, l2, l3, r3, r2, r1);
    }
    delay(500);
  }
    
}// loop


/*===========================define function===========================*/
