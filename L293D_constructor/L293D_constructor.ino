#include "L239D_motor.h"
#include "Differential_Drive.h"
#include "IR_receiver.h"
#include "Custom_servo.h"

Custom_servo s1;

L239D_motor m1;
L239D_motor m2;
Differential_Drive chassis;

IR_receiver rc;

void setup() {
  m1.init(2, 3, 4);
  m2.init(5, 6, 7);
  chassis.init(m1, m2);

  s1.init(9, 500, 2500);

  rc.init(13);
}

void loop() {
  rc.update();
  chassis.drive(rc.getDriveSignal());
  s1.setPos(rc.getServoSignal());
}