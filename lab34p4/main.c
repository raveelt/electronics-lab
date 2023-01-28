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
    P1OUT = 0b00000011;
    P4OUT = 0b10000000;
    P1REN = 0b00000010;
    P1IE = 0b00000010;
    P1IES= 0b00000010;
    _BIS_SR (LPM4_bits + GIE);


}

void __attribute__ ((interrupt(PORT1_VECTOR))) PORT1_ISR(void) {

    P1OUT ^= 0b00000001;
    P4OUT ^= 0b10000000;
    P1IFG &= ~0b00000010;
}
