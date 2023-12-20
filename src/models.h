#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED
#include <Wire.h>
#include "VL53L0X.h"
typedef struct
{
    double length;
    double width;
    double wheelbase;
    double wheelradius;
    VL53L0X sensor;
    VL53L0X sensor2;
    double velocity;
} Car;

typedef struct
{
    double length;
    double width;
} ParkingSpot;

// Função para inicializar um Car
Car createCar(double length, double width, double wheelbase);

// Função para inicializar um ParkingSpot
ParkingSpot createParkingSpot(double length, double width);

#endif // MODELS_H_INCLUDED
