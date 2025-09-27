#pragma once
#include<ESP32Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

extern int angle1;
extern int angle2;
extern int angle3;
extern int stepAngle;
extern int servoMoveSpeed;
extern Servo servo1;
extern Servo servo2;
extern Servo servo3;

void updateArm(int angleUpdate, int id);
void smoothMoveToAngle(int id, int targetAngle);
void smoothMoveToAngles(int targetAngles[], int numServos);
void takeTheBall();
void throwTheBall();
void setDefaultArm();
//
void servoUp(int id);
void servoDown(int id);
void handleCommandServo(char cmd);
void initServo();
