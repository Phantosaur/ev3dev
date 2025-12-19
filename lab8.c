#include "rbc.h"
bool sysActive = true;

task showInfo() {
    while (sysActive) {
        displayTextLine(1, "LSensor: %d", getColorReflected(S1));
        displayTextLine(2, "RSensor: %d", getColorReflected(S3));
        delay(200);  // Обновление экрана 5 раз в секунду
    }
}

float normalizeLight(int curValue, int minValue, int maxValue){
    return (float)(curValue - minValue) / (float)(maxValue - minValue);
}


task main() {
    startTask(showInfo);

    // Константы калибровки (вписать значения полученные после запуска программы kalibr.c)
    int leftMin = 7, leftMax = 54;
    int rightMin = 12, rightMax = 83; 

    // Параметры регулятора
    int baseSpeed = 20; // базовая скорость движения
    float Kp = 30.0;    // коэффициент пропорциональности

    // Нормализованные значения
    float leftNorm = 0;
    float rightNorm = 0;

    // Параметры регулировки, полученные от нормализованных значений
    float error = 0;
    float correction = 0;

    // Значения скоростей
    int leftSpeed = 0;
    int rightSpeed = 0;

    while(sysActive) {
        // Чтение и нормализация датчиков
        leftNorm = normalizeLight(getColorReflected(S1), leftMin, leftMax);
        rightNorm = normalizeLight(getColorReflected(S3), rightMin, rightMax);

        // Вычисление ошибки
        error = leftNorm - rightNorm;

        // Вычисление коррекции
        correction = error * Kp;

        // Применение коррекции к моторам
        leftSpeed = baseSpeed + correction;
        rightSpeed = baseSpeed - correction;

        setMotorSpeed(motorA, leftSpeed); // левый мотор
        setMotorSpeed(motorB, rightSpeed); // правый мотор
        delay(50); // частота обновления 20 Гц
        if (getButtonPress(buttonEnter)) 
        {
            sysActive = false;
            break;
        }
    }
}


