#include <Servo.h>          //Servo motor library. This is standard library //Robot Lk
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library //Robot Lk
//Robot Lk YouTube Channel-https://www.youtube.com/c/RobotLk
//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;
const int fan = 11;
//LED Robot LkNazia Marwiana
const int green_LED = 8;
const int yellow_LED = 3;
const int red_LED = 2;


//ultrasonic sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A0 //analog input 2
#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

//flams sensor pin
const int flamePin = A2;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
int lookRight(){  
  servo_motor.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int fire(){
  int result = analogRead(flamePin);
  Serial.print("Fire Value : ");
  Serial.println(result);
  if(result <=1000 ){
    Serial.println("Fire Detected");
    digitalWrite(fan,HIGH);
    Serial.println("Fan ON!!!");
  }else{
    Serial.println("Fire Not Detected");
    digitalWrite(fan,LOW);
    Serial.println("Fan OFf!!");
  }
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(green_LED, LOW);
  digitalWrite(yellow_LED, LOW);
  digitalWrite(red_LED, HIGH);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
  
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW); 

    digitalWrite(green_LED, HIGH);//Robot Lk//Robot Lk
    digitalWrite(red_LED, LOW);//Robot Lk//Robot Lk
    digitalWrite(yellow_LED, LOW);//Robot Lk//Robot Lk
    
  }
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

  digitalWrite(yellow_LED, HIGH);
  digitalWrite(red_LED, LOW);
  digitalWrite(green_LED, LOW);
}


void turnRight(){

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  delay(250);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void setup(){
  Serial.begin(9600);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
  pinMode(flamePin,INPUT);
  pinMode(fan,OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  Serial.println(distance);
  if (distance <= 45){
    Serial.println("Checked Fire Or Not!!!");
    fire();
    moveStop();
    Serial.println("Stopp");
    delay(300);
    moveBackward();
    Serial.println("Mundur");
    delay(400);
    moveStop();
    Serial.println("Stopp");
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance >= distanceLeft){
      Serial.println("Belok Kanan");
      turnRight();
      moveStop();
    }
    else{
      Serial.println("Belok Kiri");
      turnLeft();
      moveStop();
    }
  }
  else{
    fire();
    moveForward(); 
    Serial.println("Majuuuu");
  }
    distance = readPing();
    // delay(1000);
}