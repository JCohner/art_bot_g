#include <avr/io.h>
#include "RailAndPulley.h"

int LED_pin = 13;
volatile int val = 0;

RailAndPulley robot;

ISR(TIMER2_OVF_vect)
{
  TCNT2 = 99; // Timer Preloading
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
  TCNT2 = 99;        // Timer Preloading
  TIMSK2 |= B00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {;}
}

void loop()
{
  // Do Nothing
}