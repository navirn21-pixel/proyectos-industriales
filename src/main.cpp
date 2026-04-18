#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();
    pinMode(11, OUTPUT); // Verde
    pinMode(12, OUTPUT); // Amarillo
    pinMode(13, OUTPUT); // Rojo
    pinMode(8, OUTPUT);  // Zumbador
}

void apagarTodo() {
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);
}

void loop() {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();
    
    Serial.print("Temp: ");
    Serial.print(temp);
    Serial.print("C | Hum: ");
    Serial.println(hum);
    
    apagarTodo();
    
    if (temp < 25) {
        digitalWrite(11, HIGH); // Verde — normal
    } else if (temp < 30) {
        digitalWrite(12, HIGH); // Amarillo — advertencia
    } else if (temp < 40) {
        digitalWrite(13, HIGH); // Rojo — crítico
    } else {
        digitalWrite(13, HIGH); // Rojo + zumbador — emergencia
        digitalWrite(8, HIGH);
        delay(500);
        digitalWrite(8, LOW);
    }
    delay(2000);
}