//Nathan Li - RC Bluetooth Tank Nerf Turret Version (Servant) - 21 April 2021

#include <Wire.h>
#include <Servo.h>

int waist = 3;
int shoulder = 5;
int trigger = 6;
int flywheels = 11;
Servo waistServo;
Servo shoulderServo;
Servo triggerServo;
int servoPos;

int servoSpeed = 51;

int state = 0;

void setup() 
{
  waistServo.attach(waist);
  shoulderServo.attach(shoulder);
  triggerServo.attach(trigger);
  pinMode(flywheels, OUTPUT);
  
  waistServo.write(90);
  shoulderServo.write(90);
  triggerServo.write(115);
  digitalWrite(flywheels, LOW);

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
    else if (state == 9 || state == 10)
    {
      moveServo(waistServo, state, 180, 0);
    }

  /***********************Shoulder****************************/
    else if (state == 11 || state == 12)
    {
      moveServo(shoulderServo, state, 130, 0);
    }

  /***********************Trigger****************************/
    else if (state == 19)
    {
      triggerServo.write(55);
      delay(250);
      triggerServo.write(115);
      delay(250);
    }

  /***********************Flywheel Motors****************************/
    else if (state == 17)
    {
      digitalWrite(flywheels, LOW);
    }
    else if (state == 18)
    {
      digitalWrite(flywheels, HIGH);
    }

  /***********************Waist/Shoulder****************************/
    else if (state == 13)
    {
      moveServo(waistServo, 9, 180, 0);
      moveServo(shoulderServo, 11, 130, 0);
    }
    else if (state == 14)
    {
      moveServo(waistServo, 10, 180, 0);
      moveServo(shoulderServo, 11, 130, 0);
    }
    else if (state == 15)
    {
      moveServo(waistServo, 9, 180, 0);
      moveServo(shoulderServo, 12, 130, 0);
    }
    else if (state == 16)
    {
      moveServo(waistServo, 10, 180, 0);
      moveServo(shoulderServo, 12, 130, 0);
    }
}

void moveServo(Servo &theServo, int newState, int maxPos, int minPos) //using newState so that can combine waist/shoulder movements
{
  servoPos = theServo.read();
  if (servoSpeed == 51)
  {
    theServo.write(servoPos);
  }
  else
  {
    if (newState % 2 == 1) //if state is odd, typically left or down
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
    if (newState % 2 == 0) //if state is even, typically right or up
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
