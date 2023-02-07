/*
* PHYS319 Interrupt Example in C *
* Written by Ryan Wicks
* Modified by A.K,
*
*
*/
#include <msp430.h>
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;
    P1DIR = 0b00000001;
    P4DIR = 0b10000000;
    P1OUT = 0b00000010;
    P4OUT = 0b00000000;
    P1REN = 0b00000010;
    P1IE = 0b00000010;
    P1IES= 0b00000010;
    _BIS_SR (LPM4_bits + GIE);



}

int n = 0;

void __attribute__ ((interrupt(PORT1_VECTOR))) PORT1_ISR(void) {


    _delay_cycles (500000);

    if(n == 0){
        P1OUT ^= 0b00000001;
        n += 1;
    }

    else if(n == 1){

        P1OUT ^= 0b00000001;
        P4OUT ^= 0b10000000;
        n += 1;
    }

    else if(n == 2){
        P1OUT ^= 0b00000001;
        n += 1;

    }
    else{
        P1OUT ^= 0b00000001;
        P4OUT ^= 0b10000000;
        n = 0;

    }

    P1IFG &= ~0b00000010;

}
