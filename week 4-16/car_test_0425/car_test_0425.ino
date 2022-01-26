
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

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop() 
{
  
  //Serial.println("Start!");
  for(int i = 0;i < 10;i++)
  {
    Serial.println("Turning");
    Serial.println(i * 50);
    Serial.println("second");
    
    delay(1000);
    MotorWriting(120, 120);
    delay(100 * i);
    MotorWriting(0, 0);
    delay(3000);
  }
  
  /*
  MotorWriting(120, 120);
  delay(350);
  MotorWriting(0, 0);
  delay(3000);

  MotorWriting(120, -120);
  delay(520);
  MotorWriting(0, 0);
  delay(3000);
  */
      

}
