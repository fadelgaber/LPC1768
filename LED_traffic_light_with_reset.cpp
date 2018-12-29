#include "mbed.h"

DigitalOut red(p6);
DigitalOut yellow(p7);
DigitalOut green(p8);
DigitalIn spst(p9);

int main() {
    while(1) {
        while(spst==0){
        red=1;
        wait(2.5);
        yellow=1;
        wait(1);
        yellow=0;
        red=0;
        green=1;
        wait(2.5);
        green=0;
        yellow=1;
        wait(1);
        yellow=0;
        }
        red=1;
    }
}

//To remember the switch, use a counter.