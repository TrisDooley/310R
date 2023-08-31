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
  }
  void drive(double* controls) {
    m1.setSpeed(controls[0]-controls[1]);
    m2.setSpeed(controls[0]+controls[1]);
  }
};