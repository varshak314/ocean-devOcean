/*Combination of BlueRobotics Servo code and AdafruitPWMServoDriver code
and code from the python to arduino code YouTube link*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

String InBytes;

byte servoPin9 = 9;
byte servoPin10 =10;
Servo servo9;
Servo servo10;


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  servo9.attach(servoPin9);
  servo10.attach(servoPin10);

  servo9.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo10.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(7000); // delay to allow the ESC to recognize the stopped signal

  

}

int sig9 = 1600; //for servo 9
int sig10 = 1600; //for servo 10

void loop() {
  
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) 
  {
    Serial.write("in loop");
    InBytes = Serial.readStringUntil('\n');
    if(InBytes == "c")
    {
      servo9.writeMicroseconds(1500); // send "stop" signal to ESC.
      servo10.writeMicroseconds(1500); // send "stop" signal to ESC.
      sig9 = 1500;
      sig10 = 1500;
      //Serial.write("stopping bottom thrusters");
      delay(7000); // delay to allow the ESC to recognize the stopped signal*/
    }
    if(InBytes == "w")
    {
      if(sig9<1900)
      {
        sig9 = sig9 + 50;
        //Serial.write("Increased sig9");
      }
      /*else
      {
        Serial.write("sig9 at max");
      }*/
    }
    if(InBytes == "x")
    {
      if(sig9>1100)
      {
        sig9 = sig9 - 50;
        //Serial.write("Decreased sig9");
      }
      /*else
      {
        Serial.write("sig9 at min");
      }*/
    }
    if(InBytes == "s")
    {
        sig9 =1500;
        //Serial.write("sig9 1500");
    }
    //SERVO 10
    if(InBytes == "q")
    {
      if(sig10<1900)
      {
        sig10 = sig10 + 50;
        //Serial.write("Increased sig10");
      }
      /*else
      {
        Serial.write("sig10 at max");
      }*/
    }
    if(InBytes == "z")
    {
      if(sig10>1100)
      {
        sig10 = sig10 - 50;
        //Serial.write("Decreased sig10");
      }
      /*else
      {
        Serial.write("sig10 at min");
      }*/
    }
    if(InBytes == "a")
    {
        sig10 =1500;
        //Serial.write("sig10 1500");
    }
    /*else 
    {
      Serial.write("invalid input");
    }*/
    servo9.writeMicroseconds(sig9); 
    servo10.writeMicroseconds(sig10);
    //delay(500);

  }
  else
  {
    servo9.writeMicroseconds(1500); // send "stop" signal to ESC.
    servo10.writeMicroseconds(1500); // send "stop" signal to ESC.
    sig9 = 1500;
    sig10 = 1500;
    delay(7000); // delay to allow the ESC to recognize the stopped signal
  }

}
