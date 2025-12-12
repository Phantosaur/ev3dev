#include "rbc.h"

bool sysActiv= true;

uint8_t lblick;
uint8_t rblick;

uint8_t rblick_fixMin=255;
uint8_t lblick_fixMin=255;
uint8_t lblick_fixMax=255;
uint8_t rblick_fixMax=255;
uint8_t i = 0;
bool r;
bool l;

task Sensor_Read() {
    while (sysActiv)
    {
        lblick = getColorReflected(S4);
        rblick = getColorReflected(S3);
        delay(20);

    }


}

task Write_Display(){
    while (sysActiv)
    {
        if (lblick_fixMax != 255){
            displayTextLine(1, "Left_fixMax: %d", lblick_fixMax);
        }
        if (lblick_fixMin == 255)
        {
            displayTextLine(2, "Left: %d", lblick);
        } else {
            displayTextLine(2, "Left_fixMin: %d", lblick_fixMin); 
        }
        if (rblick_fixMin != 255){
            displayTextLine(4, "Right_fixMin: %d", rblick_fixMin);
        } else {
            displayTextLine(4, "Right: %d", rblick);
        }
        if (rblick_fixMax != 255) {
            displayTextLine(3, "Right_fixMax: %d", rblick_fixMax);
        }
        delay(200);
    }


}
task main(){
    startTask(Sensor_Read);
    startTask(Write_Display);
    while (1)
    {
        if (getButtonPress(buttonRight)){
            if (r==0){
                rblick_fixMax=rblick;
                r= !r;
                delay(20);
            } else if (r==1){
                rblick_fixMin = rblick;



            }
            
        }
        if (getButtonPress(buttonLeft))
        {
            if (l==0)
            {
                lblick_fixMax=lblick;
                l= !l;
                delay(20);
            } else if(l==1) 
            {
                lblick_fixMin = lblick;
            }
        }
        if (getButtonPress(buttonEnter))
            {
                sysActiv=false;
                break;
            }
        delay(20);


        
    

    
    }
}
