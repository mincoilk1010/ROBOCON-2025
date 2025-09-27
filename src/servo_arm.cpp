#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "robot.h"


#define SDA_PIN 6
#define SCL_PIN 7
#define SERVO_MIN 150
#define SERVO_MAX 600
#define SERVO_FREQ 50
#define SERVO_1 0
#define SERVO_2 1
#define SERVO_3 2


int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int stepAngle = 5;
int servoMoveSpeed = 20;
int defaultAngles[3] = {0, 80, 120};
int grabAngles[3]    = {0, 110, 125};
int releaseAngles[3] = {90, 110, 145};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint16_t angleToPulse(int angle) {
    // 0° -> 150, 180° -> 600 (tùy servo, có thể tinh chỉnh)
    return map(angle, 0, 180, 150, 600);
}

void updateArm(int angleUpdate, int id) {
  if (angleUpdate < 0) angleUpdate = 0;
  if (angleUpdate > 180) angleUpdate = 180;

  uint16_t pulse = map(angleUpdate, 0, 180, SERVO_MIN, SERVO_MAX);

  switch(id) {
    case 1: angle1 = angleUpdate; pwm.setPWM(SERVO_1, 0, pulse); break;
    case 2: angle2 = angleUpdate; pwm.setPWM(SERVO_2, 0, pulse); break;
    case 3: angle3 = angleUpdate; pwm.setPWM(SERVO_3, 0, pulse); break;
  }
}

void smoothMoveToAngle(int id, int targetAngle) {
  int *currentAngle = nullptr;
  int servoChannel = 0;

  switch(id) {
    case 1: currentAngle = &angle1; servoChannel = SERVO_1; break;
    case 2: currentAngle = &angle2; servoChannel = SERVO_2; break;
    case 3: currentAngle = &angle3; servoChannel = SERVO_3; break;
    default: return;
  }

  int steps = abs(targetAngle - *currentAngle);
  if (steps == 0) return;

  for (int step = 1; step <= steps; step++) {
    int intermediateAngle = *currentAngle + (targetAngle - *currentAngle) * step / steps;
    uint16_t pulse = map(intermediateAngle, 0, 180, SERVO_MIN, SERVO_MAX);
    pwm.setPWM(servoChannel, 0, pulse);
    delay(servoMoveSpeed);
  }
  *currentAngle = targetAngle;
}

void smoothMoveToAngles(int targetAngles[], int numServos) {
  int currentAngles[3] = {angle1, angle2, angle3};
  int steps = 0;

  for (int i = 0; i < numServos; i++) {
    int diff = abs(targetAngles[i] - currentAngles[i]);
    if (diff > steps) steps = diff;
  }
  if (steps == 0) return;

  for (int step = 1; step <= steps; step++) {
    for (int i = 0; i < numServos; i++) {
      int intermediateAngle = currentAngles[i] + (targetAngles[i] - currentAngles[i]) * step / steps;
      uint16_t pulse = map(intermediateAngle, 0, 180, SERVO_MIN, SERVO_MAX);
      pwm.setPWM(i, 0, pulse);
    }
    delay(servoMoveSpeed);
  }

  angle1 = targetAngles[0];
  angle2 = targetAngles[1];
  angle3 = targetAngles[2];
}

void takeTheBall() { Serial.println("Grab ball"); smoothMoveToAngles(grabAngles, 3); }
void throwTheBall() { Serial.println("Release ball"); smoothMoveToAngles(releaseAngles, 3); }
void setDefaultArm() { Serial.println("Set default arm"); smoothMoveToAngles(defaultAngles, 3); }

void servoUp(int id) { smoothMoveToAngle(id, (id==1?angle1:(id==2?angle2:angle3)) + stepAngle); }
void servoDown(int id) { smoothMoveToAngle(id, (id==1?angle1:(id==2?angle2:angle3)) - stepAngle); }


void handleCommandServo(char cmd){
    switch(cmd){
    case 'Q': servoUp(1); break;
    case 'A': servoDown(1); break;
    case 'W': servoUp(2); break;
    case 'X': servoDown(2); break;
    case 'E': servoUp(3); break;
    case 'D': servoDown(3); break;
    case 'Z': takeTheBall(); break;
    case 'N': throwTheBall(); break;
    default : break;
  }
} 

void initServo() {
  Wire.begin(SDA_PIN, SCL_PIN);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
  setDefaultArm();
  Serial.println("Servo initialized!");
}
