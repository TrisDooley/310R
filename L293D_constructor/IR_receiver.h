#pragma once
#include <IRremote.h>
#define FWD_CMD 10
#define BCK_CMD 11
#define RIGHT_CMD 12
#define LEFT_CMD 13

#define RAISE_CMD 14
#define LOWER_CMD 15

class IR_receiver{
  private:

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

  int* getDriveSignal() {
    switch(cmd) {
      case FWD_CMD:
        return new int[2] {1, 0};
        break;
      case BCK_CMD:
        return new int[2] {-1, 0};
        break;
      case RIGHT_CMD:
        return new int[2] {0, 1};
        break;
      case LEFT_CMD:
        return new int[2] {0, -1};
        break;
      default:
        return new int[2] {0, 0};
    }
  }

  double getServoSignal() {
    switch(cmd) {
      case RAISE_CMD:
        return 0.8;
        break;
      case LOWER_CMD:
        return 0.2;
        break;
      default:
        return 0.2;
    }
  }
};