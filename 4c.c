#include "rbc.h"
long y = 0;

void moveEnc(float dist)
{

    const float l = ((30 * 3.14) * 1.5) / 360;
    float i = 50;
    float i2 = 50;

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
        if (getMotorEncoder(motorA) == getMotorEncoder(motorB))
        {
            i = 50;
            i2 = 50;
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
    //     const float l = ((30 * 3.14) * 1.5) / 360;
    //     abs(angle_deg);
    //     int ang = 194.5 * 3.14 / 360 * angle_deg * 2;

    //     resetMotorEncoder(motorA);
    //     resetMotorEncoder(motorB);

    //     setMotorSpeed(motorA, il);
    //     setMotorSpeed(motorB, il2);

    //     while (getMotorEncoder(motorA) < ang / l)
    //     {
    //         delay(20);
    //         if (getMotorEncoder(motorA) > -getMotorEncoder(motorB))
    //         {
    //             il2 += 0.15;
    //         }
    //         if (getMotorEncoder(motorA) < -getMotorEncoder(motorB))
    //         {
    //             il2 -= 0.15;
    //         }
    //         if (getMotorEncoder(motorA) == -getMotorEncoder(motorB))
    //         {

    //         }
    //         setMotorSpeed(motorA, il);
    //         setMotorSpeed(motorB, il2);
    //     }

    // setMotorSpeed(motorA, 0);
    // setMotorSpeed(motorB, 0);
    int il1= 50;
    int il2= -50;
    if (angle_deg<0){
        il1=-50;
        il2=50;

    }

    resetMotorEncoder(motorA);
    resetMotorEncoder(motorB);

    const float l = ((45 * PI) ) / 360;
    float ang = 190 * PI / 360 * angle_deg;

    setMotorSpeed(motorA, il1 * sgn(angle_deg));
    setMotorSpeed(motorB, il2 * sgn(angle_deg));

    while (fabs(getMotorEncoder(motorA)) < fabs(ang) / l)
    {
        // delay(20);
        // if (getMotorEncoder(motorA) > -getMotorEncoder(motorB))
        // {
        //     il2 += 0.15;
        // }
        // if (getMotorEncoder(motorA) < -getMotorEncoder(motorB))
        // {
        //     il2 -= 0.15;
        // }

     setMotorSpeed(motorA,il1);
     setMotorSpeed(motorB,il2);   
    // }
    // if (abs(getMotorEncoder(motorA))> abs(getMotorEncoder(motorB))){
    // while (abs(getMotorEncoder(motorA))> abs(getMotorEncoder(motorB))){
    

    // }

    }

    setMotorSpeed(motorA, 0);
    setMotorSpeed(motorB, 0);
}

float moveXY(float x, float y, float ugl)
{
    float c = sqrt(x * x + y * y);

    float ugl1 = atan2f(y, x) * (180 / PI);
    ugl = ugl1 - ugl;
    turnEnc(ugl);
    moveEnc(c);

    return ugl;
}
void proba()
{
    float l1;
    float l3;

    turnEnc(-90);
    delay(20);
    l3 = getUSDistance(S2);
    turnEnc(180);
    delay(20);
    l1 = getUSDistance(S2);
    if (l1 > l3)
    {
        turnEnc(-180);
    }
}
bool probaLeft(){
float l1;
turnEnc(90);
l1=getUSDistance(S2);
if(l1>=50){
    turnEnc(-90);
 return 1;

} else{
turnEnc(-90);
return 0;
}
}
bool probaRight(){
float l1;
turnEnc(-90);
l1=getUSDistance(S2);
if(l1>=50){
    turnEnc(90);
 return 1;
    
} else{
    turnEnc(90);
 return 0;

}

}
void poisk(float dist)
{
    while (1)
    {
        stoppoka(dist);
        proba();

        delay(50);
    }
}
void obr (byte prohod){
moveEnc(300*prohod);
turnEnc(-90);
moveEnc(600);
turnEnc(-90);
moveEnc(300*prohod);
turnEnc(180);


}

void put3_obr(){
    bool l;
    byte k1;
    byte k2;
    byte k3;
for (int j=0; j<3;j++){
for(int i; i<4;i++){
l = probaLeft();
if(l==1){
if  (k1==0){
k1=i;} else if (k1!=0&& k2==0){
    k2=i;} else if (k3==0&&k2!=0){
        k3=0;
    }
turnEnc(90);
resetMotorEncoder(motorA);
resetMotorEncoder(motorB);
moveEnc(600);
turnEnc(90);
if (k2==0){moveEnc(300*k1);}else if(k3==0){
    moveEnc(300*k2);}else if(k3!=0){
        moveEnc(300*k3);
    }
}

turnEnc(-180);
delay(5000);
break;
}
moveEnc(300);
}
for (int i; i<4;i++){
if (k3!=0){
obr(k3);
k3=0;
delay(5000);
}else if (k3==0&&k2!=0){
obr(k2);
k2=0;
delay(5000);
}else if(k2==0&&k3==0){
    obr(k1);
    k1=0;
    delay(5000);
}


}
}





task main(){

put3_obr();


}



