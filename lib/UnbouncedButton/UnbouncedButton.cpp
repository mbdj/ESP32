#include <UnbouncedButton.h>

UnbouncedButton::UnbouncedButton(uint8_t pin, InputMode mode, unsigned long debounceDelay, Edge edge)
    : pin{pin}, mode{mode}, debounceDelay{debounceDelay}, edge{edge}
{
    // détermination du mode pour pinmode()
    switch (mode)
    {
    case InputMode::INPUT_EXTERNAL_PULLUP:
    case InputMode::INPUT_EXTERNAL_PULLDOWN:
        pinMode(pin, INPUT);
        break;
    case InputMode::INPUT_INTERNAL_PULLUP:
        pinMode(pin, INPUT_PULLUP);
        break;
    case InputMode::INPUT_INTERNAL_PULLDOWN:
        pinMode(pin, INPUT_PULLDOWN);
        break;
    default:
        break;
    }
};

UnbouncedButton::ButtonState UnbouncedButton::buttonState(void)
{
    // dernière fois que le bouton a changé d'état ; initialisé à 0
    static uint32_t lastMillis{0};

    // état initial du bouton, selon le niveau HIGH ou LOW de la résistance de tirage (qu'elle sot interne ou externe)
    static int buttonPreviousState = (mode == InputMode::INPUT_INTERNAL_PULLUP || mode == InputMode::INPUT_EXTERNAL_PULLUP ? HIGH : LOW);

    // Avant de déterminer le nouvel état, l'état est présumé inchangé
    ButtonState buttonState = ButtonState::UNCHANGED;

    uint32_t _millis = millis(); // instant de lecture du nouvel état électrique du bouton

    if ((_millis - lastMillis) > debounceDelay) // on ne prend en compte le nouvel état du bouton qu'après le délai anti-rebond
    {
        int buttonPinRead = digitalRead(pin); // lecture du nouvel état électrique du bouton

        switch (mode)
        {
        // Si résistance de PULLUP (HIGH) alors le bouton est pressé quand il passe de HIGH à LOW et relaché quand il passe de LOW à HIGH
        case InputMode::INPUT_INTERNAL_PULLUP:
        case InputMode::INPUT_EXTERNAL_PULLUP:
            switch (edge)
            {
            case Edge::PRESSED:
                if (buttonPinRead == LOW && buttonPreviousState == HIGH)
                    buttonState = ButtonState::PRESSED;
                break;
            case Edge::RELEASED:
                if (buttonPinRead == HIGH && buttonPreviousState == LOW)
                    buttonState = ButtonState::PRESSED;
                break;
            default:
                break;
            }
            break;

        // Si résistance de PULLDOWN (LOW) alors le bouton est pressé quand il passe de LOW à HIGJ et relaché quand il passe de HIGH à LOW
        case InputMode::INPUT_INTERNAL_PULLDOWN:
        case InputMode::INPUT_EXTERNAL_PULLDOWN:
            switch (edge)
            {
            case Edge::PRESSED:
                if ((buttonPinRead == HIGH && buttonPreviousState == LOW))
                    buttonState = ButtonState::PRESSED;
                break;
            case Edge::RELEASED:
                if (buttonPinRead == LOW && buttonPreviousState == HIGH)
                    buttonState = ButtonState::PRESSED;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }

        // on enregistre le dernier instant de lecture du bouton et son dernier état
        buttonPreviousState = buttonPinRead;
        lastMillis = _millis;
    }

    return buttonState;
};

bool UnbouncedButton::buttonPressed(void) { return buttonState() == ButtonState::PRESSED; };
bool UnbouncedButton::buttonUnchanged(void) { return buttonState() == ButtonState::UNCHANGED; };