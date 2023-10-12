
#define ledPin 13
#define sensorPin A0

//////////////////////////////////////////////////////////////////////////////////////////////////////
int ledState = LOW;
unsigned long lastMillis = 0;
unsigned long lastMillis2 = 0;
unsigned long lastMillis3 = 0;
int pause = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////
const int antallRead = 5;
int readings[antallRead];
int readIndex = 0;
int total = 0;
int average = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////

void setup(){
    pinMode(ledPin, OUTPUT);

    Serial.begin(9600);

    for (int thisReading = 0; thisReading < antallRead; thisReading++){
        readings[thisReading]=0;
    } 
}

int sensorAvg(){

    unsigned long currentMillis = millis(); 

    if(currentMillis - lastMillis > 100 ){

        total = total - readings[readIndex];

        readings[readIndex] = analogRead(sensorPin);

        total = total + readings[readIndex];

        readIndex = readIndex+1;

        if (readIndex >= antallRead){

            readIndex = 0;
        }

        average = total / antallRead;

        
        lastMillis = millis();
    }
    
    return average;
    
   /* delay ver
    int sensorValue = 0;

    for (int i = 0; i < antallRead; i++){
        sensorValue += analogRead(sensorPin);
    }

    return sensorValue/antallRead ;

    modulo for circle array eller moving average array*/
}

void fastBlink(){

    unsigned long currentMillis2 = millis();

    if (currentMillis2 - lastMillis2 > 1000){

        //Det som vil skje er at togglig ALLTID vil skje utenom når du har "pause"
        //Du bestemmer når pause begynner og hvor lenge den skal vare
        //slik jeg har skrive nå varer pause 1 periode

        if(pause == 0) { // starter med en pause 
            pause += 1;
        }
        else if ( pause < 6) { // blink 6 ganger
            if (ledState == LOW) {
                ledState = HIGH;
                } 
            else {
                ledState = LOW;
                pause += 1;
            } 
        }
        else {
            pause = 0; //resetter pause verdier 
            lastMillis2 = currentMillis2;
        }
    }

    digitalWrite(ledPin,ledState);
}

/*void blink(){
    
   unsigned long currentMillis3 = millis();
    if (currentMillis3 - lastMillis3 > 500){
        if (ledState == LOW){
            ledState = HIGH;
            
        }
        
        else if (currentMillis3 - lastMillis3 > 1500){
            ledState = LOW;
            lastMillis3 = currentMillis3 ;
        }
    }
    
}*/
void blink(){
    
    unsigned long currentMillis3 = millis();
    if (currentMillis3 - lastMillis3 < 1500){
        ledState = HIGH;
            
        
        
    } 
    else if (currentMillis3 - lastMillis3 < 2000){
        ledState = LOW;
    }
    else{
        lastMillis3 = currentMillis3 ;
    }

    digitalWrite(ledPin, ledState);
    
}



void loop(){

    Serial.print("Average Sensor Value: ");
    Serial.println(average);


     if (sensorAvg() > 100) {

        fastBlink();
    }
    else{
        blink();
    }






   /*     "delay ver"
   
   if(sensorAvg(5) > 100){

        fastBlink(6);
    }

    else{

        blink();

    } */
    }




