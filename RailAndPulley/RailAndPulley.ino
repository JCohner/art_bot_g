#include <avr/io.h>
#include "RailAndPulley.h"

int LED_pin = 13;
volatile int val = 0;

RailAndPulley robot;

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 45535; // Timer Preloading
  // Handle The 10ms Timer Interrupt
  // This triggers the tick function of the robot to check state
  robot.tick();
}
 
void setup()
{
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000010;  // Prescaler = 8
  TCNT1 = 45535;        // Timer Preloading
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {;}
}

void loop()
{
  // Do Nothing
}