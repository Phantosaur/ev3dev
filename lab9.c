#include "rbc.h"

// Константы калибровки (заполнить из задачи 8.1)
uint8_t leftMin = 5, leftMax = 34;
uint8_t rightMin = 10, rightMax = 63;
// Параметры регулятора
int baseSpeed = 20; // базовая скорость движения
float Kp = 25;    // коэффициент пропорциональности
float lineThreshold = 1.7;   //суммарный показатель ухода с черной линии
bool storona;
// Нормализованные значения
float leftNorm = 0;
float rightNorm = 0;

// Мониторинг потери линии

bool lostLine = false;
float error = 0;
float correction = 0;

// Значения скоростей
int leftSpeed = 0;
int rightSpeed = 0;

bool sysActive=1;
float normalizeValue(float value, float minValue, float maxValue){
    return (value - minValue) / (maxValue - minValue);
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

task readSensors(){
    while(sysActive){
        // Работа с датчиками цвета (чтение данных, их нормализация и т.п.)
        leftNorm = normalizeValue(getColorReflected(S1), leftMin, leftMax);
        rightNorm = normalizeValue(getColorReflected(S3), rightMin, rightMax);

        delay(20);
    }
}


task lineControl(){
    while(sysActive){
        // Отслеживание потери линии
        if (leftNorm+rightNorm>lineThreshold){
            lostLine=true;
        } else {
            lostLine=false;
        }
        
    }
}


task displayInfo(){
    while(sysActive){
        // Вывод всех значений, связанных с линией, для отладки
    
        displayTextLine(1, "Left_Sensor_Norm: %.2f", leftNorm);

        displayTextLine(2, "Right_Sensor_Norm: %.2f", rightNorm);
        displayTextLine(3, "Summa: %.2f", rightNorm+leftNorm);
        displayTextLine(4, "LineControl: %d", rightNorm+leftNorm);
    }
}


task main(){
    startTask(readSensors);
    startTask(lineControl);
    startTask(displayInfo);

    while(sysActive){
        if (lostLine==1){
            if (storona==1){
                turnEnc(5);
            } else {
                turnEnc(-5);
            }

        } else{
            // Движение робота по линии при помощи P-регулятора
                    // Вычисление ошибки
        error = leftNorm - rightNorm;

        // Вычисление коррекции
        correction = error * Kp;

        // Применение коррекции к моторам
        leftSpeed = baseSpeed + correction;
        rightSpeed = baseSpeed - correction;
        if (leftSpeed<rightSpeed){
            storona=true;
        } else {
            storona=false;
        }

        setMotorSpeed(motorA, leftSpeed); // левый мотор
        setMotorSpeed(motorB, rightSpeed); // правый мотор
        delay(20); // частота обновления 20 Гц
        }
        if (getButtonPress(buttonEnter)) 
        {
            sysActive = false;
            break;
        }
        
    }
}
