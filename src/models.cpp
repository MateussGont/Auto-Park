#include <stdio.h>
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
    double width = 2.5; // tamanho padrão
} ParkingSpot;

// Função para inicializar um Car
Car createCar(double length, double width, double wheelbase)
{
    Car car;
    car.length = length;
    car.width = width;
    car.wheelbase = wheelbase;
    return car;
}

// Função para inicializar um ParkingSpot
ParkingSpot createParkingSpot(double length, double width)
{
    ParkingSpot spot;
    spot.length = length;
    spot.width = width;
    return spot;
}
