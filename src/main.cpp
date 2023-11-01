#include <Arduino.h>
#include <Wire.h>
#include "VL53L0X.h"
TwoWire I2Cone = TwoWire(0);
VL53L0X sensor;
VL53L0X sensor2;
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
  //I2Cone.begin(21, 22, 921600); // Configuração de pinos para I2C gpio 21 e 22
  //sensor.setBus(&I2Cone);       // Leitor do sensor configurado para o barramento de entrada I2C

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
  sensor.startContinuous();
  sensor2.startContinuous();
}

void loop()
{
  uint16_t dist1 =sensor.readRangeContinuousMillimeters();
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  
  uint16_t dist2 = sensor2.readRangeContinuousMillimeters();
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.print("Sensor 1: ");
  Serial.print(dist1);
  
  Serial.print("\tSensor 2: ");
  Serial.println(dist2);

  delay(100);
}
