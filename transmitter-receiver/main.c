#include <msp430.h>
void main(void){

    WDTCTL = WDTPW|WDTHOLD; // Stop WDT
     P1DIR |= BIT2 + BIT3; // Output on Pin 1.2
     P1SEL |= BIT2 + BIT3; // Pin 1.2 selected as PWM
     TA0CCR0 = 256; // PWM period PWM period (512/1.048)
                                             //microseconds

     //TA0CCR1 = 256; // PWM duty cycle
     //TA0CCR2 = 64;
     TA0CCTL1 = OUTMOD_7; // TA0CCR1 reset/set-high voltage
     TA0CCTL2 = OUTMOD_7;
     // below count, low voltage when past

     TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0;
     // Timer A control set to SMCLK, 1MHz
     // and count up mode MC_1
     //_bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0 and enable inrerrupts



         while (1)
         {
             // Duty cycle control
             TA0CCR1 = 128; // P1.2 duty cycle
             TA0CCR2 = 256; // P1.3 duty cycle
         }
    }
