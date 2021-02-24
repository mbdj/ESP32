#include <UnbouncedButton.h>

UnbouncedButton::UnbouncedButton(uint8_t pin, uint8_t mode, unsigned long debounceDelay)
{
    switch (mode)
    {
    case INPUT || INPUT_PULLDOWN:
        buttonPreviousState = LOW;
        break;
    case INPUT_PULLUP:
        buttonPreviousState = HIGH;
        break;
    default:
        buttonPreviousState = LOW;
        break;
    };

    this->pin = pin;
    this->mode = mode;
    this->debounceDelay = debounceDelay;
    previousTimeButtonRead = 0L;
    pinMode(pin, mode);
};

UnbouncedButton::ButtonState UnbouncedButton::buttonState(void)
{
    unsigned long now = millis();
    int buttonPinRead = digitalRead(pin);
    ButtonState buttonState = ButtonState::UNCHANGED;

    // On ne lit la nouvelle valeur que si le délai de rebond est passé
    if (now - previousTimeButtonRead > debounceDelay)   // voir https://www.youtube.com/watch?v=aPmJdeJrk5M&list=PLuQznwVAhY2V7Uh0aHOgBvaiqRw9VeCis&index=10
    {

        if ((mode == INPUT_PULLDOWN && buttonPinRead == HIGH && buttonPreviousState == LOW)
         || (mode == INPUT_PULLUP && buttonPinRead == LOW && buttonPreviousState == HIGH))
        {
            buttonState = ButtonState::PRESSED;
        };

        // on met à jour l'état courant pour la prochaine lecture du bouton
        buttonPreviousState = buttonPinRead;
        previousTimeButtonRead = now;
    };

    return buttonState;
};

bool UnbouncedButton::buttonPressed(void)   { return buttonState() == ButtonState::PRESSED; };
bool UnbouncedButton::buttonUnchanged(void) { return buttonState() == ButtonState::UNCHANGED; };