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

#define spdTurn 1000000 // 수정 필요
#define spdGo 800000    // 수정 필요

#define obstacleDistance 3 // 장애물 판정 기준 거리
#define wallDistance 3     // 벽과의 거리
#define totalSize 35       // 전체 길이
#define vehicleSize 14

void initMotor()
{
    wiringPiSetup();

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    PWMinit(ENA);
    PWMinit(ENB);
}

void stopMotor()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, 0);
    PWMWriteDutyCycle(ENB, 0);
}

void goForward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, spdGo);
    PWMWriteDutyCycle(ENB, spdGo);
}

void goBackward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, spdGo);
    PWMWriteDutyCycle(ENB, spdGo);
}

void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, spdTurn);
    PWMWriteDutyCycle(ENB, spdTurn);

    usleep(250000);
    stopMotor();
}

void turnRight()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, spdTurn);
    PWMWriteDutyCycle(ENB, spdTurn);

    usleep(250000);
    stopMotor();
}

void moveBackward(int d1)
{
    double frpre = 0, frnow = 0;
    double repre = 0, renow = 0;
    int stop = 0, stat = 0;

    frpre = 0;
    repre = 0;
    stop = 0;

    while (1)
    {
        if (!stat)
        {
            goBackward();
            stat = 1;
        }

        while (1)
        {
            frnow = frontSensor(frpre);
            if (frnow != 0)
            {
                frpre = frnow;
                if (frnow > d1)
                    stop = 1;
                break;
            }
        }
        if (stop)
        {
            stopMotor();
            break;
        }

        while (!stop)
        {
            if (!stat)
                goBackward();
            renow = rearSensor(repre);
            if (renow != 0)
            {
                repre = renow;
                if (renow < obstacleDistance)
                {
                    stopMotor();
                    usleep(500000);
                    stat = 0;
                }
                else
                    break;
            }
        }
    }
}

void moveForward(int d1)
{
    double frpre = 0, frnow = 0;
    double repre = 0, renow = 0;
    int stop = 0, stat = 0;

    frpre = 0;
    repre = 0;
    stop = 0;

    while (1)
    {
        if (!stat)
        {
            goForward();
            stat = 1;
        }

        while (1)
        {
            renow = rearSensor(repre);
            if (renow != 0)
            {
                repre = renow;
                if (renow > d1)
                    stop = 1;
                break;
            }
        }
        if (stop)
        {
            stopMotor();
            break;
        }

        while (!stop)
        {
            if (!stat)
                goForward();
            frnow = frontSensor(frpre);
            if (frnow != 0)
            {
                frpre = frnow;
                if (frnow < obstacleDistance)
                {
                    stopMotor();
                    usleep(500000);
                    stat = 0;
                }
                else
                    break;
            }
        }
    }
}

void move(char dest)
{
    int d1;
    if (dest == 'A')
        d1 = 5;
    else if (dest == 'B')
        d1 = 15;
    else if (dest == 'C')
        d1 = 25;

    moveBackward(d1);
    turnRight();
    moveForward(wallDistance);
}

void moveTo(char dest)
{
    int d1;
    if (dest == 'A')
        d1 = 5;
    else if (dest == 'B')
        d1 = 15;

    moveBackward(13);
    turnLeft();
    moveForward(totalSize - d1 - vehicleSize);
    turnRight();
    moveForward(wallDistance);
}

void moveRe()
{
    moveBackward(13);
    turnLeft();
    moveForward(totalSize - vehicleSize - wallDistance);
}

#endif
