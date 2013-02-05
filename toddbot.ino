#include "Arduino.h"
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h> // ADK2011
#include <AFMotor.h> // Motor Shield


#define ACCESSORY_STRING_VENDOR "Todd"
#define ACCESSORY_STRING_NAME   "toddbot"
#define ACCESSORY_STRING_LONGNAME "Todd Bot"
#define ACCESSORY_STRING_VERSION  "1.1"
#define ACCESSORY_STRING_URL    "http://www.toddsampson.com"
#define ACCESSORY_STRING_SERIAL "0000000091239123"
#define MAX_PACKET_SZ 260  //256b payload + header

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

#define DIRECTION_MSG 0x2

AF_DCMotor motor_front(2, MOTOR12_1KHZ);
AF_DCMotor motor_rear(3, MOTOR12_1KHZ);


AndroidAccessory acc(ACCESSORY_STRING_VENDOR,
                     ACCESSORY_STRING_NAME,
                     ACCESSORY_STRING_LONGNAME,
                     ACCESSORY_STRING_VERSION,
                     ACCESSORY_STRING_URL,
                     ACCESSORY_STRING_SERIAL);

void setup() {
  Serial.begin(115200);
  delay(100);

  if(DRIVETRAIN == 6) {
    motor_front.setSpeed(150);
    motor_rear.setSpeed(150);
    motor_front.run(RELEASE);
    motor_rear.run(RELEASE);
  }
//  msg[0] = 0x2;
//  msg[1] = 'F';
  acc.powerOn();
}


void loop() {
  byte msg[2];
  if (acc.isConnected()) {
    int len = acc.read(msg, sizeof(msg), 1);
    Serial.print("Message length: ");
    Serial.println(len, DEC);
    if (len > 0) {
      if (msg[0] = DIRECTION_MSG) {
        int direction = msg[1];
        if (direction == 'F') {
          goForward();
        } else if (direction == 'R') {
          turnRight();
        } else if (direction == 'L') {
          turnLeft();
        } else if (direction == 'B') {
          goBackward();
        } else {
          stop();
        }
      }
    } else {
      stop();
    }
    msg[0] = -1;
  }
  else {
    stop();
  }
  delay(100);
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
    motor_front.run(FORWARD);
    motor_rear.run(FORWARD);
  }  
}

void turnLeft() {
  if(DRIVETRAIN == 6) {
    motor_front.run(BACKWARD);
    motor_rear.run(FORWARD);
  }  
}

void stop() {
  if(DRIVETRAIN == 6) {
    motor_front.run(RELEASE);
    motor_rear.run(RELEASE);
  }
}


// TODO: Create Library for MegaMoto Shields





