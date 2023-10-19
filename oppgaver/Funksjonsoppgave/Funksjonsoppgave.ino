
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
    }  // definerer thisReading som en tellende verdi fra 0 til antall valgte lesninger 
}

/* fått det meste til å fungere som jeg vil, men sensoravlesningen git meg over 400 når 
A0 ikke er koblet til noe og 0 med en gang jeg kobler til lys sensoren, usikker på om jeg har 
feiltolket kode eksempelet fra
https://docs.arduino.cc/built-in-examples/analog/Smoothing?queryID=eafb5025a056eef0e436af1024526730
siden det er det jeg har brukt som utgangspunkt. 
Men fungrer som den skal hvis men ser bort ifra det, så kan være en koblingsfeil også. 
Siste jeg ville gjøre er å bruke map() for å ha litt mer kontroll over lesningsverdiene, 
vil kanskje også kunne fikse det tidlgiere problemet med dette, men er usikker på hvordan jeg 
skal få det til å praksis.
*/

int sensorAvg(){  


    unsigned long currentMillis = millis(); 

    if(currentMillis - lastMillis > 100 ){ 

        total = total - readings[readIndex]; // fjerner forle lesning fra totalen

        readings[readIndex] = analogRead(sensorPin); // legger inn ny lesningsverdi 

        total = total + readings[readIndex]; // tar total + ny lesning for å få ny total  

        readIndex = readIndex+1; // ligger til en på index for å gå til neste lesning 

        if (readIndex >= antallRead){ // 0stiller index når du har kommer til maks antallet ditt for lesninger

            readIndex = 0;
        }

        average = total / antallRead; // regner ut gjennomsnittet 

        
        lastMillis = millis(); //resetter millis
    }
    
    return average;
    
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






    }


   /* 
   Trudde ikke vi skulle ta vare på versjonen uten arrays/millis, så usikker på om jeg har mistet
   biter av koden, men her er den i grove trekk. 
   
   delay ver
    int sensorValue = 0;

    for (int i = 0; i < antallRead; i++){
        sensorValue += analogRead(sensorPin);
    }

    return sensorValue/antallRead ;

    les på modulo for circle array eller moving average array*/


   /*     "delay ver"
   
   if(sensorAvg(5) > 100){

        fastBlink(6);
    }

    else{

        blink();

    } */

   

/*  Mener på det vår noe slikt jeg løste fast blink og blink var samme bare uten for løkken
    void fastBlink(n){

    for(int i = 0 , i <=n , i++){
        ledState = HIGH ;
        delay(200)
        ledstate = LOW
        delay(200)
    }
    delay(1000)
*/ 



/* alt ver. for blink med millis, men blinkingen var ikke kunne ikke tilpasses sånn jeg så for meg
som er grunnen til at den ikke er brukt, og står her bare for refferanse for min egen del

void blink(){  
    
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