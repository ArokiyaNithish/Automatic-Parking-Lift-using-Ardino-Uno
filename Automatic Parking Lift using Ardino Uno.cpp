// Arduino code for automatic parking system made by Arokiya Nithish
#include <Servo.h>
#include <NewPing.h> // Ultrasonic sensor library

const int IRSensor = 9; // Connect IR sensor module to Arduino pin 9
const int motorSpeed = 150; // Set motor speed (adjust as needed)
const int ultrasonicTrigPin = 6; // Ultrasonic sensor TRIG pin
const int ultrasonicEchoPin = 7; // Ultrasonic sensor ECHO pin
const int motorEnablePin = 10; // Connect L296 motor driver enable pin to Arduino pin 10
const int motorDirectionPin1 = 11; // Connect L296 motor driver direction pin 1 to Arduino pin 11
const int motorDirectionPin2 = 12; // Connect L296 motor driver direction pin 2 to Arduino pin 12
const int DISTANCE_THRESHOLD1 = 172; // centimeters
const int TRIG_PIN = 1; // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN = 2; // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_PIN = 3; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD2 = 50; // centimeters
const int motorForwardPin = 6; // Connect to L298N input 1
const int motorBackwardPin = 7; // Connect to L298N input 2
const int enablePin = 5; // Connect to L298N enable pin (PWM)
const int trigPin = 9;
const int echoPin = 10;
NewPing sonar(trigPin, echoPin);
Servo servo; // create servo object to control a servo

float duration_us, distance_cm;
float duration_us2, distance_cm2;

void setup() {
    pinMode(IRSensor, INPUT); // Set IR Sensor pin as INPUT
    pinMode(ultrasonicTrigPin, OUTPUT); // Set ultrasonic sensor TRIG pin as OUTPUT
    pinMode(ultrasonicEchoPin, INPUT); // Set ultrasonic sensor ECHO pin as INPUT
    pinMode(motorEnablePin, OUTPUT); // Set motor driver enable pin as OUTPUT
    pinMode(motorDirectionPin1, OUTPUT); // Set motor driver direction pin 1 as OUTPUT
    pinMode(motorDirectionPin2, OUTPUT); // Set motor driver direction pin 2 as OUTPUT
    pinMode(TRIG_PIN, OUTPUT); // set Arduino pin to output mode
    pinMode(ECHO_PIN, INPUT); // set Arduino pin to input mode
    servo.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object
    servo.write(0); // initialize servo position to 0 degrees
    Serial.begin(9600); // Initialize Serial at 9600 Baud
    pinMode(motorForwardPin, OUTPUT);
    pinMode(motorBackwardPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    analogWrite(enablePin, 150); // Range: 0 (stopped) to 255 (full speed)
    }

void loop() 
{
    // IR sensor detection
    int motionDetected = digitalRead(IRSensor);
    int distance = sonar.ping_cm(); // Corrected line

    // Ultrasonic sensor detection
    digitalWrite(ultrasonicTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigPin, LOW);
    duration_us = pulseIn(ultrasonicEchoPin, HIGH);
    distance_cm = 0.017 * duration_us;

    // Generate a 10-microsecond pulse to TRIG pin
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure duration of pulse from ECHO pin
    duration_us2 = pulseIn(ECHO_PIN, HIGH);

    // Calculate the distance
    distance_cm2 = 0.017 * duration_us;

// ir sensor dectection 
if (digitalRead(IRSensor) == HIGH) 
{  
    {
      Serial.println("Car is detected!"); // Print message to serial monitor
      digitalWrite(motorDirectionPin1, HIGH);// Set motor direction (adjust according to your motor driver)
      digitalWrite(motorDirectionPin2, LOW);
      analogWrite(motorDirectionPin1, motorSpeed);
      digitalWrite(motorEnablePin, LOW);// Enable motor (adjust HIGH/LOW based on motor driver configuration)
      delay(2000); // 2 seconds (delay before next detection)
    } 

  // Stop the motor (both directions) using ultrasonic senor by the distance of 172cm   
  if (distance_cm < DISTANCE_THRESHOLD1) 
    {
      digitalWrite(motorDirectionPin1, LOW);
      digitalWrite(motorDirectionPin2, LOW);
      digitalWrite(motorEnablePin, LOW);
      Serial.print("first floor!");// Print the value to Serial Monitor
      delay(200); // Delay for stability
    }
      
  if (distance_cm2 > DISTANCE_THRESHOLD2) 
   {
      servo.write(0); // Rotate servo motor to 0 degrees
      Serial.print("There is Free Space!");
      delay(5); // Wait for a moment before the next measurement
       
      //the convery motor to run the dection  of ultrasonic sensor
      digitalWrite(motorForwardPin, HIGH);
      delay(1200); // 2 minutes in milliseconds
      digitalWrite(motorForwardPin, LOW); // to Stop
      delay(1000); // Pause for 1 second

      // Move backward for 2 minutes
      digitalWrite(motorBackwardPin, HIGH);
      delay(120000); // 2 minutes in milliseconds
      digitalWrite(motorBackwardPin, LOW);// Stop
    } 
  
  else if (distance_cm2 < DISTANCE_THRESHOLD2)
  {
      servo.write(90); // Rotate servo motor to 0 degrees
      delay(5); // Wait for a moment before the next measurement
  }
}     

else 
  {
        Serial.println(" "); // Print message to serial monitor
        // Disable motor
        digitalWrite(motorEnablePin, LOW);
  }
}
   
    