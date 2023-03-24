#include "./hpp/stepper.hpp"

Stepper::Stepper(byte pPulPin, byte pDirPin,
				 byte pHomePointPin, uint pMaxSteps, short pStepsForRotation)
{
	pulPin = pPulPin;
	dirPin = pDirPin;
	homePointPin = pHomePointPin;
	endPos = pMaxSteps;
	stepsForRotation = pStepsForRotation;
	inputStatus = 0;
	steppercount = 0;

	pinMode(pulPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(homePointPin, INPUT_PULLUP);
}

byte Stepper::getPulPin()
{
	return pulPin;
}
// returns turn-direction
byte Stepper::getDirPin()
{
	return dirPin;
}
byte Stepper::getHomePointPin()
{
	return pulPin;
}

void Stepper::UpdateInputStatus()
{
	inputStatus = digitalRead(homePointPin);
}
byte Stepper::getInputStatus()
{
	return inputStatus;
}

int Stepper::getSteps()
{
	return steppercount;
}

int Stepper::getEndPos()
{
	return endPos;
}

void Stepper::addStep(bool direction)
{
	if (direction)
	{
		steppercount++;
	}
	else
	{
		steppercount--;
	}
}

void Stepper::resetSteps()
{
	steppercount = 0;
}
