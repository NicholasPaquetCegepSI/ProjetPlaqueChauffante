#define LED_ROUGE 0
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
  pinMode(LED_ROUGE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);

  // Déclaration capteur de température LM35
  pinMode(LM35, INPUT);
  analogReadResolution(12);

  // Déclaraction du relai
  pinMode(RELAI, OUTPUT);

  // Déclaration du bouton poussoir
  pinMode(BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), interrupt, RISING);
}

bool circuitActif = false;

void interrupt() {
  delay(200);
  circuitActif = !circuitActif;
  Serial.println("Le circuit est maintenant actif!");
}

void loop() {

  // if (digitalRead(BTN) == HIGH){
  //   circuitActif = !circuitActif;
  //   Serial.println("Le bouton a ete appuye!");
  // }

  testLeds();

  // if (circuitActif)
  //   test();
}

bool temperatureAtteinte = true;
double limiteTemperature = 50;
double ecartTemperature = 5;

void test() {
  if(circuitActif){
    testLeds();
  }
  else {

  }


  // if (circuitActif) {
  //   // Test leds
  //   digitalWrite(LED_ROUGE, HIGH);
  //   digitalWrite(LED_JAUNE, HIGH);
  //   digitalWrite(LED_VERTE, HIGH);

  //   // getTemperature(true);

  //   double temp = getTemperature(true);

  //   // if (tempo(5000)) {
  //   // if (temp <= limiteTemperature && !temperatureAtteinte) {
  //   //   // Serial.println("changement d'etat du relai");
  //   //   relaiActif = true;
  //   // } else {
  //   //   temperatureAtteinte = true;
  //   //   relaiActif = false;

  //   //   if (temp <= limiteTemperature - ecartTemperature)
  //   //     temperatureAtteinte = false;
  //   // }

  //   // Test du relai
  //   if (relaiActif) {
  //     digitalWrite(RELAI, HIGH);
  //     // Serial.println("Relai ON");
  //   } else {

  //     digitalWrite(RELAI, LOW);
  //     // Serial.println("Relai OFF");
  //   }
  // } else
  //   digitalWrite(LED_ROUGE, LOW);
}

void testLeds() {
  digitalWrite(LED_ROUGE, circuitActif);
  digitalWrite(LED_JAUNE, circuitActif);
  digitalWrite(LED_VERTE, circuitActif);
}

double getTemperature(bool print) {
  // Lecture de la valeur analogique du capteur
  int valeurDuCapteur = analogRead(LM35);
  // Calcul de conversion pour une résolution de 12 bits
  double temperatureCelcius = (double)valeurDuCapteur * (3.3 / 40.96);

  if (print) {
    Serial.print("Température: ");
    Serial.println(temperatureCelcius);
  }

  return temperatureCelcius;
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