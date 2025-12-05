#include "rbc.h"
long y = 0;

void moveEnc(float dist)
{
    
    const float l = ((30 * 3.14) * 1.5) / 360;

    float i = 50;
    float i2 = 50;
    if (dist<0){
        i = -80;
        i2= -80;
    }
    resetMotorEncoder(motorA);
    resetMotorEncoder(motorB);

    setMotorSpeed(motorA, i);
    setMotorSpeed(motorB, i2);

    while (getMotorEncoder(motorA) < (dist / l))
    {
        delay(50);
        if (getMotorEncoder(motorA) > getMotorEncoder(motorB))
        {
            i2 += 0.15;
        }
        if (getMotorEncoder(motorA) < getMotorEncoder(motorB))
        {
            i2 -= 0.15;
        }

        setMotorSpeed(motorA, i);
        setMotorSpeed(motorB, i2);
    }

    setMotorSpeed(motorA, 0);
    setMotorSpeed(motorB, 0);
}
void stoppoka(float t)
{
    setMotorSpeed(motorA, 50);
    setMotorSpeed(motorB, 50);
    while (getUSDistance(S2) > t)
    {
        setMotorReversed(motorA, 50);
        setMotorReversed(motorB, 50);
        delay(50);
    }
}

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


bool proba(bool napravlenie /*  0 - left, 1 - right  */){
    float l1;
    int16_t uglL = 90;
    
    uint8_t test_dist = 50;
    displayTextLine(1,"Ugl: %d", uglL);
    if (napravlenie==1) {
        uglL=-uglL;
        
    }
    turnEnc(uglL);
    l1=getUSDistance(S2);
    displayTextLine(2,"Ugl: %d", uglL);
    if(l1>=test_dist){
        turnEnc(-uglL);
        displayTextLine(3,"Ugl: %d", uglL);
        return 1;
    } else{
        turnEnc(-uglL);
        displayTextLine(4,"Ugl: %d", uglL);
        return 0;
    }
    delay(500);
}


void ogib (uint8_t k1,uint8_t k2 ){
    uint16_t dist = 300;
    int8_t ugl =90;
    if (k2 == k1) {
        moveEnc(dist*2);

    } else if (k1 < k2) {
        turnEnc(ugl);
        moveEnc(dist*(k2-k1));
        turnEnc(-ugl);
        moveEnc(dist*2);
    } else if (k1 > k2) {
        turnEnc(-ugl);
        moveEnc(dist*(k1-k2));
        turnEnc(ugl);
        moveEnc(dist*2);
    }


}
void put3_obr(){
    bool l;
    bool ugl =0;
    byte k1;
    byte k2;
    byte k3;
    uint16_t distant = 300;
    int16_t uglL = 90;
    uint16_t time_del = 5000;
    for (uint8_t o = 0; o<3;o++){
        for (uint8_t i = 0; i<4;i++){
            l=proba(0);
            if (l==1){
                if (o == 0){
                    k1=i;
                } else if (o == 1){
                    k2=i; 
                } else if (o == 2){
                    k3=i;
                }
                turnEnc(uglL);
                moveEnc(distant*2);
                turnEnc(uglL);
                if (o == 0){
                    moveEnc(distant*k1);
                } else if (o == 1){
                    moveEnc(distant*k2);
                } else if (o == 2){
                    moveEnc(distant*k3);
                }
                turnEnc(uglL*2);
                delay(time_del);
                break;
            }
            moveEnc(distant);
        }
    }
    for (uint8_t j = 0; l<3;j++){
        if (j == 0){
            //obr(k3);
            turnEnc(-uglL);
            ogib(0,k3);
        } else if (j == 1){
            //obr(k2);
            ogib(k3,k2);
        } else if (j == 2){
            //obr(k1);
            ogib(k2,k1);
            turnEnc(-uglL);
            moveEnc(distant*k1);
            turnEnc(2*uglL);
        }
    delay(time_del);
    }



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
// task dark_lineg(){
//         while (sysActive)
//         {
//             /* code */
        
        
//     if (lrsr<7)
//     {   
        
//         for (uint8_t i; i<250; i++){
//             setMotorSpeed(motorA,-20);
//             setMotorSpeed(motorB,-20);
//         } 
//             setMotorSpeed(motorA,0);
//             setMotorSpeed(motorB,0);


    


        
//     }
// }
//}
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


