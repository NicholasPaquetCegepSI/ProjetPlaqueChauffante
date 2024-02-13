#define LED_BLEUE 0
#define LED_JAUNE 1
#define LED_VERTE 2

#define LM35 A0

void setup() {
  Serial.begin(9600);

  // Déclaration des LEDs
  pinMode(LED_BLEUE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);

  pinMode(LM35, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BLEUE, HIGH);
  digitalWrite(LED_JAUNE, HIGH);
  digitalWrite(LED_VERTE, HIGH);

  analogReadResolution(12);
  getTemperature(true);
}

void getTemperature(bool print) {
  // Lecture de la valeur analogique du capteur
  int valeurDuCapteur = analogRead(LM35);
  // Calcul de conversion pour une résolution de 12 bits
  double temperatureCelcius = (double)valeurDuCapteur * (3.3 / 40.96);

  if (print) {
    Serial.print("Température: ");
    Serial.println(temperatureCelcius);
  }
}

// Fonction de temporisation, retourne faux tant que la durée passée en argument ne s'est pas écoulée.
bool tempo(int duree) {
  // La fonction millis retourne le temps écoulé depuis le début de l'éxécution du Arduino.
  unsigned long millisPresent = millis();

  // Si le temps présent a dépassé le temps précédent (temps depuis la dernière temporisation) + la durée,
  // on retourne vrai car la temporisation est terminé et on met à jour le temps précédent.
  if (millisPresent - millisPrecedent >= +duree) {
    millisPrecedent = millisPresent;
    return true;
  }
  return false;
}