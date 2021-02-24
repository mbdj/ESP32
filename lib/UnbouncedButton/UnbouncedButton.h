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
    enum class ButtonState {UP, DOWN};

    UnbouncedButton(uint8_t pin, uint8_t mode = INPUT_PULLDOWN, unsigned long debounceDelay = 5);
    ButtonState buttonRead();
    bool buttonIsUp();
    bool buttonIsDown();

private:
    ButtonState buttonPreviousState;
    ButtonState buttonState;
}