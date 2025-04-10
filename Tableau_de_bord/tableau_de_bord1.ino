#include<LiquidCrystal.h>
#include<SoftwareSerial.h>

LiquidCrystal lcd(11,12,2,3,4,5);
int degreeCelsius = 0;
int degreeFahrenheit = 0;
float percentHumidity = 0;
float tempCalib=5.3;
float humidCalib=2.8654;


int convertCtoF(float c) { return c * 1.8 + 32; }

void clear(void){
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,1);
   lcd.print("                 ");
  delay(500);
}

void printResultsLCD(void){
  degreeFahrenheit = convertCtoF(degreeCelsius);
  lcd.setCursor(0,0);
  lcd.print("Temp:  ");
  lcd.setCursor(6,0);
  lcd.print(degreeCelsius);
  lcd.print("\260C ");
  //lcd.setCursor(11,0);
  //lcd.print(degreeFahrenheit);
  //lcd.print("\260F ");
  lcd.setCursor(0,1);
  lcd.print("Humidity:   ");
  lcd.print((int)percentHumidity);
  lcd.setCursor(14,1);
  lcd.print("\045 ");  // octal for percent - ascii
  delay(1500);
}

// Global Variables
int DHT11_Pin = A0; // DHT11 Data Pin

int Humidity = 0;
int Temp = 0;
int TempComma = 0;
bool P_DHTError = false; // Checksum Error

// a Delay routine. Call DelayTimer(time in uSec)

void DelayTimer(long int DelayValue){
long int DelayTime = micros();
do {

}while (micros()-DelayTime < DelayValue);
}
// Main DHT Void

void DHT11(){

long int DataTime = 0;

byte Result[45];
byte DataArray = 0;
byte DataCounter = 0;
byte DHTData[4];

bool BlockDHT=false;

// Trigger Sensor - Handshake between 
// MCU and DHT  (described in the Datasheet)

pinMode(DHT11_Pin,OUTPUT);
digitalWrite(DHT11_Pin,HIGH);
DelayTimer(250000); //Wait 250millisec
digitalWrite(DHT11_Pin,LOW);
DelayTimer(30000); //Wait 30millisec
digitalWrite(DHT11_Pin,HIGH);
DelayTimer(50); //Wait 50microsec
pinMode(DHT11_Pin,INPUT);
// read the Bits and put them into a Result array (It will count 42 bits. The first two one are unused)

do {
if (digitalRead(DHT11_Pin) == 0 && BlockDHT == false) {BlockDHT = true;Result[DataArray]=(micros()-DataTime);DataArray++;DataTime=micros();} //If DHT pin is low, go to next Dataset
if (digitalRead(DHT11_Pin) == 1) {BlockDHT = false;} // As long as DHT pin is Hight add time in Microseconds to Result

}while((micros()-DataTime) < 150); // if DTH Sensor high for more than 150 usec, leave loop

// Asign 1 or 0 to Result variable. If more than 80uS Data as “1”
// Starting at Data set 02. First two Datasets are ignored!

for (int i=2; i< DataArray; i++) {
if (Result[i] <= 90) Result[i]=0; else Result[i]=1;
}

for (int j=0; j< 5; j++){ // redo it for the 5 Bytes (40 Databits /8 = 5)
for (int i=0; i< 8; i++) {bitWrite(DHTData[j], 7-i, Result[i+2+(j*8)]);} // Create 5 Databytes from the 40 Databits (Ignoring the 2 first Databits)

}
// check checksum }
  Temp = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  degreeCelsius=Temp;
  percentHumidity = DHTData[0]/humidCalib;
  Temp = DHTData[2]/tempCalib;
  degreeCelsius=Temp;
if (DHTData[4] == (DHTData[0]+DHTData[1]+DHTData[2]+DHTData[3])){Humidity = DHTData[0];Temp = DHTData[2];TempComma = DHTData[3];P_DHTError=false;} else P_DHTError=true; //If Checksum is worng, Temp=99 (Dataset 0-3 in addition = Dataset 4 = Checksum OK)

}

void setup() {
Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(9, INPUT);
  
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
lcd.setCursor(0,0);
lcd.print("Temp \046 Humidity");
lcd.setCursor(0,1);
lcd.print("    Display    ");
delay(1000);
lcd.clear();
}

void loop() {
DHT11();
printResultsLCD();
DelayTimer(500000); //wait 2,5 sec

  if (Temp > 20){
    for (int i=1; i<2; i++){
    tone(9, 440, 250);
    digitalWrite(8, HIGH);
    digitalWrite (7, LOW);
    }
  }
    if (Temp < 20) {
      for (int i=0; i<1; i++){
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
        delay(250);
      }
    }
  }   


