//****************************** QTR sensor panel **************************************
#include <QTRSensors.h>
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   52     // emitter is controlled by digital pin 52

QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];

//****************************************** Encoder ************************************
#include <Encoder.h>
Encoder knobLeft(10, 11);
Encoder knobRight(8, 9);
long oldPosition  = -999;
#define setPosition -2250 //value for turn 90 degrees

//***************************************** Motors **********************************
int enableRight = 7;
int inRight1 = 5;
int inRight2 = 6;

int enableLeft = 2;
int inLeft1 = 3;
int inLeft2 = 4;

//define the motor speeds here while tuning
int motorSpeedRight = 60;
int motorSpeedLeft = 60;
#define white 600
#define black 2500

//****************** Sonar sensor *********************
int sonarReading;
int trigger = 39;
int echo = 38;
#define obstacleDistance 150

//******************* other **************************
#define KP .25
#define KD 4
int lastError = 0;

//************************************* void setup() *****************************************
void setup() {
  //******************* motors ***********************
  pinMode(enableRight,OUTPUT);
  pinMode(enableLeft,OUTPUT);
  pinMode(inRight1,OUTPUT);
  pinMode(inRight2,OUTPUT);
  pinMode(inLeft1,OUTPUT);
  pinMode(inLeft2,OUTPUT);
  
  //****************** Sonar sensor *****************
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT); 
  delay(500);
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1000);

}
//char* directionArray[] = {"F","S", "F", "B", "F","L", "F", "L", "F", "L", "F", "R", "F", "B", "F", "L", "F", "R", "F", "R", "F", "L", "F"};
//char* directionArray[] = {"F", "R", "F", "L", "F", "L", "F", "R", "F" , "B" , "F", "L", "R", "F", "R", "L", "F"};
char* directionArray[] = {"F", "R", "F", "S", "F", "S", "F", "L", "F","R","F","L","F","B"};
//************************ void loop() **********************************
void loop() {
for (int i = 0; i <= sizeof(directionArray) - 1; i++){
  Serial.println("for loop");
  Serial.println(directionArray[i]);
  if (directionArray[i] == "F"){
      Serial.println("forward");
      forward();
      }
   if (directionArray[i] == "S"){
      Serial.println("Skip");
      skip();
      }
   if (directionArray[i] == "B"){
      Serial.println("Turn back");
      turnBack();
      }
    if (directionArray[i] == "L"){
      Serial.println("Turn left and go forward");
      turnLeft();
      forward();
      }
    if (directionArray[i] == "R"){
      Serial.println("Turn right and go forward");
      turnRight();
      forward();
      }
    if (directionArray[i] == "W"){
      Serial.println("Wait");
      delay(60000);//wait at the table for 10s
      }
  }
}
