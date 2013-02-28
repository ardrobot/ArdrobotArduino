#include "Arduino.h"
#include <AndroidAccessory.h>
#include <P2PMQTT.h>
#include <AFMotor.h>

byte direction = 'S';
int payload = -1; // Set phone payload
long timer = millis(); // Timer
P2PMQTT mqtt(true); // Set to true for debugging
//boolean subscribed = false;


// DRIVETRAINS (Based on Gordon McComb's Constructing Robot Bases book)
// NONHOLONOMIC
// 0 = Front Two Wheel Coaxial Drive (Most common)
// 1 = Mid Two Wheel Coaxial Drive (Roomba)
// 2 = Rear Two Wheel Coaxial Drive
// 3 = Four Wheel Coaxial Drive
// 4 = Six Wheel Coaxial Drive
// 5 = Eight Wheel Coaxial Drive
// 6 = Car-Type Steering Drive
// 7 = Car-Type Steering Drive, Independent Steering Wheels (e.g. Ackerman Steering)
// 8 = Three-Wheel Tricycle Drive
// 9 = Tracked Drive
// HONLONOMIC
// 10 = Three-Wheel Omnidirectional Drive
// 11 = Four-Wheel Omnidirectional Drive
// 12 = Synchronized Omnidirectional Drive
#define DRIVETRAIN 6
#define TURNSPEED 225
#define DRIVESPEED 255

AF_DCMotor motor_front(2, MOTOR12_64KHZ);
AF_DCMotor motor_rear(3);

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
  
  if(DRIVETRAIN == 6) {
    motor_front.setSpeed(TURNSPEED);
    motor_rear.setSpeed(DRIVESPEED);
    motor_front.run(RELEASE);
    motor_rear.run(RELEASE);
  }

  // Initiate connection with the phone
  mqtt.begin("Ardrobot");
  mqtt.connect(0,6000); // set 1 min timeout
}


void loop() {
  // Get P2PMQTT package and extract type
  int type = mqtt.getType(mqtt.buffer);
  
  if(type > 0) {
    Serial.print("Type: ");
    Serial.print(type);
    Serial.println();
  }
  
  // Respond to the package contents

  switch(type) {
    case CONNECT:
      Serial.println("Connected");
      break;
    case PUBLISH:
      payload = mqtt.getPayload(mqtt.buffer, type) [0];
      Serial.print("command: ");
      Serial.println(payload);
      direction = payload;
      break;
    default:
      if(type != -1) {
        Serial.println("Type: " + type);
      }
      break;
  }

  // Now we update the servo speed slowly based on the direction input
  if (mqtt.isConnected()) {
    if( millis() - timer > 20 ) {
      if (direction == 'F') {
        Serial.println("Forward");
        goForward();
      } else if (direction == 'R') {
        Serial.println("Right");
        turnRight();
      } else if (direction == 'L') {
        Serial.println("Left");
        turnLeft();
      } else if (direction == 'B') {
        Serial.println("Backward");
        goBackward();
      } else {
        stop();
      }
      timer = millis();

    }
  } else {
    // Turn off the motors if we don't have a direction
    stop();
  }
}

void goForward() {
  if(DRIVETRAIN == 6) {
    motor_front.run(RELEASE);
    motor_rear.run(FORWARD);
  }
}

void goBackward() {
  if(DRIVETRAIN == 6) {
    motor_front.run(RELEASE);
    motor_rear.run(BACKWARD);
  }  
}

void turnRight() {
  if(DRIVETRAIN == 6) {
    motor_front.run(BACKWARD);
//    motor_rear.run(FORWARD);
  }  
}

void turnLeft() {
  if(DRIVETRAIN == 6) {
    motor_front.run(FORWARD);
//    motor_rear.run(FORWARD);
  }  
}

void stop() {
  if(DRIVETRAIN == 6) {
    motor_front.run(RELEASE);
    motor_rear.run(RELEASE);
  }
}


// TODO: Create Library for MegaMoto Shields
// TODO: Create Library for Servo Drive




