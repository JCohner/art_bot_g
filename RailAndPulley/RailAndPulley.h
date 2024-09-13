#ifndef __RAILANDPULLEY_H__
#define __RAILANDPULLEY_H__

#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>
#include "AccelStepper.h"
#include "RailAndPulleyEnumerations.h"
#include "ConfigurationVariables.h"

class RailAndPulley {
public:
  void tick();
  void setup();
  RailAndPulley() {
    previous_state = NOT_INIT;
    current_state = NOT_INIT;
    pulley_state.set_state(PulleyPositionState::NOT_INIT);
    rail_state.set_state(RailPositionState::NOT_HOMED);
    arm_state.set_state(ArmCommandState::NONE);
  }
private:
  enum State {
    NOT_INIT, 
    HOMING, 
    HOMED,
    MOVING_TO_HOME_OFFSET,
    AT_HOME_OFFSET,  
    MOVING_TO_POS1, 
    AT_POS1,
    MOVING_TO_OTHER_HOME,
    AT_OTHER_HOME,
    WAIT_AT_POS1_DONE,
    MOVING_TO_POS2,
    AT_POS2, 
    LIFTING_RUG, 
    RUG_LIFTED, 
    COMMANDING_ARM,
    COMMANDING_LOWER_RUG_AND_MOVING_TO_POS3,
    AT_POS3, // should be unused
    WAIT_AT_POS3_DONE,
  };

  // State maintainers
  volatile State previous_state; // this is largely used as a gate variable to ensure we only send command once
  volatile State current_state;
  volatile stateful_member<PulleyPositionState> pulley_state;
  volatile stateful_member<RailPositionState> rail_state;
  volatile stateful_member<ArmCommandState> arm_state;

  // stepper helper functions
  void setup_stepper();
  void setup_servo();


  // sequencing function
  void command_home();
  void wait_for_home();

  void command_move_to_home_offset();
  void wait_for_move_to_home_offset();

  void command_move_to_other_home();
  void wait_for_move_to_home_other_home();

  void command_move_to_pos1();
  void wait_for_move_to_pos1();
  void wait_at_other_home();

  void command_move_to_pos2();
  void wait_for_move_to_pos2();
  
  void command_move_to_pos3();
  void wait_for_move_to_pos3();
  void wait_at_pos3();

  void command_rug_lift();
  void wait_for_rug_lift();
  
  void command_arm_sweep();
  void wait_for_arm_sweep();
  
  void command_lower_rug();
  void wait_for_lower_rug();
  
  void start_from_beggining();

  /* Pins */
  const int RAIL_HOMING_PIN = 2;
  const int RAIL_HOMING_PIN_OTHER_END = 4;
  const int PULLEY_SERVO_PIN = 6;
  const int PULLEY_HOME_SWITCH = 3;

  AccelStepper stepperX;
  Servo pulleyServo; 
  // We increment this value until it reaches home
  int initial_homing = 1;  // I really abuse this to communicate position in between states


  unsigned long lift_timer = 0;
  unsigned long pos1_wait_timer = 0;
  unsigned long pos3_wait_timer = 0;
  int ten_count = 0;
  unsigned long LIFT_TIMER_WAIT_CENTI_SECONDS = 2200;
  unsigned long POS1_TIMER_WAIT_CENTI_SECONDS = 200;
  unsigned long POS3_TIMER_WAIT_CENTI_SECONDS = 400;


  int ARM_DO_SWEEP_PIN = 13; // assert high when we want to sweep
  int ARM_DONE_SWEEPING_PIN = 11; // asssert high when done
  int ARM_RESET_PIN = 10;

}; 

#endif /* __RAILANDPULLEY_H__ */