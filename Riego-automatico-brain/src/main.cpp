#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SoftwareSerial.h>

const byte rxPin1 = 2;
const byte txPin1 = 3;

const byte rxPin2 = 4;
const byte txPin2 = 5;


// Set up a new SoftwareSerial object
SoftwareSerial Serial1 =  SoftwareSerial(rxPin1, txPin1);

SoftwareSerial Serial2 =  SoftwareSerial(rxPin2, txPin2);

//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27,20,4);  //

int sa = 0;
int sb = 0;
int sc = 0;

int dato = 0;


void pinicio()
{
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("Sistema de riego")
  
}


void setup() {

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  // Inicializar el LCD
  lcd.init();
  
  //Encender la luz de fondo.
  lcd.backlight();
  
  // Escribimos el Mensaje en el LCD.
  lcd.print("  Riego Automatico");
}

void loop() {

  Serial1.listen();

  if(Serial1.available()>0)
  {
    dato = Serial1.read();
    Serial.println(dato);
    
  }

  switch (dato)
  {
    case 'a': 
              sa = Serial1.parseInt();
      break;
    
    case 'b': 
              sb = Serial1.parseInt();
      break;

    case 'c': 
              sc = Serial1.parseInt();
      break;
    
    default:
      break;

  }

   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 0);
   // Escribimos el número de segundos trascurridos
  lcd.print("Sa = ");
  lcd.print(sa);
  lcd.setCursor(9,1);
  lcd.print("Sb = ");
  lcd.print(sb);
  lcd.setCursor(0,2);
  lcd.print("Sc = ");
  lcd.print(sc);

  

  delay(100);
}