#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X.h"
TwoWire I2Cone = TwoWire(0);
VL53L0X sensor;
uint16_t valor;

void setup()
{
  Serial.begin(921600);
  I2Cone.begin(21,22,921600); // Configuração de pinos para I2C gpio 21 e 22
  sensor.setBus(&I2Cone);     //Leitor do sensor configurado para o barramento de entrada I2C

  sensor.setTimeout(50);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void loop()
{
  delay(100);
  valor= sensor.readRangeContinuousMillimeters();
  Serial.println(valor);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}
