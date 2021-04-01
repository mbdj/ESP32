#include <Arduino.h>
#include <unity.h>

void setUp(void)
{
    const uint8_t PIN_LED{5};
    const uint8_t PIN_BOUTON{4};
}

// void tearDown(void) {
// // clean stuff up here
// }

void test_initializeButtonInternalPulldown(void)
{
    UnbouncedButton bouton{PIN_BOUTON, UnbouncedButton::InputMode::INPUT_INTERNAL_PULLDOWN, 5, UnbouncedButton::Edge::RELEASED};
    TEST_ASSERT_EQUAL(digitalRead(PIN_BOUTON), LOW);
}

void test_led_state_high(void)
{
    digitalWrite(LED_BUILTIN, HIGH);
    TEST_ASSERT_EQUAL(HIGH, digitalRead(LED_BUILTIN));
}

void test_led_state_low(void)
{
    digitalWrite(LED_BUILTIN, LOW);
    TEST_ASSERT_EQUAL(LOW, digitalRead(LED_BUILTIN));
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    RUN_TEST(test_led_builtin_pin_number);

    pinMode(LED_BUILTIN, OUTPUT);
}

uint8_t i = 0;
uint8_t max_blinks = 5;

void loop()
{
    if (i < max_blinks)
    {
        RUN_TEST(test_led_state_high);
        delay(500);
        RUN_TEST(test_led_state_low);
        delay(500);
        i++;
    }
    else if (i == max_blinks)
    {
        UNITY_END(); // stop unit testing
    }
}