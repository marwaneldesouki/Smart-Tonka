#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

RTC_DS3231 rtc;

const int trigPin = 9;   // Trig pin connected to digital pin 2
const int echoPin = A0;  // Echo pin connected to analog pin A0

const int trigPin_2 = 10;  // Trig pin connected to digital pin 2
const int echoPin_2 = A1;  // Echo pin connected to analog pin A0

const int trigPin_3 = 11;  // Trig pin connected to digital pin 2
const int echoPin_3 = A2;

const int trigPin_4 = 12;  // Trig pin connected to digital pin 2
const int echoPin_4 = A3;

float distance;
float distance_2;
float distance_3;
float distance_4;
SoftwareSerial BT(0, 1);

LiquidCrystal_I2C lcd(0x27, 16, 2);
int motor_1_Pin_1 = 2;  //IN1
int motor_1_Pin_2 = 3;  //IN2
int motor_1_ena = 5;    //ENA
int motor_2_Pin_1 = 8;  //IN3
int motor_2_Pin_2 = 7;  //IN4
int motor_2_enb = 6;    //ENB



int tonePin = 13;
char state;
int Speed = 130;
long duration;
int set = 16;


void print_Distance() {
  Serial.print("Distance1: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Distance2: ");
  Serial.print(distance_2);
  Serial.println(" cm");
  Serial.print("Distance3: ");
  Serial.print(distance_3);
  Serial.println(" cm");
  Serial.print("Distance4: ");
  Serial.print(distance_4);
  Serial.println(" cm");
}
void setup() {
  rtc.begin();
  // set the time to the current time
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(trigPin_4, OUTPUT);
  pinMode(echoPin_4, INPUT);

  pinMode(motor_1_Pin_1, OUTPUT);
  pinMode(motor_1_Pin_2, OUTPUT);

  pinMode(motor_2_Pin_1, OUTPUT);
  pinMode(motor_2_Pin_2, OUTPUT);

  analogWrite(motor_1_ena, Speed);
  analogWrite(motor_2_enb, Speed);
  pinMode(tonePin, OUTPUT);

  lcd.init();
  lcd.backlight();
  for (int i = 0; i < 5; i++) {
    lcd.print("Project Made");
    lcd.setCursor(0, 1);  // go to start of 2nd line
    lcd.print("By ZESOL");
    delay(1000);
    lcd.clear();
    delay(1000);
  }
  lcd.print("  For DR.ALYAA");
  lcd.setCursor(0, 1);  // go to start of 2nd line
  lcd.print("    By ZESOL");

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  BT.begin(9600);  // Setting the baud rate of Software Serial Library
  delay(500);
}

void loop() {

  //if some date is sent, reads it and saves in state
  data();
  if (BT.available() > 0) {
    data();
    state = BT.read();
    Serial.println(state);
    if ((state >= '0' && state <= '9') || state == 'q') {
      int state_x = state - '0';
      (state == 'q') ? Speed = 120 : Speed = (state_x * 10);
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
    }

    delayMicroseconds(200);
    print_Distance();
  }



  if (state == 'V') {
    int hornFrequency = 500; // Adjust this value to change the pitch of the tone

  // Generate the horn tone for a duration of 1 second
  tone(tonePin, hornFrequency);
  } else if (state == 'v') {
    noTone(tonePin);
  }
  // if the state is '1' the DC motor will go forward

  if (state == 'F') {
    if (!checkObstacle_front())
      forward();
    else
      Stop();
  }

  // if the state is '2' the motor will Reverse
  else if (state == 'B') {
    if (!checkObstacle_back())
    backward();
    else
      Stop();
  }

  // if the state is '3' the motor will turn left
  else if (state == 'L') {
    turnLeft();
    // Serial.println("Turn LEFT");
  }

  // if the state is '4' the motor will turn right
  else if (state == 'R') {
    turnRight();
    // Serial.println("Turn RIGHT");
  }

  // if the state is '5' the motor will Stop
  else if (state == 'S') {
    Stop();
    // Serial.println("STOP!");
  } else if (state == 'U' && distance_3 <= 6) {
    // print_Distance();
    while (distance_3 <= 10) {  //lesa wa2f mkano
      data();
      Serial.println("please move");
      Speed = 55;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
      forward();
    }
    data();
  
    unsigned long start_time;
    if (distance_3 > 6)  //start timer
    {
      start_time = millis();
      while (distance_3 > 6) {
        data();
        Serial.println("moving until another");
        // Speed = 55;
        // analogWrite(motor_1_ena, Speed);
        // analogWrite(motor_2_enb, Speed);
        // forward();
      }
    }
    Stop();
    unsigned long end_time = millis();
    // DateTime new_now = rtc.now();
    // TimeSpan difference = new_now - old_now;
    // double totalSeconds = difference.totalseconds();
    // double seconds = totalSeconds % 60;
    unsigned long time_difference = end_time - start_time;
    Serial.println(time_difference);
    delay(1000);
    data();
    if (time_difference >= 1200 && time_difference <= 3000)  //rakna 7lewa
    {
      Serial.println("ana fe rakna 7elwa");
      Speed = 120;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
      while ((distance_3 < 80 || distance_3 < 90)) {  //rotate car
        Serial.println("ana fe rotate car");
        delay(750);
        data();
        print_Distance();
        delay(250);
        data();
        while (distance_3 < 70) {
          data();
          turnLeft();
          delay(50);
          Stop();
          delay(450);
        }
      }
      Serial.println("l2eet el zawya");
      data();
      print_Distance();
      while (distance > 25) {  //harg3 be dahry
        data();
        Serial.println("harg3 be dahry");
        print_Distance();
        backward();
        delay(100);
        Stop();
        delay(550);
      }
      turnRight();
      delay(100);
      Stop();
      delay(750);

      data();
      print_Distance();
      while ((distance_2 == distance_3) || (distance_2 >= 15 && distance_3 >= 25)) {  //hakhosh ymen
        data();
        Serial.println("hakhosh ymeen");
        print_Distance();
        turnRight();
        delay(100);
        Stop();
        delay(550);
        }

    } 

    state = 0;
  } else if (state == 'u') {
    Serial.println("Parking mode out on;");
  } else if (state == 'W' && (distance_3 <= 8 && distance_2 <= 8)) {
 while (distance_3 <= 10) {  //lesa wa2f mkano
      data();
      Serial.println("please move");
      Speed = 55;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
      forward();
    }
    Stop();
    delay(520);
    Serial.println("odam msh shayf wara lesa shayf");
    while (distance_2 <= 10) {  //byt7rk lghayt ma wara myshofsh
      data();
      print_Distance();
      Serial.println("please move 2");
      Speed = 55;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
      forward();
    }
    Stop();
    delay(500);
  data();
  print_Distance();
    delay(500);
    if(distance_2&&distance_3>=20){//el etnen b2o fadyeen w hylf 3ala nafso right
    Serial.println("El etnen fadyeen wlsa hylfo");
  data();
    Speed = 120;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
    while(distance_3>10){// hylef lghayt mayb2a linear
        Serial.println("lef ymeen");
        print_Distance();
        turnRight();
        delay(100);
        Stop();
        delay(550);
    }
    Speed = 55;
      analogWrite(motor_1_ena, Speed);
      analogWrite(motor_2_enb, Speed);
    while(distance_3<10&&distance_2>10&&distance_4>=10){// hymshe odam lghayt mykhbt
  data();
        Serial.println("khosh odam");
        print_Distance();
        forward();
        delay(100);
        Stop();
        delay(550);
    }
    Stop();
    state='z';
    data();
 
  }
  }
}
bool checkObstacle_front() {
  data();
  if (distance_4 < set) {
    return true;
  } else {
    return false;
  }
}
bool checkObstacle_back() {
  data();
  if (distance < set) {
    return true;
  } else {
    return false;
  }
}
void forward() {
  digitalWrite(motor_1_Pin_1, HIGH);  //IN1
  digitalWrite(motor_1_Pin_2, LOW);   //IN2
  digitalWrite(motor_2_Pin_1, HIGH);  //IN3
  digitalWrite(motor_2_Pin_2, LOW);   //IN4
}

void backward() {
  digitalWrite(motor_1_Pin_1, LOW);   //IN1
  digitalWrite(motor_1_Pin_2, HIGH);  //IN2
  digitalWrite(motor_2_Pin_1, LOW);   //IN3
  digitalWrite(motor_2_Pin_2, HIGH);  //IN4
}

void turnRight() {
  digitalWrite(motor_1_Pin_1, HIGH);  //IN1
  digitalWrite(motor_1_Pin_2, LOW);   //IN2
  digitalWrite(motor_2_Pin_1, LOW);   //IN3
  digitalWrite(motor_2_Pin_2, HIGH);  //IN4
}

void turnLeft() {
  digitalWrite(motor_1_Pin_1, LOW);   //IN1
  digitalWrite(motor_1_Pin_2, HIGH);  //IN2
  digitalWrite(motor_2_Pin_1, HIGH);  //IN3
  digitalWrite(motor_2_Pin_2, LOW);   //IN4
}

void Stop() {
  digitalWrite(motor_1_Pin_1, LOW);
  digitalWrite(motor_1_Pin_2, LOW);
  digitalWrite(motor_2_Pin_1, LOW);
  digitalWrite(motor_2_Pin_2, LOW);
  // Serial.println("Stop!");
}
void parking_mode_back() {
}
void data() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int pulseDuration = pulseIn(echoPin, HIGH);


  digitalWrite(trigPin_2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_2, LOW);
  int pulseDuration_2 = pulseIn(echoPin_2, HIGH);

  digitalWrite(trigPin_3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_3, LOW);
  int pulseDuration_3 = pulseIn(echoPin_3, HIGH);

  digitalWrite(trigPin_4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin_4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_4, LOW);
  int pulseDuration_4 = pulseIn(echoPin_4, HIGH);

  // Display the distance in centimeters
  distance = pulseDuration * 0.034 / 2;
  // Serial.print("Distance1: ");
  // Serial.print(distance);
  // Serial.println(" cm");

  distance_2 = pulseDuration_2 * 0.034 / 2;
  // Serial.print("Distance2: ");
  // Serial.print(distance_2);
  // Serial.println(" cm");

  distance_3 = pulseDuration_3 * 0.034 / 2;
  // Serial.print("Distance3: ");
  // Serial.print(distance_3);
  // Serial.println(" cm");

  distance_4 = pulseDuration_4 * 0.034 / 2;
  // Serial.print("Distance4: ");
  // Serial.print(distance_4);
  // Serial.println(" cm");

  // delay(1000);  // Delay between measurements
}