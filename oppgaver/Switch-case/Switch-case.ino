#define redPin 13
#define greenPin 12
#define bluePin 11



int redValue = 0;
int blueValue = 0; 
int greenValue = 0;
int Byte = 0;

void setup(){

    Serial.begin(9600);

}

void loop() {


    if (Serial.available() > 0)
    {
       Byte = Serial.read(); 

       switch (Byte)
       {
       case 'r':
        redValue += 1;
        if (redValue > 1){
            redValue = 0;
        }
        break;

       case 'b':
        blueValue += 1;
        if(blueValue > 1){
            blueValue = 0;
        }
        break;


       case 'g':
        greenValue += 1;
        if(greenValue > 1 ){
            greenValue = 0;
        }
        break;

       case '-':
        allOff();
        break;

       case '+': 
        allOn();
        break;

       default:
        Serial.println("Valid commands are: r = red b = blue g = green, + = all on, - = all off");
        break;
       }

        
    }
    
   setColor() ;

}


void allOff(){
   
   redValue = 0;
   blueValue = 0;
   greenValue = 0;
    
}

void allOn(){
   
   redValue = 1;
   blueValue = 1;
   greenValue = 1;

}


void setColor() {
    if( redValue == 1){
        digitalWrite(redPin, HIGH);
    }
    if(redValue == 0){
        digitalWrite(redPin,LOW );
    }
    if (blueValue == 1)
    {
        digitalWrite(bluePin, HIGH);
    }
    if(blueValue == 0){
        digitalWrite(bluePin, LOW);
    }
    if(greenValue == 1){
        digitalWrite(greenPin, HIGH);
    }
    if(greenValue == 0){
        digitalWrite(greenPin, LOW);
    }
    
}