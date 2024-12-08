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
#define spdGo 10       // 수정 필요ㄴ
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
    printf("구역 %c 이동중 \n", now);

    printf("구역 %c 이동 완료 \n", now);
}

void moveTo(char previous, char now)
{
    printf("%c 구역에서 %c 구역 이동중", previous, now);

    if (previous == 'A')
    {
        if (now == 'B')
        {
            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }

            turnRight(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }

            turnLeft(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }
        }
        else if (now == 'C')
        {
            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(17))
                {
                    stopMotor();
                    break;
                }
            }
        }
        else if (now == 'D')
        {
            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }

            turnRight(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }

            turnLeft(10);

            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }
        }
    }
    else if (previous == 'C')
    {
        if (now == 'B')
        {
            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }

            turnRight(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }

            turnLeft(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }
        }
        else if (now == 'D')
        {
            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }

            turnRight(10);

            while (1)
            {
                if (frontSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (!frontSensor(3))
                    goForward(10);
                if (rearSensorCheck(19))
                {
                    stopMotor();
                    break;
                }
            }

            turnLeft(10);

            while (1)
            {
                if (rearSensor(3)) // 수정 필요
                {
                    stopMotor();
                    sleep(1)
                }
                if (rearSensor(3))
                    goBackward(10);
                if (frontSensorCheck(14))
                {
                    stopMotor();
                    break;
                }
            }
        }
    }
    else if (previous == 'B' &&now = 'D')
    {
        while (1)
        {
            if (rearSensor(3)) // 수정 필요
            {
                stopMotor();
                sleep(1)
            }
            if (rearSensor(3))
                goBackward(10);
            if (frontSensorCheck(14))
            {
                stopMotor();
                break;
            }
        }
    }

    printf("구역 %c 이동 완료 \n", now);
}

returnOrigin(char previous)
{
    printf("%c 에서 포장대로 복귀합니다. \n", previous);
    while (1)
    {
        if (rearSensor(3)) // 수정 필요
        {
            stopMotor();
            sleep(1)
        }
        if (rearSensor(3))
            goBackward(10);
        if (frontSensorCheck(14))
        {
            stopMotor();
            break;
        }
    }

    turnRight(10);

    while (1)
    {
        if (frontSensor(3)) // 수정 필요
        {
            stopMotor();
            sleep(1)
        }
        if (!frontSensor(3))
            goForward(10);
        if (rearSensorCheck(19))
        {
            stopMotor();
            break;
        }
    }

    printf("포장대에 도착했습니다. \n");
}
#endif