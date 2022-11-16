#include <Servo.h>

//Threshold for servo motor control with muscle sensor. 
//You can set a threshold according to the maximum and minimum values of the muscle sensor.
#define THRESHOLD 600

//Pin number where the sensor is connected. (Analog 0)
#define EMG_PIN 0

//Pin number where the servo motor is connected. (Digital PWM 3)
#define SERVO_PIN 9

//Define Servo motor
Servo SERVO_1;
#define IN_PIN A0
#define WINDOW_SIZE 25

int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

/*-------------------------------- void setup ------------------------------------------------*/

void setup(){
  
  //BAUDRATE set to 115200, remember it to set monitor serial properly. 
  //Used this Baud Rate and "NL&CR" option to visualize the values correctly.
  Serial.begin(9600);

  pinMode(IN_PIN, INPUT);
  
  //Set servo motor to digital pin 3
  SERVO_1.attach(SERVO_PIN);
}

/*--------------------------------  void loop  ------------------------------------------------*/

void loop(){

  //The "Value" variable reads the value from the analog pin to which the sensor is connected.
  int value = analogRead(EMG_PIN);

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  VALUE = analogRead(IN_PIN);        // Read the next sensor value
  READINGS[INDEX] = VALUE;           // Add the newest reading to the window
  SUM = SUM + VALUE;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result

  Serial.print(VALUE);
  Serial.print(",");
  Serial.println(AVERAGED);
  
  delay(25); 

  //If the sensor value is GREATER than the THRESHOLD, the servo motor will turn to 170 degrees.
  if(value > THRESHOLD){
    SERVO_1.write(200);
  }

  //If the sensor is LESS than the THRESHOLD, the servo motor will turn to 10 degrees.
  else{
    SERVO_1.write(150);
  }

  //You can use serial monitor to set THRESHOLD properly, comparing the values shown when you open and close your hand.
  Serial.println(value);
}
