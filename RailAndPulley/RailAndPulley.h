#ifndef __RAILANDPULLEY_H__
#define __RAILANDPULLEY_H__

#include <Arduino.h>
#include "AccelStepper.h"

class RailAndPulley {
public:
  void tick();
  RailAndPulley() {
    previous_state = NOT_INIT;
    current_state = NOT_INIT;



    // Initialize stepper object and set it up
    stepperX = AccelStepper(1, 9, 8);
    stepperX.setMaxSpeed(200.0);  // Set Max Speed of Stepper (Slower to get better accuracy)
    stepperX.setAcceleration(200.0);  // Set Acceleration of Stepper
    setup_stepper_pins();
  }
private:
  enum State {NOT_INIT, 
              HOMING, 
              HOMED,
              MOVING_TO_HOME_OFFSET,
              AT_HOME_OFFSET,  
              MOVING_TO_SWEEP, 
              AT_SWEEP, 
              LIFTING_RUG, 
              RUG_LIFTED, 
              COMMANDING_ARM,
              ARM_SWEEP_DONE,
              COMMANDING_LOWER_RUG,
              RUG_LOWERED
            };
  volatile State previous_state; // this is largely used as a gate variable to ensure we only send command once
  volatile State current_state;

  // stepper helper functions
  void setup_stepper(); // TODO unused ATM
  void setup_stepper_pins();


  // sequencing function
  void command_home();
  void wait_for_home();

  void command_move_to_home_offset();
  void wait_for_move_to_home_offset();

  void command_move_to_sweep();
  void wait_for_move_to_sweep();
  
  void command_rug_lift();
  void wait_for_rug_lift();
  
  void command_arm_sweep();
  void wait_for_arm_sweep();
  
  void command_lower_rug();
  void wait_for_lower_rug();
  
  void start_from_beggining();

  /* Pins */
  const int RAIL_HOMING_PIN = 2;
  int SWEEP_PIN = 11; // TODO: more likely this is going to be an encoder read command or hall sensor
  int RUG_LIFT_PIN = 10; // TODO: more likely this is going to be an encoder read command or hall sensor
  int ARM_SWEEP_DONE_PIN = 9; // TODO this mocks hearing back from the other MCU that arm sweep is done
  int RUG_LOWER_PIN = 8; // TODO: more likely this is going to be an encoder read command or hall sensor

  AccelStepper stepperX;
  // We increment this value until it reaches home
  int initial_homing = 1; 

}; 

#endif /* __RAILANDPULLEY_H__ */