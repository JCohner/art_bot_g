#include <Arduino.h>
#line 1 "/home/jambox/dev/g_art_proj/RailAndPulley/RailAndPulley.ino"
#include <avr/io.h>
#include "RailAndPulley.h"
int LED_pin = 13;
volatile int val = 0;

RailAndPulley robot;

#line 21 "/home/jambox/dev/g_art_proj/RailAndPulley/RailAndPulley.ino"
void setup();
#line 34 "/home/jambox/dev/g_art_proj/RailAndPulley/RailAndPulley.ino"
void loop();
#line 8 "/home/jambox/dev/g_art_proj/RailAndPulley/RailAndPulley.ino"
ISR(TIMER1_OVF_vect)
{
  TCNT1 = 40535; // Timer Preloading
  // Handle The 100ms Timer Interrupt
  
  // This is just a debug LED to show the timer interupt is not hanging
  digitalWrite(LED_pin, val);
  val = !val;

  // This triggers the tick function of the robot to check state
  robot.tick();
}
 
void setup()
{
  // Setting up timer so this all runs at fixed frequency
  TCCR1A = 0;           // Init Timer1
  TCCR1B = 0;           // Init Timer1
  TCCR1B |= B00000011;  // Prescalar = 64
  TCNT1 = 40535;        // Timer Preloading
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt
  pinMode(LED_pin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {;}
}

void loop()
{
  // Do Nothing
}
