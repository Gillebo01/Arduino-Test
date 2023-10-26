#include <Wire.h>
#include <Zumo32U4.h>

//////////////////////////////////////////////////////////
/////////////////////  Variables ////////////////////////
//////////////////////////////////////////////////////////

enum State {
    pause_state,
    run_state
};

const int motorSpeed = 100;

const int blackColor = 700;

Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3];
Zumo32U4Motors motors;
Zumo32U4OLED display;
State state = pause_state;
String tekst[6] = {"Ready", "Set", "GO!", "DONE", ">w<", "Distance: "};


//////////////////////////////////////////////////////////
/////////////////////  Setup  ////////////////////////////
//////////////////////////////////////////////////////////

void setup(){

    lineSensors.initThreeSensors();
    lineSensors.emittersOn();

}

//////////////////////////////////////////////////////////
/////////////////////  Funksjons /////////////////////////
//////////////////////////////////////////////////////////



int printText(int x)
{
    display.clear();
    display.gotoXY(2, 0.4);
    display.print(tekst[x]);
    display.gotoXY(0, 0);
}

int printEmoji(int x)
{
    display.clear();
    display.gotoXY(2.2, 0.4);
    display.print(tekst[3]);
    display.gotoXY(2, 1);
    display.print(tekst[4]);
    display.gotoXY(0, 0);
}

//////////////////////////////////////////////////////////
/////////////////////  Loop  /////////////////////////////
//////////////////////////////////////////////////////////

void loop(){

    lineSensors.read(lineSensorValues);

    bool buttonPress = buttonA.getSingleDebouncedPress();
    bool calibrateButton = buttonB.isPressed();

    if(calibrateButton == true){
        lineSensors.calibrate();
    }

    if(buttonPress && state == pause_state){
        state = run_state;
    }

    else if (buttonPress && state == run_state)
    {
        state = pause_state;
    }
    
    if(state == run_state){

        if(lineSensorValues > 2000){



        }
    }


}

