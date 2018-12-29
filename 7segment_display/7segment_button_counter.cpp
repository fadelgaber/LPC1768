#include "mbed.h"

DigitalIn spst(p13);
BusOut output (p5, p6, p7, p8, p9, p10, p11, p12); //p5 = lsb, p12 = msb

int main() {
    
    int count=0;
    static int op_values[16]={0x3f,0x06,0x5b,0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
    0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

    while(1) {
        while(spst==1){
            wait_ms(500);
            count++;
            break;
        }
        wait_ms(25);
        output=op_values[count];
        }

} 