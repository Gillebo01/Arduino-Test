
#define BUTTON_PIN 12        // Pin for modusknapp
#define POTENTIOMETER_PIN A1 // Analog pin for potensiometer
#define POWER_BUTTON_PIN 13  // Pin for strømknapp



void setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POWER_BUTTON_PIN, INPUT_PULLUP); // Strømknapp som input med pull-up motstand (trur jeg)
  Serial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(BUTTON_PIN));
}

