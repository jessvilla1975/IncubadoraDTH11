#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 12
#define DHTTYPE DHT11 // DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configuración de los pasos del motor
const int stepsPerRevolution = 2048; // Pasos por revolución (28BYJ-48)

DHT dht(DHTPIN, DHTTYPE);
int rele = 13;
int vcc = 11; // Pin de alimentación

// Pines de conexión al módulo ULN2003
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

// Crear objeto Stepper
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Variable para rastrear la posición actual del motor
int posicionActual = 0;

// Variables para el tiempo
unsigned long tiempoInicio = 0;
unsigned long tiempoTranscurrido = 0;

void mesajeInicio(){
  lcd.clear(); // Limpia el LCD
  lcd.setCursor(0, 0);
  lcd.print("Iniciando");
  lcd.setCursor(14, 0);  // Posición de la columna 10, fila 1
  lcd.write(0);          // Imprimir el primer carácter personalizado
  lcd.write(1);          // Imprimir el segundo carácter personalizado
  lcd.setCursor(14, 1);  // Posición de la columna 10, fila 1
  lcd.write(2);          // Imprimir el tercer carácter personalizado
  lcd.write(3);          // Imprimir el cuarto carácter personalizado
  delay(1000);  // Espera 1 segundo antes de continuar
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(rele, OUTPUT);
  pinMode(vcc, OUTPUT);
  dht.begin();

  // Crear caracteres personalizados
  uint8_t char0[] = {0x1F, 0x10, 0x10, 0x10, 0x10, 0x17, 0x14, 0x14};  // Ejemplo de carácter
  uint8_t char1[] = {0x1F, 0x07, 0x07, 0x07, 0x07, 0x1F, 0x03, 0x03};  // Ejemplo de carácter
  uint8_t char2[] = {0x1C, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x00, 0x00};  // Ejemplo de carácter
  uint8_t char3[] = {0x03, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x00, 0x00};  // Ejemplo de carácter
  
  lcd.createChar(0, char0);  // Crear el primer carácter
  lcd.createChar(1, char1);  // Crear el segundo carácter
  lcd.createChar(2, char2);  // Crear el tercer carácter
  lcd.createChar(3, char3);  // Crear el cuarto carácter

  // Configurar la velocidad del motor (en RPM)
  myStepper.setSpeed(15);
  Serial.begin(9600);
  Serial.println("Motor iniciado. Girando en un solo sentido...");

  // Registrar el tiempo de inicio
  tiempoInicio = millis(); // Almacena el tiempo en milisegundos desde que el programa comenzó
  posicionActual = 0;

  // Mostrar mensaje de inicio
  mesajeInicio();  // Muestra el mensaje de inicio
}

void loop() {
  digitalWrite(vcc, HIGH);

  // Calcular el tiempo transcurrido
  tiempoTranscurrido = millis() - tiempoInicio;

  // Convertir tiempo transcurrido a horas, minutos y segundos
  unsigned long segundos = (tiempoTranscurrido / 1000) % 60;
  unsigned long minutos = (tiempoTranscurrido / 1000 / 60) % 60;
  unsigned long horas = (tiempoTranscurrido / 1000 / 60 / 60);

  int t = dht.readTemperature(); // Lee la temperatura

  lcd.clear(); // Limpia el LCD
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(horas);
  lcd.print("h ");
  lcd.print(minutos);
  lcd.print("m ");
  lcd.print(segundos);
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("C");
  delay(500);

  if (t > 35) {
    // Apagar el relé
    digitalWrite(rele, LOW);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Estabilizar ");
    lcd.setCursor(2, 1);
    lcd.print("Temperatura ");
    delay(1000); // Pausa para mostrar mensaje

    // Regresar a la posición inicial
    Serial.println("Temperatura alta, regresando a posición inicial...");
    myStepper.step(-posicionActual); // Pasos en dirección opuesta
    posicionActual = 0;             // Resetear la posición actual

  } else {
    // Girar el motor hacia adelante
    Serial.println("Motor girando...");
    myStepper.step(100); // Mueve 100 pasos hacia adelante
    posicionActual += 100; // Actualiza la posición actual

    // Activa el relé
    digitalWrite(rele, HIGH);
  }
}
