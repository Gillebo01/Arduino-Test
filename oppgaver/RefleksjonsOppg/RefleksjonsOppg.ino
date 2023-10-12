
#define redLedPin 13 
#define greenLedPin 12
#define blueLedPin 11
#define sensPin A1
#define buttonPin 2

int ledState = LOW ;

int sensValue = 0; 

unsigned long preMillis = 0;

const long interval = 1000 ;

int buttonState = 0;
int prevButtonState = 0;

int mode = 0;


void setup() {
    pinMode(ledPin, OUTPUT);

}


void activateSense(){
    sensValue = analogRead(potPin)
    brightness = map(potValue, 0, 1023, 0, 255)
}

void blinkMillis(){
    unsigned long curMillis = millis();
    
    if(curMillis - preMillis >= interval){
        
        preMillis = curMillis ;

        if(ledState==LOW){
            ledState = HIGH;
        }
        else
        {
            ledState = LOW;
        }

        digitalWrite(ledPin, ledState);

    }
}

void activateButton(){

}

void loop(){

    activateSense();

    switch (mode)
    {
    case 0
    
        blinkMillis();
         
        break;
    
    default:
        break;
    }




    

    

}
