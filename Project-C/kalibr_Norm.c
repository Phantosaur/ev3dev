#include "rbc.h"

bool sysActiv= true;

float leftNorm, rightNorm;

uint8_t leftMin = 5, leftMax = 34;
uint8_t rightMin = 10, rightMax = 63;
float normalizeLight(float curValue, float minValue, float maxValue){
    return (curValue - minValue) / (maxValue - minValue);
}


task Sensor_Read() {
    while (sysActiv)
    {

        leftNorm = normalizeLight(getColorReflected(S1), leftMin, leftMax);
        rightNorm = normalizeLight(getColorReflected(S3), rightMin, rightMax);

        delay(20);

    }


}

task Write_Display(){
    while (sysActiv)
    {

        displayTextLine(1, "Left_Sensor_Norm: %.2f", leftNorm);

        displayTextLine(2, "Right_Sensor_Norm: %.2f", rightNorm);
        displayTextLine(3, "Summa: %.2f", rightNorm+leftNorm);

    }


}
task main(){
    startTask(Sensor_Read);
    startTask(Write_Display);
    while (1)
    {
        if (getButtonPress(buttonEnter))
            {
                sysActiv=false;
                break;
            }
        delay(20);


        
    

    
    }
}
