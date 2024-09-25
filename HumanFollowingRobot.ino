//Final code 
#include <Servo.h>

// Define pins for IR sensors
const int irSensorLeft = 2;
const int irSensorRight = 3;

// Define pins for Ultrasonic sensor
const int trigPin = 4;
const int echoPin = 5;

// Define pins for Motors
const int motor1A = 7;
const int motor1B = 8;
const int motor2A = 9;
const int motor2B = 10;


Servo myServo;
// Define pins for servo Motors
const int servoPin = 6; 

// Define variables for distances
int distance = 0;
int thresholdDistance = 30;  // in cm

// Variables for IR sensors
int irLeft, irRight;

void setup() {
  // Set up motor pins
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  
  // Set up IR sensor pins
  pinMode(irSensorLeft, INPUT);
  pinMode(irSensorRight, INPUT);

  // Set up Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach servo motor
  myServo.attach(servoPin);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Get IR sensor readings
  irLeft = digitalRead(irSensorLeft);
  irRight = digitalRead(irSensorRight);
//Serial.println("irLeft");
//Serial.println(irLeft);
//Serial.println("irRight");
//Serial.println(irRight);
  // Get distance from ultrasonic sensor
  distance = getDistance();
Serial.println("distance");
Serial.println(distance);
  // Check if the distance is less than the threshold
  if (distance <= thresholdDistance) {
    // Determine direction based on IR sensor readings
    if (irLeft == LOW && irRight == HIGH) {
      // Move right
      Serial.println("right");
      moveRight();
    } else if (irLeft == HIGH && irRight == LOW) {
      // Move left
      Serial.println("left");
      moveLeft();
    } else if (irLeft == HIGH && irRight == HIGH) {
      // Move forward
      Serial.println("forward");
      moveForward();
    } else {
      // Stop the robot
      Serial.println("stop robot");
      stopRobot();
    }
  } else {
    // If no object is detected, rotate the servo motor to scan
    stopRobot();
    for (int pos = 0; pos <= 180; pos += 10) {
      myServo.write(pos);
      delay(500);
      distance = getDistance();
      if (distance <= thresholdDistance) {
        break;
      }
    }
  }
}

// Function to get distance from ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  //int distance = duration * 0.034 / 2;
  int distance = duration / 58.2; 
  return distance;
}

// Function to move forward
void moveForward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

// Function to move left
void moveLeft() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

// Function to move right
void moveRight() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

// Function to stop the robot
void stopRobot() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}
