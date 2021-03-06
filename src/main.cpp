#include <Arduino.h>
#include <UnbouncedButton.h>

const uint8_t PIN_LED{5};
const uint8_t PIN_BOUTON{4};

UnbouncedButton bouton{PIN_BOUTON, UnbouncedButton::InputMode::INPUT_INTERNAL_PULLDOWN, 5, UnbouncedButton::Edge::RELEASED};

void setup()
{
  Serial.begin(9600L);
  Serial.println("\n-- Test ESP 32 demarre --");

  // On configure et on éteind la LED au démarrage
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}

void loop()
{
  if (bouton.buttonPressed())
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
};
