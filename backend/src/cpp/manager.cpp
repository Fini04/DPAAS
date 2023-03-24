#include "./hpp/manager.hpp"
// regulates stepperCounter
Manager::Manager()
{
	stepperCounter = 0;
}

void Manager::push(byte pPulPin)
{
	pulPinQueue[stepperCounter] = pPulPin;
	stepperCounter++;
}

void Manager::doStep()
{
	for (byte i = 0; i < stepperAmount; i++)
	{
		digitalWrite(pulPinQueue[i], HIGH);
	}
	delayMicroseconds(taktLenght);
	for (byte i = 0; i < stepperAmount; i++)
	{
		digitalWrite(pulPinQueue[i], LOW);
		pulPinQueue[i] = 0;
	}
	// delayMicroseconds(taktLenght);
	stepperCounter = 0;
}