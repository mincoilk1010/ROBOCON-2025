#include <Arduino.h>
#include "robot.h"

// định nghĩa hằng (definition) chỉ 1 lần trong project 

void setMotor(int in1, int in2, int channel, int speed) {
  if (speed > 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(channel, speed);
  } else if (speed < 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(channel, -speed);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(channel, 0);
  }
}
void motorSpin(int v1, int v2, int v3, int v4) {
  v1 = constrain(v1, -255, 255);
  v2 = constrain(v2, -255, 255);
  v3 = constrain(v3, -255, 255);
  v4 = constrain(v4, -255, 255);

  setMotor(IN1_1, IN2_1, PWM_CHANNEL_0, v1); // Motor 1 - Front Left
  setMotor(IN3_1, IN4_1, PWM_CHANNEL_1, v2); // Motor 2 - Back Left
  setMotor(IN1_2, IN2_2, PWM_CHANNEL_2, v3); // Motor 3 - Front Right
  setMotor(IN3_2, IN4_2, PWM_CHANNEL_3, v4); // Motor 4 - Back Right
}
void stopMotor() { motorSpin(0,0,0,0); }

void initRobot() {
  pinMode(IN1_1, OUTPUT); pinMode(IN2_1, OUTPUT);
  pinMode(IN3_1, OUTPUT); pinMode(IN4_1, OUTPUT);
  pinMode(IN1_2, OUTPUT); pinMode(IN2_2, OUTPUT);
  pinMode(IN3_2, OUTPUT); pinMode(IN4_2, OUTPUT);

  pinMode(ENA1_PIN, OUTPUT);
  pinMode(ENB1_PIN, OUTPUT);
  pinMode(ENA2_PIN, OUTPUT);
  pinMode(ENB2_PIN, OUTPUT);

  ledcSetup(PWM_CHANNEL_0, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENA1_PIN, PWM_CHANNEL_0);
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENB1_PIN, PWM_CHANNEL_1);
  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENA2_PIN, PWM_CHANNEL_2);
  ledcSetup(PWM_CHANNEL_3, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENB2_PIN, PWM_CHANNEL_3);

  stopMotor();
  Serial.println("Robot motor initialized!");
}

void moveForward(int s)    { motorSpin(s, s, s, s); }
void moveBackward(int s)   { motorSpin(-s, -s, -s, -s); }
void turnRight(int s)      { motorSpin(s, s, -s, -s); }
void turnLeft(int s)       { motorSpin(-s, -s, s, s); }
void rotateRight(int s)    { motorSpin(s, -s, s, -s); }
void rotateLeft(int s)     { motorSpin(-s, s, -s, s); }
void moveDiagRightFront(int s) { motorSpin(0, s, s, 0); }
void moveDiagLeftFront(int s)  { motorSpin(s, 0, 0, s); }
void moveDiagRightBack(int s)  { motorSpin(-s, 0, 0, -s); }
void moveDiagLeftBack(int s)   { motorSpin(0, -s, -s, 0); }

void handleCommandMotor(char cmd) {
  switch (cmd) {
    case 'F': moveForward(MOTOR_SPEED); Serial.println("Go Forward"); break;
    case 'B': moveBackward(MOTOR_SPEED); Serial.println("Go Backward"); break;
    case 'R': turnRight(MOTOR_SPEED); Serial.println("Turn Right"); break;
    case 'L': turnLeft(MOTOR_SPEED); Serial.println("Turn Left"); break;
    case 'G': rotateRight(MOTOR_SPEED); Serial.println("Rotate Right"); break;
    case 'H': rotateLeft(MOTOR_SPEED); Serial.println("Rotate Left"); break;
    case 'I': moveDiagRightFront(MOTOR_SPEED); Serial.println("Diagonal Right Front"); break;
    case 'J': moveDiagLeftBack(MOTOR_SPEED); Serial.println("Diagonal Left Back"); break;
    case 'K': moveDiagLeftFront(MOTOR_SPEED); Serial.println("Diagonal Left Front"); break;
    case 'M': moveDiagRightBack(MOTOR_SPEED); Serial.println("Diagonal Right Back"); break;
    case 'S': stopMotor(); Serial.println("Stop"); break;
    default: break;
  }
}

