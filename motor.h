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

#define spdTurn 10     // 수정 필요
#define spdGo 10       // 수정 필요
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

void goForward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, spdGo);
}

void goBackward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, spdGo);
}

void turnLeft()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    PWMWriteDutyCycle(ENA, spdTurn);

    sleep(1);
    stopMotor();
}

void turnRight()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    PWMWriteDutyCycle(ENA, spdTurn);

    sleep(1);
    stopMotor();
}

void move(char now)
{
    double frontDistance = 0;
    double rearDistance = 0;

    switch (now)
    {
    case 'A':
        frontDistance = 4.5;
        rearDistance = 19.5;
        break;

    case 'B':
        frontDistance = 18.0;
        rearDistance = 19.5;
        break;

    case 'C':
        frontDistance = 23.0;
        rearDistance = 15;
        break;

    default:
        break;
    }

    printf("포장대 > %c 구역 이동 시작 \n", now);
    while (1)
    {
        // frontSensor 기준 자리 잡기
        if (frontSensor(frontDistance) == 1)
            goBackward();
        else
            break;

        // 장애물 만난 경우
        if (rearSensor(2) == 1)
        {
            printf("%c 구역 > %c 구역: 장애물로 인해 일시 정지 \n", previous, now);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (rearSensor(2) == 0)
                {
                    printf("%c 구역 > %c 구역: 이동 중 \n", previous, now);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    turnRight();

    // 우회전 후 직진
    while (1)
    {
        // rearSensor 기준 자리 잡기
        if (rearSensor(rearDistance) == 1)
            goForward();
        else
            break;

        // 장애물 만난 경우
        if (frontSensor(2) == 1)
        {
            printf("%c 구역 > %c 구역: 장애물로 인해 일시 정지 \n", previous, now);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (frontSensor(2) == 0)
                {
                    printf("%c 구역 > %c 구역: 이동 중 \n", previous, now);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    printf("%c 구역: 도착 \n", now);
}

void moveTo(char previous, char now)
{
    double frontDistance = 17; // 처음에 후진
    double rearDistance1 = 0;  // 좌회전 후 직진
    double rearDistance2 = 0;  // 우회전 후 직진

    switch (now)
    {
    case 'A':
        rearDistance1 = 19.5;
        rearDistance2 = ;
        break;

    case 'B':
        rearDistance1 = 19.5;
        rearDistance2 = ;
        break;

    default:
        break;
    }

    printf("%c 구역 > %c 구역: 이동 시작", previous, now);

    // 후진
    while (1)
    {
        // frontSensor 기준 자리 잡기
        if (frontSensor(frontDistance) == 1)
            goBackward();
        else
            break;

        // 장애물 만난 경우
        if (rearSensor(2) == 1)
        {
            printf("%c 구역 > %c 구역: 장애물로 인해 일시 정지 \n", previous, now);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (rearSensor(2) == 0)
                {
                    printf("%c 구역 > %c 구역: 이동 중 \n", previous, now);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    turnLeft();

    // 좌회전 후 직진
    while (1)
    {
        // rearSensor 기준 자리 잡기
        if (rearSensor(rearDistance1) == 1)
            goForward();
        else
            break;

        // 장애물 만난 경우
        if (frontSensor(2) == 1)
        {
            printf("%c 구역 > %c 구역: 장애물로 인해 일시 정지 \n", previous, now);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (frontSensor(2) == 0)
                {
                    printf("%c 구역 > %c 구역: 이동 중 \n", previous, now);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    turnRight();

    // 우회전 후 직진
    while (1)
    {
        // rearSensor 기준 자리 잡기
        if (rearSensor(rearDistance2) == 1)
            goForward();
        else
            break;

        // 장애물 만난 경우
        if (frontSensor(2) == 1)
        {
            printf("%c 구역 > %c 구역: 장애물로 인해 일시 정지 \n", previous, now);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (frontSensor(2) == 0)
                {
                    printf("%c 구역 > %c 구역: 이동 중 \n", previous, now);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    printf("%c 구역: 도착 \n", now);
}

returnOrigin(char previous)
{
    int isSleep = 0;
    double frontDistance = 17;  // 처음에 후진
    double rearDistance = 22.5; // 좌회전 후 직진

    printf("%c 구역 > 포장대: 이동 시작\n", previous);

    // 처음 후진
    while (1)
    {
        // frontSensor 기준 자리 잡기
        if (frontSensor(frontDistance) == 1)
            goBackward();
        else
            break;

        // 장애물 만난 경우
        if (rearSensor(2) == 1)
        {
            printf("%c 구역 > 포장대: 장애물로 인해 일시 정지 \n", previous);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (rearSensor(2) == 0)
                {
                    printf("%c 구역 > 포장대: 이동 중 \n", previous);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    turnLeft();

    // 좌회전 후 직진
    while (1)
    {
        // rearSensor 기준 자리 잡기
        if (rearSensor(rearDistance) == 1)
            goForward();
        else
            break;

        // 장애물 만난 경우
        if (frontSensor(2) == 1)
        {
            printf("%c 구역 > 포장대: 장애물로 인해 일시 정지 \n", previous);
            sleep(1);
            // 장애물 만난 후 장애물이 아직 있는지 확인
            while (1)
            {
                if (frontSensor(2) == 0)
                {
                    printf("%c 구역 > 포장대: 이동 중 \n", previous);
                    break;
                }
                sleep(0.5);
            }
        }
    }

    printf("포장대: 도착 \n");
}

#endif