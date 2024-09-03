#include <Servo.h>

// Defines the pins for the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;

// Variables for the duration and the distance
long duration;
int distance;

// Define distance threshold (e.g., 200 cm for 2 meters)
const int DISTANCE_THRESHOLD = 200;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  
  Serial.begin(9600);
}

void loop() {
  // Measure the distance
  distance = calculateDistance();
  
  // Send the distance value to the Serial Monitor
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
  
  delay(1000); // Delay for 1 second before the next measurement
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  int distance = duration * 0.034 / 2;
  return distance;
}
