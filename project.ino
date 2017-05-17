#include <Adafruit_NeoPixel.h>
#include <NewPing.h>
#define MAX_DISTANCE 200 
#define MAX_DISTANCE_OBJECT 10
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define PIN 8
#define leftmotordirection  4
#define leftmotorspeed  5
#define rightmotorspeed  6
#define rightmotordirection  7
#define FORWARD HIGH
#define REVERSE LOW
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE);
unsigned long previousMillis = 0;
int interval = 200;
const int d = 0; 
int count = 0;
void setupRobot(void)
{
  pinMode(TRIGGER_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  Serial.begin(9600);
  pinMode(leftmotordirection, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotordirection, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);
}
void setup() 
{
  Serial.begin(9200);
  strip.begin();
  strip.show();
  setupRobot();
}
void loop() 
{
unsigned long currentMillis = millis();
if ((unsigned long)(currentMillis - previousMillis) >= interval)
{
previousMillis = currentMillis; 
unsigned int PING = sonar.ping_cm();
Serial.println ("DISTANCE : " + String(PING) + "cm");
if ( PING <  MAX_DISTANCE_OBJECT )
{
  strip.setPixelColor(0,255,0,0);
  strip.show();
  findroute(100);
}
else
{
  strip.setPixelColor(0,0,0,255);
  strip.show();
  goForward(50);
}
}
}
void goForward(int d)
{
    analogWrite(leftmotorspeed, 200);
    analogWrite(leftmotordirection, 255);
    analogWrite(rightmotorspeed, 200);
    analogWrite(rightmotordirection, 255);  
    delay (d);
}
void turnLeft(int d)
{
   analogWrite(leftmotorspeed, 200);
   analogWrite(leftmotordirection,0);
   analogWrite(rightmotorspeed, 200);
   analogWrite(rightmotordirection, 255);  
   delay (d);
}
void goBackward(int d)
{
    analogWrite(leftmotorspeed, 200);
    analogWrite(leftmotordirection, 0);
    analogWrite(rightmotorspeed, 200);
    analogWrite(rightmotordirection, 0);
    delay (d);  
}
void turnRight(int d)
{
    analogWrite(leftmotorspeed, 155);
    analogWrite(leftmotordirection, 255);
    analogWrite(rightmotorspeed, 155);
    analogWrite(rightmotordirection, 0);
    delay (d);      
}
void stoP(int d)
{
    digitalWrite(leftmotorspeed, LOW);
    digitalWrite(rightmotorspeed, LOW);
    delay (d);
}
void findroute(int d)
{                                                                                          
    goBackward(50);
    count++;
    stoP(100);
    if(count>5)
    {
      if(rand()%2==0)
      {
        turnLeft(100);
      }
      else    
      {
       turnRight(100);
      }
      count = 0;
    }
}
