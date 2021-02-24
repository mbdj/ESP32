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

    UnbouncedButton(uint8_t pin, uint8_t mode = INPUT_PULLDOWN, unsigned long debounceDelay = 5);
    ButtonState buttonState(void);
    bool buttonPressed(void);   // Le bouton a été pressé
    bool buttonUnchanged(void); // Le bouton n'a pas été pressé

private:
    unsigned long previousTimeButtonRead;
    int buttonPreviousState;
    uint8_t pin;
    uint8_t mode;
    unsigned long debounceDelay;
};