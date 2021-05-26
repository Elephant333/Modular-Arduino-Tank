//Nathan Li - RC Bluetooth Tank 6-Axis Arm Version (Servant) - 28 January 2021

#include <Wire.h>
#include <Servo.h>

int waist = 3;
int shoulder = 5;
int elbow = 6;
int wristRoll = 9;
int wristPitch = 10;
int grip = 11;
Servo waistServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristRollServo;
Servo wristPitchServo;
Servo gripServo;
int servoPos;

int servoSpeed = 51;

int state = 0;

void setup() 
{
  waistServo.attach(waist);
  shoulderServo.attach(shoulder);
  elbowServo.attach(elbow);
  wristRollServo.attach(wristRoll);
  wristPitchServo.attach(wristPitch);
  gripServo.attach(grip);
  
  waistServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristRollServo.write(90);
  wristPitchServo.write(90);
  gripServo.write(90);

  Wire.begin(3);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes)
{
  state = Wire.read();
}

void loop()
{
  /***********************Servo Speed****************************/
    if (state >= 200 && state <= 250)
    {
      servoSpeed = map(state, 200, 250, 51, 10); //will be used for delay, but 51 will constitute no movement
    }

  /***********************Waist****************************/
    if (state == 9 || state == 10)
    {
      moveServo(waistServo, 180, 0);
    }

  /***********************Shoulder****************************/
    if (state == 11 || state == 12)
    {
      moveServo(shoulderServo, 180, 0);
    }

  /***********************Elbow****************************/
    if (state == 13 || state == 14)
    {
      moveServo(elbowServo, 180, 0);
    }

  /***********************Wrist Roll****************************/
    if (state == 15 || state == 16)
    {
      moveServo(wristRollServo, 180, 0);
    }

  /***********************Wrist Pitch****************************/
    if (state == 17 || state == 18)
    {
      moveServo(wristPitchServo, 180, 0);
    }

  /***********************Grip****************************/
    if (state == 19 || state == 20)
    {
      moveServo(gripServo, 90, 0);
    }
}

void moveServo(Servo &theServo, int maxPos, int minPos)
{
  servoPos = theServo.read();
  if (servoSpeed == 51)
  {
    theServo.write(servoPos);
  }
  else
  {
    if (state % 2 == 1)
    {
      if (servoPos < maxPos)
      {
        servoPos = servoPos + 2;
        theServo.write(servoPos);
        delay(servoSpeed); 
      }
      else
      {
        servoPos = maxPos;
        theServo.write(servoPos);
      }
    }
    if (state % 2 == 0)
    {
      if (servoPos > minPos)
      {
        servoPos = servoPos - 2;
        theServo.write(servoPos);
        delay(servoSpeed); 
      }
      else
      {
        servoPos = minPos;
        theServo.write(servoPos);
      }
    }
  }
}
