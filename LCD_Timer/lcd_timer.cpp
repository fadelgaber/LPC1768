/* Program to show Elapsed Time oon mbed Application Board LCD Display */

#include "mbed.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);

volatile int count = 0, seconds = 0;
volatile int flag = 0;
volatile int minutes=0, hours=0;

void led_switch(void);  // Prototypes
void T1_isr (void);

Ticker Tick; 
DigitalOut myled(LED1);
void led_switch()
{ myled=!myled;
}
void T1_isr ()
{  count++; 
   if (count >= 100) //1 second has passed?
     {seconds++;
      count = 0;
      flag = 1;
      }
    if(seconds >= 60){
     minutes++;
     seconds=0;
     flag=1;
     }
    if(minutes >= 60){
     hours++;
     minutes=0;
     flag=1;
     }
     
     // }
}
int main()
{ 
   Tick.attach_us(&T1_isr, 10000);   //initializes the ticker with period of 10msec
                                  //and attaches it to T1 ISR

   lcd.cls();
   lcd.locate(0,0);
   lcd.printf("Elapsed Time Monitor");
    while(1) {
        while (flag == 0); // wait for new data
        lcd.locate(0,15);
        lcd.printf("Elapsed h,m,s: %d %d %d", hours, minutes, seconds);
        flag = 0; //reset flag
        led_switch(); //blink light
        }
}