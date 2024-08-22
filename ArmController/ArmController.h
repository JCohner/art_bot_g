#ifndef __ARMCONTROLLER_H__
#define __ARMCONTROLLER_H__

#include <Arduino.h>
#include <Servo.h>

class ArmController {
public:
  ArmController(){
    state_ = NOT_INIT;
  }
  // TODO this should be defined in two places.. move up a directory and reference
  enum ArmInteraction {
    NONE = 0,
    BEGIN_SWEEPING = 1,
    I_AM_SWEEPING = 2, // ONLY EVER SENT FROM ARM
    TELL_ME_WHEN_SWEEP_DONE = 3,
    SWEEP_DONE = 4, // ONLY EVER SENT FROM ARM 
    ERROR = 5
  };

  enum ArmState {
    NOT_INIT, 
    EXECUTING_COMMAND,
    DONE
  };
  void setup();
  void do_arm_animation();
  ArmController::ArmState get_state() {return state_;}
  ArmController::ArmInteraction interact(ArmController::ArmInteraction command);

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