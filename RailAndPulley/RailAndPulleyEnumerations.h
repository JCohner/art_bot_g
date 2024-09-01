#ifndef __RAILANDPULLEY_ENUMS_H__
#define __RAILANDPULLEY_ENUMS_H__

// For systems (rail and pulley) where want to check enumerated state against enumerated value
template <typename S_ENUM>
struct stateful_member {
private:
  S_ENUM state;
  S_ENUM prev_state;

  // TODO: could take value enum as template and then map between desired state and values...

public:
  void set_state(S_ENUM new_state) { 
    prev_state = state;
    state = new_state;
  }
  S_ENUM get_state() {return state;}

  bool check_edge() {
    auto ret_val = state != prev_state;
    prev_state = state; // .checking edge, updates or notion of last state so the edge will no longer remain
    return ret_val;
  }
  // Check specific edge, do not increment if no match
  bool check_edge(S_ENUM specific_previous_state) {
    if (prev_state != specific_previous_state) return false;
    auto ret_val = state != prev_state;
    prev_state = state; // .checking edge, updates or notion of last state so the edge will no longer remain
    return ret_val;
  }
};

// Rail State Machine
enum struct RailPositionState {
  NOT_HOMED,
  HOMING,
  HOMED,
  MOVING_TO_HOME_OFFSET,
  AT_HOME_OFFSET,  
  MOVING_TO_POS1,
  AT_POS1,
  WAIT_AT_POS1_DONE,
  MOVING_TO_POS2,
  AT_POS2,
  MOVING_TO_POS3,
  AT_POS3,
  WAIT_AT_POS3_DONE
};

enum struct RailPositionValue {
  POSITION_1 = 1,
  POSITION_2 = 2500,
  POSITION_3 = 6600,
  HOME_CORRECTION_VALUE = 6800
};

// Pulley State Machine
enum struct PulleyPositionState {
  NOT_INIT,
  LIFTING_RUG,
  RUG_LIFTED,
  LOWERING_RUG,
  RUG_LOWERED
};

enum struct PulleyPositionValue {
  STOP = 94,// This is the stop value for the servo when on continuous mode
  LIFT = 135, // In continous mode this instructs the servo to lift in the correct direction: CCW
  LOWER = 45 // Continous mode CW command
};

// Arm State Machine
enum struct ArmCommandState {
  NONE,
  COMMANDING_ARM,
  ARM_SWEEP_DONE
};

// TODO this should be defined in two places.. move up a directory and reference
enum struct ArmCommandValue {
  NONE = 0,
  BEGIN_SWEEPING = 1,
  TELL_ME_WHEN_SWEEP_DONE = 3,
  START_OVER = 5
};

enum struct ArmResponseValue {
  NOTHING = 0,
  I_AM_SWEEPING = 2,
  SWEEP_DONE = 4, 
  STARTING_OVER = 5
};

enum struct ProgramState {
  SETUP_RAIL_AND_MOVE_TO_SWEEP,
  SWEEP_INTERACTION,
  MOVE_FROM_SWEEP
};

#endif /* __RAILANDPULLEY_ENUMS_H__ */