#include <Servo.h>
#define Sensor A2

int motor_R_r=6; 
int motor_R_f=5;
int motor_L_r=10;
int motor_L_f=9;

int trig_f=12;
int echo_f=13;

int s1=11;

long duration;
float distance,FD,BD;

int buzz = 2;

char value;
// int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;

char data;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);
  servo.attach(s1);
  pinMode(Sensor, INPUT);  
  pinMode(motor_R_f, OUTPUT);
  pinMode(motor_R_r, OUTPUT);
  pinMode(motor_L_f, OUTPUT);
  pinMode(motor_L_r, OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  digitalWrite(3,HIGH);
  digitalWrite(4, HIGH);
  // Obstacle();  // uncomment for obstacle avoiding mode
  Bluetoothcontrol();
  int gas_value = analogRead(Sensor);
  Serial.print("Sensor Value:");
  Serial.println(gas_value);
  if (gas_value > 430) tone(buzz,1000);
  else noTone(buzz);
  delay(1000);
}

void Obstacle() {
  distance = ultrasonic();
  if (distance <= 12) {
    delay(100);
    Serial.println(distance);
    stopall();
    L = leftsee();
    servo.write(103);
    delay(400);
    R = rightsee();
    servo.write(103);
    if (L < R) {
      right();
      delay(400);
      stopall();
      delay(200);
    } else if (L > R) {
      left();
      delay(400);
      stopall();
      delay(200);
    }
  } else {
    forward();
  }
}


void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
  if (value == 'F') {
    forward();
    delay(1000);
    stopall();
  } else if (value == 'B') {
    backward();
    delay(1000);
    stopall();
  } else if (value == 'L') {
    left();
    delay(1000);
    stopall();
  } else if (value == 'R') {
    right();
    delay(1000);
    stopall();
  } else if (value == 'S') {
    stopall();
  }
}

int rightsee() {
  servo.write(20);
  delay(200);
  Left = ultrasonic();
  return Left;
}
int leftsee() {
  servo.write(180);
  delay(200);
  Right = ultrasonic();
  return Right;
}

void forward()
{
  digitalWrite(motor_R_f,HIGH);
  digitalWrite(motor_R_r,LOW);
  digitalWrite(motor_L_f,HIGH);
  digitalWrite(motor_L_r,LOW);
  // Serial.println("Forward");  
}
void backward()
{
  digitalWrite(motor_R_f,LOW);
  digitalWrite(motor_R_r,HIGH);
  digitalWrite(motor_L_f,LOW);
  digitalWrite(motor_L_r,HIGH);
  // Serial.println("Back");
}
void left()
{
  digitalWrite(motor_R_f,HIGH);
  digitalWrite(motor_R_r,LOW);
  digitalWrite(motor_L_f,LOW);
  digitalWrite(motor_L_r,LOW);
  // Serial.println("Left");
}
void right()
{
  digitalWrite(motor_R_f,LOW);
  digitalWrite(motor_R_r,LOW);
  digitalWrite(motor_L_f,HIGH);
  digitalWrite(motor_L_r,LOW);
  // Serial.println("Right");
}
void stopall()
{
  digitalWrite(motor_R_f,LOW);
  digitalWrite(motor_R_r,LOW);
  digitalWrite(motor_L_f,LOW);
  digitalWrite(motor_L_r,LOW);
  // Serial.println("Stop");
}

int ultrasonic() {
  digitalWrite(trig_f, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_f, HIGH);
  delayMicroseconds(10);
  // digitalWrite(trig_f, LOW);
  long t = pulseIn(echo_f, HIGH);
  long cm = t / 29 / 2; //time convert distance
  // Serial.print("distance ");
  // Serial.println(cm);
  return cm;
}
