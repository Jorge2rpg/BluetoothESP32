//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <Arduino.h>

#define LED 2


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

int estado_anterior = HIGH;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  
  while(SerialBT.available()){
    int comando;
    comando = SerialBT.read();
    SerialBT.write(comando);

    if(comando == '1'){

      int estado_atual = digitalRead(LED);

      if(estado_atual != estado_anterior)
      {
        digitalWrite(LED, estado_anterior);
        estado_anterior = estado_atual;

        if(estado_atual == HIGH)
        {
          SerialBT.println("Led off pai!");
        }
        else
        {
          SerialBT.println("Led on pai!");
        }
      }
  }

  delay(30);
  }
}