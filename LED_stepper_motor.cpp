/*  Program to show Stepper Motor Drive Waveform on LEDS1-4  */

#include "mbed.h"

volatile int count = 0;
volatile char drive = 0x01;
void T1_isr (void); // Prototype

Ticker Step; 
BusOut leds(LED1,LED2,LED3,LED4);

void T1_isr ()
{  count++; 
   if (count >= 250) //1 second passed?
     {
      if (drive == 0x01) drive = 0x08; //wrap round
      else drive >>= 1;
      count = 0;
      leds = drive;      // update drive waveform
      }
}

int main()
{ 
   Step.attach_us(&T1_isr, 1000);   //initializes ticker with period of 1msec
                                  //and attaches it to T1 ISR
   leds = drive; //output first pattern
    while(1) { //do nothing
        
        }
}