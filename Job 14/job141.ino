#include <LiquidCrystal.h>

// Définir les broches de l'écran LCD
const int RS = 12;
const int EN = 11;
const int D4 = 5;
const int D5 = 4;
const int D6 = 3;
const int D7 = 2;

// Définir la broche du bouton
const int boutonPin = 8;

// Initialisation de l'objet LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Variables pour le compteur
unsigned long tempsPrecedent = 0;
unsigned long compteur = 0;
bool compteurActif = true;

// Gestion du bouton (anti-rebond)
bool etatBoutonPrecedent = LOW;
unsigned long dernierDebounce = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(boutonPin, INPUT_PULLUP); // Bouton avec résistance pull-up interne
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Groupe Louis"); // <<<< Nom du groupe

  // Affiche le compteur dès le départ
  afficherTemps(compteur);
}

void loop() {
  // Lire l'état du bouton (logique inversée avec pull-up)
  bool lectureBouton = !digitalRead(boutonPin);

  // Anti-rebond : vérifie si l'état a changé
  if (lectureBouton != etatBoutonPrecedent) {
    dernierDebounce = millis();
  }

  // Si état stable après rebond, bascule l'état du compteur
  if ((millis() - dernierDebounce) > debounceDelay) {
    if (lectureBouton && !etatBoutonPrecedent) {
      compteurActif = !compteurActif;
    }
  }

  etatBoutonPrecedent = lectureBouton;

  // Si le compteur est actif, mise à jour toutes les secondes
  if (compteurActif && millis() - tempsPrecedent >= 1000) {
    tempsPrecedent = millis();
    compteur++;
    afficherTemps(compteur);
  }
}

// Fonction pour afficher le temps au format mm:ss
void afficherTemps(unsigned long secondesTotales) {
  int minutes = secondesTotales / 60;
  int secondes = secondesTotales % 60;

  lcd.setCursor(0, 1);
  lcd.print("Temps: ");
  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");
  if (secondes < 10) lcd.print("0");
  lcd.print(secondes);
  lcd.print("  "); // Efface les vieux caractères si besoin
}
