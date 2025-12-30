/* *************************************************************************************************
 * Project:               UART_Fingerprint_Sensor_ESP32
 * Author:                Waveshare Team (Adapté pour ESP32)
 * Module:                UART Fingerprint Sensor (C)
 * Development Board:     ESP32
 * Working Voltage:       3.3V (IMPORTANT: 3.3V uniquement)
 * Pins connection:       VCC:3.3V; GND:GND; RX: GPIO16; TX:GPIO17; RST: GPIO4; WAKE: GPIO5
 * *************************************************************************************************
 * Target: Add fingerprint, fingerprint comparing, delete fingerprint
 * Version: V2.0 - ESP32 Pure
 * Modification: Adaptation complète pour ESP32 avec UART matériel (Serial2)
 * *************************************************************************************************
 * Note: Code original fourni par Waveshare Team, adapté pour ESP32 par Mike.
 * Utilise l'UART matériel Serial2 au lieu de SoftwareSerial.
 * *************************************************************************************************
 */

#include "finger.h"
 
void setup() {
  // Initialisation de la communication série avec le PC
  Serial.begin(115200);
  delay(1000);  // Délai pour permettre l'initialisation
  
  // LED intégrée sur ESP32 (GPIO 2 sur la plupart des cartes)
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  
  // Configuration des pins RST et WAKE
  pinMode(Finger_RST_Pin, OUTPUT);
  digitalWrite(Finger_RST_Pin, HIGH);
 
  pinMode(Finger_WAKE_Pin, INPUT);

  // Initialisation de l'UART matériel Serial2 pour le capteur
  Finger_UART_Init(); 
  delay(1000);

  Finger_Wait_Until_OK();
}

void loop() {
  // put your main code here, to run repeatedly:
  Analysis_PC_Command();
  if(Finger_SleepFlag == 1)
  {
    Auto_Verify_Finger();
  } 
}
