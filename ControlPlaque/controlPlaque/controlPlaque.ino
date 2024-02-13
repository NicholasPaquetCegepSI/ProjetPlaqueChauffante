#define LED_BLEUE 0
#define LED_JAUNE 1
#define LED_VERTE 2

#define LM35 A0

#define RELAI 3

#define BTN 4

unsigned long millisPrecedent = 0;  // Variable globale pour garder le compte sur le temps.
bool relaiActif = false;

void setup() {
  Serial.begin(9600);

  // Déclaration des LEDs
  pinMode(LED_BLEUE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);

  pinMode(LM35, INPUT);
  analogReadResolution(12);

  pinMode(RELAI, OUTPUT);
}

void loop() {
  test();
}

void test() {
  // Test leds
  digitalWrite(LED_BLEUE, HIGH);
  digitalWrite(LED_JAUNE, HIGH);
  digitalWrite(LED_VERTE, HIGH);

  // getTemperature(true);

  if (tempo(5000)) {
    Serial.println("changement d'etat du relai");
    relaiActif = !relaiActif;
  }

  // Test du relai
  // if (relaiActif) {
  //   digitalWrite(RELAI, HIGH);
  //   Serial.println("Relai ON");
  // } else {

  //   digitalWrite(RELAI, LOW);
  //   Serial.println("Relai OFF");
  // }
}

void getTemperature(bool print) {
  // Lecture de la valeur analogique du capteur
  int valeurDuCapteur = analogRead(LM35);
  // Calcul de conversion pour une résolution de 12 bits
  double temperatureCelcius = (double)valeurDuCapteur * (3.3 / 40.96);

  if (print && tempo(3000)) {
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