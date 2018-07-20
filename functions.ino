//*********************** forward with PID ********************************
void forward(){
  while(1){
  Serial.println("forward function is running");
  qtrrc.read(sensorValues);
  unsigned int position = qtrrc.readLine(sensorValues);    
  int error = 3500 - position;
  int speedError = KP * error + KD * (error - lastError);
  speedError = speedError*0.04;
    int rightMotorSpeed = motorSpeedRight - speedError;
    int leftMotorSpeed = motorSpeedLeft + speedError;
    lastError = error;
    if (rightMotorSpeed < 0){
      rightMotorSpeed = 0;
      }
    if (leftMotorSpeed > motorSpeedLeft){
      leftMotorSpeed = motorSpeedLeft;
      }
    if (rightMotorSpeed > motorSpeedRight){
      rightMotorSpeed = motorSpeedRight;
      }
    if (leftMotorSpeed < 0){
      leftMotorSpeed = 0;
      }
    Serial.print("rightMotorSpeed = ");
    Serial.print(rightMotorSpeed);
    Serial.print("  leftMotorSpeed = ");
    Serial.print(leftMotorSpeed);
    Serial.print("  error = ");
    Serial.print(error);
    if (!junction()){
      rotate(rightMotorSpeed,leftMotorSpeed);
    }
      else{
      activeBreak();
      return;
          }
    }  
 }

//******************** how to react at a junction ********************************
bool junction(){
  qtrrc.read(sensorValues);
  unsigned int position = qtrrc.readLine(sensorValues);
  int right = (sensorValues[0] + sensorValues[1] + sensorValues[2])/3;
  int middle = (sensorValues[3] + sensorValues[4])/2;
  int left = (sensorValues[5] + sensorValues[6] + sensorValues[7])/3;
  Serial.print("  Left = ");
  Serial.print(left);
  Serial.print("  middle= ");
  Serial.print(middle);
  Serial.print("  Right = ");
  Serial.println(right);
  if ((left == black) && (middle == black)){return true;}
  else if ((right == black) && (middle == black)){return true;}
  else if ((left == black) && (right == black)){return true;}
  else if ((left < white) && (middle < white) && (right < white)){
    Serial.println("off the track");
    offTrack();
    junction();}
  else{return false;}
  }
  
//******************** turn Right ************************************
void turnRight(){
  while(1){
  Serial.println("turn left is runing");
  qtrrc.read(sensorValues);
        int right = (sensorValues[0] + sensorValues[1] + sensorValues[2])/3;
        int middle = (sensorValues[3] + sensorValues[4])/2;
        int left = (sensorValues[5] + sensorValues[6] + sensorValues[7])/3;
        Serial.print("  Left = ");
        Serial.print(left);
        Serial.print("  middle= ");
        Serial.print(middle);
        Serial.print("  Right = ");
        Serial.println(right);
        if ((left < white) && (middle == black) && (right < white)){
          activeBreak();
          return;
          }
        else{
          if (obstacle()){
                analogWrite(enableRight,motorSpeedRight);
                analogWrite(enableLeft,motorSpeedLeft);
                digitalWrite(inRight1,LOW);
                digitalWrite(inRight2,LOW);
                digitalWrite(inLeft1,HIGH);
                digitalWrite(inLeft2,LOW);
                  }
            else{
                 Serial.println("Active break");
                 activeBreak();
                  }
        }
    }
  }

//*********************** turn left ********************************
void turnLeft(){
  while(1){
  Serial.println("turn left is runing");
  qtrrc.read(sensorValues);
        int right = (sensorValues[0] + sensorValues[1] + sensorValues[2])/3;
        int middle = (sensorValues[3] + sensorValues[4])/2;
        int left = (sensorValues[5] + sensorValues[6] + sensorValues[7])/3;
        Serial.print("  Left = ");
        Serial.print(left);
        Serial.print("  middle= ");
        Serial.print(middle);
        Serial.print("  Right = ");
        Serial.println(right);
        if ((left < white) && (middle == black) && (right < white)){
          activeBreak();
          return;
          }
        else{
            if (obstacle()){
                analogWrite(enableRight,motorSpeedRight);
                analogWrite(enableLeft,motorSpeedLeft);
                digitalWrite(inRight1,HIGH);
                digitalWrite(inRight2,LOW);
                digitalWrite(inLeft1,LOW);
                digitalWrite(inLeft2,LOW);
                  }
            else{
                 Serial.println("Active break");
                 activeBreak();
                  }
        }
    }
  }

//*********************** turn back ********************************
void turnBack(){
  while(1){
  Serial.println("turn back is runing");
  qtrrc.read(sensorValues);
        int right = (sensorValues[0] + sensorValues[1] + sensorValues[2])/3;
        int middle = (sensorValues[3] + sensorValues[4])/2;
        int left = (sensorValues[5] + sensorValues[6] + sensorValues[7])/3;
        Serial.print("  Left = ");
        Serial.print(left);
        Serial.print("  middle= ");
        Serial.print(middle);
        Serial.print("  Right = ");
        Serial.println(right);
        if ((left < white) && (middle == black) && (right < white)){
          activeBreak();
          return;
          }
        else{
          if (obstacle()){
              analogWrite(enableRight,55);
              analogWrite(enableLeft,55);
              digitalWrite(inRight1,LOW);
              digitalWrite(inRight2,HIGH);
              digitalWrite(inLeft1,HIGH);
              digitalWrite(inLeft2,LOW);
            }
          else{
           Serial.println("Active break");
           activeBreak();
             }
        }
    }
  }

//********************************** skiping the junction ***************************************
void skip(){
  while(1){
  Serial.println("skiping the junction is runing");
  qtrrc.read(sensorValues);
  int count = 0;
  for (unsigned char i = 0; i <= sizeof(sensorValues) - 1; i++){
    if (sensorValues[i] == 2500){
      count = count + 1;
      }
    }

  if ((count > 0) && (count <= 3)){
    activeBreak();
    return;
    }
       
    else{
          unsigned int position = qtrrc.readLine(sensorValues);    
          int error = 3500 - position;
          int speedError = KP * error + KD * (error - lastError);
          speedError = speedError*0.04;
            int rightMotorSpeed = motorSpeedRight - speedError;
            int leftMotorSpeed = motorSpeedLeft + speedError;
            lastError = error;
            if (rightMotorSpeed < 0){
              rightMotorSpeed = 0;
              }
            if (leftMotorSpeed > motorSpeedLeft){
              leftMotorSpeed = motorSpeedLeft;
              }
            if (rightMotorSpeed > motorSpeedRight){
              rightMotorSpeed = motorSpeedRight;
              }
            if (leftMotorSpeed < 0){
              leftMotorSpeed = 0;
              }
          rotate(rightMotorSpeed,leftMotorSpeed);
        }
    }
  }

//******************************* offTrack ****************************************************
void offTrack(){
  Serial.println("offtrack is runing");
  qtrrc.read(sensorValues);
  int count = 0;
  for (unsigned char i = 0; i <= 8; i++){
    if (sensorValues[i] == 2500){
      count = count + 1;
      }
    }
  if (count == 0){
    Serial.println("Robot is out of the track");
  
  while(1){
        Serial.println("trying to return back to the track");
        qtrrc.read(sensorValues);
        int count = 0;
        for (unsigned char i = 0; i <= 8; i++){
          if (sensorValues[i] == 2500){
            count = count + 1;
            }
          }
      
        if ((count > 0) && (count <= 3)){
          activeBreak();
          return;
          }
        else{
          reverse(motorSpeedRight,motorSpeedLeft);
          delay(200);
        }
    }
    }
  }


//*********************** robot functinalities *********************
void activeBreak(){
  analogWrite(enableRight,0);
  analogWrite(enableLeft,0);
  digitalWrite(inRight1,LOW);
  digitalWrite(inRight2,LOW);
  digitalWrite(inLeft1,LOW);
  digitalWrite(inLeft2,LOW);
  delay(600);
  }

void rotate(int motorSpeedRight, int motorSpeedLeft){
  if (obstacle()){
        analogWrite(enableRight,motorSpeedRight);
        analogWrite(enableLeft,motorSpeedLeft);
        digitalWrite(inRight1,HIGH);
        digitalWrite(inRight2,LOW);
        digitalWrite(inLeft1,HIGH);
        digitalWrite(inLeft2,LOW);
    }
  else{
   Serial.println("Active break");
   activeBreak();
    }
        
  }

void reverse(int motorSpeedRight, int motorSpeedLeft){
        analogWrite(enableRight,motorSpeedRight);
        analogWrite(enableLeft,motorSpeedLeft);
        digitalWrite(inRight1,LOW);
        digitalWrite(inRight2,HIGH);
        digitalWrite(inLeft1,LOW);
        digitalWrite(inLeft2,HIGH);
  }

bool obstacle(){
      digitalWrite(trigger,1);
      delayMicroseconds (10);
      digitalWrite(trigger,0);
      
      while (digitalRead(echo)==0){
        sonarReading=0;
      }
      while (digitalRead(echo)==1){
        delayMicroseconds(1);
        sonarReading=sonarReading+1;
      }
      if ((sonarReading < obstacleDistance) && (sonarReading >= 0)){
        Serial.println("obstacle ditected");
        return false;
        }
      Serial.println("free to go");
      return true;
  }

