#define buttonPin 2
#define redPin 13
#define greenPin 11
#define yellowPin 12

int ledState = LOW;

unsigned long prevMillis = 0;

const long intervall = 500;

int buttonState = 0;
int lastButtonState = 0;
int mode = 0;


void setup(){

    pinMode(buttonPin, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(greenPin, OUTPUT);

    Serial.begin(9600);


}


void yellowBlink(){

    unsigned long curMillis = millis();

    if (curMillis - prevMillis > intervall){

        prevMillis = curMillis;
    
    if(ledState == LOW){
        ledState = HIGH;
    }else{
        ledState = LOW;
    }

    digitalWrite(yellowPin, ledState);

    }

}

void activateButton(){
   // Les tilstanden til modusknappen
  buttonState = digitalRead(buttonPin);

  // Sjekk om modusknappen er trykket
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      mode++; // Øk modusen når knappen trykkes
      Serial.println(mode);
      if (mode > 1) {
        mode = 0; // Tilbake til første modus etter den siste
      }
    }
   delay(50); // delay siden millis blokker av en eller annen grunn
  }
lastButtonState = buttonState;
}



void loop (){

    activateButton();
    yellowBlink();

    
    /*if (!mode){
       digitalWrite(redPin, HIGH);
       digitalWrite(greenPin, LOW); 
    }
    else if (mode == 1)
    {
        digitalWrite(redPin,LOW);
        digitalWrite(greenPin, HIGH);
    } */
    

   switch (mode)
   {
   case 0:
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    break;
   
   case 1:
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin, HIGH);
    break;
   } 


  

    
}