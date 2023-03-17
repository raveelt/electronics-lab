//#include <msp430.h>
// #include <stdio.h>
//
//
//
//int main(void)
//{
//
//  WDTCTL = WDTPW + WDTHOLD;
//
//
//  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
//  ADC12CTL1 = ADC12SHP;                     // sampling timer
//  ADC12CTL0 |= ADC12ENC;                    // ADC enable (moved this around for multiADC, did not work)
//
//  // for multi ADC (not working)
//  //ADC12CTL0 = ADC12SHT02 + ADC12ON; //ADC12MSC;         // Sampling time, ADC12 on
//  //ADC12CTL1 = ADC12SHP; // + ADC12CONSEQ_3;                     // sampling timer + set sequence of conversions
//
//
//  //ADC12EOS = BIT0;
//
//  ADC12MCTL0 = ADC12INCH_0;
// //ADC12MCTL0 = ADC12INCH_6;  //storing 6.6 in ADC12MEM0
//  //ADC12MCTL1 = ADC12INCH_1;  //storing 6.1 in ADC12MEM1
//  //ADC12MCTL2 = ADC12INCH_2; //| ADC12EOS;  //storing 6.2 in ADC12MEM2 //
//
//
//
//  P6SEL |= BIT0 + BIT1 + BIT2;   //allow ADC on pin 6.0, 6.1, 6.2
//
//
//  /* Configure hardware UART */
//  UCA1CTL1 = UCSWRST; //Recommended to place USCI in reset first
//  P4SEL |= BIT4 + BIT5;
//  UCA1CTL1 |= UCSSEL_2; // Use SMCLK
//  UCA1BR0 = 109; // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
//  UCA1BR1 = 0; // Set baud rate to 9600 with 1.048MHz clock
//  UCA1MCTL = UCBRS_2; // Modulation UCBRSx = 2
//  UCA1CTL1 &= ~UCSWRST; // Initialize USCI state machine
// /* if we were going to receive, we would also:
//    IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt */
//
//
//  P1DIR = BIT0;
//  P4DIR = BIT7;
//
//
//
//  while(1){
//
//      _delay_cycles(100000);
//
//      ADC12CTL0 |= ADC12SC; //start sampling
//
//
//      while (ADC12CTL1 & ADC12BUSY);
//
//      int six0 = ADC12MEM0;
//
//
//      if (six0 > 3000)
//         P1OUT |= BIT0;
//      else
//         P1OUT &= ~BIT0;
//
//      if (six0 < 3000)
//         P4OUT |= BIT7;
//      else
//         P4OUT &= ~BIT7;
//
//
//      six0 = six0 >> 4; //Im reducing the range to 0 to 255
//
//      while (! (UCA1IFG & UCTXIFG));
//      UCA1TXBUF = six0;
//
//
//
//
//    }
//}
//
//
//










//
//void main(void)
//{
//    WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer
//
//    ADC12CTL0 = ADC12ON + ADC12MSC + ADC12SHT02;  // Turn on ADC12 module, set multiple sample conversion, and set sampling time
//    ADC12CTL1 = ADC12SHP + ADC12CONSEQ_3;           // Use internal sample timer and set sequence of conversions
//    ADC12MCTL0 = ADC12INCH_0;                       // Set channel 0 for conversion
//    ADC12MCTL1 = ADC12INCH_1;                       // Set channel 1 for conversion
//    ADC12MCTL2 = ADC12INCH_2 | ADC12EOS;            // Set channel 2 for conversion and enable end of sequence
//
//    P6SEL |= BIT0 + BIT1 + BIT2;                    // Enable analog input on selected channels
//
//    /* Configure hardware UART */
//    UCA1CTL1 = UCSWRST; //Recommended to place USCI in reset first
//    P4SEL |= BIT4 + BIT5;
//    UCA1CTL1 |= UCSSEL_2; // Use SMCLK
//    UCA1BR0 = 109; // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
//    UCA1BR1 = 0; // Set baud rate to 9600 with 1.048MHz clock
//    UCA1MCTL = UCBRS_2; // Modulation UCBRSx = 2
//    UCA1CTL1 &= ~UCSWRST; // Initialize USCI state machine
//   /* if we were going to receive, we would also:
//      IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt */
//
//
//    P1DIR = BIT0;
//    P4DIR = BIT7;
//
//
//    while(1)
//    {
//        ADC12CTL0 |= ADC12ENC + ADC12SC;            // Enable conversion and start sampling
//        while (ADC12CTL1 & ADC12BUSY);              // Wait for conversion to complete
//        int six0 = ADC12MEM0;                   // Read conversion result from channel 0
//        int six1 = ADC12MEM1;                   // Read conversion result from channel 1
//        int six2 = ADC12MEM2;                   // Read conversion result from channel 2
//        // Process the conversion results
//
//        if (six0 > 3000)
//            P1OUT |= BIT0;
//        else
//            P1OUT &= ~BIT0;
//
//        if (six1 > 3000)
//            P4OUT |= BIT7;
//        else
//            P4OUT &= ~BIT7;
//
//
//        six2 = six2 >> 4;
//
//        while (! (UCA1IFG & UCTXIFG));
//        UCA1TXBUF = six2;
//
//
//    }
//}




#include <msp430f5529.h>
#include<stdio.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;
  ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
  ADC12CTL1 = ADC12SHP;                     // sampling timer
  ADC12MCTL0 = ADC12INCH_0; //selects A0 to be stored in memory ADC12MEM0
  ADC12MCTL1 = ADC12INCH_1; //selects A1 to be stored in memory ADC12MEM1

  //ADC12CTL0 |= ADC12ENC;                               // ADC enable conversions
  P6SEL |= BIT0 + BIT1 + BIT2;                            // allow ADC on pin 6.0,6.1
  //ADC12MCTL0 = ADC12INCH_0  //selects which input results are
          //stored in memory ADC12MEM0. Input
          //one is selected on reset so this line is not needed
  P1DIR |= 0x01;                            // set pin P1.0 (LED1) as output
  P4DIR |= 0x80;                            // set pin P4.7 (LED2) as output


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
    ADC12CTL0 &= ~ADC12ENC;                    // ADC disable conversions to change start address
    ADC12CTL1 = ADC12CSTARTADD_0 | ADC12SHP; //Select starting address 0 and sampling timer
    ADC12CTL0 |= ADC12ENC;                    // ADC enable conversions
    ADC12CTL0 |= ADC12SC;                   // Start sampling
    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait

    int volts_y = ADC12MEM0;


    ADC12CTL0 &= ~ADC12ENC;                    // ADC disable conversions to change start address
    ADC12CTL1 = ADC12CSTARTADD_1 | ADC12SHP; //Select starting address 1 and sampling timer
    ADC12CTL0 |= ADC12ENC;                    // ADC enable conversions
    ADC12CTL0 |= ADC12SC;                   // Start sampling
    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait

    int volts_x = ADC12MEM1;



    ADC12CTL0 &= ~ADC12ENC;                    // ADC disable conversions to change start address
    ADC12CTL2 = ADC12CSTARTADD_2 | ADC12SHP; //Select starting address 1 and sampling timer
    ADC12CTL0 |= ADC12ENC;                    // ADC enable conversions
    ADC12CTL0 |= ADC12SC;                   // Start sampling
    while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait

    int volts_z = ADC12MEM2;




    if(volts_y>=200) //This value depends on the input voltage
    {
        P1OUT |= BIT0;
    }

    else
    {
        P1OUT &= ~BIT0;
    }

    if(volts_x>=200) //This value depends on the input voltage
    {
        P4OUT |= BIT7;
    }

    else
    {
        P4OUT &= ~BIT7;
    }

    //volts_x = volts_x >> 4; //Im reducing the range to 0 to 255

      while (! (UCA1IFG & UCTXIFG));
      UCA1TXBUF = volts_y;



  }

}

