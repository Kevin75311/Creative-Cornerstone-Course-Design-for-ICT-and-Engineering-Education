int r3, r2, r1, l3, l2, l1;

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
void MotorWriting(int vR, int vL){
  if(vR >= 0 && vL >= 0){
    analogWrite(ENA, vR);
    analogWrite(ENB, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    
  }
  else if(vR < 0 && vL >= 0){
    analogWrite(ENA, -vR);
    analogWrite(ENB, vL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if(vR >= 0 && vL < 0){
    analogWrite(ENA, vR);
    analogWrite(ENB, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else{
    analogWrite(ENA, -vR);
    analogWrite(ENB, -vL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

}
void left_turn()
{
    MotorWriting(120, 120);
    delay(200);
    MotorWriting(-120, 120);
    delay(350);
    MotorWriting(0, 0);
}
void right_turn()
{
    MotorWriting(120, 120);
    delay(200);
    MotorWriting(120, -120);
    delay(350);
    MotorWriting(0, 0);
}
void turn_around()
{
    MotorWriting(120, 120);
    delay(200);
    MotorWriting(-120, 120);
    delay(520);
    MotorWriting(0, 0);
}

void TCRT_detect()
{
  r3 = digitalRead(R3);
  r2 = digitalRead(R2);
  r1 = digitalRead(R1);
  l1 = digitalRead(L1);
  l2 = digitalRead(L2);
  l3 = digitalRead(L3);
}

void tracking(int l1,int l2,int l3,int r3,int r2,int r1)
{
    TCRT_detect();
    double value = 0.0;
    if((l1 + l2 + l3 + r1 + r2 + r3) == 0)value = 0;
    else value = ( 2 * r2 + 1 * r1 - 1 * l1 - 2 * l2 ) / ( r2 + r1 + l1 + l2 );

    if(r3 == 1 || l3 == 1)
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
}// tracking


void setup() {

  Serial.begin(9600);
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

  Serial.println("start!");
}

int i=0;


void loop() 
{
    //紅外線感測器TCRT
  TCRT_detect();
  while(r2!=1 || r1!=1 || r3!=1 || l3!=1 || l1!=1 || l2!=1)
  {
    TCRT_detect();
    tracking(l1, l2, l3, r3, r2, r1);
    //Serial.println("tracking!");
  }
  delay(1000);
  if (i%3==2){
      turn_around();
      Serial.println("turn around!");
  }
  else if (i%12==0 || i%12==1 || i%12==3 || i%12 == 4){
      right_turn();
      Serial.println("turn right!");
  }
  else if (i%12==6 || i%12==7 || i%12==9 || i%12 == 10){
      left_turn();
      Serial.println("turn left!");
  }
  i++;
  Serial.println(i);
}
