#pragma once
#include <Arduino.h>
class L239D_motor {
  private: 
    int fwd_pin;
    int rev_pin;
    int spd_pin;

  public: 
  
  void init(int fwd_pin, int rev_pin, int spd_pin) {
    this->fwd_pin = fwd_pin;
    this->rev_pin = rev_pin;
    this->spd_pin = spd_pin;
    pinMode(fwd_pin, OUTPUT);
    pinMode(rev_pin, OUTPUT);
    pinMode(spd_pin, OUTPUT);
    Serial.print("motor setup");
  }

  void setSpeed(double speed) {
    if(speed > 0) {
      digitalWrite(fwd_pin, HIGH);
      digitalWrite(rev_pin, LOW);
      analogWrite(spd_pin, speed*255);
    } else if(speed < 0) {
      digitalWrite(fwd_pin, LOW);
      digitalWrite(rev_pin, HIGH);
      analogWrite(spd_pin, abs(speed)*255);
    } else {
      digitalWrite(fwd_pin, LOW);
      digitalWrite(rev_pin, LOW);
      analogWrite(spd_pin, 0);
    }
  }
};
