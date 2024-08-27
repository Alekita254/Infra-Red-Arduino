#include <Servo.h> 

// Defines the pins for the Ultrasonic Sensor, LEDs, and PIR sensor
const int trigPin = 10;
const int echoPin = 11;
const int ledPin = 7;
const int pirPin = 4;

// Variables for the duration and the distance
long duration;
int distance;

// Servo object for controlling the servo motor
Servo myServo;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  pinMode(ledPin, OUTPUT);  // Sets the ledPin as an Output
  pinMode(pirPin, INPUT);   // Sets the pirPin as an Input
  
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin the servo motor is attached
}

void loop() {
  int pirState = digitalRead(pirPin); // Reads the state of the PIR sensor

  if (pirState == HIGH) { // If motion is detected
    digitalWrite(ledPin, HIGH); // Turns on the LED

    // Rotates the servo motor from 15 to 165 degrees
    for(int i = 15; i <= 165; i++){  
      myServo.write(i);
      delay(30);
      distance = calculateDistance(); // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
      
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      Serial.print(distance); // Sends the distance value into the Serial Port
      Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    }

    // Repeats the previous lines from 165 to 15 degrees
    for(int i = 165; i > 15; i--){  
      myServo.write(i);
      delay(30);
      distance = calculateDistance();
      Serial.print(i);
      Serial.print(",");
      Serial.print(distance);
      Serial.print(".");
    }
  } else {
    digitalWrite(ledPin, LOW); // Turns off the LED if no motion is detected
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}
