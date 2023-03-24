#include <Arduino.h>

class Manager
{
private:
        const static byte stepperAmount = 5;
        const byte taktLenght = 20;
        byte stepperCounter;
        byte pulPinQueue[stepperAmount];

public:
        Manager();
        void push(byte pPulPin);
        void doStep();
};