#pragma once

#define ENA1 42 // trước trái
#define IN1_1 41
#define IN2_1 40

#define ENB1 37 // trước phải
#define IN3_1 39
#define IN4_1 38

#define ENA2  9  // sau trái
#define IN1_2  8
#define IN2_2 3

#define ENB2 4 // sau phải
#define IN3_2 6
#define IN4_2 5 

// Khai báo hằng (declaration) - dùng extern để tránh multiple definition
const int freq=1000;
const int resolution=8;
const int MOTOR_SPEED=200;

// Prototypes
void initRobot();
void motorSpin(int v1, int v2, int v3, int v4);
void moveForward(int speed);
void moveBackward(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void rotateRight(int speed);
void rotateLeft(int speed);
void handleCommandMotor(char cmd);
