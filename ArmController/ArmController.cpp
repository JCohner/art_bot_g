#include "ArmController.h"

void ArmController::setup(){
  Shoulder.attach(6);  // attaches the servo on pin 9 to the servo object
  UpperArm.attach(7);
  Elbow.attach(8);
  Wrist.attach(9);
}

ArmController::ArmInteraction ArmController::interact(ArmInteraction command){
  ArmInteraction return_val = ERROR;
  switch (command){
    case BEGIN_SWEEPING:
      if (state_ == NOT_INIT){
        return_val = I_AM_SWEEPING;
        Serial.println("Got command to sweep");
        state_ = EXECUTING_COMMAND; // TOD: could move to begining of do_arm_animation
      }
      break;
    case TELL_ME_WHEN_SWEEP_DONE:
      switch(state_){
       case EXECUTING_COMMAND:
        Serial.println("Was polled, brother I am still sweeping");
        return_val = I_AM_SWEEPING;
        break;
       case DONE:
        return_val = SWEEP_DONE;
        Serial.println("Brother we are done");
        break;
      }
      break;
  }
  return return_val;
}

void ArmController::do_arm_animation(){
  Wrist.write(30); 
//delay(55000);
//delay(10000);
// UPPER ARM TURN OUT
  for (posUpperArm = 91; posUpperArm < 180; posUpperArm += 1) { 
    UpperArm.write(posUpperArm);  // tell servo to go to position in variable 'pos'
    delay(25);  // waits 15 ms for the servo to reach the position
  }
// ELBOW DOWN
  for (posElbow = 60; posElbow > 0; posElbow -= 1) { // Elbow move down
    Elbow.write(posElbow);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
// WRIST SWEEP 4X SLOW
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
// SHOULDER SWEEP 4X SLOW
  // Shoulder Start Center to Back
    for (posShoulder = 90; posShoulder > 0; posShoulder -= 1) { // Shoulder move from center back
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  // Shoulder Full Sweep 1X
    for (posShoulder = 0; posShoulder < 180; posShoulder += 1) { // Shoulder move all the way forward
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
    for (posShoulder = 180; posShoulder > 0; posShoulder -= 1) { // Shoulder move all the way back
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  // Shoulder Full Sweep 1X
    for (posShoulder = 0; posShoulder < 180; posShoulder += 1) { // Shoulder move all the way forward
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
    for (posShoulder = 180; posShoulder > 0; posShoulder -= 1) { // Shoulder move all the way back
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  // Shoulder Full Sweep 1X
    for (posShoulder = 0; posShoulder < 180; posShoulder += 1) { // Shoulder move all the way forward
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
    for (posShoulder = 180; posShoulder > 0; posShoulder -= 1) { // Shoulder move all the way back
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
  // Shoulder Full Sweep & Stop at Center 1X
    for (posShoulder = 0; posShoulder < 180; posShoulder += 1) { // Shoulder move all the way forward
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
    for (posShoulder = 180; posShoulder > 90; posShoulder -= 1) { // Shoulder move all the way back
      Shoulder.write(posShoulder);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15 ms for the servo to reach the position
    }
    delay(1000);
// WRIST SWEEP 4X FAST
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
  // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    // Wrist Full Sweep 1X Slow
    for (posWrist = 30; posWrist < 90; posWrist += 1) { // Wrist sweep forward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    for (posWrist = 90; posWrist > 30; posWrist -= 1) { // Wrist sweep backward slow
      Wrist.write(posWrist);              // tell servo to go to position in variable 'pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    delay(500);
// ELBOW UP
  for (posElbow = 0; posElbow < 60; posElbow += 1) { // Elbow move up
    Elbow.write(posElbow);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
// UPPER ARM TURN IN
  for (posUpperArm = 180; posUpperArm > 91; posUpperArm -= 1) { // goes from 180 degrees to 0 degrees
    UpperArm.write(posUpperArm);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15 ms for the servo to reach the position
  }

  state_ = DONE;
}