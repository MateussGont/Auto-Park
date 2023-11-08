#include <stdio.h>

typedef struct
{
    double length;
    double width;
    double wheelbase;
    double wheelradius;
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
