#define LED_BLEUE A0
#define LED_JAUNE A1
#define LED_VERTE A2

void setup() {
  // Déclaration des LEDs
  pinMode(LED_BLEUE, OUTPUT);
  pinMode(LED_JAUNE, OUTPUT);
  pinMode(LED_VERTE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BLEUE, HIGH);
  digitalWrite(LED_JAUNE, HIGH);
  digitalWrite(LED_VERTE, HIGH);
}
