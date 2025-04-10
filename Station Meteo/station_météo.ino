// bibliothèque LCD
#include <LiquidCrystal.h>

// initialise la bibliothèque lcd
LiquidCrystal LCD(12,11,5,4,3,2);

// définir la broche analogique A0
int SensorTemp=0;

// définir la pin 8 pour l'alerte de température froide
int alertefroid=8;
// définir la pin 13 pour l'alerte de température chaude
int alertechaud=13;

// définir température basse en dessous de 0°C
int TempBasse=0;
// dfinir température haute au dessus de 40°C
int TempHaute=40;

void setup() {
	// dfinir la broche d’alerte de basse température en sortie
  	pinMode(alertefroid, OUTPUT);
	// dfinit la broche d’alerte de haute température en sortie
	pinMode(alertechaud, OUTPUT);

	// définir le nombre de colonnes de l'écran LCD
	LCD.begin(16,2);
	// imrime le message sur l'écran LCD
	LCD.print("Temperature:");
	// bacule le curseur sur la première colonne et la deuxième ligne de l'écran LCD
	LCD.setCursor(0,1);
	// affiche le message sur l'écran LCD
	LCD.print("      'C        ");
}

void loop() {
	//lecture du capteur de température
	int SensorTempTension=analogRead(SensorTemp);

  	//conversion de la tension
	float Tension=SensorTempTension*5;
	Tension/=1024;

  	//convertir la tension lue en degrés Celsius
	float TemperatureC=(Tension-0.5)*100;

  	
  	// bascule le curseur sur la première colonne et la deuxième ligne de l'écran LCD
  	LCD.setCursor(0,1);

  	// affiche la température sur l'écran LCD
	LCD.print(TemperatureC);

	// allume ou éteint les led de températures basses et hautes
  	if (TemperatureC>=TempHaute) {
  		digitalWrite(alertefroid, LOW);
  		digitalWrite(alertechaud, HIGH);
    }
  	else if (TemperatureC<=TempBasse){
  		digitalWrite(alertefroid, HIGH);
  		digitalWrite(alertechaud, LOW);
  	}
  	else {
  		digitalWrite(alertefroid, LOW);
  		digitalWrite(alertechaud, LOW);
    }

  	// attendre 1000ms
  	delay(1000);
}