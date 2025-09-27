#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "robot.h"

int angle1 = 0;
int angle2 = 110;
int angle3 = 145;
int stepAngle = 5;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

uint16_t angleToPulse(int angle) {
    // 0° -> 150, 180° -> 600 (tùy servo, có thể tinh chỉnh)
    return map(angle, 0, 180, 150, 600);
}

void updateArm(int angleUpdate, int id){
    if (angleUpdate < 0 ) angleUpdate = 0;
    if (angleUpdate > 180) angleUpdate = 180;

    uint16_t pulse = angleToPulse(angleUpdate);
    switch(id){
        case 1 : 
            angle1 = angleUpdate;
            pwm.setPWM(0,0,pulse);
            break;
        case 2 : 
            angle2 = angleUpdate;
            pwm.setPWM(1,0,pulse);
            break;
        case 3 : 
            angle3 = angleUpdate;
            pwm.setPWM(2,0,pulse);
            break;
    }
}

void setupToTakeAndThrowTheBall(int id, int target){
    int *anglePtr;
    switch(id){
        case 1: anglePtr = &angle1; break;
        case 2: anglePtr = &angle2; break;
        case 3: anglePtr = &angle3; break;
        default: return;
    }

    while (*anglePtr != target){
        if (*anglePtr < target) (*anglePtr)++;
        else if (*anglePtr > target) (*anglePtr)--;
        // Gửi lệnh tới PCA9685 thay cho servoPtr->write()
        uint16_t pulse = angleToPulse(*anglePtr);
        pwm.setPWM(id - 1, 0, pulse); // kênh = id-1: servo1->ch0, servo2->ch1, servo3->ch2
        delay(20);
    }
}

void takeTheBall(){
    setupToTakeAndThrowTheBall(3, 80);
    delay(200);
    setupToTakeAndThrowTheBall(2, 85);
    delay(200);
    setupToTakeAndThrowTheBall(3, 125);
    delay(200);
}

void throwTheBall(){
    setupToTakeAndThrowTheBall(2,145);
    delay(200);
    setupToTakeAndThrowTheBall(1, 180);
    delay(200);
    setupToTakeAndThrowTheBall(3, 180);
    delay(200);
}

void setDefaultArm(){
    updateArm(angle1, 1);
    delay(500);
    updateArm(angle2, 2);
    delay(500);
    updateArm(angle3, 3);
    delay(500);
}

void servoUp(int id){
    if(id==1) updateArm(angle1 + stepAngle, 1);
    if(id==2) updateArm(angle2 + stepAngle, 2);
    if(id==3) updateArm(angle3 + stepAngle, 3);
    Serial.println(String(angle1) + " - " + String(angle2) + " - " + String(angle3));
}

void servoDown(int id){
    if(id==1) updateArm(angle1 - stepAngle, 1);
    if(id==2) updateArm(angle2 - stepAngle, 2);
    if(id==3) updateArm(angle3 - stepAngle, 3);
    Serial.println(String(angle1) + " - " + String(angle2) + " - " + String(angle3));
}

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

void initServo(){
    Wire.begin();
    pwm.begin();
    pwm.setPWMFreq(50);
    delay(10);
    // Đặt vị trí ban đầu
    updateArm(angle1, 1);
    updateArm(angle2, 2);
    updateArm(angle3, 3);
}
