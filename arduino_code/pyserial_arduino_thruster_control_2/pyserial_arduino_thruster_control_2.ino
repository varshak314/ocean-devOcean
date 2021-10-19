#include <Servo.h>
String InBytes;

byte servoPin9 = 9;
byte servoPin10 =10;
Servo servo9;
Servo servo10;

void setup() {
  Serial.begin(9600);
  //for debugging
  //pinMode(LED_BUILTIN, OUTPUT);

  servo9.attach(servoPin9); //left thruster
  servo10.attach(servoPin10); //right thruster

  servo9.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo10.writeMicroseconds(1500); // send "stop" signal to ESC.
  delay(7000); // delay to allow the ESC to recognize the stopped signal

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0) 
  {
    digitalWrite(LED_BUILTIN, HIGH);

    InBytes = Serial.readStringUntil('\n');
    //InBytes is a number: LLLLRRRR for the speed for L and R motors
    //Extract LLLL RRRR
    int i9 = (InBytes.toInt())/10000;
    int i10 = (InBytes.toInt()) - i9*10000;
    //set thruster speed
    servo9.writeMicroseconds(i9);
    servo10.writeMicroseconds(i10);
    //Code for debugging
    /*if(InBytes == "o")
    {
      servo9.writeMicroseconds();
      servo9.writeMicroseconds(1700);
      Serial.write("LED on");
    }
    if(InBytes == "f")
    {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.write("LED off");
    }
    else 
    {
      Serial.write("invalid input");
    }
  }*/
  }

}
