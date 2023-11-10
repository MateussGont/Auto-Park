#ifndef CTR_H_INCLUDED
#define CTR_H_INCLUDED

#include "models.h"

class Ctr
{
public:
    // Função para calcular a distância que o carro deve percorrer para entrar na vaga
    double calculateDistanceToTravel(Car car, ParkingSpot spot);

    // Função para calcular o ângulo que o carro deve girar para entrar na vaga
    double calculateAngleToTurn(Car car, ParkingSpot spot);

    // Função para controlar a direção do carro
    void controlSteering(double angle);

    // Função para controlar a velocidade do carro
    void controlSpeed(double distance);

    bool setInitialPosition(int dist1, int dist2);

    int setState(int state);
};

#endif // CTR_H_INCLUDED
