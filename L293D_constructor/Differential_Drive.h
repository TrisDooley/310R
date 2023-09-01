#pragma once
#include "L239D_motor.h"
class Differential_Drive {
  private:
    L239D_motor m1;
    L239D_motor m2;

  public: 

  void init(L239D_motor m1, L239D_motor m2) {
    this->m1 = m1;
    this->m2 = m2;
    Serial.print("Chassis setup");
  }
  void drive(int fwd, int trn) {
    m1.setSpeed(fwd-trn);
    m2.setSpeed(fwd+trn);
  }
};