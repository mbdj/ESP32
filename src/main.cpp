#include <Arduino.h>

const uint8_t PIN_LED{5};
const uint8_t PIN_BOUTON{4};

const unsigned long debounceDelay{5};
static unsigned long lastTimeEtatBouton{0L};
static uint8_t etatPrecedentBouton{HIGH};
static uint8_t etatBouton{HIGH};
static unsigned long now;

static int nbreClic{0};

void setup()
{
  Serial.begin(9600L);
  Serial.println("\n-- Test ESP 32 --");

  // configuration des pin de l'ESP32
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOUTON, INPUT_PULLUP);

  digitalWrite(PIN_LED, LOW);
}

void loop()
{
  // lecture de l'état du bouton poussoir si le délai de debounce est passé depuis la dernière lecture
  now = millis();
  if (now > lastTimeEtatBouton + debounceDelay)
  {
    etatBouton = digitalRead(PIN_BOUTON);

    if (etatBouton == LOW && etatPrecedentBouton == HIGH)
    {
      // on change l'état de la LED à l'appui du bouton
      digitalWrite(PIN_LED, !digitalRead(PIN_LED));

      Serial.print("Clic ");
      Serial.println(nbreClic);
      nbreClic++;
    };

    // on met à jour l'état courant pour la prochaine lecture du bouton
    etatPrecedentBouton = etatBouton;
    lastTimeEtatBouton = now;
  }
};
