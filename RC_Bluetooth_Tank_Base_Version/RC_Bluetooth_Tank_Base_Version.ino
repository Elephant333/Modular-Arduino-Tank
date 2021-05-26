//Nathan Li - RC Bluetooth Tank Base Version - 28 December 2020

   int motorA1  = 6; //Left Forward
   int motorA2  = 11;
   int motorB1  = 3; //Right Forward
   int motorB2  = 5;
   int dataIn[3] = {255, 125, 125}; //initialize 255, x, and y to be in the center of joystick (meaning stop)
   int in_byte;
   int index;
   int mainSpeed;

void setup() 
{
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);   
    Serial.begin(9600);
}

void loop() 
{
    //Save incoming data to variable 'in_byte'
    if(Serial.available() > 0)
    {
      in_byte = Serial.read();
      if (in_byte == (255)) 
      {
        index = 0;
      }
      dataIn[index] = in_byte;
      index = index + 1;
    }

    Serial.print (dataIn[0]);
    Serial.print (", X: ");
    Serial.print (dataIn[1]);
    Serial.print (", Y: ");
    Serial.println (dataIn[2]);
  /***********************Forward****************************/
    if (dataIn[2] <= 100 && dataIn[1] >= 100 && dataIn[1] <= 150) //pushing joystick forward
    {
      mainSpeed = map(dataIn[2], 100, 0, 125, 255);
      analogWrite(motorA1, mainSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, mainSpeed); analogWrite(motorB2, 0);
    }
  
  /***********************Backward****************************/
    else if (dataIn[2] >= 150 && dataIn[1] >= 100 && dataIn[1] <= 150)
    {
      mainSpeed = map(dataIn[2], 150, 250, 125, 255);
      analogWrite(motorA1, 0); analogWrite(motorA2, mainSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, mainSpeed);
    }

  /***************************Right*****************************/
    else if (dataIn[2] > 100 && dataIn[2] < 150 && dataIn[1] >= 150 && dataIn[1] <= 250) 
    {
      mainSpeed = map(dataIn[1], 150, 250, 125, 255);
      analogWrite(motorA1, mainSpeed); analogWrite(motorA2, 0); 
      analogWrite(motorB1, 0); analogWrite(motorB2, mainSpeed);
    }
    
  /***************************Left*****************************/
    else if (dataIn[2] > 100 && dataIn[2] < 150 && dataIn[1] >= 0 && dataIn[1] <= 100) 
    {
      mainSpeed = map(dataIn[1], 100, 0, 125, 255);
      analogWrite(motorA1, 0); analogWrite(motorA2, mainSpeed);
      analogWrite(motorB1, mainSpeed); analogWrite(motorB2, 0);
    }

  /**********************Forward Right************************/
    else if (dataIn[2] <= 100 && dataIn[1] >= 150 && dataIn[1] <= 250) 
    {
      mainSpeed = map(dataIn[2], 100, 0, 125, 255);
      analogWrite(motorA1, mainSpeed); analogWrite(motorA2, 0);
      analogWrite(motorB1, map(dataIn[1], 150, 250, mainSpeed, 0)); analogWrite(motorB2, 0);
    }
    
  /**********************Forward Left************************/
    else if (dataIn[2] <= 100 && dataIn[1] >= 0 && dataIn[1] <= 100) 
    {
      mainSpeed = map(dataIn[2], 100, 0, 125, 255);
      analogWrite(motorA1, map(dataIn[1], 100, 0, mainSpeed, 0)); analogWrite(motorA2, 0);
      analogWrite(motorB1, mainSpeed); analogWrite(motorB2, 0);     
    }
    
  /**********************Backward Right************************/
    else if (dataIn[2] >= 150 && dataIn[1] >= 150 && dataIn[1] <= 250) 
    {
      mainSpeed = map(dataIn[2], 150, 250, 125, 255);
      analogWrite(motorA1, 0); analogWrite(motorA2, mainSpeed); 
      analogWrite(motorB1, 0); analogWrite(motorB2, map(dataIn[1], 150, 250, mainSpeed, 0));   
    }
    
  /**********************Backward Left************************/
    else if (dataIn[2] >= 150 && dataIn[1] >= 0 && dataIn[1] <= 100) 
    {
      mainSpeed = map(dataIn[2], 150, 250, 125, 255);
      analogWrite(motorA1, 0); analogWrite(motorA2, map(dataIn[1], 100, 0, mainSpeed, 0));
      analogWrite(motorB1, 0); analogWrite(motorB2, mainSpeed);  
    }
    
  /***************************Stop*****************************/
    else if (dataIn[2] > 100 && dataIn[2] < 150 && dataIn[1] > 100 && dataIn[1] < 150) 
    {
      analogWrite(motorA1, 0); analogWrite(motorA2, 0);
      analogWrite(motorB1, 0); analogWrite(motorB2, 0);
    }
}
