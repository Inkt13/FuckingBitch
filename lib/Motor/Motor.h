#include <Arduino.h>
#include <ftb.h>
class Motor
{
    int pin1;
    int pin2;
    int enablePin;
    int motorSpeed;
    public:
        Motor(){}
        Motor(int p1, int p2, int enable, int speed)
        : pin1(p1), pin2(p2), enablePin(enable), motorSpeed(speed)
        {}
        void forward();
        void backward();
        void setSpeed(int speed);
        void move(int speed);
        void stop();
};
    
class RobotMovement
{
    Motor motorA;
    Motor motorB;
    Motor motorC;
    Motor motorD;
    public:
        RobotMovement()
        {
            motorA = Motor(9, 10, 8, 50);
            motorB = Motor(12, 11, 13, 50);
            motorC = Motor(6, 5, 7, 50);
            motorD = Motor(3, 4, 2, 50);
        }
        int speed = 100;

        void moveX(int speed);
        void moveY(int speed);
        void moveDiagonal13(int speed);
        void moveDiagonal24(int speed);
        // void moveX(int distance);
        // void moveY(int distance);
        // void moveDiagonal13(int distance);
        // void moveDiagonal24(int distance);
        void rotateFromWheel(int angle, int wheel); //Negative angle will be counter clockwise
        void rotateBody(int angle); //Negative angle will be a counter clockwise
        void rotateEdge(int angle, int edge); //The edge will be specified later for convenient usage
};

void motorA(int speed);
void motorB(int speed);
void motorC(int speed);
void motorD(int speed);

int time(int distance, RobotMovement& speed);

extern RobotMovement robotMovement;
