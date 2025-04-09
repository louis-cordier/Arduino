#include <LiquidCrystal.h>

// Définir les broches de l'écran LCD
const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

// Initialisation de l'écran LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Variables pour la barre de chargement
int position = 0;
unsigned long dernierTemps = 0;
const unsigned long intervalle = 3000;  // 3 secondes

void setup() {
  lcd.begin(16, 2);      // LCD 16 colonnes, 2 lignes
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chargement...");
}

void loop() {
  unsigned long maintenant = millis();

  // Toutes les 3 secondes, ajouter un bloc à la barre
  if ((maintenant - dernierTemps >= intervalle) && position < 16) {
    lcd.setCursor(position, 1);  // Ligne 2, colonne actuelle
    lcd.print("#"); // ou lcd.print("="); ou lcd.print(">");
    //lcd.write(byte(255));        // Affiche un rectangle plein (█)
    position++;
    dernierTemps = maintenant;
  }

  // Facultatif : Redémarre la barre une fois remplie
  if (position >= 16) {
    delay(2000);                 // Pause 2 secondes à la fin
    lcd.setCursor(0, 1);
    lcd.print("                ");  // Efface la ligne
    position = 0;                // Réinitialise la position
    dernierTemps = millis();    // Redémarre le timer
  }
}
