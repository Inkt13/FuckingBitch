#include <Arduino.h>
#include <ftb.h>
#include <Motor.h>

RobotMovement robotMovement;
Motor *motor1234[4];

void Motor::forward()
{
    setPWM(pin1,0,0);
    setPWM(pin2,0,this->motorSpeed * 40);
    setPWM(enablePin,0,4000);
}

void Motor::backward()
{
    setPWM(pin1,0,this->motorSpeed * 40);
    setPWM(pin2,0,0);
    setPWM(enablePin,0,4000);
}

void Motor::setSpeed(int speed)
{
    this->motorSpeed = speed;
}

void Motor::stop()
{
    setPWM(pin1,0,0);
    setPWM(pin2,0,0);
    setPWM(enablePin,0,0);
}

void Motor::move(int speed)
{
    Serial.print("This pin1 is moving:");
    Serial.println(this->pin1);
    if(speed > 0)
    {
        this->forward();
    }
    else if(speed < 0)
    {
        const int opposite_dir = -1;
        this->backward();
    }
    else
    {
        stop();
    }
}

int time(int distance, int speed)
{
    return speed / distance;
}

void RobotMovement::motorsInit()
{
    motor1234[0] = &robotMovement.motorA;
    motor1234[1] = &robotMovement.motorB;
    motor1234[2] = &robotMovement.motorC;
    motor1234[3] = &robotMovement.motorD;
}

void RobotMovement::moveX(int speed)
{
    const int opposite_dir = -1;
    motorA.move(speed);
    motorB.move(speed * opposite_dir);
    motorC.move(speed);
    motorD.move(speed * opposite_dir);
}

void RobotMovement::moveY(int speed)
{
    motorA.move(speed);
    motorB.move(speed);
    motorC.move(speed);
    motorD.move(speed);
}

void RobotMovement::moveDiagonal13(int speed)
{
    motorA.move(speed);
    motorB.stop();
    motorC.move(speed);
    motorD.stop();
}

void RobotMovement::moveDiagonal24(int speed)
{
    motorA.stop();
    motorB.move(speed);
    motorC.stop();
    motorD.move(speed);
}