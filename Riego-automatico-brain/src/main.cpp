#include <Arduino.h>

#include <SPI.h> 
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
int i = 0;
int t_regado = 5;

int l_rojo = 13;
int l_azul = 12;

int valvula1 = 6;
int valvula2 = 7;

int c_dis = 1;
int next = 10;
int home = 9;
int prev = 8;

int m = 9; //Promedio cama 1
int n = 10; //Promedio cama 2

int sa = 0;
int sb = 0;
int sc = 0;
int sd = 0;

int sf = 0;
int sg = 0;
int sh = 0;
int si = 0;

int dato = 0;

int humedad_ideal = 80;
int humedad_min = 60;

void p_inicio()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Sistema de riego");
  

  lcd.setCursor(1, 3);
  lcd.print("<-");
  lcd.setCursor(10, 3);
  lcd.print("O");
  lcd.setCursor(18, 3);
  lcd.print("->");
}

void p_general()
{

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Humedad Cama 1: ");
  lcd.print(m);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Humedad Cama 2: ");
  lcd.print(n);
  lcd.print("%");

  lcd.setCursor(1, 3);
  lcd.print("<-");
  lcd.setCursor(10, 3);
  lcd.print("O");
  lcd.setCursor(18, 3);
  lcd.print("->");
}

void p_cama1()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Sensores Cama 1 ");

    // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
  lcd.print("S1 = ");
  lcd.print(sa);

  lcd.setCursor(9,1);
  lcd.print("S2 = ");
  lcd.print(sb);

  lcd.setCursor(0,2);
  lcd.print("S3 = ");
  lcd.print(sc);

  lcd.setCursor(9,2);
  lcd.print("S4 = ");
  lcd.print(sd);

}

void p_cama2()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Sensores Cama 2 ");

    // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.setCursor(0, 1);
  lcd.print("S1 = ");
  lcd.print(sf);

  lcd.setCursor(9,1);
  lcd.print("S2 = ");
  lcd.print(sg);

  lcd.setCursor(0,2);
  lcd.print("S3 = ");
  lcd.print(sh);

  lcd.setCursor(9,2);
  lcd.print("S4 = ");
  lcd.print(si);

}

void p_time()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Ultima irrigacion");
  

  lcd.setCursor(1, 3);
  lcd.print("<-");
  lcd.setCursor(10, 3);
  lcd.print("O");
  lcd.setCursor(18, 3);
  lcd.print("->");
}

void p_creditos1()
{
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Hecho con <3 por:");
  lcd.setCursor(2, 2);
  lcd.print(" --------------->");
  lcd.setCursor(1, 3);
  lcd.print("<-");
  lcd.setCursor(10, 3);
  lcd.print("O");
  lcd.setCursor(18, 3);
  lcd.print("->");
}

void p_creditos2()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Karla  Lillian G.");
  lcd.setCursor(0, 1);
  lcd.print("Pablo S.  Diego R.");
  lcd.setCursor(0, 2);
  lcd.print("Daniela M.");

  lcd.setCursor(1, 3);
  lcd.print("<-");
  lcd.setCursor(10, 3);
  lcd.print("O");
  lcd.setCursor(18, 3);
  lcd.print("->");
}

void lec_boton()
{

    if(digitalRead(prev))
  {

    while (digitalRead(prev))
    {

    }

      if (c_dis == 1)
      {
        c_dis = 7;
      }
      else
      {
        c_dis--;
      }

      digitalWrite(l_azul,LOW);
      delay(100);
  }

if(digitalRead(next))
  {

    while (digitalRead(next))
    {

    }
      if (c_dis == 7)
      {
        c_dis = 1;
      }
      else
      {
        c_dis++;
      }

      digitalWrite(l_azul,LOW);
      delay(100);
  }

  if(digitalRead(home))
  {

    while (digitalRead(home))
    {

    }
    c_dis = 1;

      digitalWrite(l_azul,LOW);
      delay(100);
  }


}

void regado_cama1()
{

  digitalWrite(l_rojo,HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Secuencia de regado");
  lcd.setCursor(0, 1);
  lcd.print("cama 1, espere");

  digitalWrite(valvula1,HIGH);

  i = t_regado;

  while (i > 0)
  {
    lcd.setCursor(7, 2);
    lcd.print(i);
    lcd.print(" Segundos");
    delay(1000);
    i--;
  }
  
  
  digitalWrite(l_rojo,LOW);
  digitalWrite(valvula1,LOW);

}

void regado_cama2()
{

  digitalWrite(l_rojo,HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Secuencia de regado");
  lcd.setCursor(0, 1);
  lcd.print("cama 2, espere");

  digitalWrite(valvula2,HIGH);

  i = t_regado;

  while (i > 0)
  {
    lcd.setCursor(7, 2);
    lcd.print(i);
    lcd.print(" Segundos");
    delay(1000);
    i--;
  }
  
  digitalWrite(l_rojo,LOW);
  digitalWrite(valvula2,LOW);

}

void setup() {

  pinMode(l_azul,OUTPUT);
  pinMode(l_rojo,OUTPUT);
  pinMode(valvula1,OUTPUT);
  pinMode(valvula2,OUTPUT);

  pinMode(next,INPUT);
  pinMode(home,INPUT);
  pinMode(prev,INPUT);

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
  
  digitalWrite(l_azul,HIGH);

  lec_boton();

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

    case 'd': 
              sd = Serial1.parseInt();
      break;

    case 'm': 
              m = Serial1.parseInt();
      break;

    default:
      break;
  }

    Serial2.listen();

     if(Serial2.available()>0)
  {
    dato = Serial2.read();
    Serial.println(dato);
  }

  switch (dato)
  {
    case 'f': 
              sf = Serial2.parseInt();
      break;
    
    case 'g': 
              sg = Serial2.parseInt();
      break;

    case 'h': 
              sh = Serial2.parseInt();
      break;

    case 'i': 
              si = Serial2.parseInt();
      break;

    case 'n': 
              n = Serial2.parseInt();
      break;

    default:
      break;
  }


  if (m < humedad_min)
  {
    regado_cama1();
  }

  if (n < humedad_min)
  {
    regado_cama2();
  }
  
  


  switch (c_dis)
  {
  case (1):
            p_inicio();
    break;
  
  case (2):
            p_general();
    break;

  case (3):
            p_cama1();
    break;

  case (4):
            p_cama2();
    break;

  case (5):
            p_time();
    break;
  
  case (6):
            p_creditos1();
    break;

  case (7):
            p_creditos2();
    break;
  
  default:
            p_general();
    break;
  }

  delay(100);
}