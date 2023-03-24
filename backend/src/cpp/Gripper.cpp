#include "./hpp/Gripper.hpp"

Gripper::Gripper(byte pServoPin, byte pGrabPos, byte pReleasePos)
{
    servoPin = pServoPin;
    grabPos = pGrabPos;
    releasePos = pReleasePos;
}

void Gripper::setup()
{
    servo.attach(servoPin);
    release();
}
// servo turns out -> gripper grabs
void Gripper::grap()
{
    servo.write(grabPos);
    released = false;
}
// servo turns in -> gripper releases
void Gripper::release()
{
    servo.write(releasePos);
    released = true;
}
// sets gripper status "released"
bool Gripper::isReleased()
{
    return released;
}