#include "rbc.h"



void turnEnc(float angle_deg)
{

    int16_t il1 = 50;
    int16_t il2 = -50;
    float   k = 1;

    if (angle_deg>0){
        il1=-50;
        il2=50;

    }

    resetMotorEncoder(motorA);
    resetMotorEncoder(motorB);

    const float l = ((45 * PI) ) / 360;
    float ang = 190 * PI / 360 * angle_deg*k;

    setMotorSpeed(motorA, il1 * sgn(angle_deg));
    setMotorSpeed(motorB, il2 * sgn(angle_deg));

    while (fabs(getMotorEncoder(motorA)) < fabs(ang) / l)
    {

     setMotorSpeed(motorA,il1);
     setMotorSpeed(motorB,il2);   


    }

    setMotorSpeed(motorA, 0);
    setMotorSpeed(motorB, 0);
}


float l1;
float lrRed;
float lrBlue;
float lrGreen;
float lrsr;
bool sysActive = true;
task sensorReader() {
    while (sysActive) {
        delay(20);  // Частота чтения 50 Гц
        lrRed=(getColorRed(S1)+getColorRed(S3))/2;
        lrBlue=(getColorBlue(S1)+getColorBlue(S3))/2;
        lrGreen=(getColorGreen(S1)+getColorGreen(S3))/2;
        l1=getUSDistance(S2);
        lrsr=(lrRed+lrBlue+lrGreen)/3;

    }
}

task showInfo() {
    while (sysActive) {
        displayTextLine(1, "Red: %.2f", lrRed);
        displayTextLine(2, "Blue: %.2f", lrBlue);
        displayTextLine(3, "Green: %.2f", lrGreen);
        delay(200);  // Обновление экрана 5 раз в секунду
    }
}


task main(){
    startTask(sensorReader);
    startTask(showInfo);
    //startTask(dark_lineg);
    uint8_t i = -80;
    uint8_t i2 = -80;

    // Основной поток управления
    while (true) 
    {

        if(lrsr<7){
            
        while (lrsr<7){
            setMotorSpeed(motorA,-60);
            setMotorSpeed(motorB,-60);
        }
        

    
        } else if (l1<=50)
        {
            setMotorSpeed(motorA,50);
            setMotorSpeed(motorB,50);            

        } else {

            turnEnc(5);


        }

        if (getButtonPress(buttonEnter)) {
            sysActive = false;
            break;
        }
    delay(10);
    }

}
