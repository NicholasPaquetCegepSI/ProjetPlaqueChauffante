#include <AM2302-Sensor.h>
#include <DHT.h>

#define LED_ROUGE 0
#define LED_JAUNE 1
#define LED_VERTE 2

#define LM35 A0

#define RELAI 3

#define BTN 4

#define DHT22 6
AM2302::AM2302_Sensor am2302{ DHT22 };

#define DHTTYPE DHT22     // Type du capteur (AM2302)
DHT dht(DHT22, DHTTYPE);  // Objet pour l'utilisation du capteur DHT22

unsigned long millisPrecedent = 0;  // Variable globale pour garder le compte sur le temps.
bool relaiActif = false;

void setup() {
  Serial.begin(9600);

  // am2302.begin();
  dht.begin();



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

  pinMode(DHT22, INPUT);
  // dht.begin();  // Demarrage de lecture du capteur DHT22


  delay(1000);
  Serial.println("Demarrage du Arduino");
}

bool circuitActif = false;

void interrupt() {
  delay(500);
  circuitActif = !circuitActif;

  if (circuitActif)
    Serial.println("ON: Le circuit est maintenant actif!");
  else
    Serial.println("OFF: Le circuit est maintenant inactif!");

  digitalWrite(LED_VERTE, circuitActif);
}

void loop() {


  // if (digitalRead(BTN) == HIGH){
  //   circuitActif = !circuitActif;
  //   Serial.println("Le bouton a ete appuye!");
  // }

  // testLeds();
  test();

  // if (circuitActif)
  //   test();
}

bool temperatureAtteinte = true;
double limiteTemperature = 35;
double ecartTemperature = 5;

void test() {
  if (circuitActif) {
    // testLeds();
    testPlaque();
  } else {
    testLeds();
    digitalWrite(RELAI, LOW);
  }
}

double temp = 0;

void controlerPlaque() {
  // Lecture de la temperature aux 2 secondes
  if (tempo(2000))
    temp = getTemperature(true);

  // Si la température est inférieure à celle voulue et que la 
  // température désirée n'a pas été atteinte, le relai sera activé.  
  if (temp <= limiteTemperature && !temperatureAtteinte) {    
    relaiActif = true;
  } 
  // Si la température dépasse la limite, le relai sera désactivé
  // et la température désirée sera donc atteinte  
  else {    
    temperatureAtteinte = true;
    relaiActif = false;

    // Si la température baisse sous le seuil de l'intervalle de température
    // La température désirée ne sera plus atteinte
    if (temp <= limiteTemperature - ecartTemperature)
      temperatureAtteinte = false;
  }

  // L'état du relai et de la LED rouge dépende du booléen contrôlant le relai
  digitalWrite(LED_ROUGE, relaiActif);
  digitalWrite(RELAI, relaiActif);
}

void testPlaque() {

  if (tempo(2000))
    temp = getTemperature(true);

  if (temp <= limiteTemperature && !temperatureAtteinte) {
    // if (tempo(2000))
    //   Serial.println("La plaque chauffe");
    // Serial.println("changement d'etat du relai");
    relaiActif = true;
    digitalWrite(LED_ROUGE, HIGH);
  } else {
    // if (tempo(2000))
    //   Serial.println("La plaque ne chauffe pas");

    digitalWrite(LED_ROUGE, LOW);
    temperatureAtteinte = true;
    relaiActif = false;

    if (temp <= limiteTemperature - ecartTemperature)
      temperatureAtteinte = false;
  }

  digitalWrite(RELAI, relaiActif);
}

void testLeds() {
  digitalWrite(LED_ROUGE, circuitActif);
  digitalWrite(LED_JAUNE, circuitActif);
  digitalWrite(LED_VERTE, circuitActif);
}

// Lit les données du capteur et les retourne dans un string.
float getTemperatureDHT22(bool print) {
  // auto status = am2302.read();

  // Capture de la temperature
  float temperatureCelcius = dht.readTemperature();
  if (print) {
    // Serial.print("\n\nstatus of sensor read(): ");
    // Serial.println(status);

    Serial.print("Température:");
    Serial.println(temperatureCelcius);
  }

  return temperatureCelcius;
}

double getTemperature(bool print) {
  // Lecture de la valeur analogique du capteur
  int valeurDuCapteur = analogRead(LM35);
  // Calcul de conversion pour une résolution de 12 bits
  double temperatureCelcius = (double)valeurDuCapteur * (3.3 / 40.96);

  if (print) {
    Serial.print("Température:");
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