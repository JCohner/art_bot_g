#ifndef __ARMCONTROLLER_H__
#define __ARMCONTROLLER_H__

class ArmController {
public:
  void tick();
  ArmController() {
    previous_state = NOT_INIT;
    current_state = NOT_INIT;
  }
private:
  enum State {NOT_INIT,
              WAIT_FOR_SWEEP_COMMAND,
              SWEEP_COMMAND_RECEIVED,
              SEND_DONE_SWEEPING
             };
  volatile State previous_state; // this is largely used as a gate variable to ensure we only send command once
  volatile State current_state;
};

#endif /* ARMCONTROLLER */