#include <Wire.h>
#include "MPU6050_tockn.h"

MPU6050 mpu(Wire);

const int actuatorPin = 9; // Pino do atuador
const float desiredAngleX = 0.0; // Ângulo desejado no eixo X (zero)
const float Kp = 1.0; // Ganho proporcional

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true); // Calcular offsets do giroscópio
  pinMode(actuatorPin, OUTPUT); // Configurar pino do atuador como saída
}

void loop() {
  mpu.update(); // Atualizar os valores do sensor

  float currentAngleX = mpu.getAngleX(); // Obter o ângulo atual no eixo X
  float error = desiredAngleX - currentAngleX; // Calcular o erro
  float controlSignal = Kp * error; // Calcular o sinal de controle

  // Converter o sinal de controle para um valor PWM (0-255)
  int pwmValue = constrain(map(controlSignal, -90, 90, 0, 255), 0, 255);

  analogWrite(actuatorPin, pwmValue); // Enviar o sinal PWM para o atuador

  // Imprimir os valores para depuração
  Serial.print("Current Angle X: ");
  Serial.print(currentAngleX);
  Serial.print(" | Control Signal: ");
  Serial.println(controlSignal);

  delay(10); // Pequeno atraso para estabilidade
}