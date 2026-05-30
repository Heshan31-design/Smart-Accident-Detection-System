// =====================================================
// SMART ACCIDENT DETECTION & EMERGENCY ALERT SYSTEM
// ESP32-S3 + MPU6050 + GPS + VIBRATION SENSOR
// =====================================================

// ---------------- BLYNK ----------------

#define BLYNK_TEMPLATE_ID "TMPL63ta0dT6Z"
#define BLYNK_TEMPLATE_NAME "Smart Accident Detection System"
#define BLYNK_AUTH_TOKEN "-CrvhlbY2KdoBFFfhoB94VXT940zccrR"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Heshan";
char pass[] = "Heshan0531";

// ---------------- LIBRARIES ----------------

#include <Wire.h>
#include <MPU6050.h>
#include <TinyGPS++.h>

// ---------------- OBJECTS ----------------

MPU6050 mpu;
TinyGPSPlus gps;

BlynkTimer timer;

// ---------------- PIN DEFINITIONS ----------------

// Vibration Sensor
#define VIBRATION_PIN 4

// LED
#define LED_PIN 13

// Buzzer
#define BUZZER_PIN 6

// GPS RX/TX
#define GPS_RX 16
#define GPS_TX 17

// ---------------- VARIABLES ----------------

int16_t ax, ay, az;

float totalAcceleration;

int vibrationValue;

float latitude;
float longitude;

// =====================================================
// SENSOR FUNCTION
// =====================================================

void sendSensorData() {

  // RESET OUTPUTS
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // =====================================================
  // MPU6050 READING
  // =====================================================

  mpu.getAcceleration(&ax, &ay, &az);

  totalAcceleration =
    sqrt((ax * ax) + (ay * ay) + (az * az)) / 16384.0;

  // =====================================================
  // VIBRATION SENSOR READING
  // =====================================================

  vibrationValue = digitalRead(VIBRATION_PIN);

  // =====================================================
  // GPS READING
  // =====================================================

  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }

  if (gps.location.isValid()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }

  // =====================================================
  // SERIAL MONITOR
  // =====================================================

  Serial.println("--------------------------------");

  Serial.print("Acceleration: ");
  Serial.println(totalAcceleration);

  Serial.print("Vibration: ");
  Serial.println(vibrationValue);

  Serial.print("Latitude: ");
  Serial.println(latitude, 6);

  Serial.print("Longitude: ");
  Serial.println(longitude, 6);

  // =====================================================
  // ✅ ALWAYS SEND VIBRATION DATA TO BLYNK (FIX)
  // =====================================================

  Blynk.virtualWrite(V3, vibrationValue);

  // =====================================================
  // ACCIDENT DETECTION
  // =====================================================

  if (totalAcceleration > 2.0 || vibrationValue == HIGH) {

    Serial.println("ACCIDENT DETECTED!");

    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    // BLYNK VALUES

    Blynk.virtualWrite(V0, "ACCIDENT DETECTED");
    Blynk.virtualWrite(V1, totalAcceleration);
    Blynk.virtualWrite(V2, latitude);

    // GOOGLE MAP LINK

    String locationLink =
      "https://www.google.com/maps?q=" +
      String(latitude, 6) + "," +
      String(longitude, 6);

    Blynk.logEvent(
      "accident_alert",
      "Accident Detected!\nLocation:\n" + locationLink
    );

    delay(3000);
  }

  // =====================================================
  // NORMAL CONDITION
  // =====================================================

  else {

    Serial.println("System Normal");

    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    Blynk.virtualWrite(V0, "NORMAL");
  }
}

// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  // GPS SERIAL
  Serial2.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);

  // MPU6050
  Wire.begin();

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 Connected");
  } else {
    Serial.println("MPU6050 Connection Failed");
  }

  // PIN MODES

  pinMode(VIBRATION_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // OUTPUTS OFF

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // BLYNK CONNECTION

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // TIMER

  timer.setInterval(1000L, sendSensorData);

  Serial.println("================================");
  Serial.println("SMART ACCIDENT DETECTION SYSTEM");
  Serial.println("System Started");
  Serial.println("================================");
}

// =====================================================
// LOOP
// =====================================================

void loop() {

  Blynk.run();
  timer.run();
}