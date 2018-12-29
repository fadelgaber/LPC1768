#include "mbed.h"


BusOut output (p5, p6, p7, p8, p9, p10, p11, p12); //p5 = lsb, p12 = msb

int main() {
    
    int count;
    static int op_values[16]={0x3f,0x06,0x5b,0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f,
    0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
    /* static makes the array permanent ... variables in a function
    usually exist only during its execution */
    /* also initialises the values of the 4 array elements */
    while(1) {
        for(count = 0; count < 16 ; count++)
        {
            output = op_values[count];
            wait_ms(1000); /* 1s delay */
        }
    
    }

} 