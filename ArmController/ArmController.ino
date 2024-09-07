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

void setup() {
  Serial.begin(9600);
  Arm.setup();
}

void loop() {
  static int print_slow = 0;
  if ((print_slow++ % 10) == 0)
    Serial.print("State is: "); Serial.println(Arm.get_state());

  switch (Arm.get_state()){
    case ArmController::NOT_INIT:
      if (digitalRead(Arm.ARM_DO_SWEEP_PIN)){
        Arm.set_state(ArmController::EXECUTING_COMMAND);
        Serial.println("Got do sweep");
      }
      break;
    case ArmController::EXECUTING_COMMAND:
      Arm.do_arm_animation();
      digitalWrite(Arm.ARM_DONE_SWEEPING_PIN, HIGH);
      Serial.println("Done sweeping");
      Arm.set_state(ArmController::DONE);
      break;
    case ArmController::DONE:
      if (digitalRead(Arm.ARM_RESET_PIN)){
        Arm.set_state(ArmController::NOT_INIT);
        Serial.println("Got reset");
      }
      digitalWrite(Arm.ARM_DONE_SWEEPING_PIN, LOW);
      break;
  }
  delay(5);
}