#include "./hpp/Gripper.hpp"

Gripper::Gripper(byte pServoPin, byte pGripperPos1, byte pGripperPos2)
{
    servoPin = pServoPin;
    gripperPos1 = pGripperPos1;
    gripperPos2 = pGripperPos2;
}

void Gripper::setup()
{
    servo.attach(servoPin);
    goGripperPos1();
}
// servo turns in -> gripper releases
void Gripper::goGripperPos1()
{
    servo.write(gripperPos1);
}
// servo turns out -> gripper grabs
void Gripper::goGripperPos2()
{
    servo.write(gripperPos2);
}