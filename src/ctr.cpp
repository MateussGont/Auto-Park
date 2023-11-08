#include <stdio.h>
#include "models.h"
#include <math.h>

class Ctr
{
public:
    // Função para calcular a distância que o carro deve percorrer para entrar na vaga
    double calculateDistanceToTravel(Car car, ParkingSpot spot)
    {
        // Calcular a distância entre o carro e a vaga de estacionamento
        double distance = sqrt(pow(spot.length - car.length, 2) + pow(spot.width - car.width, 2));

        return distance;
    }

    // Função para calcular o ângulo que o carro deve girar para entrar na vaga
    double calculateAngleToTurn(Car car, ParkingSpot spot)
    {
        // Implementar a lógica para calcular o ângulo
        return 0.0;
    }

    // Função para controlar o volante do carro
    void controlVolante(double angle)
    {
        // Implementar a lógica para controlar volante
    }

    // Função para controlar a velocidade do carro
    void controlSpeed(double distance)
    {
        // Implementar lógica para controlar velocidade
    }
};

/*int main()
{
    Ctr ctr;
    Car car = {4.0, 1.8, 2.5};     // Exemplo de dimensões do carro
    ParkingSpot spot = {5.0, 2.2}; // Exemplo de dimensões da vaga de estacionamento

    double distance = ctr.calculateDistanceToTravel(car, spot);
    double angle = ctr.calculateAngleToTurn(car, spot);

    ctr.controlSteering(angle);
    ctr.controlSpeed(distance);

    return 0;
}*/
