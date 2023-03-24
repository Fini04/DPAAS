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

//  NOTE - Docs Pins
/*
  Docs for used microcontroller Pins

  X-Axis:
    PulPin: 16,
    DirPin: 4,
    HomePin: 32,
    EndPos: 310750,

  Y-Axis:
    PulPin: 18,
    DirPin: 17,
    HomePin: 33,
    EndPos: -332360,

  Mag-Axis:
    PulPin: 21,
    DirPin: 19,
    HomePin: 25,
    EndPos: 130000,

  Arm-Axis:
    PulPin: 26,
    DirPin: 27,
    HomePin: 23,
    EndPos: 121855,

  Gripper:
    ServoPin: 13,
    ClosedPos: 20,
    OpenPos: 100,

  MagConfig:
    Pos1: 896,
    Pos2: 61685,
    Pos3: 122373,
*/

Stepper xS(16, 4, 32, 310750);
Stepper yS(18, 17, 33, -332360);
Stepper mS(21, 19, 25, 130000);
Stepper aS(26, 27, 23, 123855);
Gripper aGripper(13, 20, 100);
// Gripper aPress(13, 20, 100);
// Gripper dGripper(13, 20, 100);
Akku akkuMag(896, 61685, 122373);

Manager step;

Websocket wst;

int relpos = 11925;

// Define the stepper motor and the pins that is connected to
// (Typeof driver: with 2 pins, STEP, DIR)
AccelStepper xAxis(1, 16, 4);
AccelStepper yAxis(1, 18, 17);
AccelStepper mag(1, 21, 19);
AccelStepper arm(1, 26, 27);

void setup()
{
  xAxis.setMaxSpeed(15000);    // Set maximum speed value for the stepper
  xAxis.setAcceleration(5000); // Set acceleration value for the stepper
  xAxis.setCurrentPosition(0); // Set the current position to 0 steps

  yAxis.setMaxSpeed(15000);
  yAxis.setAcceleration(3000);
  yAxis.setCurrentPosition(0);

  mag.setMaxSpeed(20000);
  mag.setAcceleration(5000);
  mag.setCurrentPosition(0);

  arm.setMaxSpeed(20000);
  arm.setAcceleration(5000);
  arm.setCurrentPosition(0);

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
    mag.moveTo(mS.getEndPos());
    mag.runToPosition();
  }

  else isAction("magZuruck")
  {
    mag.moveTo(0);
    mag.runToPosition();
  }

  else isAction("armReinSchieben")
  {
    arm.moveTo(aS.getEndPos());
    arm.runToPosition();
    wst.setAction("armZuruck");
  }

  // arm
  else isAction("armVor")
  {
    arm.moveTo(aS.getEndPos());
    arm.runToPosition();
    wst.setAction("armRausZiehen");
  }

  else isAction("armZuruck")
  {
    arm.moveTo(0);
    arm.runToPosition();
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
      mag.setCurrentPosition(0);
    }

    if (aS.getInputStatus())
    {
      digitalWrite(aS.getDirPin(), LOW);
      step.push(aS.getPulPin());
    }
    else
    {
      aS.resetSteps();
      arm.setCurrentPosition(0);
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
    arm.moveTo(9925);
    arm.runToPosition();
    aGripper.release();
    delay(1000);
    arm.moveTo(0);
    arm.runToPosition();
    wst.setAction("akkuVoll");
  }
  else isAction("akkuLeer")
  {
    mag.moveTo(akkuMag.getFreePos());
    mag.runToPosition();
    wst.setAction("armVor");
  }
  else isAction("akkuVoll")
  {
    mag.moveTo(akkuMag.getFullPos());
    mag.runToPosition();
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
