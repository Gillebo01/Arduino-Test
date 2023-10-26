#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4OLED display;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;
Zumo32U4ButtonB buttonB;
Zumo32U4Encoders encoders;
Zumo32U4ProximitySensors proxSensors;
String tekst[6] = {"Ready", "Set", "GO!", "DONE", ">w<", "Distance: "};

const uint16_t motorSpeed = 250;

int rightSens;
int leftSens;
int centerRightSens=0;
int centerLeftSens=0;
int frontSens= 0;
bool buttonstate = false;

unsigned long preMillis = 0;

unsigned long intervall = 1000;

void setup()
{
    display.clear();
    proxSensors.initThreeSensors();
}

void sensorRead()
{
    proxSensors.read();
    leftSens = proxSensors.countsLeftWithLeftLeds();
    centerLeftSens = proxSensors.countsFrontWithLeftLeds();
    centerRightSens = proxSensors.countsFrontWithRightLeds();
    rightSens = proxSensors.countsRightWithRightLeds();

    frontSens =(centerLeftSens + centerRightSens)/2;
}

void forward()
{
    sensorRead();

    int angle = (((int32_t)turnAngle >> 16)*360 )>>16;

   
}

void reverse(long count)
{
    encoders.getCountsAndResetLeft();
    encoders.getCountsAndResetRight();

    long countsLeft = 0;
    long countsRight = 0;
    motors.setSpeeds(-motorSpeed, -motorSpeed);
    while (countsLeft < count)
    {
        countsLeft -= encoders.getCountsAndResetLeft();
        countsRight -= encoders.getCountsAndResetRight();
        display.gotoXY(1, 1);
        display.print(countsLeft);
        display.print(" ");
        delay(2);
    };

    motors.setSpeeds(0, 0);
}

void turnRight(long count)
{
    sensorRead();
        }

    motors.setSpeeds(0, 0);
}

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


void sensData()
{

    display.clear();
    display.gotoXY(2, 0.4);
    display.print(centerLeftSens);
    display.gotoXY(0, 0);
}

void loop()
{

    
    
}


