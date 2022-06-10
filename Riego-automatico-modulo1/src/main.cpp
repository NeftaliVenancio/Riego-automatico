#include <Arduino.h>
#include <Wire.h>
#include "LowPower.h"

#define s1 0  //Sensor de humedad 1 conectado al pin A0
#define s2 1  //Sensor de humedad 1 conectado al pin A1
#define s3 2  //Sensor de humedad 1 conectado al pin A2
#define s4 3  //Sensor de humedad 1 conectado al pin A3
#define s5 3  //Sensor de humedad 1 conectado al pin A4

#define int_pin 2

int hum1 = 0; //Humedad del sensor 1
int hum2 = 0; //Humedad del sensor 2
int hum3 = 0; //Humedad del sensor 3
int hum4 = 0; //Humedad del sensor 4
int hum5 = 0; //Humedad del sensor 5

int n = 5; //Ventana de muestreo
int i = 0; //variable de iteraciones

int hum_ideal = 80; //Porcentaje de humedad relativa ideal para el crecimiento de la huerta


void lec_hum()
{

  for(i = 0; i < n; i++)
  {
    hum1 += analogRead(s1);
    hum2 += analogRead(s2);
    hum3 += analogRead(s3);
    hum4 += analogRead(s4);
    hum5 += analogRead(s5);

    delay(100);
  }

  hum1 = hum1/(n+1);
  hum2 = hum2/(n+1);
  hum3 = hum3/(n+1);
  hum4 = hum4/(n+1);
  hum5 = hum5/(n+1);

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(int_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(int_pin), lec_hum, RISING);


}

void loop() {
  // put your main code here, to run repeatedly:

  
LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  //Pone en modo ahorro de energía el arduino


}