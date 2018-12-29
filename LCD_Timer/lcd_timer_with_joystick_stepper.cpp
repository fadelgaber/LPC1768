/* Program to show Elapsed Time oon mbed Application Board LCD Display */

#include "mbed.h"
#include "C12832.h"

C12832 lcd(p5, p7, p6, p8, p11);
Serial pc(USBTX, USBRX);

volatile int count = 0;
volatile char drive = 0x01;

Ticker Step;
Ticker Tick; 
BusOut leds(LED1,LED2,LED3,LED4);

volatile int minutes=0, hours=0;
int verified_hours = 1, verified_minutes=1;
int step_speed=250;
int direction=0;

volatile int count_timer = 0, seconds = 0;
volatile int flag = 0;

InterruptIn left(p13);
InterruptIn right(p16);
InterruptIn up(p15);
InterruptIn down(p12);
InterruptIn centre(p14);

void timer_isr ()
{  count_timer++; 
   if (count_timer >= 1000) //1 second has passed?
     {seconds++;
      count_timer = 0;
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
}

void anticlockwise(){
    direction=1;
}

void clockwise(){
    direction=0;
}

void reduce_speed(){
    if(step_speed<1000){
        step_speed=step_speed+50;
    }
}

void increase_speed(){
    if(step_speed>50){
        step_speed=step_speed-50;
    }
}

void reverse(){
    direction = !direction;
    wait_ms(200);
}
  
void T1_isr(){  
    if(direction==1){
    count++; 
       if (count >= step_speed) //1 second passed?
         {
          if (drive == 0x01) drive = 0x08; //wrap round
          else drive >>= 1;
          count = 0;
          leds = drive;      // update drive waveform
          }
    }
    
    if(direction==0){
       count++; 
       if (count >= step_speed) //1 second passed?
         {
          if (drive == 0x08) drive = 0x01; //wrap round
          else drive <<= 1;
          count = 0;
          leds = drive;      // update drive waveform
          }
        }
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
    
    left.fall(&anticlockwise);
    right.fall(&clockwise);
    up.fall(&reduce_speed);
    down.fall(&increase_speed);

   Tick.attach_us(&timer_isr, 1000);   //initializes the ticker with period of 1msec
                                  //and attaches it to T1 ISR
   Step.attach_us(&T1_isr, 1000);
   leds = drive; //output first pattern                              

   lcd.cls();
   lcd.locate(0,0);
   lcd.printf("Elapsed Time Monitor");
    while(1) {
        while (flag == 0); // wait for new data
        lcd.locate(0,15);
        lcd.printf("Elapsed h,m,s: %d %d %d", hours, minutes, seconds);
        flag = 0; //reset flag
        }
}