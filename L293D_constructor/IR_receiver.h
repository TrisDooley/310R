#pragma once
#include <IRremote.h>

class IR_receiver{
  private:
  int fwd_code = 10;
  int rev_code = 11;
  int right_code = 12;
  int left_code = 13;
  int raise_code = 14;
  int lower_code = 15;

  public:
    int cmd;
    IRrecv receiver;
  void init(int receiver_pin) {
    IRrecv receiver(receiver_pin);
    receiver.enableIRIn();
    receiver.blink13(true);
  }

  void update() {
    if(receiver.decode()) {
      cmd = receiver.decodedIRData.command;
    }
    receiver.resume();
  }

  double* getDriveSignal() {
    if(cmd == fwd_code) {
      return new double[2] {1, 0};
    } else if(cmd == rev_code) {
      return new double[2] {-1, 0};
    } else if(cmd == right_code) {
      return new double[2] {0, 1};
    } else if(cmd == left_code) {
      return new double[2] {0, -1};
    } else {
      return new double[2] {0, 0};
    }
  }

  double getServoSignal() {
    if(cmd == raise_code) {
      return 0.8;
    } else if(cmd == lower_code) {
      return 0.2;
    } else {
      return 0.2;
    }
  }
};