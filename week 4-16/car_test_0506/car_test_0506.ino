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
    black_to_white();
    for (int i=0;i<140;i++)
    {
      MotorWriting(-160, 70);
      delay(5);
      MotorWriting(0,0);
      delay(5);
    }
    MotorWriting(0,0);
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

}

int i=0;


void loop() 
{
  while(!TCRT_detect())
  {
    if (TCRT_detect()) break;
    tracking(l1, l2, l3, r3, r2, r1);
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
