#include <Arduino.h>
#include <ftb.h>
#include <ESP32Servo.h>
class Motor
{
    int pin1;
    int pin2;
    int enablePin;
    int motorSpeed;
    int motorTargetSpeed;

    bool isMoving;

    unsigned long startTime;
    unsigned int duration; //its in desiseconds
    unsigned int rampTime_ms; //its in desiseconds
    public:
        Motor(){}
        Motor(int p1, int p2, int enable, int speed)
        : pin1(p1), pin2(p2), enablePin(enable), motorSpeed(speed)
        {
            motorTargetSpeed = 75;
            rampTime_ms = 300;
        }
        void forward();
        void backward();
        void stop();

        void setTargetSpeed(int speed);
        void setrampTime_ms(unsigned int duration_ms);
        void startMove(unsigned int duration_ms);
        void applySpeed(int speed);
        void update();
};
    
class RobotMovement
{
    public:
        int servoCurrentAngle;
        Motor motorA;
        Motor motorB;
        Motor motorC;
        Motor motorD;
        Servo servo;
        RobotMovement()
        {
            motorA = Motor(9, 10, 8, 50);
            motorB = Motor(12, 11, 13, 50);
            motorC = Motor(6, 5, 7, 50);
            motorD = Motor(3, 4, 2, 50);
        }
        void motorsInit();
        void servoInit();
        void servoWriteControlled(int angle, int delayTime);
};

extern RobotMovement robotMovement;
extern Motor *motors[4];
