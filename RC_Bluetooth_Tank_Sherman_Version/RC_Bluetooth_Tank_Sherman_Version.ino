//Nathan Li - RC Bluetooth Tank Sherman Version - 13 January 2021

#include <Servo.h> //Something I learned during this project: calling the servo library disables PWM for pins 9 and 10, and that is why the right motor was having trouble.
#include <SoftwareSerial.h>

SoftwareSerial BT(4, 2); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
//Another thing I learned: use SoftwareSerial for bluetooth instead of just Serial because Serial is more for the serial monitor, while SoftwareSerial is better used for bluetooth electronics communications.
//I believe this is what solved the delay issues I was having previously between the app, bluetooth module, and Arduino controller.

int motorA1  = 6; //Left Forward
int motorA2  = 11;
int motorB1  = 3; //Right Forward
int motorB2  = 5;
int LED1 = 7; //front lights
int LED2 = 8;
int LED3 = 12; //rear lights
int LED4 = 13;
int state = 0;
int index;
int motorSpeed = 0;
int turretSpeed = 51; //the delay between turret changes
int turretPos = 90;

Servo myservo;

void setup() 
{
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    myservo.attach(9);
    myservo.write(turretPos);
    
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    
    Serial.begin(9600);
    BT.begin(9600);
}

void loop() 
{
    //Save incoming data to variable 'state'
    if(BT.available() > 0)
    {
      state = BT.read();
    }

    Serial.print("state: " );
    Serial.println(state);

  /***********************Motor Speed****************************/
    if (state >= 50 && state <= 199)
    {
      motorSpeed = map(state, 50, 199, 0, 255);
    }
    
  /***********************Turret Speed****************************/
    if (state >= 200 && state <= 250)
    {
      turretSpeed = map(state, 200, 250, 51, 10); //will be used for delay, but 51 will constitute no movement
    }
    
  /***********************Forward****************************/
    if (state == 1)
    {
      analogWrite(motorA1, motorSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, motorSpeed); analogWrite(motorB2, 0);
    }
  
  /***********************Backward****************************/
    else if (state == 5)
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, motorSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, motorSpeed);
    }

  /***************************Right*****************************/
    else if (state == 3) 
    {
      analogWrite(motorA1, motorSpeed); analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0); analogWrite(motorB2, motorSpeed);
    }
    
  /***************************Left*****************************/
    else if (state == 7) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, motorSpeed);
      analogWrite(motorB1, motorSpeed); analogWrite(motorB2, 0);
    }

  /**********************Forward Right************************/
    else if (state == 2) 
    {
      analogWrite(motorA1, motorSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, 0);
    }
    
  /**********************Forward Left************************/
    else if (state == 8) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0);
      analogWrite(motorB1, motorSpeed); analogWrite(motorB2, 0);     
    }
    
  /**********************Backward Right************************/
    else if (state == 4) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, motorSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, 0);   
    }
    
  /**********************Backward Left************************/
    else if (state == 6) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, motorSpeed);  
    }
    
  /***************************Stop*****************************/
    else if (state == 0) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, 0);
    }

  /***********************Turret Left****************************/
    else if (state == 9) //to do: make the turret turn a bit faster by increasing turretPos change and adding a limitation to change in order to prevent <0 or >180 outputs
    {
      if (turretSpeed == 51)
      {
        myservo.write(turretPos);
      }
      else
      {
        if (turretPos < 180)
        {
          turretPos = turretPos + 2;
          myservo.write(turretPos);
          delay(turretSpeed); 
        }
        else
        {
          turretPos = 180;
          myservo.write(turretPos);
        }
      }
    }

  /***********************Turret Right****************************/
    else if (state == 10) 
    {
      if (turretSpeed == 51)
      {
        myservo.write(turretPos);
      }
      else
      {
        if (turretPos > 0)
        {
          turretPos = turretPos - 2;
          myservo.write(turretPos);
          delay(turretSpeed); 
        }
        else
        {
          turretPos = 0;
          myservo.write(turretPos);
        }
      }
    }
}
