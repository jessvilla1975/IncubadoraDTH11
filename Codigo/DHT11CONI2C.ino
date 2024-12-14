#include <Wire.h>      
           
#include <LiquidCrystal_I2C.h>
    
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "DHT.h"
#define DHTPIN 12 
#define DHTTYPE DHT11 //DHT22
DHT dht(DHTPIN, DHTTYPE);
int rele=13;
int vcc= 11; //crear pines de 5v

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(rele,OUTPUT);
  pinMode(vcc,OUTPUT);
  dht.begin();
}
void loop() { 

digitalWrite(vcc,HIGH);
int h = dht.readHumidity();    // Lee la humedad
int t= dht.readTemperature();

lcd.clear();//Elimina todos los simbolos del LCD
lcd.setCursor(0,0);//Posiciona la primera letra despues del segmento 5 en linea 1              
lcd.print("Humedad: ");
lcd.setCursor(8,0);
lcd.print(h);//Escribe la humedad
lcd.print("%");                     
             
lcd.setCursor(0,1);
lcd.print("Temperatura: "); 
lcd.setCursor(12,1);
lcd.print(t);//Escribe la temperatura
lcd.print("C");                   
delay (500);

if(t>35)
{
  digitalWrite(rele,LOW);
  lcd.clear();

  }
  else
  {
    digitalWrite(rele,HIGH);
    }
}
