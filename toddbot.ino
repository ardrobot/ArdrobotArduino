// AOA1/ADK1
#include "Arduino.h"
#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>
#include <AFMotor.h>






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


#define DRIVETARAIN 2

uint8_t cmd;

AndroidAccessory acc(ACCESSORY_STRING_VENDOR,
                     ACCESSORY_STRING_NAME,
                     ACCESSORY_STRING_LONGNAME,
                     ACCESSORY_STRING_VERSION,
                     ACCESSORY_STRING_URL,
                     ACCESSORY_STRING_SERIAL);

void setup() {
  Serial.begin(115200);
  delay(100);
  acc.powerOn();
}


void loop() {
  if (acc.isConnected()) {
    uint8_t msg[MAX_PACKET_SZ];
    uint8_t outmsg[MAX_PACKET_SZ];
    int recvLen = acc.read(msg, sizeof(msg));
    if (recvLen > 0) {
      // process message
 
    }
//    acc.write(cmd);
  }
//  acc.adkEventProcess();
}

void 



