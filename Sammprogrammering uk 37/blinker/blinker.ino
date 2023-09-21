const int LED_PIN = 13;

void blinkerLed()
{digitalWrite(LED_PIN, HIGH);
delay(2000);
digitalWrite(LED_PIN, LOW);
delay(2000);
}

void setup()
{
    Serial.begin(9600);

}

void loop()
{
    blinkerLed();
}