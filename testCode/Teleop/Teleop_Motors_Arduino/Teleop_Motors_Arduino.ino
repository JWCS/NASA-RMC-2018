/* Teleop_Motors_Arduino
 *  Runs the teleop code from the pi over serial to the motors.
 *  Do not use for final without cleanup.
 *  Needs Formatter library/files, and Ideally common fmt defs
 */

// Include Formatter.zip of Formatter.hh/cc files
#include <Formatter.hh>

val_fmt motor_msg_fmt = {"Motors_msg", '!', 3, 0, 200, 100, 100};
val_fmt motor_fmt = {"Motors", '#', 4, 1000, 2000, 1500, 500};

Formatter fmt = Formatter(2,[motor_msg_fmt,motor_fmt]);

#include <Servo.h>

Servo left;
Servo right;

int motorVals[] = [1500,1500];
#define leftInd 0
#define rightInd 1

// Reading / parsing
char inData[300];
char inChar = -1;
byte index = 0;

void setup() {
  Serial.begin(9600);
  right.attach(11);
  left.attach(3);
}

void loop() {
  while(Serial.available() > 0 && (inChar != '\0')){
    if(index < 299){
      inChar = Serial.read();
      inData[index++] = inChar;
      inData[index] = '\0';
    }
  }
  IV_list* list = fmt.parse(inData,"Motors_msg","Motors");
  IV* ivPtr;
  while(!(ivPtr = fmt.nextIV(list))){
    motorVals[ivPtr->i] = ivPtr->v;
  }
  left.writeMicroseconds(motorVals[leftInd]);
  right.writeMicroseconds(motorVals[rightInd]);
}
