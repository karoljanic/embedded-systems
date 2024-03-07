#include "Wheels.h"

#define MOTOR1_EN   10
#define MOTOR1_IN1  9
#define MOTOR1_IN2  8

#define MOTOR2_EN   6
#define MOTOR2_IN1  5
#define MOTOR2_IN2  4

Wheels w;
volatile char cmd;

void setup() {
  // put your setup code here, to run once:
  w.attach(MOTOR1_IN1, MOTOR1_IN2, MOTOR1_EN, MOTOR2_IN1, MOTOR2_IN2, MOTOR2_EN);

  for(int i = 0; i < 3; i++) {
    w.goForward(20);
  }

  delay(500);

  w.goBack(60);

  // Serial.begin(9600);
  // Serial.println("Forward: WAD");
  // Serial.println("Back: ZXC");
  // Serial.println("Stop: S");
}

void loop() {
  // while(Serial.available())
  // {
  //   cmd = Serial.read();
  //   switch(cmd)
  //   {
  //     case 'w': w.forward(); break;
  //     case 'x': w.back(); break;
  //     case 'a': w.forwardLeft(); break;
  //     case 'd': w.forwardRight(); break;
  //     case 'z': w.backLeft(); break;
  //     case 'c': w.backRight(); break;
  //     case 's': w.stop(); break;
  //     case '1': w.setSpeedLeft(75); break;
  //     case '2': w.setSpeedLeft(200); break;
  //     case '9': w.setSpeedRight(75); break;
  //     case '0': w.setSpeedRight(200); break;
  //     case '5': w.setSpeed(100); break;
  //   }
  // }
}
