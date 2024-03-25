#include <Servo.h>

Servo servo;
const byte servoPin = 6;
const byte pingPin = 7;
const byte gPin = 8;
const byte rPin = 9;
int m_distance=0;
boolean state = false;
unsigned long timeVal=0;

void setup()
{
  pinMode(gPin, OUTPUT);
  pinMode(rPin, OUTPUT);

  servo.attach(servoPin); 
  servo.write(0);
  delay(1000);

  digitalWrite(rPin, HIGH);
}

void loop()
{
  m_distance=CalDistance(7);  //초음파센서로 거리계산함수
  if(m_distance<50){
    if(state==false){
      servo.write(90);
      delay(2000); 
      state=true;
      digitalWrite(rPin, LOW);
      digitalWrite(gPin, HIGH);
    }
    timeVal=millis();
  }
  if(state==true){
    if(millis()-timeVal>=2000){
      servo.write(0);
      state=false;
      digitalWrite(gPin, LOW);
      digitalWrite(rPin, HIGH);
    }
  }
}

int CalDistance (int Pin){  //초음파센서(3핀) 예제를 그대로 외부함수로 빼냄
  pinMode(Pin,OUTPUT); //출력모드로  사용
  digitalWrite(Pin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(Pin,HIGH); 
  delayMicroseconds(10); 
  digitalWrite(Pin,LOW);

  pinMode(Pin,INPUT);    //입력모드로 사용
  int duration = pulseIn(Pin, HIGH);
  int distance = duration / 57.5;  //가상시뮬레이션의 오차율을 줄이기 위해 이걸로 테스트 함.
  return distance; //거리값 리턴
}