#include <Arduino.h>
#include <ftb.h>
#include <Motor.h>
#include <ESP32Servo.h>

#define SERVO_PIN 17

RobotMovement robotMovement;
Motor *motors[4];

void Motor::forward()
{
    setPWM(pin1, 0, 0);
    setPWM(pin2, 0, this->motorSpeed * 40);
    setPWM(enablePin, 0, 4000);
}

void Motor::backward()
{
    setPWM(pin1, 0, this->motorSpeed * 40);
    setPWM(pin2, 0, 0);
    setPWM(enablePin, 0, 4000);
}

void Motor::startMove(unsigned int duration_s)
{
    Serial.println("startMove is called");

    // ds = desiseconds
    this->duration = duration_s * 100UL; // seconds → ds
    this->startTime = millis();
    this->isMoving = true;
}

void Motor::setrampTime_ms(unsigned int ramp_s)
{
    this->rampTime_ms = ramp_s * 100UL; // seconds → ds
}

void Motor::setTargetSpeed(int speed)
{
    if (speed > 0 && speed <= 100)
    {
        this->motorTargetSpeed = speed;
        Serial.print("Positive speed of ");
        Serial.println(this->motorTargetSpeed);
    }
    else if (speed > 100 && speed <= 200)
    {
        speed *= -1;
        const int opposite_dir = 100;
        this->motorTargetSpeed = speed + opposite_dir;
        Serial.print("Negative speed of ");
        Serial.println(this->motorTargetSpeed);
    }
    else if (speed == 0)
    {
        stop();
    }
}

void Motor::applySpeed(int speed)
{
    if (speed > 0)
    {
        setPWM(pin1, 0, 0);
        setPWM(pin2, 0, speed * 40);
    }
    else if (speed < 0)
    {
        setPWM(pin1, 0, (-speed) * 40);
        setPWM(pin2, 0, 0);
    }
    else
    {
        stop();
    }

    setPWM(enablePin, 0, 4000);
}

void RobotMovement::servoWriteControlled(int targetAngle, int delayTime = 1)
{
    int step = 2;
    int currentAngle = robotMovement.servoCurrentAngle;
    
    if (currentAngle == targetAngle) return;

    if (targetAngle > currentAngle)
    {
        for (int i = currentAngle; i <= targetAngle;i += step)
        {
            robotMovement.servo.write(i);
            delay(delayTime * 10);//*10 makes its so from millisecond to centiseconds
        }
    }
    else
    {
        for (int i = currentAngle; i >= targetAngle;i -= step)
        {
            robotMovement.servo.write(i);
            delay(delayTime * 10);//*10 makes its so from millisecond to centiseconds
        }
    }

    robotMovement.servoCurrentAngle = targetAngle;
    robotMovement.servo.write(targetAngle);
}

void Motor::stop()
{
    Serial.print("This pin1 is stopping:");
    Serial.println(this->pin1);
    setPWM(pin1, 0, 0);
    setPWM(pin2, 0, 0);
    setPWM(enablePin, 0, 0);
}

void Motor::update()
{
    if (!this->isMoving)
        return;

    unsigned long now = millis();
    unsigned long elapsed = now - this->startTime;

    if (elapsed >= duration)
    {
        stop();
        this->isMoving = false;
        return;
    }

    int currentSpeed;
    if (duration < 2 * rampTime_ms)
    {
        // TRIANGLE PROFILE aka its not long enough, ill explain later please remind me
        unsigned long half = duration / 2;

        if (elapsed < half)
            currentSpeed = map(elapsed, 0, half, 0, this->motorTargetSpeed);
        else
            currentSpeed = map(elapsed, half, duration, this->motorTargetSpeed, 0);
    }
    else
    {
        // TRAPEZOID PROFILE
        if (elapsed < rampTime_ms)
        {
            currentSpeed = map(elapsed, 0, rampTime_ms, 0, this->motorTargetSpeed);
        }
        else if (elapsed < duration - rampTime_ms)
        {
            currentSpeed = this->motorTargetSpeed;
        }
        else
        {
            currentSpeed = map(elapsed, duration - rampTime_ms, duration, this->motorTargetSpeed, 0);
        }
    }

    Motor::applySpeed(currentSpeed);
}

void RobotMovement::motorsInit()
{
    motors[0] = &robotMovement.motorA;
    motors[1] = &robotMovement.motorB;
    motors[2] = &robotMovement.motorC;
    motors[3] = &robotMovement.motorD;
}

void RobotMovement::servoInit()
{
    robotMovement.servo.attach(SERVO_PIN);
}