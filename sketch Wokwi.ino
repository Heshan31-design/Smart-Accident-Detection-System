// =====================================================
// SMART ACCIDENT DETECTION SYSTEM (WOKWI + BLYNK)
// =====================================================

// ---------------- BLYNK ----------------

#define BLYNK_TEMPLATE_ID "TMPL6ehd7L1rc"
#define BLYNK_TEMPLATE_NAME "Smart Accident Detection System Wokwi"
#define BLYNK_AUTH_TOKEN "5kogfLZXxfkN5HIv9BE0RULBYQboLDYd"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// WiFi (Wokwi)
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// ---------------- LIBRARIES ----------------

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// ---------------- PIN DEFINITIONS ----------------

// Ultrasonic Sensor
#define TRIG_PIN 5
#define ECHO_PIN 18

// Potentiometer
#define POT_PIN 4

// LED
#define LED_PIN 13

// Buzzer
#define BUZZER_PIN 12

// ---------------- VARIABLES ----------------

float ax, ay, az;

int potValue = 0;
long duration;
int distance;

// =====================================================

void setup() {

  Serial.begin(115200);

  // Blynk Start
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // MPU6050 Setup
  if (!mpu.begin()) {
    Serial.println("MPU6050 NOT FOUND!");
    while (1);
  }

  Serial.println("MPU6050 Connected!");

  // Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Output Devices
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("System Started...");
}

// =====================================================

void loop() {

  Blynk.run();  // IMPORTANT

  // Turn OFF outputs initially
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // ---------------- MPU6050 ----------------

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;

  float totalAcceleration = sqrt(ax * ax + ay * ay + az * az);

  // ---------------- POTENTIOMETER ----------------

  potValue = analogRead(POT_PIN);

  // ---------------- ULTRASONIC SENSOR ----------------

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // ---------------- SERIAL MONITOR ----------------

  Serial.println("------------------------");

  Serial.print("Acceleration: ");
  Serial.println(totalAcceleration);

  Serial.print("Potentiometer: ");
  Serial.println(potValue);

  Serial.print("Distance: ");
  Serial.println(distance);

  // ---------------- SEND DATA TO BLYNK ----------------

  Blynk.virtualWrite(V1, totalAcceleration); // MPU6050
  Blynk.virtualWrite(V2, distance);          // Ultrasonic
  Blynk.virtualWrite(V3, potValue);          // Potentiometer

  // ---------------- ACCIDENT LOGIC ----------------

  bool accident = false;

  if (potValue > 3000) {
    Serial.println("High Vibration Detected!");
    accident = true;
  }

  if (totalAcceleration > 18) {
    Serial.println("Sudden Movement Detected!");
    accident = true;
  }

  // ---------------- OUTPUT CONTROL ----------------

  if (accident) {

    Serial.println("ACCIDENT DETECTED!");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Blynk.virtualWrite(V0, "ACCIDENT DETECTED");

  } else {

    Blynk.virtualWrite(V0, "NORMAL");
  }

  // ---------------- OBSTACLE DETECTION ----------------

  if (distance < 15) {

    Serial.println("Obstacle Detected!");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);
}