#include "L239D_motor.h"
#include "Differential_Drive.h"
#include "IR_receiver.h"
#include "Custom_servo.h"

Custom_servo s1;

L239D_motor m1;
L239D_motor m2;
Differential_Drive chassis;

IR_receiver rc;

unsigned long lastTime;

void setup() {
  m1.init(8, 9, 10);
  m2.init(13, 12, 11);
  chassis.init(m1, m2);

  s1.init(9, 500, 2500);

  rc.init(2);
  Serial.begin(115200);
}

void loop() {
  // Serial.println(1000.0/(millis()-lastTime));
  lastTime = millis();
  rc.update();
  chassis.drive(rc.getFwdSignal(), rc.getTurnSignal());
  s1.setPos(rc.getServoSignal());
}