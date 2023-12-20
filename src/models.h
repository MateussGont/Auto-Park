#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED
#include <Wire.h>
#include "VL53L0X.h"
typedef struct
{
    double largura;
    double comprimento;
    double wheelbase;
    double wheelradius;
    VL53L0X sensor_DF, sensor_EF, sensor_DT, sensor_ET, sensor_CT;
    double velocity;
} Car;

typedef struct
{
    double length;
    double width;
} ParkingSpot;

// Função para inicializar um Car
Car createCar(double comprimento, double largura, double wheelbase);

// Função para inicializar um ParkingSpot
ParkingSpot createParkingSpot(double length, double width);

#endif // MODELS_H_INCLUDED
