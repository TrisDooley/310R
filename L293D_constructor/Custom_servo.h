#pragma once
#include <Servo.h>

class Custom_servo {
  private:
    double current_pos;
    double goal_pos;

  public:
  Servo s;
  
  void init(int pin, int min_us, int max_us) {
    this->s=s;
    s.attach(pin, min_us, max_us);
    Serial.print("servo setup");
  }

  void setPos(double pos){
    s.write(pos*180);
  }
};