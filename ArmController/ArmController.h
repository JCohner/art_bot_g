#ifndef __ARMCONTROLLER_H__
#define __ARMCONTROLLER_H__

#include <Arduino.h>
#include <Servo.h>

// TODO this should be defined in two places.. move up a directory and reference
enum ArmInteraction {
  BEGIN_SWEEPING = 0,
  I_AM_SWEEPING = 1, // ONLY EVER SENT FROM ARM
  TELL_ME_WHEN_SWEEP_DONE = 2,
  SWEEP_DONE = 3, // ONLY EVER SENT FROM ARM 
  ERROR = 4
};

enum ArmState {
  NOT_INIT, 
  EXECUTING_COMMAND,
  DONE
};

class ArmController {
public:
  ArmController(){
    state_ = NOT_INIT;
  }

  void setup();
  void do_arm_animation();
  ArmState get_state() {return state_;}
  ArmInteraction interact(ArmInteraction command);



private:

  ArmState state_;

  Servo Shoulder;  // create servo object to control a servo
  Servo UpperArm;
  Servo Elbow;
  Servo Wrist;
  // twelve servo objects can be created on most boards

  int posShoulder = 90;    // variable to store the servo position
  int posUpperArm = 100;
  int posElbow = 0;
  int posWrist = 30;

};

#endif /* ARMCONTROLLER */