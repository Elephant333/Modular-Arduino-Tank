//Nathan Li - RC Bluetooth Tank Nerf Turret Version (Master) - 21 April 2021

#include <SoftwareSerial.h>
#include <Wire.h> 

SoftwareSerial BT(4, 2); // Arduino(RX, TX) - HC-05 Bluetooth (TX, RX)
//Another thing I learned: use SoftwareSerial for bluetooth instead of just Serial because Serial is more for the serial monitor, while SoftwareSerial is better used for bluetooth electronics communications.
//I believe this is what solved the delay issues I was having previously between the app, bluetooth module, and Arduino controller.

int motorA1  = 6; //Left Forward
int motorA2  = 11;
int motorB1  = 3; //Right Forward
int motorB2  = 5;
int state = 0;
int index;
int motorSpeed = 0;

void setup() 
{
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    
    Serial.begin(9600);
    BT.begin(9600);

    Wire.begin(); 
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
    
  /***********************Servo Speed****************************/
    if (state >= 200 && state <= 250)
    {
      Wire.beginTransmission(3); //transmit to device #3, where 3 is an arbitrary number that we use as an ID
      Wire.write(state);
      Wire.endTransmission();
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
      Wire.beginTransmission(3); //transmit to device #3, where 3 is an arbitrary number that we use as an ID
      Wire.write(state);
      Wire.endTransmission();
    }

  /***************************Nerf Turret Servos/Motors*****************************/
    else if (state >= 9 && state <= 19) 
    {
      Wire.beginTransmission(3); //transmit to device #3, where 3 is an arbitrary number that we use as an ID
      Wire.write(state);
      Wire.endTransmission();
    }
}
