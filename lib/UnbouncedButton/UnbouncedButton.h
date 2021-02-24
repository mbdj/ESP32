/*
La classe UnboucedButton permet de créer des boutons qui peuvent être lus
en évitant les problèmes de rebond

Mehdi Ben Djedidia
24/02/2021
*/
#include <arduino.h>

class UnbouncedButton
{
public:
    enum class ButtonState
    {
        PRESSED,
        UNCHANGED
    };

    enum class Edge
    {
        PRESSED,
        RELEASED
    };

    UnbouncedButton(uint8_t pin, uint8_t mode = INPUT, unsigned long debounceDelay = 5, Edge edge = Edge::PRESSED);
    ButtonState buttonState(void);
    bool buttonPressed(void);   // Le bouton a été pressé
    bool buttonUnchanged(void); // Le bouton n'a pas été pressé

private:
    uint8_t pin;  // pin du bouton
    uint8_t mode; // INPUT ou PULLUP ou PULLDOWN
    unsigned long debounceDelay;    // délai mini du rebond après lequel on reteste l'état du bouton
    Edge edge; // quel changement de front est détecté ?
};