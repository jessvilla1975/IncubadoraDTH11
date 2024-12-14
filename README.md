# Proyecto: Incubadora con Control de Temperatura

Este proyecto implementa una incubadora automatizada que utiliza un sistema de control de temperatura basado en un sensor DHT11. El sistema incluye un bombillo como fuente de calor, controlado mediante un dimmer y un relé. Cuando la temperatura supera los 35°C, el relé apaga el bombillo y un motor paso a paso ajusta la posición de la incubadora para estabilizar la temperatura.

---

## Características Principales
- **Control de Temperatura**: Monitorización en tiempo real usando un sensor DHT11.
- **Sistema de Calor**: El bombillo controlado por un dimmer se apaga automáticamente cuando la temperatura excede el umbral.
- **Visualización en LCD**: Información en tiempo real de la temperatura y el tiempo transcurrido.
- **Motor Paso a Paso**: Ajusta la posición interna para garantizar la distribución uniforme del calor.
- **Eficiencia Energética**: El sistema apaga el calor cuando no es necesario.

---

## Materiales Necesarios

### Componentes Electrónicos:
- Arduino Uno (o equivalente)
- Sensor de temperatura y humedad DHT11
- Relé de 5V
- Dimmer
- Bombillo (fuente de calor)
- Motor paso a paso 28BYJ-48 y controlador ULN2003
- Pantalla LCD I2C (16x2)
- Resistencias y cables de conexión

### Herramientas:
- Protoboard
- Fuente de alimentación (5V/12V según requerimientos)

---

## Diagrama de Conexión

1. **Sensor DHT11**:
   - Pin de datos conectado al pin digital 12 del Arduino.
2. **Relé**:
   - Controlado desde el pin digital 13 del Arduino.
   - Conecta y desconecta el bombillo.
3. **Dimmer**:
   - Controla la intensidad de luz del bombillo.
4. **Motor Paso a Paso**:
   - Conectado al módulo ULN2003 y controlado por los pines digitales 4, 5, 6, y 7 del Arduino.
5. **Pantalla LCD**:
   - Conectada mediante interfaz I2C (dirección 0x27).
### Circuito conexiones arduino
![Circuito arduino](https://github.com/user-attachments/assets/e82724d3-d74c-4231-bb2c-2f9f205fd350)

### Circuito conexiones bombillo, dimmer y relé
![circuito fuente de calor con dimmer](https://github.com/user-attachments/assets/73e89be7-1136-4ced-8f2a-a4aef24652cb)


---

## Instalación y Configuración
1. **Clona el repositorio**:
   ```bash
   git clone <URL-del-repositorio>
   ```
2. **Carga el código en el Arduino**:
   - Abre el archivo `.ino` en el IDE de Arduino.
   - Selecciona el puerto y la placa correspondiente.
   - Sube el código.
3. **Conexiones**:
   - Realiza las conexiones según el diagrama.
4. **Alimentación**:
   - Conecta los componentes a la fuente de energía correspondiente.

---

## Código Fuente
El código fuente está disponible en el archivo principal del proyecto y utiliza las siguientes bibliotecas:
- [DHT](https://github.com/adafruit/DHT-sensor-library): Para leer la temperatura y humedad.
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C): Para manejar la pantalla LCD.
- [Stepper](https://www.arduino.cc/en/reference/stepper): Para controlar el motor paso a paso.

---

## Funcionamiento
1. **Inicialización**:
   - Se muestra un mensaje en el LCD indicando que el sistema está iniciando.
2. **Monitoreo**:
   - La temperatura se mide continuamente.
   - Se muestra la temperatura y el tiempo transcurrido en el LCD.
3. **Control de Temperatura**:
   - Si la temperatura supera los 35°C, el relé apaga el bombillo y el motor regresa a su posición inicial.
   - Si la temperatura está por debajo del umbral, el motor gira y el relé enciende el bombillo.

---

## Mejoras Futuras
- Integración de sensores de humedad.
- Control del dimmer a través del Arduino para ajustar dinámicamente la intensidad del calor.
- Implementación de una interfaz gráfica para monitoreo remoto.

---

## Créditos
Desarrollado por Yessica Villa.

---

