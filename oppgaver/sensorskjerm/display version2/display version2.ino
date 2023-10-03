
#include <Arduino.h>
#include <SPI.h>
#include <U8g2lib.h>

#define buttonPin 2
#define photoPin A2
#define tempPin A0

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0 , /* clock=*/ 10, /* data=*/ 9, /* cs=*/ 12, /* dc=*/ 11, /* reset=*/ 13);

int buttonState = 0;
int lastButtonState = 0;
int photoValue = 0;
int photoMap = 0; 
int tempValue = 0;
int tempMap = 0;
int mode =  0;
bool powerOn = true;


void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
}

void activatePhoto(){
 // Les potensiometerets verdi
  photoValue = analogRead(photoPin);
   photoMap= map(photoValue, 0, 1023, 0, 255); // Kartlegg verdien til lysstyrken

}

void activateTemp(){
 // Les potensiometerets verdi
  tempValue = analogRead(tempPin);
   tempMap= map(tempValue, 0, 1023, 0, 100); // Kartlegg verdien til lysstyrken

}


void activateButtons(){
   // Les tilstanden til modusknappen
  buttonState = digitalRead(buttonPin);

  // Sjekk om modusknappen er trykket
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      mode++; // Øk modusen når knappen trykkes
      if (mode > 2) {
        mode = 0; // Tilbake til første modus etter den siste
      }
    }
    delay(50); // delay siden millis blokker av en eller annen grunn
  }

}

void valueReset(){
  lastButtonState = buttonState;
}

void tempSensor_Display(){
    u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(20,15,"Temp Sensor");
    u8g2.setFont(u8g2_font_ncenB10_tr);
    String tempValueString = String(tempMap);
    u8g2.drawStr(50,50, tempValueString.c_str());
  } while ( u8g2.nextPage() ); 



  delay(100);
}

void photoSensor_Display(){
    u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(20,15,"Photo sensor");
    u8g2.setFont(u8g2_font_ncenB10_tr);
    String photoValueString = String(photoValue);
    u8g2.drawStr(50,50, photoValueString.c_str());
  } while ( u8g2.nextPage() ); 


  delay(100);
}

void loop(void) {

    activatePhoto();
    activateTemp();
  activateButtons();
    

    if (powerOn) {
    switch (mode) {
      case 0:
       photoSensor_Display();
       break;

      case 1:
        tempSensor_Display();
        break;

    }

    valueReset();
    }

}