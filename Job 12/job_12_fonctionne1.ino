/*
 Affiche la chaîne "Hello World"
 sur un écran LCD compatible HD44780
*/

/* Inclut la bibliothèque pour la gestion de l'écran LCD */
#include <LiquidCrystal.h>

/* Correspondance des broches LCD – broches Arduino */
/* la broche 5 (RW) doit être connectée à GND */

const int RS = 12 ;
const int EN = 11 ;
const int D7 = 2  ;
const int D6 = 3  ;
const int D5 = 4  ;
const int D4 = 5  ;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); // crée un objet lcd

void setup()
{
   lcd.begin(2, 16); // Utilise un écran LCD 2x16
}

void loop()
{
   lcd.clear();            // Efface l'écran
   lcd.noBlink();          // Désactive le clignotement du curseur
   lcd.setCursor(0, 0);    // Positionne le curseur à x=0, y=0 (1ère colonne, 1ère ligne)
   lcd.print("Hello");
   lcd.setCursor(0, 1);    // Positionne le curseur à x=0, y=1 (1ère colonne, 2e ligne)
   lcd.print("World");
   delay(500);
}
