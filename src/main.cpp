#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X.h"
#include "models.h"
#include "stdlib.h"

// definições de direção
#define LEFT 0
#define RIGHT 1
#define FOWARD 2
#define BACK 3

// Definições de alerta
#define OK 0
#define DANGER -1
#define SAFE 1

// Pipeline para entrar na vaga 180°
#define PROCURANDO -1 // // Botão start apertado e inicio dos sensores
#define PRONTO 0      // Painel exibe que encontrou uma vaga compativel
#define CALIBRANDO 1  // alinhamento das traseiras dos carros (Carro encontra momento q a variação da distancia seja repentina)
#define TURN 2        // Faz a rotação das rodas e anda para trás até atingir um angulo X (Medição a ser feita)
#define ENTRY 3       // Após estar no angulo alinha as rodas ao centro e anda uma distancia X (Medição a ser feita)
#define RETURN 4      // após andar a distancia anterior vira as rodas completamente a esquerda e continua a entrada até o sensor de ré apitar
#define ENDUP 5       // volante volta ao centro e usuário termina com ajustes finos
#define FINISHED 6    // Para os sensores

int state;
Car carro = createCar(160, 70, 68); // carro em mm
// ParkingSpot spot = createParkingSpot();
TwoWire I2Cone = TwoWire(0);
VL53L0X sensor;
VL53L0X sensor2;
uint16_t valor;
uint16_t buffer1, bufffer2, buffer3;
float scale[2] = {35.0, 22.0}; // passa a largura e comprimento do carro para medição de escala -verificar implementação
int tipo_vaga = 1;             // tipo da vaga, 1 = 90°, 2 = baliza, 3 = 45°
int direção;
/*
Futuramente será feito um método que freia o carro sozinho

Envia um sinal para que o motor pare
*/
void freia_sozinho()
{
}

int estaciona_90_graus(VL53L0X sensores)
{
  int done = 0;
  while (done != 1)
  {
    switch ()
    {
    case /* constant-expression */:
      /* code */
      break;

    default:
      break;
    }
  }
}

/*
  Verifica a unidade de medida do sensor

  Posteriormente irá setar tambvem levar a setar
  o valor de stage do carro em relação a vaga

*/
int verfica_sensor(VL53L0X sensor)
{
  if (sensor.timeoutOccurred())
  {
    Serial.print("TIMEOUT");
  }
  uint16_t dist = sensor.readRangeContinuousMillimeters();

  if (dist < 10)
  {
    Serial.print("Cuidado");
    return DANGER;
  }
  else if (dist >= 10 || dist < 30)
  {
    Serial.print("Distancia Ótima");
    return OK;
  }
  else if (dist > 30)
  {
    Serial.print("Tranquilo");
    return SAFE;
  }
}
float read_vaga()
{
}
int verifica_vaga(int tipo)
{
  // Implementar Outros tipos de vaga
  if (tipo == 1)
  { // Vaga 90°
    while (sensor.readRangeContinuousMillimeters() < 5000)
    {
      Serial.println("Continue a ré");
    }
    if (sensor.readRangeContinuousMillimeters() >= 5000)
    {
      state++;
      return 1;
    }
    else
    {
      return -1;
    }
  }
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
  switch (state)
  {
  case PRONTO:
    // se sinal de pronto tiver sido enviado muda estado para calibrando
    break;
  case CALIBRANDO:
    // Encontra o primeira variação de distancia grande
    verifica_vaga(tipo_vaga);
    break;
  case TURN:
    // Inicia a rotação das rotas até que o carro atinja angulo necessário (A ser testado) para proximo estágio
    gira_rodas();
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

  Serial.print("Sensor 1: ");
  Serial.print(dist1);

  Serial.print("\tSensor 2: ");
  Serial.println(dist2);

  delay(100);
}
