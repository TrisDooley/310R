  //Remote assignments:
//	IR_Button_VolUp = Forward
//	IR_Button_VolDown = Reverse
//	IR_Button_Play = All Stop
//	IR_Button_EQ = Servo
#define IR_SMALLD_NEC         //1st: define which protocol to use:
//#define IR_SMALLD_NECx      //     IR_SMALLD_NEC or IR_SMALLD_NECx, (not both);
#include <IRsmallDecoder.h>   //2nd: include the library;
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

#define RECV_PIN 2 //Define sensor pin

#define FWD_PIN 8
#define REV_PIN 7
#define SPD_PIN 6
#define Servo_PIN 9

IRsmallDecoder irDecoder(RECV_PIN);  //3rd: create one decoder object with the correct digital pin;
irSmallD_t irData;            //4th: declare one decoder data structure;

int timeout;
long lastTime;
int cmd = 1;
int filtered_cmd = 1;
Servo flag_servo;
bool repeat;
bool killed;

void setup(){
  Serial.begin(9600); //Output to Serial Monitor @ 9600 Baud
  
  pinMode(FWD_PIN, OUTPUT);
  pinMode(REV_PIN, OUTPUT);
  pinMode(SPD_PIN, OUTPUT);
  flag_servo.attach(Servo_PIN);
}

//Loops constantly during operation, shows information sent to serial monitor
void loop(){ 
  if(irDecoder.dataAvailable(irData)){
    Serial.print("decoded!");
    killed = false;
    cmd = irData.cmd;
    repeat = irData.keyHeld;
    lastTime = millis();
    if(repeat) {
      timeout = 200;
    } else {
      timeout = 600;
    }
    if(cmd == 0) {} else {
      filtered_cmd = cmd;
    } 
  }

  if(millis()-timeout > lastTime && !killed) {
    filtered_cmd = 1;
    killed = true;
  }

  switch(filtered_cmd) {
    //Go forward
    case IR_Button_Forward:
    	digitalWrite(FWD_PIN, HIGH);
    	digitalWrite(REV_PIN, LOW);
    	analogWrite(SPD_PIN, 255);
      Serial.println("forward");
    	break;
    //Go backward
    case IR_Button_Back:
    	digitalWrite(FWD_PIN, LOW);
    	digitalWrite(REV_PIN, HIGH);
    	analogWrite(SPD_PIN, 255);
      Serial.println("reverse");
    	break;
    //All stop
    // case IR_Button_Power:
    // 	analogWrite(SPD_PIN, 0);
    //   Serial.println("stop");
    // 	break;
    //Servo
    case IR_Button_EQ:
      Serial.println("servo 180");
      flag_servo.write(180);
    	break;
    case 1:
      Serial.println("off");
    	analogWrite(SPD_PIN, 0);
      flag_servo.write(0);
      filtered_cmd = 2;
      break;
    case 2:
      break;
   	default:
   		Serial.print("Unbound button: ");
    	Serial.println(filtered_cmd);
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