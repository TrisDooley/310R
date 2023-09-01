#include <IRremote.h>

// C++ code
//

int bckPin1 = 4;
int fwdPin1 = 2;
int spdPin1 = 3;
int bckPin2 = 7;
int fwdPin2 = 5;
int spdPin2 = 6;
int rcv_pin = 13;
int cmd;
double fwd;
double trn;
int timeout = 200; //Motor timeout in millis
unsigned long last_time;
double killed;
double m1s;
double m2s;
double accel = 0.001;

void setup()
{
  pinMode(fwdPin1, OUTPUT);
  pinMode(bckPin1, OUTPUT);
  pinMode(spdPin1, OUTPUT);
  pinMode(fwdPin2, OUTPUT);
  pinMode(bckPin2, OUTPUT);
  pinMode(spdPin2, OUTPUT);
  
  Serial.begin(9600);
  IrReceiver.begin(rcv_pin);
}

void loop()
{
  if(IrReceiver.decode()) {
    killed = false;
    if(IrReceiver.decodedIRData.command != 0) {
      cmd = IrReceiver.decodedIRData.command;
    }
    // Serial.println(cmd);
    IrReceiver.resume();
    last_time = millis();
    Serial.println(last_time);
  } else {
    if(millis() - last_time > timeout && !killed) {
      cmd = 0;
      Serial.println(millis() - last_time);
      // Serial.println("killed!");
      killed = true;
    }
  }
  if(cmd == 70){ 
    fwd = 1;
    trn = 0;
  } else if(cmd == 21) {
    fwd = -1;
    trn = 0;
  } else if(cmd == 68) {
    trn = 1;
    fwd = 0;
  } else if(cmd == 67) {
    trn = -1;
    fwd = 0;
  } else if(cmd == 0) {
    fwd = 0;
    trn = 0;
  }
  diff_drive(fwd, trn);
}

void diff_drive(double spd, double turn) {
  m1_speed(spd-turn);
  m2_speed(spd+turn);
}

void m1_speed(double speed) {
//   if(speed > 0) {
//   	digitalWrite(fwdPin1, HIGH);
//   	digitalWrite(bckPin1, LOW);
//   	analogWrite(spdPin1, 255*speed);
//   } else if(speed < 0) {
//   	digitalWrite(fwdPin1, LOW);
//   	digitalWrite(bckPin1, HIGH);
//   	analogWrite(spdPin1, 255*abs(speed));
//   } else {
//     analogWrite(spdPin1, 0);
//   }
  if(speed > 0) {
    m1s += accel;
    if(m1s > 1) {
      m1s = 1;
    }
  } else if(speed < 0) {
    m1s -= accel;
    if(m1s < -1) {
      m1s = -1;
    }
  } else {
    m1s *= 0.99;
  }

  if(m1s > 0) {
  	digitalWrite(fwdPin1, HIGH);
  	digitalWrite(bckPin1, LOW);
  	analogWrite(spdPin1, 255*m1s);
  } else if(m1s < 0) {
    digitalWrite(fwdPin1, LOW);
  	digitalWrite(bckPin1, HIGH);
  	analogWrite(spdPin1, 255*abs(m1s));
  } else {
    analogWrite(spdPin1, 0);
  }
}

void m2_speed(double speed) {
  if(speed > 0) {
  	digitalWrite(fwdPin2, HIGH);
  	digitalWrite(bckPin2, LOW);
  	analogWrite(spdPin2, 255*speed);
  } else if(speed < 0) {
  	digitalWrite(fwdPin2, LOW);
  	digitalWrite(bckPin2, HIGH);
  	analogWrite(spdPin2, 255*abs(speed));
  } else {
    analogWrite(spdPin2, 0);
  }
}