#include "RailAndPulley.h"
#include <Arduino.h>

/*
Josh Cohen

Note on archtiecture: 
command_* functions are built as gates to send desrired command once and then transition to
wait_* state which will poll continously until condition checked in that state returns 

The tick function should be called at a fixed frequency from a timer interupt. 
Likely the Serial.writes will have to be commented out. 
*/

void RailAndPulley::tick(){
  switch(current_state){
    case NOT_INIT:
      command_home();
      break;
    case HOMING:
      wait_for_home();
      break;
    case HOMED:
      command_move_to_sweep();
      break;
    case MOVING_TO_SWEEP:
      wait_for_move_to_sweep();
      break;
    case AT_SWEEP:
      command_rug_lift();
      break;
    case LIFTING_RUG:
      wait_for_rug_lift();
      break;
    case RUG_LIFTED:
      command_arm_sweep();
      break;
    case COMMANDING_ARM:
      wait_for_arm_sweep();
      break;
    case ARM_SWEEP_DONE:
      command_lower_rug();
      break;
    case COMMANDING_LOWER_RUG:
      wait_for_lower_rug();
      break;
    case RUG_LOWERED:
      start_from_beggining(); // TODO: may be inelegant, start from home we can decide if theres a cooler way in future
      break;
  }
}

// Send the command to home.
// Intended to transition from NOT_INIT -> HOMING state to indicate homing command sent.
void RailAndPulley::command_home(){
  Serial.println("Sending homing command..."); 
  // Cheff off homing commands 
  ;
  // Increment state to HOMING
  current_state = RailAndPulley::State::HOMING;
}

// Check if home has been reached
// Intended to transition from HOMING -> HOMED to indicate home has been reached
void RailAndPulley::wait_for_home(){
  // print once gate
  if (previous_state == RailAndPulley::State::NOT_INIT){
    Serial.println("Waiting for home...");
    previous_state = RailAndPulley::State::HOMING;
  }

  // Circumventing drive for detecting home.
  if (digitalRead(HOMING_PIN)){
    // increment current state to indicate home reached
    current_state = RailAndPulley::State::HOMED;
    Serial.println("HOMED");
  }
}

// Send command to move to sweep
// Intended to transition from HOMED -> MOVING_TO_SWEEP to indicate moving to sweep command has been sent
void RailAndPulley::command_move_to_sweep(){
  Serial.println("Sending move to sweep command..."); 
  // Cheff off move to sweep command
  ;
  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache HOMED
  current_state = RailAndPulley::State::MOVING_TO_SWEEP;
}

// Wait for rail to reach sweep position
// Intended to transition from MOVING_TO_SWEEP -> AT_SWEEP to indicate we have reached the sweep position
void RailAndPulley::wait_for_move_to_sweep(){
  // print once gate
  if (previous_state == RailAndPulley::State::HOMED){
    Serial.println("Waiting for move to sweep...");
    previous_state = RailAndPulley::State::MOVING_TO_SWEEP;
  }

  // Whatever mechanism we use to detect at sweep pos
  if (digitalRead(SWEEP_PIN)){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::AT_SWEEP;
    Serial.println("AT SWEEP");
  }
}

// Send command for pulley to lift rug // TODO: this could be fired off at the same time as move to sweep oestensibly
// Intended to transition from AT_SWEEP -> LIFTING_RUG to indicate moving to rug lift
void RailAndPulley::command_rug_lift(){
  Serial.println("Commanding rug lift..."); 
  // Cheff off command to lift rug
  ;
  // Increment state to LIFTING_RUG
  previous_state = current_state; // cache AT_SWEEP
  current_state = RailAndPulley::State::LIFTING_RUG;
}

// Wait for rug to be lifted
// Intended to transition from LIFTING_RUG -> RUG_LIFTED to indicate rug successfully lifted
void RailAndPulley::wait_for_rug_lift(){
  if (previous_state == RailAndPulley::State::AT_SWEEP){
    Serial.println("Lifting rug...");
    previous_state = RailAndPulley::State::LIFTING_RUG;
  }

  // Whatever mechanism we use to detect at sweep pos
  if (digitalRead(RUG_LIFT_PIN)){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::RUG_LIFTED;
    Serial.println("RUG LIFTED");
  }
}

// Send command MCU that controls arm to begin sweeping operation
// Intended to transition from RUG_LIFTED -> COMMANDING_ARM to indicate command for sweep has been sent to other MCU
void RailAndPulley::command_arm_sweep(){
  Serial.println("Commanding rug lift..."); 
  // Here we communicate to other MCU to start sweeping arm
  ;
  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache RUG_LIFTED
  current_state = RailAndPulley::State::COMMANDING_ARM;
}

// Wait for arm sweeper MCU to indicate that it has completed sweeping action
// Intended to transition from COMMANDING_ARM -> ARM_SWEEP_DONE to indicate the arm MCU has completed its task
void RailAndPulley::wait_for_arm_sweep(){
  if (previous_state == RailAndPulley::State::RUG_LIFTED){
    Serial.println("Lifting rug...");
    previous_state = RailAndPulley::State::COMMANDING_ARM;
  }

  // Whatever mechanism we use to detect at sweep pos
  if (digitalRead(ARM_SWEEP_DONE_PIN)){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::ARM_SWEEP_DONE;
    Serial.println("RUG LIFTED");
  }
}

// Send command to pulley to lower rug
// Intended to transition from ARM_SWEEP_DONE -> COMMANDING_LOWER_RUG to indicate command to lower rug has been sent
void RailAndPulley::command_lower_rug(){
  Serial.println("Commanding rug lower..."); 
  // Here we communicate to the rug pulley motor to lower rug
  ;
  // Increment state to COMMANDING_LOWER_RUG
  previous_state = current_state; // cache ARM_SWEEP_DONE
  current_state = RailAndPulley::State::COMMANDING_LOWER_RUG;
}

// Wait pulley to lower rug
// Intended to transition from COMMANDING_LOWER_RUG -> RUG_LOWERED to indicate rug has been lowered
void RailAndPulley::wait_for_lower_rug(){
  if (previous_state == RailAndPulley::State::ARM_SWEEP_DONE){
    Serial.println("Lowering rug...");
    previous_state = RailAndPulley::State::COMMANDING_LOWER_RUG;
  }

  // Whatever mechanism we use to detect at sweep pos
  if (digitalRead(RUG_LOWER_PIN)){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::RUG_LOWERED;
    Serial.println("RUG LOWERED");
  }
}

void RailAndPulley::start_from_beggining(){
  Serial.println("Lets give it another go...");
  previous_state = NOT_INIT;
  current_state = NOT_INIT;
}