#include <msp430.h>

#define c  16.35 //various pitch frequencies
#define d  18.35
#define e  20.60
#define f  21.83
#define g  24.50
#define a  27.50
#define b  30.87


void main(void){

     WDTCTL = WDTPW|WDTHOLD; // Stop WDT
     P1DIR |= BIT2; // Output on Pin 1.2
     P1SEL |= BIT2; // Pin 1.2 selected as PWM
     //TA0CCR0 = 512; // PWM period PWM period (512/1.048)
                                             //microseconds
     //TA0CCR1 = 256; // PWM duty cycle
     TA0CCTL1 = OUTMOD_7; // TA0CCR1 reset/set-high voltage
     // below count, low voltage when past

     TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0;
     // Timer A control set to SMCLK, 1MHz
     // and count up mode MC_1
     //_bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0 and enable interrupts

     float period;
     int i;
     const int size = 63;
     //float pitches[size] = {30*c, 40*d, 50*e, 40*f,  30*g, 0};
     float pitches[size] = {30*g, 40*c, 40*d, 40*e, 40*e, 40*e, 40*e,
                            40*e, 40*e, 40*d, 40*e, 40*c, 40*c, 40*c,
                            40*c, 40*c, 40*c, 40*d, 40*e, 40*f, 40*a,
                            40*a, 40*a, 40*a, 40*a, 40*g, 40*f, 40*e,
                            40*e, 40*e, 40*e, 40*e, 40*c, 40*d, 40*e,
                            40*f, 40*f, 40*a, 40*a, 40*a, 40*g, 40*f,
                            40*e, 40*c, 40*c, 40*c, 40*c, 40*c, 40*c,
                            40*d, 40*e, 40*e, 40*e, 40*f, 40*d, 40*d,
                            40*d, 40*e, 40*c, 40*c, 40*c, 40*c, 40*c};


     for (i = 0; i < size; i++) {

         _delay_cycles(500000);// 0.3s delay

         TA0CCR1 = 0;

         _delay_cycles(100000);// 0.1s delay

         period = 1/(pitches[i]); //seconds
         period *= 1e6; //microseconds
         TA0CCR0 = period * 1.048;
         TA0CCR1 = TA0CCR0 / 2.0;
     }



}
