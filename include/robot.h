#pragma once

// L298N số 1 (motor trái)
#define IN1_1 12
#define IN2_1 11
#define ENA1_PIN 13   // PWM

#define IN3_1 10
#define IN4_1 9
#define ENB1_PIN 46   // PWM

// L298N số 2 (motor phải)
#define IN1_2 39
#define IN2_2 38
#define ENA2_PIN 40   // PWM

#define IN3_2 37
#define IN4_2 36
#define ENB2_PIN 35   // PWM

// LEDC channels (0-15 available on ESP32)
#define PWM_CHANNEL_0 0
#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3

#define PWM_FREQ 1000
#define PWM_RESOLUTION 8
#define MOTOR_SPEED 150

// Prototypes
void setMotor(int in1, int in2, int channel, int speed);
void motorSpin(int v1, int v2, int v3, int v4);
void initRobot();
void moveForward(int s);
void moveBackward(int s);
void turnRight(int s);
void turnLeft(int s);
void rotateRight(int s);
void rotateLeft(int s);
void moveDiagRightFront(int s);
void moveDiagLeftFront(int s);
void moveDiagRightBack(int s);
void moveDiagLeftBack(int s) ;
void handleCommandMotor(char cmd);
