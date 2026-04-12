#include <Arduino.h>
#include <ftb.h>
#include <Motor.h>

Motor motor;

void motorForwardA(int speed) {
    setPWM(9, 0, 0);     
    setPWM(10, 0, speed * 40);  
    setPWM(8, 0, 4000);  
}

void motorBackwardA(int speed)
{
    setPWM(9, 0, speed * 40);  
    setPWM(10, 0, 0);     
    setPWM(8, 0, 4000);  
}

void motorForwardB(int speed) {
    setPWM(11, 0, speed * 40);  
    setPWM(12, 0, 0);     
    setPWM(13, 0, 4000);  
}

void motorBackwardB(int speed)
{
    setPWM(11, 0, 0);     
    setPWM(12, 0, speed * 40);  
    setPWM(13, 0, 4000);  
}

void motorForwardC(int speed) {
    setPWM(5, 0, speed * 40);  
    setPWM(6, 0, 0);     
    setPWM(7, 0, 4000);  
}

void motorBackwardC(int speed)
{
    setPWM(5, 0, 0);     
    setPWM(6, 0, speed * 40);  
    setPWM(7, 0, 4000);  
}

void motorForwardD(int speed) {
    setPWM(3, 0, 0);     
    setPWM(4, 0, speed * 40);  
    setPWM(2, 0, 4000);  
}

void motorBackwardD(int speed)
{
    setPWM(3, 0, speed * 40);  
    setPWM(4, 0, 0);
    setPWM(2, 0, 4000);  
}

void motorA(int speed)
{
    if(speed < 0)
    {
        motorBackwardA(speed*-1);
    }
    else
    {
        motorForwardA(speed);
    }
}

void motorB(int speed)
{
    if(speed < 0)
    {
        motorBackwardB(speed*-1);
    }
    else
    {
        motorForwardB(speed);
    }
}

void motorC(int speed)
{
    if(speed < 0)
    {
        motorBackwardC(speed*-1);
    }
    else
    {
        motorForwardC(speed);
    }
}

void motorD(int speed)
{
    if(speed < 0)
    {
        motorBackwardD(speed*-1);
    }
    else
    {
        motorForwardD(speed);
    }
}

int time(int distance, int speed)
{
    return speed / distance;
}

void Motor::moveY(int distance)
{
    if(distance == 0)return;
    int direction = 1;
    if(distance < 0)direction = -1;
    
    motorA(speed * direction);
    motorB(speed * direction);
    motorC(speed * direction);
    motorD(speed * direction);
    // delay(time(distance, motor.speed));
}