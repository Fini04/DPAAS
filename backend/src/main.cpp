#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>

#include "./hpp/Websocket.hpp"
#include "./hpp/stepper.hpp"
#include "./hpp/manager.hpp"
#include "./hpp/Gripper.hpp"
#include "./hpp/akku.hpp"

/*
  Docs for used microcontroller Pins

  Gripper:
    ServoPin: 13,
    ClosedPos: 20,
    OpenPos: 100,

  MagConfig:
    Pos1: 896,
    Pos2: 61685,
    Pos3: 122373,
*/

const int xAxisPulPin = 16, xAxisDirPin = 4, xAxisHomePin = 32, xAxisEndPoint = 310750;
const int yAxisPulPin = 18, yAxisDirPin = 17, yAxisHomePin = 33, yAxisEndPoint = -332360;
const int mAxisPulPin = 21, mAxisDirPin = 19, mAxisHomePin = 25, mAxisEndPoint = 130000;
const int aAxisPulPin = 26, aAxisDirPin = 27, aAxisHomePin = 23, aAxisEndPoint = 123855;
Stepper xS(xAxisPulPin, xAxisDirPin, xAxisHomePin, xAxisEndPoint);
Stepper yS(yAxisPulPin, yAxisDirPin, yAxisHomePin, yAxisEndPoint);
Stepper mS(mAxisPulPin, mAxisDirPin, mAxisHomePin, mAxisEndPoint);
Stepper aS(aAxisPulPin, aAxisDirPin, aAxisHomePin, aAxisEndPoint);
Gripper aGripper(13, 20, 100);
// Gripper aPress(13, 20, 100);
// Gripper dGripper(13, 20, 100);
Akku akkuMag(896, 61685, 122373);

Manager step;

Websocket wst;

int relpos = 11925;

#define drivertype 1
AccelStepper xAxis(drivertype, xAxisPulPin, xAxisDirPin);
AccelStepper yAxis(drivertype, yAxisPulPin, yAxisDirPin);
AccelStepper mAxis(drivertype, mAxisPulPin, mAxisDirPin);
AccelStepper aAxis(drivertype, aAxisPulPin, aAxisDirPin);

void setup()
{
  xAxis.setMaxSpeed(15000);    // Set maximum speed value for the stepper
  xAxis.setAcceleration(5000); // Set acceleration value for the stepper
  xAxis.setCurrentPosition(0); // Set the current position to 0 steps

  yAxis.setMaxSpeed(15000);
  yAxis.setAcceleration(3000);
  yAxis.setCurrentPosition(0);

  mAxis.setMaxSpeed(20000);
  mAxis.setAcceleration(5000);
  mAxis.setCurrentPosition(0);

  aAxis.setMaxSpeed(20000);
  aAxis.setAcceleration(5000);
  aAxis.setCurrentPosition(0);

  wst.socketSetup();
  pinMode(22, OUTPUT); // ON/OFF Stepper
  aGripper.setup();
}

#define isAction(x) if (wst.getAction() == x)
void loop()
{
  xS.UpdateInputStatus();
  yS.UpdateInputStatus();
  mS.UpdateInputStatus();
  aS.UpdateInputStatus();

  // Y-axis moving away from endstop
  isAction("yZuruck")
  {
    xAxis.moveTo(0);
  }
  // Y-axis moving towards endstop
  else isAction("yVor")
  {
    yAxis.moveTo(-332360);
    yAxis.runSpeedToPosition();
  }
  // X-axis moving towards endstop
  else isAction("xVor")
  {
    xAxis.moveTo(310750);
    xAxis.runSpeedToPosition();
  }
  // X-axis moving away from endstop
  else isAction("xZuruck")
  {
    xAxis.moveTo(0);
    xAxis.runSpeedToPosition();
  }
  // Both axis stop moving
  else isAction("stop")
  {
    // wst.setAction("grab");
    xAxis.moveTo(310750);
    // stepper1.runToPosition();
    yAxis.moveTo(-332360);
    // stepper2.runToPosition();

    while (xAxis.currentPosition() != 310750 || yAxis.currentPosition() != -332360)
    {
      xAxis.run();
      yAxis.run();
    }
  }

  else isAction("start")
  {
    // yAxis.moveTo(0);
    // yAxis.runToPosition();
    // xAxis.moveTo(0);
    // xAxis.runToPosition();
    wst.setAction("grab");
  }

  // magazine
  else isAction("magVor")
  {
    mAxis.moveTo(mS.getEndPos());
    mAxis.runToPosition();
  }

  else isAction("magZuruck")
  {
    mAxis.moveTo(0);
    mAxis.runToPosition();
  }

  else isAction("armReinSchieben")
  {
    aAxis.moveTo(aS.getEndPos());
    aAxis.runToPosition();
    wst.setAction("armZuruck");
  }

  // arm
  else isAction("armVor")
  {
    aAxis.moveTo(aS.getEndPos());
    aAxis.runToPosition();
    wst.setAction("armRausZiehen");
  }

  else isAction("armZuruck")
  {
    aAxis.moveTo(0);
    aAxis.runToPosition();
    wst.setAction("release");
  }
  // All axis move towards endstops
  else isAction("callibrate")
  {
    // xAxis.setCurrentPosition(0); // Set the current position to 0 steps
    if (xS.getInputStatus())
    {
      digitalWrite(xS.getDirPin(), LOW);
      step.push(xS.getPulPin());
    }
    else
    {
      xS.resetSteps();
      xAxis.setCurrentPosition(0);
    }

    if (yS.getInputStatus())
    {
      digitalWrite(yS.getDirPin(), HIGH);
      step.push(yS.getPulPin());
    }
    else
    {
      yS.resetSteps();
      yAxis.setCurrentPosition(0);
    }

    if (mS.getInputStatus())
    {
      digitalWrite(mS.getDirPin(), LOW);
      step.push(mS.getPulPin());
    }
    else
    {
      mS.resetSteps();
      mAxis.setCurrentPosition(0);
    }

    if (aS.getInputStatus())
    {
      digitalWrite(aS.getDirPin(), LOW);
      step.push(aS.getPulPin());
    }
    else
    {
      aS.resetSteps();
      aAxis.setCurrentPosition(0);
    }
    step.doStep();
  }

  else isAction("motorAus")
  {
    digitalWrite(22, LOW);
  }
  else isAction("motorAn")
  {
    digitalWrite(22, HIGH);
    wst.setAction("callibrate");
  }
  else isAction("grab")
  {
    yAxis.moveTo(0);
    yAxis.runToPosition();
    xAxis.moveTo(0);
    xAxis.runToPosition();
    wst.setAction("akkuLeer");
  }
  else isAction("armRausZiehen")
  {
    aGripper.grap();
    delay(1000);
    aAxis.moveTo(9925);
    aAxis.runToPosition();
    aGripper.release();
    delay(1000);
    aAxis.moveTo(0);
    aAxis.runToPosition();
    wst.setAction("akkuVoll");
  }
  else isAction("akkuLeer")
  {
    mAxis.moveTo(akkuMag.getFreePos());
    mAxis.runToPosition();
    wst.setAction("armVor");
  }
  else isAction("akkuVoll")
  {
    mAxis.moveTo(akkuMag.getFullPos());
    mAxis.runToPosition();
    wst.setAction("armReinSchieben");
  }

  else isAction("release")
  {
    xAxis.moveTo(155375);
    yAxis.moveTo(-166180);

    while (xAxis.currentPosition() != 155375 || yAxis.currentPosition() != -166180)
    {
      xAxis.run();
      yAxis.run();
    }
  }

  else isAction("getStepPos")
  {
    wst.notifyClients();
    wst.setAction("stop");
  }

  else isAction("armGrab")
  {
    aGripper.grap();
  }

  else isAction("armRelease")
  {
    aGripper.release();
  }
}
