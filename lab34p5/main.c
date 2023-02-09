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
  P1DIR = 0b10000101;                           // set pin P1.0 as output
  P4DIR = 0b10000000;                        // set pin P4.7 to output



  float high;
  float low;

  high = (4095 * 2.4) / 3.3;
  low = (4095 * 0.5) / 3.3;

  while(1){


    ADC12CTL0 |= ADC12SC;
    // Start sampling
    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait

    if(ADC12MEM0 >= high){    //This value depends on the input voltage
       P1OUT |= BIT0;
       P1OUT &= ~BIT2;
       P4OUT &= ~BIT7;
    }

    else if(ADC12MEM0 <= low){
        P1OUT &= ~BIT0;
        P4OUT |= BIT7;
        P1OUT &= ~BIT2;
    }

    else{

      P1OUT &= ~BIT0;
      P4OUT &= ~BIT7;
      P1OUT |= BIT2;
      //P1OUT = 0b00000100;

    }

  }

}




//#include <msp430f5529.h> #include<stdio.h>
//int main(void) {
//  WDTCTL = WDTPW + WDTHOLD;
//  ADC12CTL0 = ADC12SHT02 + ADC12ON;
//  ADC12CTL1 = ADC12SHP;
//  ADC12CTL0 |= ADC12ENC;
//  P6SEL |= 0x01;
//  P1DIR |= 0x01;
//while (1) {
//// Sampling time, ADC12 on
//// sampling timer
//// ADC enable
//// P6.0 allow ADC on pin 6.0
//// set pin P1.0 as output
//// Start sampling //This value depends on the input voltage
//ADC12CTL0 |= ADC12SC;
//while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait
//if(ADC12MEM0>=3072)
//    P1OUT |= BIT0;
//
//else
//      P1OUT &= ~BIT0;
//  }
//}
