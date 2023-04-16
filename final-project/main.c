#include <msp430f5529.h>
#include<stdio.h>

int main(void)
{

  ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;             // Sampling time, ADC12 on, automatic multiple conversions
  ADC12CTL1 = ADC12SHP | ADC12CONSEQ_1 | ADC12CSTARTADD_0;// sampling timer, multichannel, starting memory address
  ADC12MCTL0 = ADC12INCH_0;                               //selects A0 to be stored in memory ADC12MEM0
  ADC12MCTL1 = ADC12INCH_1;
  ADC12MCTL2 = ADC12INCH_2+ADC12EOS;        //selects A2 to be stored in memory ADC12MEM2 and this memory to be the last of sequence
  ADC12CTL0 |= ADC12ENC;                    // ADC enable conversions
  P6SEL |= 0b00000111;                      // allow ADC on pin 6.0,6.1,6.2
  P1DIR = 0b00111100;                       //configuring P1.2-1.5 for motor control


  while (1)
  {
    ADC12CTL0 |= ADC12SC;                   // Start sampling


    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait


    int volts_z = ADC12MEM0; // not used
    int volts_x = ADC12MEM1; //good for forward / reverse movement
    int volts_y = ADC12MEM2; // good for turning


    if (volts_x > 3200){ //Car in reverse condition


        if(volts_y > 3200 && volts_y < 3300){ //slow turn reverse right
            P1OUT &= ~BIT3;
            P1OUT |=  BIT5;
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT4;
        }
        else if(volts_y < 2850 && volts_y > 2650){ //slow turn reverse left
            P1OUT &= ~BIT5;
            P1OUT |=  BIT3;
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT4;
        }

        else if(volts_y > 3300){ //fast turn reverse right - counterclockwise spin
            P1OUT &= ~BIT3;
            P1OUT |=  BIT5;
            P1OUT |=  BIT2;
            P1OUT &= ~BIT4;
        }
        else if(volts_y < 2650){ //fast turn reverse left - clockwise spin
            P1OUT &= ~BIT5;
            P1OUT |=  BIT3;
            P1OUT |=  BIT4;
            P1OUT &= ~BIT2;
        }
        else{  // car moving in reverse, no turning
        P1OUT |=  BIT3;
        P1OUT |=  BIT5;
        P1OUT &= ~BIT2;
        P1OUT &= ~BIT4;
        }




    }

    else if(volts_x < 2800){


        if(volts_y > 3200 && volts_y < 3300){ //slow turn right
            P1OUT &= ~BIT3;
            P1OUT |=  BIT4;
            P1OUT &= ~BIT2;
            P1OUT &= ~BIT5;
        }
        else if(volts_y < 2850 && volts_y > 2650){ //slow turn left
            P1OUT &= ~BIT5;
            P1OUT |=  BIT2;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT4;
        }

        else if(volts_y > 3300){ //fast turn right - clockwise spin
            P1OUT &= ~BIT2;
            P1OUT |=  BIT4;
            P1OUT |=  BIT3;
            P1OUT &= ~BIT5;
        }
        else if(volts_y < 2650){ //fast turn left - counterclockwise spin
            P1OUT &= ~BIT3;
            P1OUT |=  BIT2;
            P1OUT |=  BIT5;
            P1OUT &= ~BIT4;
        }
        else{    // car moving forward, no turning
            P1OUT |=  BIT2;
            P1OUT |=  BIT4;
            P1OUT &= ~BIT3;
            P1OUT &= ~BIT5;
        }

    }
    else{       // motors off - buffer condition

        P1OUT &= ~BIT2;
        P1OUT &= ~BIT3;
        P1OUT &= ~BIT4;
        P1OUT &= ~BIT5;

    }


  }

}

