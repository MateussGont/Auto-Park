#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X.h"

// Pipeline para entrar na vaga 180°
#define PRONTO 0       // botão start apertado e inicio dos sensores
#define CALIBRANDO 1   // sensor traseiro identifica o inicio do carro ao lado e quando encontrado inicia o proximo estágio
#define VOL_DIREITA 2  // Volante se vira todo para a direita e é feito uma medição de distancia percorrida
#define VOL_CENTRO 3   // apoós uma certa distancia percorrida o volante volta ao centro e anda mais uma certa distancia
#define VOL_ESQUERDA 4 // após identificado outra distancia percorrida se passa para o proximo estágio
#define VOL_INICIAL 5  // volante volta ao centro e usuário termina com ajustes finos

TwoWire I2Cone = TwoWire(0);
VL53L0X sensor_direita_frente;
VL53L0X sensor_direita_tras;
VL53L0X sensor_traseiro;
VL53L0X sensor_esquerda_frente;
VL53L0X sensor_esquerda_tras;
uint16_t valor;

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

  sensor_direita_frente.setTimeout(50);
  if (!sensor_direita_frente.init())
  {
    Serial.println("Failed to detect and initialize sensor 1!");
    while (1)
    {
    }
  }
  sensor_direita_frente.setAddress((uint8_t)22);
  delay(100);
  digitalWrite(17, HIGH);

  if (!sensor_direita_tras.init())
  {
    Serial.println("Failed to detect and initialize sensor 2!");
    while (1)
    {
    }
  }

  sensor_direita_tras.setAddress((uint8_t)25);
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor_direita_frente.startContinuous();
  sensor_direita_tras.startContinuous();
}

void loop()
{
  uint16_t dist1 = sensor_direita_frente.readRangeContinuousMillimeters();
  if (sensor_direita_frente.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  uint16_t dist2 = sensor_direita_tras.readRangeContinuousMillimeters();
  if (sensor_direita_tras.timeoutOccurred())
  {
    Serial.print(" TIMEOUT");
  }

  Serial.print("Sensor 1: ");
  Serial.print(dist1);

  Serial.print("\tSensor 2: ");
  Serial.println(dist2);

  delay(100);
}
