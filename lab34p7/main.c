#include <msp430f5529.h>
#include<stdio.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
  ADC12CTL1 = ADC12SHP;                     // sampling timer
  ADC12CTL0 |= ADC12ENC;                    // ADC enable
  P6SEL |= 0x01;                            // P6.0 allow ADC on pin 6.0
  ADC12MCTL0 = ADC12INCH_0;  //selects which input results are
          //stored in memory ADC12MEM0. Input
          //one is selected on reset so this line is not needed

  P1DIR = 0b10000100;                           // set pin P1.2 as output
  P1SEL |= BIT2;
  TA0CCR0 = 256;
  //TA0CCR1 = 128;
  TA0CCTL1 = OUTMOD_7;
  TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0;
 // _bis_SR_register(LPM0_bits + GIE); // Enter Low power mode 0 and enable interrupts


  while(1){


    ADC12CTL0 |= ADC12SC;
    // Start sampling
    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait

    TA0CCR1 = (256.0 * ADC12MEM0) / 4095.0;

    }

}




