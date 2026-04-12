#include <Arduino.h>
#include <ftb.h>
class Motor
{
    int pin1;
    int pin2;
    int enablePin;
    public:
        Motor(int p1, int p2, int enable)
        : pin1(p1), pin2(p2), enablePin(enable)
        {}
        
        int speed = 100;
        void motorInit();
        void moveX(int distance);
        void moveY(int distance);
        void moveDiagonal13(int distance);
        void moveDiagonal24(int distance);
        void rotateFromWheel(int angle, int wheel); //Negative angle will be counter clockwise
        void rotateBody(int angle); //Negative angle will be a counter clockwise
        void rotateEdge(int angle, int edge); //The edge will be specified later for convenient usage
};

void motorA(int speed);
void motorB(int speed);
void motorC(int speed);
void motorD(int speed);

int time(int distance, Motor& speed);

extern Motor motor;
