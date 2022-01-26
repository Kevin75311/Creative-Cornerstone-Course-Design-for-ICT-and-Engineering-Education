#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>

#define RST_PIN    9  
#define SS_PIN    10
    
MFRC522 *mfrc522;

int rxPIN = 0;
int txPIN = 1;

SoftwareSerial BT (rxPIN,txPIN);


enum TCRT{
  R3 = A5, //右3
  R2 = A4, //右2
  R1 = A3, //右1
  L1 = A2, //左1
  L2 = A1, //左2
  L3 = A0  //左3
};
enum L298N{
  ENA = 5,
  ENB = 6,
  IN1 = 7,
  IN2 = 4,
  IN3 = 3,
  IN4 = 2
};

//馬達
void MotorWriting(int vR, int vL)
{
  if(vR >= 0 && vL >= 0)
  {
    analogWrite(ENA, vR);
    analogWrite(ENB, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
  }
  else if(vR < 0 && vL >= 0)
  {
    analogWrite(ENA, -vR);
    analogWrite(ENB, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if(vR >= 0 && vL < 0)
  {
    analogWrite(ENA, vR);
    analogWrite(ENB, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else
  {
    analogWrite(ENA, -vR);
    analogWrite(ENB, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

}

void setup() 
{
  //TCCR2B = TCCR2B & B11111000|B00000001;
  Serial.begin(9600);
  SPI.begin();
  mfrc522 = new MFRC522(SS_PIN, RST_PIN); 
  mfrc522->PCD_Init();
  BT.begin(9600);
  
  pinMode(rxPIN,INPUT);
  pinMode(txPIN,OUTPUT);  

  pinMode(R3, INPUT);
  pinMode(R2, INPUT);
  pinMode(R1, INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println(F("Read UID on a MIFARE PICC:"));
  
  
}

void loop() {
  
 //RFID
 if(!mfrc522->PICC_IsNewCardPresent()) {
 goto FuncEnd;
  }     //PICC_IsNewCardPresent()：是否感應到新的卡片?
    if(!mfrc522->PICC_ReadCardSerial()) {
  goto FuncEnd;
  }      //PICC_ReadCardSerial()：是否成功讀取資料?
  Serial.println(F("**Card Detected:**"));
  mfrc522->PICC_DumpDetailsToSerial(&(mfrc522->uid)); //讀出 UID
  mfrc522->PICC_HaltA();                         // 讓卡片進入停止模式
  mfrc522->PCD_StopCrypto1();               // 停止 Crypto1
  FuncEnd:;                                                 // goto 跳到這.

  //Bluetooth
  if(BT.available())
  {
    //Serial.write(BT.read());
    char command = BT.read();
    Serial.write(command);
    if(command == 'W' || command == 'w')
    {
      MotorWriting(100, 100);
    }
    else if(command == 'S' || command == 's')
    {
      MotorWriting(-100, -100);
    }
    else if(command == 'A' || command == 'a')
    {
      MotorWriting(-100, 100);
    }
    else if(command == 'D' || command == 'd')
    {
      MotorWriting(100, -100);
    }
    else if(command == 'F' || command == 'f')
    {
      MotorWriting(0, 0);
    }
    else if(command == 'T' || command == 't')
    {
      while(true)
      {
        //紅外線感測器TCRT
        int sensorR3 = digitalRead(R3);
        int sensorR2 = digitalRead(R2);
        int sensorR1 = digitalRead(R1);
        int sensorL1 = digitalRead(L1);
        int sensorL2 = digitalRead(L2);
        int sensorL3 = digitalRead(L3);
        double value; 
        if((sensorR3 + sensorR2 + sensorR1 + sensorL1 + sensorL2 + sensorL3) == 0)value = 0;
        else value = ( 2 * sensorR2 + 1 * sensorR1 - 1 * sensorL1 - 2 * sensorL2 ) / ( sensorR2 + sensorR1 + sensorL1 + sensorL2 );
        
        if(sensorR3 == 1 || sensorL3 == 1)
        {
          if(value < 0)MotorWriting(100, 0);
          else if(value > 0)MotorWriting(0, 100);
        }
        else
        {
          if(value < 0)
          {
            MotorWriting(160 - 30 * value, 160 + 30 * value);
            delay(6);
            MotorWriting(0, 0);
            delay(10);
          }
          else if(value > 0)
          {
            MotorWriting(160 - 30 * value, 160 + 30 * value);
            delay(6);
            MotorWriting(0, 0);
            delay(10);
          }
          else
          {
            MotorWriting(160, 160);
            delay(6);
            MotorWriting(0, 0);
            delay(10);
          }
        }
        if(BT.available())break;
      }
    }
  }
  
   
}
