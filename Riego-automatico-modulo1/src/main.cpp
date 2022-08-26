#include <Arduino.h>
#include <Wire.h>

#include <SoftwareSerial.h>

const byte rxPin1 = 2;
const byte txPin1 = 3;

#define s1 0  //Sensor de humedad 1 conectado al pin A0
#define s2 1  //Sensor de humedad 1 conectado al pin A1
#define s3 2  //Sensor de humedad 1 conectado al pin A2
#define s4 3  //Sensor de humedad 1 conectado al pin A3
#define s5 4  //Sensor de humedad 1 conectado al pin A4

//#define int_pin 2

long hum1 = 0; //Humedad del sensor 1
long hum2 = 0; //Humedad del sensor 2
long hum3 = 0; //Humedad del sensor 3
long hum4 = 0; //Humedad del sensor 4
long hum5 = 0; //Humedad del sensor 5

int n = 5; //Ventana de muestreo
int i = 0; //variable de iteraciones

int hum_ideal = 80; //Porcentaje de humedad relativa ideal para el crecimiento de la huerta


// Set up a new SoftwareSerial object
SoftwareSerial Serial1 =  SoftwareSerial(rxPin1, txPin1);



void lec_hum()
{

  hum1 = 0; //Humedad del sensor 1
  hum2 = 0; //Humedad del sensor 2
  hum3 = 0; //Humedad del sensor 3
  hum4 = 0; //Humedad del sensor 4
  hum5 = 0;

  for(i = 0; i < n; i++)
  {
    hum1 += analogRead(s1); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s1
    hum2 += analogRead(s2); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s2
    hum3 += analogRead(s3); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s3
    hum4 += analogRead(s4); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s4
    //hum5 += analogRead(s5); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s5
 
    //hum1 = random(0,1000); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s1
    //hum2 = random(0,1000); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s2
    //hum3 = random(0,1000); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s3
    //hum4 = random(0,1023); //Acumula el valor de la lectura actual del sensor con las muestras anteriores de s4
    //hum5 = random(0,1023);

    delay(100);

  }

  hum1 = hum1/(n+1); //Filtro m¡promedio para obtener una lectura estable de s1
  hum2 = hum2/(n+1); //Filtro m¡promedio para obtener una lectura estable de s2
  hum3 = hum3/(n+1); //Filtro m¡promedio para obtener una lectura estable de s3
  hum4 = hum4/(n+1); //Filtro m¡promedio para obtener una lectura estable de s4
  //hum5 = hum5/(n+1); //Filtro m¡promedio para obtener una lectura estable de s5

  hum1 = map(hum1,0,1024,0,100); //Ajusta los valores de s1 de 0 - 1024 en un rango de 0 a 100%
  hum2 = map(hum2,0,1024,0,100); //Ajusta los valores de s2 de 0 - 1024 en un rango de 0 a 100% 
  hum3 = map(hum3,0,1024,0,100); //Ajusta los valores de s3 de 0 - 1024 en un rango de 0 a 100%
  hum4 = map(hum4,0,1024,0,100); //Ajusta los valores de s4 de 0 - 1024 en un rango de 0 a 100%
  //hum5 = map(hum5,0,1024,0,100); //Ajusta los valores de s5 de 0 - 1024 en un rango de 0 a 100%
  
  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial1.begin(9600);

  //pinMode(int_pin, INPUT);
  //attachInterrupt(digitalPinToInterrupt(int_pin), lec_hum, RISING);


}

void loop() {
  // put your main code here, to run repeatedly:
  //LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);  //Pone en modo ahorro de energía el arduino

  lec_hum();
  Serial.print('a');
  Serial.print(hum1);

  Serial.print('b');
  Serial.print(hum2);

  Serial.print('c');
  Serial.print(hum3);

  Serial.print('d');
  Serial.print(hum4);

  Serial1.print('a');
  Serial1.print(hum1);

  Serial1.print('b');
  Serial1.print(hum2);

  Serial1.print('c');
  Serial1.print(hum3);

  Serial1.print('d');
  Serial1.print(hum4);

}