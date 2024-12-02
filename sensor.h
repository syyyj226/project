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

static int initSensor()
{
  // Enable GPIO pins
  if (-1 == GPIOExport(POUT1) || -1 == GPIOExport(PIN1))
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

  // init ultrawave trigger
  GPIOWrite(POUT2, 0);

  // Enable GPIO pins
  if (-1 == GPIOExport(POUT2) || -1 == GPIOExport(PIN2))
  {
    printf("gpio export err\n");
    return (1);
  }
  // wait for writing to export file
  usleep(100000);

  // Set GPIO directions
  if (-1 == GPIODirection(POUT2, OUT) || -1 == GPIODirection(PIN2, IN))
  {
    printf("gpio direction err\n");
    return (2);
  }

  // init ultrawave trigger
  GPIOWrite(POUT1, 0);
}

static int disableSensor()
{
  // Disable GPIO pins
  if (-1 == GPIOUnexport(POUT1) || -1 == GPIOUnexport(PIN1))
    return (4);

  // Disable GPIO pins
  if (-1 == GPIOUnexport(POUT2) || -1 == GPIOUnexport(PIN2))
    return (4);
}

// 거리 return 하도록 수정
double distance1()
{
  clock_t start_t, end_t;
  double time;
  double distance;

  usleep(10000);
  // start
  if (-1 == GPIOWrite(POUT1, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  // 1sec == 1000000ultra_sec, 1ms = 1000ultra_sec
  GPIOWrite(POUT1, 0);

  while (GPIORead(PIN1) == 0)
    start_t = clock();

  while (GPIORead(PIN1) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  distance = time / 2 * 34000;

  printf("Sensor 1 distance: %.2lf\n", distance);

  /*if (distance < (double)criteria) // 거리 변경
    return 1;
  else
    return 0; */
}

double distance2()
{
  clock_t start_t, end_t;
  double time;
  double distance;

  usleep(10000);
  // start
  if (-1 == GPIOWrite(POUT2, 1))
  {
    printf("gpio write/trigger err\n");
    return (3);
  }

  // 1sec == 1000000ultra_sec, 1ms = 1000ultra_sec
  GPIOWrite(POUT2, 0);

  while (GPIORead(PIN2) == 0)
    start_t = clock();

  while (GPIORead(PIN2) == 1)
    end_t = clock();

  time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // ms
  distance = time / 2 * 34000;

  printf("Sensor 2 distance: %.2lf\n", distance);

  /*if (distance < (double)criteria) // 거리 변경
    return 1;
  else
    return 0;*/
}

#endif
