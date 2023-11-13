#include <SPI.h>
//#include <Servo.h>
//Servo myservo;
#include "SoftwareSerial.h"
SoftwareSerial mySerial(2, 3); // broches TX, RX

// Définir les broches
//#define SERVO 9
#define SS_PIN 10   // Broche Slave Select
#define MOSI_PIN 11 // Broche MOSI
#define MISO_PIN 12 // Broche MISO
#define SCK_PIN 13  // Broche SCK

// Constantes pour la sensibilité du gyroscope et la plage maximale
const float GYRO_SENSITIVITY = 0.01; // Sensibilité du gyroscope en LSB/(°/s)
const float GYRO_MAX_RANGE = 2000;   // Plage maximale du gyroscope en °/s
#define PI 3.14159265358979323846
const int SPI_CLOCK_SPEED = 1000000;

// Variables pour stocker les données du gyroscope
int gyroData;
int gyroData2;
double gyroReading = 0;

// Variables pour la moyenne glissante
const int numReadings = 100;      // Nombre de lectures pour la moyenne glissante
float gyroReadings[numReadings]; // Tableau pour stocker les lectures du gyroscope
int gyroIndex = 0;                // Index de la lecture actuelle
float gyroTotal = 0;              // Total des lectures du gyroscope
float gyroCalibre = 0.0065; 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  //myservo.attach(SERVO);
  // Initialiser l'interface SPI
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(SPI_CLOCK_SPEED, MSBFIRST, SPI_MODE0));

  // Configurer le gyroscope
  delay(100);
  SPI.transfer16(0x2000); // Définir la plage complète à +/- 2000 degrés/sec
  SPI.transfer16(0x0003); // Activer le filtre passe-haut du gyroscope
  delay(150);
}

void loop() {
  //myservo.write(45);
  digitalWrite(SS_PIN, LOW);

  // Lire les données du gyroscope via SPI
  gyroData = SPI.transfer(0x20);
  gyroData = gyroData << 8 | SPI.transfer(0x00);
  gyroData2 = SPI.transfer(0x00) >> 2;
  SPI.transfer(0x00);
  gyroData = gyroData << 6 | gyroData2;

  gyroReading = (gyroReading)*0.000001 + gyroData * (1 - 0.000001); // Filtre passe-bas

  // Conversion des LSB en rad/s
  float gyroInRadPerSec = gyroReading * GYRO_SENSITIVITY * PI / 180.0;

  // Calcul de la moyenne glissante
  gyroTotal = gyroTotal - gyroReadings[gyroIndex];
  gyroReadings[gyroIndex] = gyroInRadPerSec;
  gyroTotal = gyroTotal + gyroReadings[gyroIndex];

  gyroIndex++;
  if (gyroIndex >= numReadings) {
    gyroIndex = 0;
  }

  float gyroMovingAverage = (gyroTotal / numReadings) - gyroCalibre; // Moyenne glissante

  //Serial.print("Gyro Moving Average: ");
  mySerial.println(gyroInRadPerSec, 7);
  Serial.println(gyroMovingAverage, 7);

  digitalWrite(SS_PIN, HIGH);
  delay(200);
}
