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
  enum ArmCommandFromRP {
    NONE = 0,
    BEGIN_SWEEPING = 1,
    TELL_ME_WHEN_SWEEP_DONE = 3,
    START_OVER = 5
  };

  enum ArmResponseToRP {
    NOTHING = 0,
    I_AM_SWEEPING = 2,
    SWEEP_DONE = 4, 
    STARTING_OVER = 5
  };

  enum ArmState {
    NOT_INIT, 
    EXECUTING_COMMAND,
    DONE
  };

  void setup();
  void do_arm_animation();
  ArmController::ArmState get_state() {return state_;}
  void set_state(ArmController::ArmState new_state) { 
    prevState_ = state_;
    state_ = new_state;
  }

  int ARM_DO_SWEEP_PIN = 13; // assert high when we want to sweep
  int ARM_DONE_SWEEPING_PIN = 11; // asssert high when done
  int ARM_RESET_PIN = 10;

private:
  volatile ArmState state_;
  volatile ArmState prevState_;

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