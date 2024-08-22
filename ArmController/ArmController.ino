// UpperArm Out
// Elbow Down
// Wrist Sweep 2X Slow
// Shoulder Sweep 3X Slow
// Wrist Sweep 3X Fast
// Elbow Up
// UpperArm In

#include <SPI.h>
#include "ArmController.h"

ArmController Arm;


ISR (SPI_STC_vect) // SPI interrupt routine 
{ 
   ArmController::ArmCommandFromRP command = SPDR; // read byte from SPI Data Register

   auto arm_response = Arm.interact(command);

   // Write out to SPDR
   SPDR = arm_response;
}

void setup() {
  // SPI Setup
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  SPI.attachInterrupt(); // turn on interrupt

  Arm.setup();
}

void loop() {
  // TODO maybe a smarter way to trigger this. With gate variable?
  if (Arm.get_state() == ArmController::ArmState::EXECUTING_COMMAND){
    Arm.do_arm_animation();
  }
  delay(5);
}