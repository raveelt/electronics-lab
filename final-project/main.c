#include <msp430.h> 
 #include <stdio.h>


int unsigned volts;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;


  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
  ADC12CTL1 = ADC12SHP;                     // sampling timer
  ADC12CTL0 |= ADC12ENC;                    // ADC enable

//  ADC12CTL0 = ADC12SHT0_2 + ADC12ON + ADC12MSC;         // Sampling time, ADC12 on
//  ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3;                     // sampling timer



 // ADC12CTL0 |= ADC12ENC;                    // ADC enable

  ADC12MCTL0 = ADC12INCH_0;  //selects which input results are
                                       //stored in memory ADC12MEM0. Input
                      //one is selected on reset so this line is not needed
  //ADC12MCTL0 = ADC12INCH_6;  //storing 6.6 in ADC12MEM0
  ADC12MCTL1 = ADC12INCH_1;  //storing 6.1 in ADC12MEM1
  ADC12MCTL2 = ADC12INCH_2; //+ ADC12EOS;  //storing 6.2 in ADC12MEM2 //




  P6SEL |= BIT0;                            // P6.0 allow ADC on pin 6.0
  P6SEL |= BIT1;
  P6SEL |= BIT2;

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



  while(1){

      _delay_cycles(100000);
      ADC12CTL0 |= ADC12SC; //start sampling


      while (ADC12CTL1 & ADC12BUSY); //waits?
      volts = ADC12MEM1;
      volts = volts >> 4; //Im reducing the range to 0 to 255

      while (! (UCA1IFG & UCTXIFG));
      UCA1TXBUF = volts;

    }
}




//void main(void)
//{
//    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
//
//    ADC12CTL0 = ADC12ON + ADC12MSC + ADC12SHT0_15;  // Turn on ADC12 module, set multiple sample conversion, and set sampling time
//    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3;           // Use internal sample timer and set sequence of conversions
//    ADC12MCTL0 = ADC12INCH_0;                       // Set channel 0 for conversion
//    ADC12MCTL1 = ADC12INCH_1;                       // Set channel 1 for conversion
//    ADC12MCTL2 = ADC12INCH_2 | ADC12EOS;            // Set channel 2 for conversion and enable end of sequence
//
//    P6SEL |= BIT0 + BIT1 + BIT2;                    // Enable analog input on selected channels
//
//    while(1)
//    {
//        ADC12CTL0 |= ADC12ENC + ADC12SC;            // Enable conversion and start sampling
//        while (ADC12CTL1 & ADC12BUSY);              // Wait for conversion to complete
//        int result_0 = ADC12MEM0;                   // Read conversion result from channel 0
//        int result_1 = ADC12MEM1;                   // Read conversion result from channel 1
//        int result_2 = ADC12MEM2;                   // Read conversion result from channel 2
//        // Process the conversion results
//    }
//}

