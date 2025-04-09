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

// Variables pour le chronomètre
unsigned long startMillis = 0;  // Temps du début du chronomètre
unsigned long elapsedMillis = 0;  // Temps écoulé total
bool running = false;  // Statut du chronomètre

// Variables pour gérer le bouton
bool etatBoutonPrecedent = LOW;  // Etat précédent du bouton
unsigned long dernierDebounce = 0;  // Temps du dernier changement d'état du bouton
const unsigned long debounceDelay = 200;  // Délai anti-rebond (200 ms pour être plus réactif)

void setup() {
  pinMode(boutonPin, INPUT_PULLUP); // Bouton avec résistance pull-up interne
  lcd.begin(16, 2);  // Initialisation de l'écran LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Chronometre");
}

void loop() {
  // Lire l'état du bouton (logique inversée avec pull-up)
  bool lectureBouton = !digitalRead(boutonPin);

  // Anti-rebond : vérifier si l'état du bouton a changé
  if (lectureBouton != etatBoutonPrecedent) {
    dernierDebounce = millis();
  }

  // Si état stable après rebond, basculer l'état du chronomètre
  if ((millis() - dernierDebounce) > debounceDelay) {
    if (lectureBouton && !etatBoutonPrecedent) {
      if (running) {
        // Arrêter le chronomètre
        elapsedMillis += millis() - startMillis;
        running = false;
      } else {
        // Démarrer le chronomètre
        startMillis = millis();
        running = true;
      }
    }
  }

  etatBoutonPrecedent = lectureBouton;

  // Si le chronomètre est en marche, calculer et afficher le temps écoulé
  if (running) {
    unsigned long tempsEcoule = millis() - startMillis + elapsedMillis;
    afficherTemps(tempsEcoule);
  } else {
    // Si le chronomètre est arrêté, afficher le temps actuel
    afficherTemps(elapsedMillis);
  }
}

// Fonction pour afficher le temps sous le format HH:MM:SS
void afficherTemps(unsigned long temps) {
  int secondes = temps / 1000;
  int minutes = secondes / 60;
  int heures = minutes / 60;

  secondes = secondes % 60;
  minutes = minutes % 60;

  lcd.setCursor(0, 1);  // Placer le curseur sur la 2e ligne
  lcd.print("Temps: ");
  
  // Afficher les heures, minutes et secondes avec des zéros en tête si nécessaire
  if (heures < 10) lcd.print("0");
  lcd.print(heures);
  lcd.print(":");

  if (minutes < 10) lcd.print("0");
  lcd.print(minutes);
  lcd.print(":");

  if (secondes < 10) lcd.print("0");
  lcd.print(secondes);
  lcd.print("  ");  // Effacer les anciens chiffres
}
