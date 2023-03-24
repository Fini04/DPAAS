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
const int xAxisRelPoint = xAxisEndPoint / 2, yAxisRelPoint = yAxisEndPoint / 2;
Stepper xS(xAxisPulPin, xAxisDirPin, xAxisHomePin, xAxisEndPoint);
Stepper yS(yAxisPulPin, yAxisDirPin, yAxisHomePin, yAxisEndPoint);
Stepper mS(mAxisPulPin, mAxisDirPin, mAxisHomePin, mAxisEndPoint);
Stepper aS(aAxisPulPin, aAxisDirPin, aAxisHomePin, aAxisEndPoint);
Gripper aGripper(13, 20, 100);
Gripper aPress(14, 20, 100);
Gripper dGripper(15, 20, 100);
Akku akkuMag(896, 61685, 122373);

Manager step;

Websocket wst;

int relpos = 11925;

#define startPoint 0
#define drivertype 1
AccelStepper xAxis(drivertype, xAxisPulPin, xAxisDirPin);
AccelStepper yAxis(drivertype, yAxisPulPin, yAxisDirPin);
AccelStepper mAxis(drivertype, mAxisPulPin, mAxisDirPin);
AccelStepper aAxis(drivertype, aAxisPulPin, aAxisDirPin);

void setup()
{
  xAxis.setMaxSpeed(15000);             // Set maximum speed value for the stepper
  xAxis.setAcceleration(5000);          // Set acceleration value for the stepper
  xAxis.setCurrentPosition(startPoint); // Set the current position to 0 steps

  yAxis.setMaxSpeed(15000);
  yAxis.setAcceleration(3000);
  yAxis.setCurrentPosition(startPoint);

  mAxis.setMaxSpeed(20000);
  mAxis.setAcceleration(5000);
  mAxis.setCurrentPosition(startPoint);

  aAxis.setMaxSpeed(20000);
  aAxis.setAcceleration(5000);
  aAxis.setCurrentPosition(startPoint);

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

  isAction("yZuruck")
  {
    xAxis.moveTo(startPoint);
  }
  else isAction("yVor")
  {
    yAxis.moveTo(yAxisEndPoint);
    yAxis.runSpeedToPosition();
  }
  else isAction("xVor")
  {
    xAxis.moveTo(xAxisEndPoint);
    xAxis.runSpeedToPosition();
  }
  else isAction("xZuruck")
  {
    xAxis.moveTo(startPoint);
    xAxis.runSpeedToPosition();
  }
  else isAction("stop")
  {
    // wst.setAction("grab");
    xAxis.moveTo(xAxisEndPoint);
    // stepper1.runToPosition();
    yAxis.moveTo(yAxisEndPoint);
    // stepper2.runToPosition();

    while (xAxis.currentPosition() != xAxisEndPoint || yAxis.currentPosition() != yAxisEndPoint)
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

  else isAction("magVor")
  {
    mAxis.moveTo(mAxisEndPoint);
    mAxis.runToPosition();
  }

  else isAction("magZuruck")
  {
    mAxis.moveTo(startPoint);
    mAxis.runToPosition();
  }

  else isAction("armReinSchieben")
  {
    aAxis.moveTo(aAxisEndPoint);
    aAxis.runToPosition();
    wst.setAction("armZuruck");
  }

  else isAction("armVor")
  {
    aAxis.moveTo(aAxisEndPoint);
    aAxis.runToPosition();
    wst.setAction("armRausZiehen");
  }

  else isAction("armZuruck")
  {
    aAxis.moveTo(startPoint);
    aAxis.runToPosition();
    wst.setAction("release");
  }
  else isAction("callibrate")
  {
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
    yAxis.moveTo(startPoint);
    yAxis.runToPosition();
    xAxis.moveTo(startPoint);
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
    xAxis.moveTo(xAxisRelPoint);
    yAxis.moveTo(yAxisRelPoint);

    while (xAxis.currentPosition() != xAxisRelPoint || yAxis.currentPosition() != yAxisRelPoint)
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
