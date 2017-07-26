#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#define MAX_DISTANCE 200
#define MAX_DISTANCE_OBJECT 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define PIN 8
#define leftMotorDirection  4
#define leftMotorSpeed  5
#define rightMotorSpeed  6
#define rightMotorDirection  7
#define turnSpeed 200
#define straightSpeed 250
#define FORWARD HIGH
#define REVERSE LOW
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
unsigned long previousMillis = 0;
int interval = 100;
const int d = 0;
int count = 0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setupRobot(void) {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(TRIGGER_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  pinMode(leftMotorDirection, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorDirection, OUTPUT);
  pinMode(rightMotorSpeed, OUTPUT);
}

void setup() {
  strip.begin();
  strip.show();
  setupRobot();
  inputString.reserve(200);
}

void loop() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    previousMillis = currentMillis;
    unsigned int PING = sonar.ping_cm();
    Serial.println ("DISTANCE : " + String(PING) + "cm");
    if ( PING <  MAX_DISTANCE_OBJECT ) {
      strip.setPixelColor(0,255,0,0);
      strip.show();
      findRoute(100);
    } else {
      strip.setPixelColor(0,0,0,255);
      strip.show();
      goForward(1);
    }
  }
}

void goForward(int d) {
  analogWrite(leftMotorSpeed, straightSpeed);
  digitalWrite(leftMotorDirection, HIGH);
  analogWrite(rightMotorSpeed, straightSpeed);
  digitalWrite(rightMotorDirection, HIGH);
  delay(d);
}

void goBackward(int d) {
  analogWrite(leftMotorSpeed, straightSpeed);
  digitalWrite(leftMotorDirection, LOW);
  analogWrite(rightMotorSpeed, straightSpeed);
  digitalWrite(rightMotorDirection, LOW);
  delay(d);
}

void turnLeft(int d) {
  analogWrite(leftMotorSpeed, turnSpeed);
  digitalWrite(leftMotorDirection, LOW);
  analogWrite(rightMotorSpeed, turnSpeed);
  digitalWrite(rightMotorDirection, HIGH);
  delay(d);
}

void turnRight(int d) {
  analogWrite(leftMotorSpeed, turnSpeed);
  digitalWrite(leftMotorDirection, HIGH);
  analogWrite(rightMotorSpeed, turnSpeed);
  digitalWrite(rightMotorDirection, LOW);
  delay(d);
}

void stopMotors(int d) {
  analogWrite(leftMotorSpeed, 0);
  analogWrite(rightMotorSpeed, 0);
  delay(d);
}

void findRoute(int d) {
  goBackward(200);
  count++;
  stopMotors(300);
  if(count>5) {
    if(rand()%2==0) {
      turnLeft(500);
    } else {
      turnRight(500);
    }
    count = 0;
  }
}