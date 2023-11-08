#ifndef MODELS_H_INCLUDED
#define MODELS_H_INCLUDED

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
    double width;
} ParkingSpot;

// Função para inicializar um Car
Car createCar(double length, double width, double wheelbase);

// Função para inicializar um ParkingSpot
ParkingSpot createParkingSpot(double length, double width);

#endif // MODELS_H_INCLUDED
