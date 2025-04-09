/*
 Affiche un smiley
 sur un écran LCD compatible HD44780
*/

/* Inclut la bibliothèque pour la gestion de l'écran LCD */
#include <LiquidCrystal.h>

/* Correspondance des broches LCD – broches Arduino */
/* la broche 5 (RW) doit être connectée à GND */

const int RS = 12;
const int EN = 11;
const int D7 = 2;
const int D6 = 3;
const int D5 = 4;
const int D4 = 5;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); // crée un objet lcd

// Définition du caractère personnalisé pour un smiley (8x5 pixels)
byte smiley[8] = {
  B00000,
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.begin(2, 16);         // Utilise un écran LCD 2x16
  lcd.createChar(0, smiley); // Crée le smiley dans la position 0
  lcd.clear();              // Efface l’écran
  lcd.setCursor(7, 0);      // Centre le smiley (colonne 7, ligne 0)
  lcd.write(byte(0));       // Affiche le smiley
}

void loop() {
  // Pas de mise à jour continue nécessaire ici
}
