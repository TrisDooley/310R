  //Remote assignments:
//	IR_Button_VolUp = Forward
//	IR_Button_VolDown = Reverse
//	IR_Button_Play = All Stop
//	IR_Button_EQ = Servo
//Include IR Remote Library by Ken Shirriff
//hashtag is part of include library statement
#include "TinyIRReceiver.hpp"
#include <Servo.h>

//Define mapped buttons
#define IR_Button_Power 69
#define IR_Button_VolUp 70
#define IR_Button_Func 2
#define IR_Button_Back 68
#define IR_Button_Play 64
#define IR_Button_Forward 67
#define IR_Button_Down 8
#define IR_Button_VolDown 21
#define IR_Button_Up 10
#define IR_Button_0 12
#define IR_Button_EQ 25
#define IR_Button_ST 14
#define IR_Button_1 16
#define IR_Button_2 17
#define IR_Button_3 18
#define IR_Button_4 20
#define IR_Button_5 21
#define IR_Button_6 22
#define IR_Button_7 24
#define IR_Button_8 25
#define IR_Button_9 26

#define RECV_PIN 12 //Define sensor pin

#define FWD_PIN 8
#define REV_PIN 7
#define SPD_PIN 6
#define Servo_PIN 11

int cmd = 0;
int filtered_cmd = 1;
Servo flag_servo;

void setup(){
  Serial.begin(9600); //Output to Serial Monitor @ 9600 Baud
  IrReceiver.begin(RECV_PIN); //Enable IR Receiver
  
  pinMode(FWD_PIN, OUTPUT);
  pinMode(REV_PIN, OUTPUT);
  pinMode(SPD_PIN, OUTPUT);
  flag_servo.attach(Servo_PIN);
}

//Loops constantly during operation, shows information sent to serial monitor
void loop(){ 
  if(IrReceiver.decode()){
    cmd = IrReceiver.decodedIRData.command;
    if(cmd == 0 || cmd == 64) {} else {
      filtered_cmd = cmd;
    } 
  	IrReceiver.resume();
  }
  if(IrReceiver.isIdle()){} else {
  switch(filtered_cmd) {
    //Go forward
    case IR_Button_VolUp:
    	digitalWrite(FWD_PIN, HIGH);
    	digitalWrite(REV_PIN, LOW);
    	analogWrite(SPD_PIN, 255);
      Serial.println("forward");
    	break;
    //Go backward
    case IR_Button_VolDown:
    	digitalWrite(FWD_PIN, LOW);
    	digitalWrite(REV_PIN, HIGH);
    	analogWrite(SPD_PIN, 255);
      Serial.println("reverse");
    	break;
    //All stop
    case IR_Button_Power:
    	analogWrite(SPD_PIN, 0);
      Serial.println("stop");
    	break;
    //Servo
    case IR_Button_EQ:
      Serial.println("servo start");
      flag_servo.write(0);
    	delay(1000);
      flag_servo.write(180);
      Serial.println("servo end");
      filtered_cmd = 1;
    	break;
   	default:
   		Serial.print("Unbound button: ");
    	Serial.println(filtered_cmd);
  }
  }
}

//Must map keys for IR remote
//Real life mapping: (by rows, down columns)
//69, 70, 71
//68, 64, 67
//7, 21, 9
//22, 25, 13
//12, 24, 94
//8, 28, 90
//66, 82, 74