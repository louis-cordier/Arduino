#include <LiquidCrystal.h>

// Initialisation de l'écran LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Broches connectées aux axes du joystick
int potPinX = A1;
int potPinY = A2;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  int valX = analogRead(potPinX);
  int valY = analogRead(potPinY);

  lcd.clear();  // Efface l'écran à chaque boucle pour éviter de mélanger les mots

  lcd.setCursor(0, 0);
  lcd.print("Direction:");

  // Joystick au repos : autour de 512
  // Seuils à ajuster si besoin
  if (valX > 700) {
    lcd.setCursor(0, 1);
    lcd.print("Droite");
  } else if (valX < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Gauche");
  } else if (valY > 700) {
    lcd.setCursor(0, 1);
    lcd.print("Haut");
  } else if (valY < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Bas");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Centre");
  }

  delay(200); // Petite pause pour éviter les clignotements rapides
}
