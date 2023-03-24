#include <Arduino.h>

class Stepper
{
private:
	byte pulPin;
	byte dirPin;
	byte homePointPin;
	byte inputStatus;
	short stepsForRotation;
	int steppercount;
	int endPos;

public:
	bool callibrated = false;

	Stepper(byte pPulPin, byte pDirPin,
			byte pHomePointPin, uint endPos, short pStepsForRotation = 1600);

	byte getPulPin();
	byte getDirPin();
	byte getHomePointPin();
	void UpdateInputStatus();
	byte getInputStatus();
	int getSteps();
	int getEndPos();
	void addStep(bool direction);
	void resetSteps();
};