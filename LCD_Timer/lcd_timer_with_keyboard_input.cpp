/* Program to show Elapsed Time oon mbed Application Board LCD Display */

#include "mbed.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);
Serial pc(USBTX, USBRX);

volatile int minutes=0, hours=0;
int verified_hours = 1, verified_minutes=1;

volatile int count = 0, seconds = 0;
volatile int flag = 0;


void led_switch(void);  // Prototypes
void T1_isr (void);

Ticker Tick; 
DigitalOut myled(LED1);
void led_switch()
{ myled=!myled;
}
void T1_isr ()
{  count++; 
   if (count >= 200) //1 second has passed?
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
    do{
        pc.printf("Input the minutes\n");
        pc.scanf("%d", &minutes);
        if(minutes>60){
            pc.printf("Minutes should be less than 60\n");
            verified_minutes=0;
            }
            else{
                verified_minutes=1;
                }
        }while(verified_minutes==0);
    do{
        pc.printf("Input the hours\n");
        pc.scanf("%d", &hours);
        if(hours>12){
            pc.printf("Hours should be less than 12\n");
            verified_hours=0;
            }
            else{
                verified_hours=1;
                }
    }while(verified_hours==0);

   Tick.attach_us(&T1_isr, 5000);   //initializes the ticker with period of 5msec
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