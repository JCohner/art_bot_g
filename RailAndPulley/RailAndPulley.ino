#include <avr/io.h>
#include "RailAndPulley.h"
//#include <Servo.h>

RailAndPulley robot;

ISR(TIMER2_COMPA_vect)
{
  OCR2A += 156;// Timer Preloading
  // Handle The 10ms Timer Interrupt
  // This triggers the tick function of the robot to check state
  robot.tick();
}
 
void setup()
{
  // Thanks to this lovely little calculator: https://deepbluembedded.com/arduino-timer-calculator-code-generator/
  TCCR2A = 0;           // Init Timer2A
  TCCR2B = 0;           // Init Timer2B
  TCCR2B |= B00000111;  // Prescaler = 1024
  OCR2A = 156;        // Timer Compare2A Register
  TIMSK2 |= B00000010;  // Enable Timer COMPA Interrupt
  Serial.begin(9600);

  robot.setup();
  while (!Serial) {;}
}

void loop()
{
  // Do Nothing
}