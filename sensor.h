#ifndef SENSOR_H
#define SENSOR_H

#include "header.h"
#include "GPIO.h"

#define BUFFER_MAX 3
#define DIRECTION_MAX 256
#define VALUE_MAX 256

#define IN 0
#define OUT 1
#define LOW 0
#define HIGH 1

#define POUT1 22
#define PIN1 23

#define POUT2 24
#define PIN2 25

#define POUT3 26
#define PIN3 27

#define POUT4 28
#define PIN4 29

#define obstacleDistance 5.0;

static int initSensor()
{
  // Enable GPIO pins
  if (-1 == GPIOExport(POUT1) || -1 == GPIOExport(PIN1))
  {
    printf("gpio export err\n");
    return (1);
  }

  if (-1 == GPIOExport(POUT2) || -1 == GPIOExport(PIN2))
  {
    printf("gpio export err\n");
    return (1);
  }

  if (-1 == GPIOExport(POUT3) || -1 == GPIOExport(PIN3))
  {
    printf("gpio export err\n");
    return (1);
  }

  if (-1 == GPIOExport(POUT4) || -1 == GPIOExport(PIN4))
  {
    printf("gpio export err\n");
    return (1);
  }

  // wait for writing to export file
  usleep(100000);

  // Set GPIO directions
  if (-1 == GPIODirection(POUT1, OUT) || -1 == GPIODirection(PIN1, IN))
  {
    printf("gpio direction err\n");
    return (2);
  }

  if (-1 == GPIODirection(POUT2, OUT) || -1 == GPIODirection(PIN2, IN))
  {
    printf("gpio direction err\n");
    return (2);
  }

  if (-1 == GPIODirection(POUT3, OUT) || -1 == GPIODirection(PIN3, IN))
  {
    printf("gpio direction err\n");
    return (2);
  }

  if (-1 == GPIODirection(POUT4, OUT) || -1 == GPIODirection(PIN4, IN))
  {
    printf("gpio direction err\n");
    return (2);
  }

  // init ultrawave trigger
  GPIOWrite(POUT1, 0);
  GPIOWrite(POUT2, 0);
  GPIOWrite(POUT3, 0);
  GPIOWrite(POUT4, 0);
}

static int disableSensor()
{
  // Disable GPIO pins
  if (-1 == GPIOUnexport(POUT1) || -1 == GPIOUnexport(PIN1))
    return (4);

  if (-1 == GPIOUnexport(POUT2) || -1 == GPIOUnexport(PIN2))
    return (4);

  if (-1 == GPIOUnexport(POUT3) || -1 == GPIOUnexport(PIN3))
    return (4);

  if (-1 == GPIOUnexport(POUT4) || -1 == GPIOUnexport(PIN4))
    return (4);
}

// 거리 return 하도록 수정
int forwardSensor() // 0 or 1 return
{
  clock_t start_t, end_t;
  double time;
  double distance;

  // sensor 1
  GPIOWrite(POUT1, 0);
  usleep(10000);

  if (-1 == GPIOWrite(POUT1, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  usleep(10);
  GPIOWrite(POUT1, 0);

  while (GPIORead(PIN1) == 0)
    start_t = clock();

  while (GPIORead(PIN1) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  if (time / 2 * 34000 < obstacleDistance)
    return 1;

  // sensor 2
  GPIOWrite(POUT2, 0);
  usleep(10000);

  if (-1 == GPIOWrite(POUT2, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  usleep(10);
  GPIOWrite(POUT2, 0);

  while (GPIORead(PIN2) == 0)
    start_t = clock();

  while (GPIORead(PIN2) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  if (time / 2 * 34000 < obstacleDistance)
    return 1;
  else
    return 0;
}

int BackSensor() // 0 or 1 return
{
  clock_t start_t, end_t;
  double time;
  double distance;

  // sensor 1
  GPIOWrite(POUT3, 0);
  usleep(10000);

  if (-1 == GPIOWrite(POUT3, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  usleep(10);
  GPIOWrite(POUT3, 0);

  while (GPIORead(PIN3) == 0)
    start_t = clock();

  while (GPIORead(PIN3) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  if (time / 2 * 34000 < obstacleDistance)
    return 1;

  // sensor 2
  GPIOWrite(POUT4, 0);
  usleep(10000);

  if (-1 == GPIOWrite(POUT4, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  usleep(10);
  GPIOWrite(POUT4, 0);

  while (GPIORead(PIN4) == 0)
    start_t = clock();

  while (GPIORead(PIN4) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  if (time / 2 * 34000 < obstacleDistance)
    return 1;
  else
    return 0;
}

#endif