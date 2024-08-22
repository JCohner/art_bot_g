#include "RailAndPulley.h"
/*
Josh Cohen

Note on archtiecture: 
command_* functions are built as gates to send desrired command once and then transition to
wait_* state which will poll continously until condition checked in that state returns 

The tick function should be called at a fixed frequency from a timer interupt. 
Likely the Serial.writes will have to be commented out. 
*/

void RailAndPulley::setup(){
  setup_stepper();
  setup_servo();
  Serial.println("Setup servo and stepper");
   digitalWrite(SS, HIGH); // disable Slave Select // TODO just wire slaves low as it is only one
   SPI.begin ();
   SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
}

void RailAndPulley::tick(){
  switch(current_state){
    case NOT_INIT:
      command_home();
      break;
    case HOMING:
      wait_for_home();
      break;
    case HOMED:
      command_move_to_home_offset();
      break;
    case MOVING_TO_HOME_OFFSET:
      wait_for_move_to_home_offset();
      break;
    case AT_HOME_OFFSET:
      command_move_to_pos1();
      break;
    case MOVING_TO_POS1:
      wait_for_move_to_pos1();
      break;
    case AT_POS1:
      wait_at_pos1();
      break;
    case WAIT_AT_POS1_DONE:
      command_move_to_pos2();
      break;
    case MOVING_TO_POS2:
      wait_for_move_to_pos2();
      break;
    case AT_POS2:
      command_rug_lift();
      break;
    case LIFTING_RUG:
      wait_for_rug_lift(); // TODO: G make this shit happen
      break;
    case RUG_LIFTED:
      command_arm_sweep(); // TODO: G make this shit happen
      break;
    case COMMANDING_ARM:
      wait_for_arm_sweep();
      break;
    case ARM_SWEEP_DONE:
      command_lower_rug();
      break;
    case COMMANDING_LOWER_RUG:
      wait_for_lower_rug(); // TODO: G make this shit happen
      break;
    case RUG_LOWERED:
      command_move_to_pos3(); 
      break;
    case MOVING_TO_POS3:
      wait_for_move_to_pos3();
      break;
    case AT_POS3:
      wait_at_pos3();
      break;
    case WAIT_AT_POS3_DONE: 
      start_from_beggining(); // TODO: may be inelegant, start from home we can decide if theres a cooler way in future
      break;
  }
}

// Send the command to home. (NOT ACTUALLY USED ATM)
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
  
  /*
  TODO: We should instead have a jog call (i think runSpeed()) in the command section 
  and then just wait to detect homing switch, this is fine for now.
  NOTE: MAKES HOMING SPEED DEPENDENT ON LOOP SPEED FOR NOW
  */
  stepperX.moveTo(initial_homing);
  initial_homing+=1;  
  stepperX.run();

  // Circumventing drive for detecting home
  //NOTE: pin set to INPUT_PULLUP the switch pulls the signal down so we need to check when it goes low.
  if (!digitalRead(RAIL_HOMING_PIN)){ 
    // increment current state to indicate home reached
    current_state = RailAndPulley::State::HOMED;
    Serial.print("HOMED at pos: "); Serial.print(initial_homing); Serial.println(" ");
  }
}

// Send the command to home.offset (NOT ACTUALLY USED ATM)
// Intended to transition from HOMED -> MOVING_TO_HOME_OFFSET state to indicate homing command sent.
void RailAndPulley::command_move_to_home_offset(){
  Serial.println("Sending move to home offset command..."); 
  // Cheff off homing commands 
  // NOTE: needed setup for the ensuing operation to work
  stepperX.setCurrentPosition(0); // Set the current position as zero for now
  initial_homing=-1;  // Go CCW

  // Increment state to HOMING
  previous_state = current_state; // cache HOMED
  current_state = RailAndPulley::State::MOVING_TO_HOME_OFFSET;
}

// Check if home offset position has been reached
// Intended to transition from MOVING_TO_HOME_OFFSET -> AT_HOME_OFFSET to indicate home has been reached
void RailAndPulley::wait_for_move_to_home_offset(){
  // print once gate
  if (previous_state == RailAndPulley::State::HOMED){
    Serial.println("Waiting for home...");
    previous_state = RailAndPulley::State::MOVING_TO_HOME_OFFSET;
  }
  
  /*
  TODO: We should instead have a jog call (i think runSpeed()) in the command section 
  and then just wait to detect homing switch, this is fine for now.
  NOTE: MAKES HOMING SPEED DEPENDENT ON LOOP SPEED FOR NOW
  */
  stepperX.moveTo(initial_homing);
  initial_homing-=1;  
  stepperX.run();

  // Circumventing drive for detecting home
  //NOTE: pin set to INPUT_PULLUP the switch pulls the signal down so we need to check when it goes low.
  if (digitalRead(RAIL_HOMING_PIN)){ 
    // increment current state to indicate home reached
    current_state = RailAndPulley::State::AT_HOME_OFFSET;
    Serial.println("AT HOME OFFSET");
    stepperX.setCurrentPosition(HOME_CORRECTION_VALUE);  // 7600 is the furthest left end of the rail
  }
}

// Send command to move to sweep
// Intended to transition from AT_HOME_OFFSET -> MOVING_TO_SWEEP to indicate moving to sweep command has been sent
void RailAndPulley::command_move_to_pos1(){
  Serial.println("Move to sweep command..."); 
  // Cheff off move to sweep command (not quite it just sets an internal count, .run() is required to actually move)  
  stepperX.moveTo(POSITION_1);

  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache AT_HOME_OFFSET
  current_state = RailAndPulley::State::MOVING_TO_POS1;
}

// Wait for rail to reach sweep position
// Intended to transition from MOVING_TO_SWEEP -> AT_POS1 to indicate we have reached the sweep position
void RailAndPulley::wait_for_move_to_pos1(){
  // print once gate
  if (previous_state == RailAndPulley::State::AT_HOME_OFFSET){
    Serial.println("Waiting for move to pos1..");
    previous_state = RailAndPulley::State::MOVING_TO_POS1;
  }

  // As per library specification this has to be called once per loop. We could circumevent if really needed for more constant speed thangs.
  stepperX.run();

  int pos_difference = RailPosition::POSITION_1 - stepperX.currentPosition();
  // Whatever mechanism we use to detect at sweep pos
  if (pos_difference == 0){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::AT_POS1;
    Serial.println("AT SWEEP");
  }
}

void RailAndPulley::wait_at_pos1(){
  if (previous_state == RailAndPulley::State::MOVING_TO_POS1){
    previous_state = RailAndPulley::State::AT_POS1;
    pos1_wait_timer = micros();
    Serial.println("Waiting at pos1");
    return; // TODO i think I can take out now
  }

  // NOTE: This was really weird, counting was super difficult. For some reason at a certain point it stopped counting well ~11 million. Maybe has to do with how math was done at CPU level? Not sure play with this
  unsigned long current_ms = micros();
  long delta = current_ms - pos1_wait_timer;
  if (delta % 10000000){
    ten_count++;
    pos1_wait_timer = current_ms;
  }
 
  static int print_slow = 0;
  if ((print_slow++ % 20) == 0)
    Serial.print(".");
  

  if (ten_count > POS1_TIMER_WAIT_CENTI_SECONDS){
    Serial.println("");
    // increment current state to indicate at home
    current_state = RailAndPulley::State::WAIT_AT_POS1_DONE;
    Serial.println("Done waiting for pos 1 wait..._");
    ten_count = 0;
  }
}

void RailAndPulley::command_move_to_pos2(){
  Serial.println("Move to pos2..."); 
  // Cheff off move to sweep command (not quite it just sets an internal count, .run() is required to actually move)  
  stepperX.moveTo(POSITION_2);

  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache WAIT_AT_POS1_DONE
  current_state = RailAndPulley::State::MOVING_TO_POS2;
}

// Wait for rail to reach sweep position
// Intended to transition from MOVING_TO_POS2 -> AT_POS2 to indicate we have reached the sweep position
void RailAndPulley::wait_for_move_to_pos2(){
  // print once gate
  if (previous_state == RailAndPulley::State::WAIT_AT_POS1_DONE){
    Serial.println("Waiting for move to pos2..");
    previous_state = RailAndPulley::State::MOVING_TO_POS2;
  }

  // As per library specification this has to be called once per loop. We could circumevent if really needed for more constant speed thangs.
  stepperX.run();

  int pos_difference = RailPosition::POSITION_2 - stepperX.currentPosition();
  // Whatever mechanism we use to detect at sweep pos
  if (pos_difference == 0){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::AT_POS2;
    Serial.println("AT SWEEP POSITION");
  }
}

// Send command for pulley to lift rug // TODO: this could be fired off at the same time as move to sweep oestensibly
// Intended to transition from AT_POS2 -> LIFTING_RUG to indicate moving to rug lift
void RailAndPulley::command_rug_lift(){
  Serial.println("Commanding rug lift..."); 
  // Cheff off command to lift rug
  pulleyServo.write(PulleyPosition::LIFT);
  // Increment state to LIFTING_RUG
  previous_state = current_state; // cache AT_POS2
  current_state = RailAndPulley::State::LIFTING_RUG;
}

// Wait for rug to be lifted
// Intended to transition from LIFTING_RUG -> RUG_LIFTED to indicate rug successfully lifted
void RailAndPulley::wait_for_rug_lift(){
  if (previous_state == RailAndPulley::State::AT_POS2){
    Serial.println("Lifting rug...");
    previous_state = RailAndPulley::State::LIFTING_RUG;
  }

  // Whatever mechanism we use to detect at sweep pos
  if (!digitalRead(PULLEY_HOME_SWITCH)){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::RUG_LIFTED;
    Serial.println("RUG LIFTED, stopping motion");
    pulleyServo.write(PulleyPosition::STOP);
  }
}

// Send command MCU that controls arm to begin sweeping operation
// Intended to transition from RUG_LIFTED -> COMMANDING_ARM to indicate command for sweep has been sent to other MCU
void RailAndPulley::command_arm_sweep(){
  Serial.println("Commanding arm sweep..."); 
  // Here we communicate to other MCU to start sweeping arm
  arm_interaction(BEGIN_SWEEPING);
  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache RUG_LIFTED
  current_state = RailAndPulley::State::COMMANDING_ARM;
}

// Wait for arm sweeper MCU to indicate that it has completed sweeping action
// Intended to transition from COMMANDING_ARM -> ARM_SWEEP_DONE to indicate the arm MCU has completed its task
void RailAndPulley::wait_for_arm_sweep(){
  if (previous_state == RailAndPulley::State::RUG_LIFTED){
    Serial.println("Wait for arm sweep...");
    previous_state = RailAndPulley::State::COMMANDING_ARM;
  }

  arm_interaction(TELL_ME_WHEN_SWEEP_DONE);

  // TODO put waiting debug

  // recv_val is populated by the value returned by the SPI trasnfer invoked in arm_interaction
  if (recv_val == SWEEP_DONE){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::ARM_SWEEP_DONE;
    Serial.println("Arm swept");
  }
}

// Send command to pulley to lower rug
// Intended to transition from ARM_SWEEP_DONE -> COMMANDING_LOWER_RUG to indicate command to lower rug has been sent
void RailAndPulley::command_lower_rug(){
  Serial.println("Commanding rug lower..."); 
  // Here we communicate to the rug pulley motor to lower rug
  pulleyServo.write(PulleyPosition::LOWER);
  // Increment state to COMMANDING_LOWER_RUG
  previous_state = current_state; // cache ARM_SWEEP_DONE
  current_state = RailAndPulley::State::COMMANDING_LOWER_RUG;
}

// Wait pulley to lower rug
// Intended to transition from COMMANDING_LOWER_RUG -> RUG_LOWERED to indicate rug has been lowered
void RailAndPulley::wait_for_lower_rug(){
  if (previous_state == RailAndPulley::State::ARM_SWEEP_DONE){
    previous_state = RailAndPulley::State::COMMANDING_LOWER_RUG;
    lift_timer = micros();
    Serial.println("Lowering rug. Current mircos ");
    return; // TODO i think I can take out now
  }

  // NOTE: This was really weird, counting was super difficult. For some reason at a certain point it stopped counting well ~11 million. Maybe has to do with how math was done at CPU level? Not sure play with this
  unsigned long current_ms = micros();
  long delta = current_ms - lift_timer;
  if (delta % 10000000){
    ten_count++;
    lift_timer = current_ms;
  }
 
  // // Whatever mechanism we use to detect at sweep pos
  static int print_slow = 0;
  if ((print_slow++ % 20) == 0)
    Serial.print(".");
  
  if (ten_count > LIFT_TIMER_WAIT_CENTI_SECONDS){
    Serial.println("");
    // increment current state to indicate at home
    current_state = RailAndPulley::State::RUG_LOWERED;
    pulleyServo.write(PulleyPosition::STOP);
    Serial.println("RUG LOWERED");
    ten_count = 0;
  }
}

void RailAndPulley::command_move_to_pos3(){
  Serial.println("Move to pos3..."); 
  // Cheff off move to sweep command (not quite it just sets an internal count, .run() is required to actually move)  
  stepperX.moveTo(POSITION_3);

  // Increment state to MOVING_TO_SWEEP
  previous_state = current_state; // cache RUG_LOWERED
  current_state = RailAndPulley::State::MOVING_TO_POS3;
}

// Wait for rail to reach sweep position
// Intended to transition from MOVING_TO_POS2 -> AT_POS2 to indicate we have reached the sweep position
void RailAndPulley::wait_for_move_to_pos3(){
  // print once gate
  if (previous_state == RailAndPulley::State::RUG_LOWERED){
    Serial.println("Waiting for move to pos3..");
    previous_state = RailAndPulley::State::MOVING_TO_POS3;
  }

  // As per library specification this has to be called once per loop. We could circumevent if really needed for more constant speed thangs.
  stepperX.run();

  int pos_difference = RailPosition::POSITION_3 - stepperX.currentPosition();
  // Whatever mechanism we use to detect at sweep pos
  if (pos_difference == 0){
    // increment current state to indicate at home
    current_state = RailAndPulley::State::AT_POS3;
    Serial.println("AT POS3 POSITION");
  }
}

void RailAndPulley::wait_at_pos3(){
  if (previous_state == RailAndPulley::State::MOVING_TO_POS3){
    previous_state = RailAndPulley::State::AT_POS3;
    pos3_wait_timer = micros();
    Serial.println("Waiting at pos3");
    return; // TODO i think I can take out now
  }

  // NOTE: This was really weird, counting was super difficult. For some reason at a certain point it stopped counting well ~11 million. Maybe has to do with how math was done at CPU level? Not sure play with this
  unsigned long current_ms = micros();
  long delta = current_ms - pos3_wait_timer;
  if (delta % 10000000){
    ten_count++;
    pos3_wait_timer = current_ms;
  }
 
  static int print_slow = 0;
  if ((print_slow++ % 20) == 0)
    Serial.print(".");
  

  if (ten_count > POS3_TIMER_WAIT_CENTI_SECONDS){
    Serial.println("");
    // increment current state to indicate at home
    current_state = RailAndPulley::State::WAIT_AT_POS3_DONE;
    Serial.println("Done waiting for pos 3 wait...");
    ten_count = 0;
  }
}

void RailAndPulley::start_from_beggining(){
  Serial.println("Lets give it another go...");
  initial_homing = POSITION_3;
  previous_state = NOT_INIT;
  current_state = NOT_INIT;
  arm_interaction(START_OVER);
}

// Stepper related helper functions
void RailAndPulley::setup_stepper(){
  // Initialize stepper object and set it up
  stepperX = AccelStepper(1, 9, 8);
  stepperX.setMaxSpeed(200.0);  // Set Max Speed of Stepper (Slower to get better accuracy)
  stepperX.setAcceleration(200.0);  // Set Acceleration of Stepper
  pinMode(RAIL_HOMING_PIN, INPUT_PULLUP);
}

void RailAndPulley::setup_servo(){
      pulleyServo.attach(PULLEY_SERVO_PIN);
      pulleyServo.write(PulleyPosition::STOP);
      pinMode(PULLEY_HOME_SWITCH, INPUT_PULLUP);
}

void RailAndPulley::arm_interaction(ArmInteraction command){
  digitalWrite(SS, LOW); // enable Slave Select
  recv_val = SPI.transfer (command); // TODO maybe the function should return thsi value as opposed to assigning to a member variable....
  digitalWrite(SS, HIGH); // disable Slave Select
}