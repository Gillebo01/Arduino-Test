#define buttonPin 2
#define redPin 13
#define greenPin 11
#define yellowPin 12

int ledState = LOW;

unsigned long prevMillis = 0;
unsigned long prevMillis2 = 0;


const long intervall = 500;

int buttonState = 0;
int lastButtonState = 0;
int mode = 0;
bool power = false;


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

  unsigned long buttonMillis = millis();

  // Sjekk om modusknappen er trykket
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      mode++; // Øk modusen når knappen trykkes
      Serial.println(mode);
      if (mode > 1) {
        mode = 0; // Tilbake til første modus etter den siste
      }
    }
   /*
   Dette err hvordan jeg ville sotte opp long/short press, med vanelig trykknapp på short
   og en timer på longknappen, her lik 3 sekunder. Fikk ikke tid til å sjekke om dene biten fungerer
   i praksis med resten av koden, men hvet at koden fungerte uten. litt for at jeg også er usikekr på
   om du kan bruke "&&" på denne måten 

   else if (buttonState != lastButtonState && buttonMillis - prevMillis2 > 3000 )
    {
        power != power;
    }
    */
    
   delay(50); 
  }
lastButtonState = buttonState;
}



void loop (){

    activateButton(); // aktiverer for knappetrykk 
    yellowBlink(); //setter gult til å blinke konstant

    
    /* Alternativ versjon av switch delen
    
    if (!mode){  
       digitalWrite(redPin, HIGH);
       digitalWrite(greenPin, LOW); 
    }
    else if (mode == 1)
    {
        digitalWrite(redPin,LOW);
        digitalWrite(greenPin, HIGH);
    } */
    
   /* hvis powerON delen jeg har i knappe funskjonen fungerer som jeg har planlagt,
   tenkte jeg å sette inn en if(powerON) for hele switch funksjonen, for å da ha langpress for å 
   slå av og på de "vekslende" lysene*/ 
   switch (mode)
   {
   case 0: // Setter på rødt lys og skrur av 
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    break;
   
   case 1: // skrur av rødt lys og på grønt
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin, HIGH);
    break;
   } 


  

    
}