#include <Wire.h>
#include <LiquidCrystal.h>

// Define the analog input pins for the sensors
const int tempSensorPin = A0;
const int forceSensorPin = A1;
const int trigPin = 3;
const int echoPin = 4;
const int buzzerPin = 10;

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(forceSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Ultrasonic Sensor
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  // Force Sensor
  int forceSensorValue = analogRead(forceSensorPin);
  int mappedForceValue = map(forceSensorValue, 0, 1023, 0, 255);
  
  // Temperature Sensor
  int tempSensorValue = analogRead(tempSensorPin);
  float voltage = tempSensorValue * (5.0 / 1023.0);
  float temperatureCelsius = (voltage - 0.5) * 100.0;
  
  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
  
  lcd.setCursor(0, 1);
  lcd.print("Force: ");
  lcd.print(mappedForceValue);
  
  lcd.setCursor(9, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureCelsius);
  lcd.print(" C");
  
  // Display data on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, ");
  
  Serial.print("Force: ");
  Serial.print(mappedForceValue);
  Serial.print(", ");
  
  Serial.print("Temperature: ");
  Serial.print(temperatureCelsius);
  Serial.println(" C");
  
  // Activate/deactivate buzzer based on force sensor value
  if (mappedForceValue > 100) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }
  
  delay(1000); // Adjust delay as needed
}
