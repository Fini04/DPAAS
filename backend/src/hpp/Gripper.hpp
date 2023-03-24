#include <Arduino.h>
#include <ESP32Servo.h>

class Gripper
{
private:
    Servo servo;
    byte servoPin;
    byte grabPos;
    byte releasePos;
    bool released;

public:
    Gripper(byte pServoPin, byte pClosedPos, byte pOpenPos);
    void setup();
    void release();
    void grap();
    bool isReleased();
};