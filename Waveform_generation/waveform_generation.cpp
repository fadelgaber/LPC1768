#include "mbed.h"
//Sets up an output bus at pins p5-p10
BusOut output (p5, p6, p7, p8, p9, p10); //p5 = lsb, p10 = msb
DigitalIn spst(p11);

int main() {
    
    static int durations[7]={20,20,20,20,20,20,80};
    static int op_values[7]={0x3f,0x3e,0x3c,0x38,0x30,0x20,0x00};

    while(1) {
        while(spst==1){
            wait_ms(300);
            for(int n=0; n<7; n++){
                output=op_values[n];
                wait_ms(durations[n]);
            }
        }
 }

} 