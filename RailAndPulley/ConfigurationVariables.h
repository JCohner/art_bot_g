#ifndef __CONFIGURATION_VARIABLES_H__
#define __CONFIGURATION_VARIABLES_H__

enum RailAndPulleyTimer {
  LIFT_WAIT_CENTI_SECONDS = 4000,
  POS1_WAIT_CENTI_SECONDS = 200,
  POS3_WAIT_CENTI_SECONDS = 400
};

enum RailPosition {
  POSITION_1 = 1,
  POSITION_2 = 300,
  POSITION_3 = 12450,
  HOME_CORRECTION_VALUE = 12750
};

enum PulleyPosition {
  STOP = 94,// This is the stop value for the servo when on continuous mode
  LIFT = 135, // In continous mode this instructs the servo to lift in the correct direction: CCW
  LOWER = 45 // Continous mode CW command
};



#endif /* __CONFIGURATION_VARIABLES_H__ */