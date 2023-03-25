#include <Arduino.h>
#include <ESP32Servo.h>

class Gripper
{
private:
    Servo servo;
    byte servoPin;
    byte gripperPos1;
    byte gripperPos2;
    bool released;

public:
    Gripper(byte pServoPin, byte pGripperPos1, byte pGripperPos2);
    void setup();
    void goGripperPos1();
    void goGripperPos2();
    bool isReleased();
};