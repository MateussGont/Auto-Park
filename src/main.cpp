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
String sidePark = "";
String reverseSide = "";
bool initPark = false;
Car carro = createCar(5.1, 2.3, 2.1);
Ctr States;
// ParkingSpot spot = createParkingSpot();
TwoWire I2Cone = TwoWire(0);
VL53L0X sensor_direita_frente;
VL53L0X sensor_direita_tras;
VL53L0X sensor_traseiro;
VL53L0X sensor_esquerda_frente;
VL53L0X sensor_esquerda_tras;
uint16_t valor;
float scale[2] = {35.0, 22.0}; // passa a largura e comprimento do carro para medição de escala -verificar implementação

void freia_sozinho()
{
}

void setup()
{
  Serial.begin(921600);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  delay(100);
  digitalWrite(15, LOW);
  delay(100);
  digitalWrite(16, LOW);
  delay(100);
  digitalWrite(17, LOW);
  delay(100);
  digitalWrite(18, LOW);
  delay(100);
  digitalWrite(19, LOW);
  delay(100);
  digitalWrite(15, HIGH);
  delay(100);
  digitalWrite(16, HIGH);
  delay(100);
  digitalWrite(17, HIGH);
  delay(100);
  digitalWrite(18, HIGH);
  delay(100);
  digitalWrite(19, HIGH);
  delay(100);
  Wire.begin();
  // I2Cone.begin(21, 22, 921600); // Configuração de pinos para I2C gpio 21 e 22
  // sensor.setBus(&I2Cone);       // Leitor do sensor configurado para o barramento de entrada I2C

  sensor_esquerda_frente.setTimeout(50);
  sensor_direita_frente.setTimeout(50);
  sensor_esquerda_tras.setTimeout(50);
  sensor_direita_tras.setTimeout(50);
  sensor_traseiro.setTimeout(50);
  if (!sensor_esquerda_frente.init() || !sensor_direita_frente.init() || !sensor_direita_tras.init() || !sensor_esquerda_tras.init() || !sensor_traseiro.init())
  {
    Serial.println("Failed to detect and initialize sensor 1!");
    while (1)
    {
    }
  }
  sensor_esquerda_frente.setAddress((uint8_t)22);
  sensor_direita_frente.setAddress((uint8_t)22);
  sensor_esquerda_tras.setAddress((uint8_t)22);
  sensor_direita_tras.setAddress((uint8_t)22);
  sensor_traseiro.setAddress((uint8_t)22);
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor_esquerda_frente.startContinuous(100);
  sensor_esquerda_tras.startContinuous(100);
  sensor_direita_tras.startContinuous(100);
  sensor_direita_frente.startContinuous(100);
  sensor_traseiro.startContinuous(100);
}

void loop()
{
  uint16_t distEF = sensor_esquerda_frente.readRangeContinuousMillimeters();
  uint16_t distET = sensor_esquerda_tras.readRangeContinuousMillimeters();
  uint16_t distDT = sensor_direita_tras.readRangeContinuousMillimeters();
  uint16_t distDF = sensor_direita_frente.readRangeContinuousMillimeters();
  uint16_t distT = sensor_traseiro.readRangeContinuousMillimeters();
  if (sensor_esquerda_frente.timeoutOccurred() || sensor_esquerda_tras.timeoutOccurred() || sensor_direita_frente.timeoutOccurred() || sensor_direita_tras.timeoutOccurred() || sensor_traseiro.timeoutOccurred())
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
      if (States.setInitialPositionLeft(distEF, distET))
      {
        sidePark = "esquerda";
        reverseSide = "direita";
        Serial.print("Posicionamento concluído.");
        state = States.setState(state);
      }
      else if (States.setInitialPositionRight(distDF, distDT))
      {
        sidePark = "direita";
        reverseSide = "esquerda";
        Serial.print("Posicionamento concluído.");
        state = States.setState(state);
      }
      break;
    case TURN:
      Serial.print("Gire o volante todo para ");
      Serial.print(sidePark);
      Serial.print(". Em seguida entre na vaga devagar...");
      if (distT >= 80 && distT <= 90)
      {
        Serial.print("Pare o carro!");
        delay(1000);
        state = States.setState(state);
      }
      break;
    case ENTRY:
      Serial.print("Alinhe o volante e continue dando ré devagar...");
      if (distT >= 60 && distT <= 70)
      {
        Serial.print("Pare o carro!");
        delay(1000);
        state = States.setState(state);
      }
      break;
    case RETURN:
      Serial.print("Vire o volante completamente para a ");
      Serial.print(reverseSide);
      Serial.print(" agora.");

      break;
    case ENDUP:

      break;
    case FINISHED:
      // Termina a vaga e os sensores são desativados
      break;
    default:

      break;
    }
  }
  if (distEF < 45 || distET < 45 || distDF < 45 || distDT < 45)
  {
    Serial.print("Atenção, risco de colisão! \n");
    Serial.print("Medidas do lado esquerdo: \n");
    Serial.print(distEF, distET);
    Serial.print("Medidas do lado direito: \n");
    Serial.print(distDF, distDT);
  }

  delay(100);
}
