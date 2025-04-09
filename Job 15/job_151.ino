#include <SoftwareSerial.h>
#define blue 9
#define red 11
#define green 10
#define KNOB 0

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(KNOB);
  Serial.print("Potentiometer value: ");
  Serial.println(val);
  if (val >= 600){
  analogWrite(blue, 255);
  analogWrite(red, 0);
  analogWrite(green, 0);
    }
  else if (val<300){
  analogWrite(blue, 0);
  analogWrite(red, 255);
  analogWrite(green, 0);
  	}
  else if ((val>=300) && (val<600)){
  analogWrite(blue, 0);
  analogWrite(red, 0);
  analogWrite(green, 255);
  }}
