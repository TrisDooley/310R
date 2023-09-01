#pragma once
#include <IRremote.hpp>
#include <Arduino.h>

#define FWD_CMD 70
#define BCK_CMD 82
#define RIGHT_CMD 90
#define LEFT_CMD 8
#define RAISE_CMD 9
#define LOWER_CMD 7

#define DECODE_NEC

class IR_receiver{
  private:
    int timeout = 250; //max of 32000 before the in rolls-over
    unsigned long last_command = 0;
    boolean killed = false;
    byte rcv_cmd;
    byte dummy;

  public:
    int cmd;

  void init(int receiver_pin) {
    IrReceiver.begin(receiver_pin, true);
    Serial.println("IR setup");
  }

  void update() {
    if(IrReceiver.decode()) {
      Serial.println("decoding");
      Serial.println(IrReceiver.decodedIRData.command);
      if(IrReceiver.decodedIRData.command != 0){
        cmd = IrReceiver.decodedIRData.command;
      } else {
        dummy = IrReceiver.decodedIRData.command;
      }
      IrReceiver.resume();
      last_command = millis();
      killed = false;
    }

    if(millis()-last_command > timeout && !killed) {
      killed = true;
      cmd = 0;
      Serial.println("killed!");
    }
  }

  int getFwdSignal() {
    switch(cmd) {
      case FWD_CMD:
        return 1;
        break;
      case BCK_CMD:
        return -1;
        break;
      default:
        return 0;
    }
  }

  int getTurnSignal() {
    switch(cmd) {
      case RIGHT_CMD:
        return 1;
        break;
      case LEFT_CMD:
        return -1;
        break;
      default:
        return 0;
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