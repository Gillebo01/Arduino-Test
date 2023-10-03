#include <Adafruit_NeoPixel.h>

#define LED_PIN 3           // Pin for LED-stripe
#define NUM_LEDS 32          // Antall LED-er i stripen
#define BUTTON_PIN 12        // Pin for modusknapp
#define POTENTIOMETER_PIN A1 // Analog pin for potensiometer
#define POWER_BUTTON_PIN 13 // Pin for strømknapp
#define SPEED_BUTTON 1 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int buttonState = 0;       // Gjeldende tilstand av modusknapp
int lastButtonState = 0;   // Forrige tilstand av modusknapp
int powerButtonState = 0;  // Gjeldende tilstand av strømknapp
int lastPowerButtonState = 0; // Forrige tilstand av strømknapp
int mode = 0;              // Gjeldende modus
int brightness = 128;      // Gjeldende lysstyrke (0-255)
int potValue = 0;          // Verdi fra potensiometer
bool powerOn = true;    // Strømstatus
int currentLED = 0;        // Gjeldende LED i mønsteret

void setup() {
  strip.begin();
  strip.show(); // sett alle pixel til 'off', siden man slår av lyset når... 
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POWER_BUTTON_PIN, INPUT_PULLUP); // Strømknapp som input med pull-up motstand (trur jeg)
}

void loop() {
 
  activatePot();
  activateButtons();

 
  // Oppdater LED-stripen basert på strømstatus og gjeldende modus
  if (powerOn) {
    switch (mode) {
      case 0: // Modus 0: Rød
        setColor(255, 0, 0);
        break;
      case 1: // Modus 1: Grønn
        setColor(0, 255, 0);
        break;
      case 2: // Modus 2: Blå
        setColor(0, 0, 255);
        break;
      case 3: // Skulle være nytt mønster, men ble regulering av fart istedet
      	setColor(255, 0, 0);
      	delay(100);
      	setColor(0, 255, 0);
      	delay(100);
        setColor(0, 0, 255);
        break;
      case 4: // et faktiksst nytt mønster, går gradvis gjennom regnbuefargene
      	rainbowCycle();
      	break;
  
    }
    // Blink en etter en i mønsteret 
    blinkPattern();
  } else {
    setColor(0, 0, 0); // Slå av LED-stripen når strømmen er av
  }
	
  	valueReset();
  
}



void activatePot(){
 // Les potensiometerets verdi
  potValue = analogRead(POTENTIOMETER_PIN);
  brightness = map(potValue, 0, 1023, 0, 255); // Kartlegg verdien til lysstyrken
}

void activateButtons(){
   // Les tilstanden til modusknappen
  buttonState = digitalRead(BUTTON_PIN);

  // Sjekk om modusknappen er trykket
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      mode++; // Øk modusen når knappen trykkes
      if (mode > 4) {
        mode = 0; // Tilbake til første modus etter den siste
      }
    }
    delay(50); // delay siden millis blokker av en eller annen grunn
  }

  // Les tilstanden til strømknappen
  powerButtonState = digitalRead(POWER_BUTTON_PIN);

  // Sjekk om strømknappen er trykket
  if (powerButtonState != lastPowerButtonState) {
    if (powerButtonState == LOW) {
      powerOn = !powerOn; // Bytt strømstatus når knappen trykkes
      if (!powerOn) {
        // Slå av LED-stripen når strømmen er av
        setColor(0, 0, 0);
        strip.show();
      }
    }
    delay(50); 
  }
}

void valueReset(){
  lastButtonState = buttonState; // Lagre forrige tilstand for modusknappen
  lastPowerButtonState = powerButtonState; // Lagre forrige tilstand for strømknappen
  strip.setBrightness(brightness); // Oppdater lysstyrken til LED-stripen
  strip.show(); // Oppdater LED-stripen
}

// Funksjon for å angi RGB-farge på LED-stripen
void setColor(int red, int green, int blue) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, red, green, blue);
  }
}

// Funksjon for å blinke LED-ene en etter en i mønsteret
void blinkPattern() {
  strip.setPixelColor(currentLED, 0, 0, 0); // Slå av forrige LED
  currentLED++; // Gå til neste LED i mønsteret
  if (currentLED >= NUM_LEDS) {
    currentLED = 0; // Start mønsteret på nytt når siste LED er nådd
  }
  strip.setPixelColor(currentLED, 0, 0, 0); // Slå på gjeldende LED
  delay(100); // Vent litt mellom hver LED
}

/*Eneste funksjonen med millis, denne blokerte av/på 
knappen uten millis, mens hadde problemer med lys 
mønsterne når jeg brukte millis på de andre funksjonene 
*/
void rainbowCycle() { 
  static int currentColor = 0;
  static unsigned long previousMillis = 0;
  int wait = 50; // Juster denne verdien for å endre blinkenes hastighet

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= wait) {
    previousMillis = currentMillis;

    strip.setPixelColor(currentLED, Wheel(currentColor));
    strip.show();

    currentColor++;
    if (currentColor >= 256) {
      currentColor = 0;
      setColor(0, 0, 0); // Slå av alle LED-er mellom fargene
    }
  }
}



// sett inn verdi 0 til 255 for farge verdi.
// fargene er overganger fra r - g - b - tilbake til r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
} 

/* med knapp for lysstyrke så var det vanskelig å se noe noe
betydelig forskjell med verdiene jeg brukte. 
For long/short press, gikk jeg tom for tid til å implimentere, 
men trur det skal være fult mulig med hvordan jeg har sotte 
opp knappene mine til nå*/

