#include "ArmController.h"

void ArmController::setup(){
  Shoulder.attach(3);  // attaches the servo on pin 9 to the servo object
  UpperArm.attach(4);
  Elbow.attach(8);
  Wrist.attach(9);

  Wrist.write(30); 


  pinMode(ARM_DO_SWEEP_PIN, INPUT);
  pinMode(ARM_RESET_PIN, INPUT);
  pinMode(ARM_DONE_SWEEPING_PIN, OUTPUT);

  digitalWrite(ARM_DONE_SWEEPING_PIN, LOW);
}

void ArmController::do_arm_animation(){
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

  // set_state(ArmState::DONE);
}