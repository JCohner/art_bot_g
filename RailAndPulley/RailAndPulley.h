#ifndef __RAILANDPULLEY_H__
#define __RAILANDPULLEY_H__

#include <Arduino.h>
#include <Servo.h>
#include "AccelStepper.h"

static Servo pulleyServo; 

class RailAndPulley {
public:
  void tick();
  void setup();
  RailAndPulley() {
    previous_state = NOT_INIT;
    current_state = NOT_INIT;
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
    WAIT_AT_POS1_DONE,
    MOVING_TO_POS2,
    AT_POS2, 
    LIFTING_RUG, 
    RUG_LIFTED, 
    COMMANDING_ARM,
    ARM_SWEEP_DONE,
    COMMANDING_LOWER_RUG,
    RUG_LOWERED,
    MOVING_TO_POS3,
    AT_POS3,
    WAIT_AT_POS3_DONE,
  };

  enum RailPosition {
    POSITION_1 = 1,
    POSITION_2 = 2500,
    POSITION_3 = 6600,
    HOME_CORRECTION_VALUE = 6800
  };

  enum PulleyPosition {
    STOP = 94,// This is the stop value for the servo when on continuous mode
    LIFT = 135, // In continous mode this instructs the servo to lift in the correct direction: CCW
    LOWER = 45 // Continous mode CW command
  };

  volatile State previous_state; // this is largely used as a gate variable to ensure we only send command once
  volatile State current_state;

  // stepper helper functions
  void setup_stepper();
  void setup_servo();


  // sequencing function
  void command_home();
  void wait_for_home();

  void command_move_to_home_offset();
  void wait_for_move_to_home_offset();

  void command_move_to_pos1();
  void wait_for_move_to_pos1();
  void wait_at_pos1();

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
  int SWEEP_PIN = 11; // TODO: more likely this is going to be an encoder read command or hall sensor
  int ARM_SWEEP_DONE_PIN = 8;
  AccelStepper stepperX;
  // We increment this value until it reaches home
  int initial_homing = 1; 

  // Servo pulleyServo;
  const int PULLEY_SERVO_PIN = 13;
  const int PULLEY_HOME_SWITCH = 3;


  unsigned long lift_timer = 0;
  unsigned long pos1_wait_timer = 0;
  int ten_count = 0;
  unsigned long LIFT_TIMER_WAIT_CENTI_SECONDS = 2000;
  unsigned long POS1_TIMER_WAIT_CENTI_SECONDS = 200;


}; 

#endif /* __RAILANDPULLEY_H__ */