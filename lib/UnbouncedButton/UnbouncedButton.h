/************************************************************************
La classe UnboucedButton permet de créer des boutons qui peuvent être lus
en évitant les problèmes de rebond

Mehdi Ben Djedidia
24/02/2021
************************************************************************/

#include <arduino.h>

class UnbouncedButton
{
public:
    enum class ButtonState
    {
        PRESSED,  // le bouton a été pressé
        UNCHANGED // pas d'appui sur le bouton
    };

    // spécifie si ButtonState == PRESSED est détecté à l'appui ou au relachement du bouton
    enum class Edge
    {
        PRESSED, // détection à l'appui du bouton
        RELEASED // détection au relachement du bouton
    };

    enum class InputMode
    {
        INPUT_INTERNAL_PULLUP,   // mode INPUT_PULLUP (résistance de tirage interne HIGH)
        INPUT_INTERNAL_PULLDOWN, // mode INPUT_PULLDOWN (résistance de tirage interne LOW)
        INPUT_EXTERNAL_PULLUP,   // mode INPUT avec résistance de tirage externe HIGH
        INPUT_EXTERNAL_PULLDOWN  // mode INPUT avec résistance de tirage externe LOW
    };

    UnbouncedButton(uint8_t pin, InputMode mode = InputMode::INPUT_INTERNAL_PULLUP, unsigned long debounceDelay = 5, Edge edge = Edge::PRESSED);
    /*
    * pin : pin du bouton
    * mode : choix du type de résistance de tirage, interne ou externe
    * debouncedDelay : délai maxi de rebond
    * edge : détection sur appui (PRESSED) ou relachement du bouton (RELEASED)
    */
    ButtonState buttonState(void); // renvoie l'état du bouton
    bool buttonPressed(void);      // Le bouton a été pressé
    bool buttonUnchanged(void);    // Le bouton n'a pas été pressé

private:
    uint8_t pin;                 // pin du bouton
    InputMode mode;              // INPUT ou PULLUP ou PULLDOWN
    unsigned long debounceDelay; // délai mini du rebond après lequel on reteste l'état du bouton
    Edge edge;                   // indique quel changement de front est détecté : à l'appui (PRESSED) ou au relachement du bouton (RELEASED)
};