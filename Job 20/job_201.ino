// C++ code
//
#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
const int triggerPin = 8;
const int echoPin = 9;
const int lowerDistanceThreshold = 50;
const int upperDistanceThreshold = 150;
void setup()
{
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void print_on_serial_monitor(double distance){
  Serial.print("Distance from the object is ");
  Serial.print(distance);
  Serial.println(" cm");
}

void print_on_lcd_screen(double distance){
 if(distance< lowerDistanceThreshold)
 {lcd.setCursor(0,0);
  lcd.print("Distance from the object is ");
  lcd.print(distance);
  lcd.setCursor(0,1);
  lcd.scrollDisplayLeft();
  lcd.println("Water level is too low turn on the pump ");
 }
  
  else if(distance> upperDistanceThreshold)
 {lcd.setCursor(0,0);
  lcd.print("Distance from the object is ");
  lcd.print(distance);
  lcd.setCursor(0,1);
  lcd.scrollDisplayLeft();
  lcd.println("Water level is too high turn off the pump ");
 }
  else
 {lcd.setCursor(0,0);
  lcd.print("Distance from the object is ");
  lcd.print(distance);
  lcd.setCursor(0,1);
  lcd.scrollDisplayLeft();
  lcd.println("Water level is okay ");
 }
  
}


void loop()
{
  digitalWrite(triggerPin, LOW);
  delay(2); // Wait for 2 millisecond(s)
  digitalWrite(triggerPin, HIGH);
  delay(10); // Wait for 10 millisecond(s)
  digitalWrite(triggerPin, LOW);
  int timetaken=pulseIn(echoPin,HIGH);
  double distance=(timetaken*0.034)/2;
 print_on_serial_monitor(distance);
 print_on_lcd_screen(distance);
  
}