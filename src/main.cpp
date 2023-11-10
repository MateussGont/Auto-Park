#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X.h"
#include "models.h"
#include "ctr.h"

// Pipeline para entrar na vaga 180°
#define CALIBRANDO 0 // alinhamento das traseiras dos carros
#define INIT 1       // botão start apertado e inicio dos sensores
#define TURN 2       // Faz a rotação das rodas e anda para trás até atingir um angulo X (Medição a ser feita)
#define ENTRY 3      // Após estar no angulo alinha as rodas ao centro e anda uma distancia X (Medição a ser feita)
#define RETURN 4     // após andar a distancia anterior vira as rodas completamente a esquerda e continua a entrada até o sensor de ré apitar
#define ENDUP 5      // volante volta ao centro e usuário termina com ajustes finos
#define FINISHED 6   // Para os sensores

int state = INIT;
bool initPark = false;
Car carro = createCar(5.1, 2.3, 2.1);
Ctr States;
// ParkingSpot spot = createParkingSpot();
TwoWire I2Cone = TwoWire(0);
VL53L0X sensor;
VL53L0X sensor2;
uint16_t valor;
float scale[2] = {35.0, 22.0}; // passa a largura e comprimento do carro para medição de escala -verificar implementação

void freia_sozinho()
{
}

void setup()
{
  Serial.begin(921600);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  delay(100);
  digitalWrite(16, LOW);
  delay(100);
  digitalWrite(17, LOW);
  delay(100);
  digitalWrite(16, HIGH);
  delay(100);
  Wire.begin();
  // I2Cone.begin(21, 22, 921600); // Configuração de pinos para I2C gpio 21 e 22
  // sensor.setBus(&I2Cone);       // Leitor do sensor configurado para o barramento de entrada I2C

  sensor.setTimeout(50);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor 1!");
    while (1)
    {
    }
  }
  sensor.setAddress((uint8_t)22);
  delay(100);
  digitalWrite(17, HIGH);

  if (!sensor2.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    while (1)
    {
    }
  }

  sensor2.setAddress((uint8_t)25);
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous(100);
  sensor2.startContinuous(100);
}

void loop()
{
  uint16_t dist1 = sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  uint16_t dist2 = sensor2.readRangeContinuousMillimeters();
  if (sensor2.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  // States
  if (initPark)
  {
    switch (state)
    {
    case CALIBRANDO:
      // após passar uma vaga de um certo tamanho passa para proximo estágio
      break;
    case INIT:
      // se sinal de pronto tiver sido enviado muda estado para calibrando
      Serial.print("Alinhe seu automóvel...");
      if (States.setInitialPosition(dist1, dist2))
      {
        Serial.print("Posicionamento concluído.");
        state = States.setState(state);
      }
      break;
    case TURN:
      // Inicia a rotação das rotas até que o carro atinja angulo necessário (A ser testado) para proximo estágio
      break;
    case ENTRY:
      // retorna as rodas e inicia o movimento de entrada na vaga até percorrer uma certa distancia
      break;
    case RETURN:
      // faz a rotação das rodas para o lado oposto e continua entrada
      break;
    case ENDUP:
      // termina de ajustar o carro  na vaga caso seja necessário
      break;
    case FINISHED:
      // Termina a vaga e os sensores são desativados
      break;
    default:

      break;
    }
  }
  if (dist1 < 45 || dist2 < 45)
  {
    Serial.print("Atenção, risco de colisão! \n");
    Serial.print(dist1, dist2);
  }

  delay(100);
}
