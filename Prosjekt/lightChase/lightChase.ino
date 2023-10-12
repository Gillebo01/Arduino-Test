#include <Servo.h>

#define servoPin 9
#define servoPin2 10
//#define potPin 10
#define inputPin A0
#define inputPin2 A1
#define inputPin3 A2
#define inputPin4 A3

//int potValue = 0;


int average1 = 0;
int averageMap1= 0;

int pin1Value = 0;
int pin2Value = 0;
int pin3Value = 0;
int pin4Value = 0;
int average2 = 0;
int averageMap2 = 0;


Servo servo;
Servo servo2;

void setup(){

    Serial.begin(9600);
    
    servo.attach(servoPin);

    //pinMode(potPin, INPUT);

}

void loop(){

    
        pin1Value = analogRead(inputPin);
        pin2Value = analogRead(inputPin2);
        pin4Value = analogRead(inputPin4);
        pin3Value = analogRead(inputPin3);

    if (pin1Value + pin2Value > pin3Value + pin4Value){

        average1 = (pin1Value+ pin2Value)/2 ;
        averageMap1 = map(average1, 0, 1023, 0, 180 );

        servo.write(averageMap1);
    }
    else if( pin1Value + pin2Value < pin3Value + pin4Value){
        average1 = (pin1Value+ pin2Value)/2 ;
        averageMap1 = map(average1, 0, 1023, 0, 180 );
        servo.write(-averageMap1);
    }

    if (pin1Value + pin3Value > pin2Value + pin4Value ) {

        average2 = (pin1Value + pin3Value)/2;
        averageMap2 = map(average2, 0 , 1023, 0, 180);

        servo2.write(averageMap2);

    }
    else if(pin1Value + pin3Value < pin2Value + pin4Value ) {

        average2 = (pin1Value + pin3Value)/2;
        averageMap2 = map(average2, 0 , 1023, 0, 180);

        servo2.write(-averageMap2);

    }

    /*if (2pin > 2_2pin)

        value += 1
        servo2.write(value)

    } */

    /* faktor = 0.1
    
    diff = (average1 - average2)* faktor
    
    diffMap = map( diff, -1023, 1023,0,180)
    
    servo1.write(diffMap)*/


   

    

  
  /*  potValue = analogRead(potPin);
    potValue = map(potValue, 0, 1023, 0, 180);

    servo.write(potValue);
    delay(15);*/

}



    

