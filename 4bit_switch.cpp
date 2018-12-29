#include "mbed.h"

DigitalOut led1(p30);
DigitalOut led2(p29);
DigitalOut led3(p28);
DigitalOut led4(p27);

DigitalIn bit1(p5);
DigitalIn bit2(p6);
DigitalIn bit3(p7);
DigitalIn bit4(p8);

DigitalIn spst(p9);

int main() {
    while(1){
        if(spst==1){
            wait_ms(25);
            if(spst==0){
                wait_ms(25);   
                led1=bit1;
                led2=bit2;
                led3=bit3;
                led4=bit4;
            }
        }
    }
}
