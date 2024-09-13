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
  MOVING_TO_OTHER_HOME,
  AT_OTHER_HOME,
  WAIT_AT_POS1_DONE,
  MOVING_TO_POS2,
  AT_POS2,
  MOVING_TO_POS3,
  AT_POS3,
  WAIT_AT_POS3_DONE
};

// Pulley State Machine
enum struct PulleyPositionState {
  NOT_INIT,
  LIFTING_RUG,
  RUG_LIFTED,
  LOWERING_RUG,
  RUG_LOWERED
};


// Arm State Machine
enum struct ArmCommandState {
  NONE,
  COMMANDING_ARM,
  COMMAND_RECEIVED,
  ARM_SWEEP_DONE
};

enum struct ProgramState {
  SETUP_RAIL_AND_MOVE_TO_SWEEP,
  SWEEP_INTERACTION,
  MOVE_FROM_SWEEP
};

#endif /* __RAILANDPULLEY_ENUMS_H__ */