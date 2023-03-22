#include <msp430f5529.h>
#include<stdio.h>


int main(void)
{

  ADC12CTL0 = ADC12SHT02 + ADC12ON + ADC12MSC;         // Sampling time, ADC12 on, automatic multiple conversions
  ADC12CTL1 = ADC12SHP | ADC12CONSEQ_1 | ADC12CSTARTADD_0;// sampling timer, multichannel, starting memory address
  ADC12MCTL0 = ADC12INCH_0;          //selects A0 to be stored in memory ADC12MEM0
  ADC12MCTL1 = ADC12INCH_1;
  ADC12MCTL2 = ADC12INCH_2+ADC12EOS; //selects A2 to be stored in memory ADC12MEM2 and this memory to be the last of sequence
  ADC12CTL0 |= ADC12ENC;                    // ADC enable conversions
  P6SEL |= 0b00000111;                      // allow ADC on pin 6.0,6.1,6.2


  P1DIR |= 0x01;                            // set pin P1.0 (LED1) as output
  P4DIR |= 0x80;

  /* Configure hardware UART */
  UCA1CTL1 = UCSWRST; //Recommended to place USCI in reset first
  P4SEL |= BIT4 + BIT5;
  UCA1CTL1 |= UCSSEL_2; // Use SMCLK
  UCA1BR0 = 109; // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
  UCA1BR1 = 0; // Set baud rate to 9600 with 1.048MHz clock
  UCA1MCTL = UCBRS_2; // Modulation UCBRSx = 2
  UCA1CTL1 &= ~UCSWRST; // Initialize USCI state machine
 /* if we were going to receive, we would also:
    IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt */




  while (1)
  {

    _delay_cycles(10000);
    ADC12CTL0 |= ADC12SC;                   // Start sampling


    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait
    int volts_z = ADC12MEM0;
    int volts_x = ADC12MEM1; //good for pitch
    int volts_y = ADC12MEM2;


    if(volts_y>=3000)    //This value depends on the input voltage
       P1OUT |= BIT0;
    else
      P1OUT &= ~BIT0;


    if(volts_z>=3000) //This value depends on the input voltage
        P4OUT |= BIT7;
    else
        P4OUT &= ~BIT7;


    volts_z = volts_z >> 4; //Im reducing the range to 0 to 255
      while (! (UCA1IFG & UCTXIFG));
      UCA1TXBUF = volts_z;


  }

}





