#ifndef MOTOR_H
#define MOTOR_H

#include "header.h"
#include "PWM.h"

#define ENA 1
#define IN1 4
#define IN2 5
#define ENB 26
#define IN3 3
#define IN4 2

#define PWM_RANGE 1024 // range of PWM

void initMotor()
{
    wiringPiSetup();

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    PWMinit(ENA);
}

void stopMotor()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, 0);
}

void goForward(int num)
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, num);
}

void goBackward(int num)
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, num);
}

void turnLeft(int num)
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, num);
}

void turnRight(int num)
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, num);
}

#endif