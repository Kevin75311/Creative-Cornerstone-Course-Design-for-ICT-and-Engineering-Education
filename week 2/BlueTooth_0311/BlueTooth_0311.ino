#include <SoftwareSerial.h>
int rxPIN = 12;
int txPIN = 13;


SoftwareSerial BT (rxPIN,txPIN);

void setup() 
{
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(rxPIN,INPUT);
  pinMode(txPIN,OUTPUT);
  
}

void loop() 
{
  if(BT.available())
  {
      char c = BT.read();
      Serial.println(c);
  }
  if(Serial.available())
  {

      BT.write(Serial.read());
  }
}
