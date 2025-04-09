#include <LiquidCrystal.h>

// Configuration des broches LCD
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Variables pour l'heure
int heures = 0, minutes = 0, secondes = 0;

void setup() {
  lcd.begin(16, 2); // Initialise le LCD 16 colonnes x 2 lignes
  lcd.print("Heure actuelle:"); // Message statique
}

void loop() {
  // Mise à jour de l'heure (simulée)
  secondes++;
  if (secondes >= 60) {
    secondes = 0;
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
      heures++;
      if (heures >= 24) {
        heures = 0;
      }
    }
  }

  // Affichage sur le LCD (format HH:MM:SS)
  lcd.setCursor(0, 1); // Seconde ligne
  if (heures < 10) lcd.print("0"); // Ajoute un zéro pour les heures < 10
  lcd.print(heures);
  lcd.print(":");
  if (minutes < 10) lcd.print("0"); // Ajoute un zéro pour les minutes < 10
  lcd.print(minutes);
  lcd.print(":");
  if (secondes < 10) lcd.print("0"); // Ajoute un zéro pour les secondes < 10
  lcd.print(secondes);

  delay(1000); // Attend 1 seconde
}