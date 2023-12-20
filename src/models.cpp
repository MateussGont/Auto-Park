#include <stdio.h>
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
    double width = 2.5; // tamanho padrão
} ParkingSpot;

// Função para inicializar um Car
Car createCar(double comprimento, double largura, double wheelbase)
{
    Car car;
    car.largura = largura;
    car.comprimento = comprimento;
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
