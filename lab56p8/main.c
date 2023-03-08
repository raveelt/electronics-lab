#include  "msp430.h"


/*1. Device starts up in LPM3 + blinking LED to indicate device is alive
 //    + Upon first button press, device transitions to application mode
 // 2. Application Mode
 //    + Continuously sample ADC Temp Sensor channel
 //
 //    + Transmit temperature value via TimerA UART to PC
*/


#define     LED1                  BIT0                         //for P1.0
#define     LED2                  BIT7                         //for P4.7

#define     BUTTON                BIT1

#define     TXD                   BIT4                      // TXD on P4.4
#define     RXD                   BIT5                      // RXD on P4.5

#define     PreAppMode            0
#define     RunningMode           1


#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   //probably dont need this // Temperature Sensor Calibration-30 C
                                                      //probably dont need this//See device datasheet for TLV table memory mapping
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C


unsigned int TXByte;
volatile unsigned int Mode;

void InitializeButton(void);
void PreApplicationMode(void);

void main(void)
{
//  long tempMeasured;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

  /* next  line to use internal calibrated 1.048MHz clock: */

  TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0; // Timer A control set to SMCLK, 1MHz and count up mode MC_1



  InitializeButton();


  P1DIR |= LED1;
  P4DIR |= LED2;
  P1OUT &= ~LED1;     //LEDs off
  P4OUT &= ~LED2;
  P4DIR |= TXD;
  P4OUT |= TXD;





  Mode = PreAppMode;
  __enable_interrupt();      // Enable interrupts.
  PreApplicationMode();          // Blinks LEDs, waits for button press

//  /* Configure ADC Temp Sensor Channel */
//
//  REFCTL0 &= ~REFMSTR;  // Reset REFMSTR to hand over control to ADC12_A ref control registers
//
//  ADC12CTL0 |= ADC12SHT03 + ADC12ON + ADC12REFON;  // Sampling time 32 cycles, ADC12 on and reference voltage for Temperature sensor is on
//  ADC12CTL1 |= ADC12SHP;                     // sampling timer
//  ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // Select internal Vref and A10 = temp sense i/p
//  ADC12CTL0 |= ADC12ENC ;                     // enable conversion
//
//   __delay_cycles(1000);                     // Wait for ADC Ref to settle





   /* Configure hardware UART */
  UCA1CTL1 = UCSWRST; //Recommended to place USCI in reset first
  P4SEL |= BIT4 + BIT5;
  UCA1CTL1 |= UCSSEL_2; // Use SMCLK
  UCA1BR0 = 109; // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
  UCA1BR1 = 0; // Set baud rate to 9600 with 1.048MHz clock
  UCA1MCTL = UCBRS_2; // Modulation UCBRSx = 2
  UCA1CTL1 &= ~UCSWRST; // Initialize USCI state machine
  /* if we were going to receive, we would also:
     IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt
  */

  /* Main Application Loop */


  /*~~~~~~~~~~~~~~~~~ My code addition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  P1DIR |=  BIT2;    // going to use P1.2 as the trigger
  P8DIR &= ~BIT1;    // going to use P8.1 for the echo pin
  P8REN |=  BIT1;    // enable pullup/pull down on P8.1
  P8OUT &= ~BIT1;    // pulldown P8.1


  //from example code lecture 5
  unsigned int time;
  TA0CTL = TASSEL_2 + MC_0 + ID_0;
  TA0CTL |= MC_2;
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`~~*/



  while(1)
  {
   // ADC12CTL0 |= ADC12SC;        // Sampling and conversion start


     // wait for TX buffer to be ready for new data

//
//    tempMeasured = ADC12MEM0;
//    tempMeasured = ((tempMeasured - CALADC12_15V_30C) * (85 - 30)) / (CALADC12_15V_85C - CALADC12_15V_30C) + 30.0;
//
//
//    TXByte = tempMeasured;
//    UCA1TXBUF = TXByte;//Transmit TXByte;



    P1OUT ^= LED1;  // toggle the light every time we make a measurement.
    P4OUT &= ~LED2;// make sure that green LED is off

    // go to sleep, wait till timer expires to do another measurement.

   //_delay_cycles(500000);


   /*~~~~~~~~~~~~~~~~~ My code addition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

   P1OUT |= BIT2; //turning it on
   _delay_cycles(20); // P1.2 output for 20 microseconds
   P1OUT &= ~BIT2; //turning it off

   int check;
   check = 1;
   while(check)
   {
       if(P8IN & BIT1)
       {
           // start timer
           TA0R = 0;
           //TA0CTL |= MC_2;
           check = 0;
       }
   }

   check = 1;
   while(check){

       if(!(P8IN & BIT1))
       {
           // stop timer
           time = TA0R / 58.0;
           while (! (UCA1IFG & UCTXIFG));
           UCA1TXBUF = time;
           check = 0;
       }
   }



   /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



  }
}

void PreApplicationMode(void)
{
  P1DIR |= LED1;
  P4DIR |= LED2;
  P1OUT |= LED1;                 // To enable the LED toggling effect
  P4OUT &= ~LED2;

  while (Mode == PreAppMode)  {
    P1OUT ^= LED1;
    P4OUT ^= LED2;                      // toggle the two lights.
    _delay_cycles (500000);             //This function introduces 0.5 s delay

                              }


}

void InitializeButton(void)                 // Configure Push Button
{
  P1DIR &= ~BUTTON;
  P1OUT |= BUTTON;
  P1REN |= BUTTON;
  P1IES |= BUTTON;
  P1IFG &= ~BUTTON;
  P1IE |= BUTTON;
}

/* *************************************************************
 * Port Interrupt for Button Press
 * 1. During standby mode: to enter application mode
 *
 * *********************************************************** */

void __attribute__ ((interrupt(PORT1_VECTOR))) PORT1_ISR(void) // Port 1 interrupt service routine
 {                                                    //code of the interrupt routine goes here
    Mode = RunningMode;

    P1IE &= ~BUTTON;         // Disable port 1 interrupts
    P1IFG &= ~0b00000010;        // Clear P1.1 IFG.If you don't, it just happens again.
 }
































/// My code ///
//
//
//void main(void)
//{
//    //////////// This is to activate PWM //////////
//    WDTCTL = WDTPW|WDTHOLD; // Stop WDT
//    P1DIR |= BIT2; // Output on Pin 1.2
//    P1SEL |= BIT2; // Pin 1.2 selected as PWM
//    TA0CCR0 = 65535; // PWM period (max value 16 bit number, each is a microsecond)
//    TA0CCR1 = 10; // PWM duty cycle (on for 10 microseconds)
//    TA0CCTL1 = OUTMOD_7; // TA0CCR1 reset/set-high voltage
//                          // below count, low voltage when past
//
//    TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0; // Timer A control set to SMCLK, 1MHz
//                                           // and count up mode MC_1
//    _bis_SR_register(LPM0_bits + GIE);     // Enter Low power mode 0 and enable interrupts
//
//    ////////////////////////////////////////////////
//
//
//
//     /////////// Activate input ////////////////////
//
////     WDTCTL = WDTPW + WDTHOLD;
////     ADC12CTL0 = ADC12SHT02 + ADC12ON;
////     ADC12CTL1 = ADC12SHP;
////     ADC12CTL0 |= ADC12ENC;
////     P6SEL |= 0x01;
//
//     //////////////////////////////////////////////
//
//
//
//
//while (1)
//{
//        // Start sampling //This value depends on the input voltage
//        ADC12CTL0 |= ADC12SC;
//        while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait
//
//
//        if(ADC12MEM0>3072)
//
//            P1OUT |= BIT0;
//
//        else
//            P1OUT &= ~BIT0;
//  }
//}
//
//}
//




 //My code second try



//
//unsigned int time
//
//void main(void)
//{
//
//    //////////// This is to activate PWM //////////
//    WDTCTL = WDTPW|WDTHOLD; // Stop WDT
//    P1DIR |= BIT2; // Output on Pin 1.2
//    ///////////////////////////////////////////////
//
//
//     /////////// Activate input ////////////////////
//
////     WDTCTL = WDTPW + WDTHOLD;
////     ADC12CTL0 = ADC12SHT02 + ADC12ON;
////     ADC12CTL1 = ADC12SHP;
////     ADC12CTL0 |= ADC12ENC;
////     P6SEL |= 0x01;
//
//     //////////////////////////////////////////////
//
//     ///////////  ////////////////////
//
////      TA0CTL = TASSEL_2 + MC_0 + ID_0;
////
////      TA0CTL |= MC_2;
//
//     //////////////////////////////////////////////
//
////    /* Configure hardware UART */
////     UCA1CTL1 = UCSWRST;         // Recommended to place USCI in reset first
////     UCA1CTL1 |= UCSSEL_2;       // Use SMCLK
////     UCA1BR0 = 109;              // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
////     UCA1BR1 = 0;                // Set baud rate to 9600 with 1.048MHz clock
////     UCA1MCTL = UCBRS_2;         // Modulation UCBRSx = 2
////     UCA1CTL1 &= ~UCSWRST;       // Initialize USCI state machine
////
////
////
////     /*  if we were going to receive, we would also:
////    IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt
////    */
//
//
//       /* Configure hardware UART */
//       UCA1CTL1 = UCSWRST; //Recommended to place USCI in reset first
//       P4SEL |= BIT4 + BIT5;
//       UCA1CTL1 |= UCSSEL_2; // Use SMCLK
//       UCA1BR0 = 109; // Set baud rate to 9600 with 1.048MHz clock (Data Sheet 36.3.13)
//       UCA1BR1 = 0; // Set baud rate to 9600 with 1.048MHz clock
//       UCA1MCTL = UCBRS_2; // Modulation UCBRSx = 2
//       UCA1CTL1 &= ~UCSWRST; // Initialize USCI state machine
//       /* if we were going to receive, we would also:
//          IE2 |= UCA1RXIE; // Enable USCI_A1 RX interrupt
//       */
//
//
//
//    while (1)
//    {
//
//            P1OUT = BIT2
//            _delay_cycles(20)
//
//            while (! (UCA1IFG & UCTXIFG));
//            // Start sampling //This value depends on the input voltage
//            ADC12CTL0 |= ADC12SC;
//
//            while (ADC12CTL1 & ADC12BUSY);//while bit ADC12BUSY in register ADC12CTL1 is high wait
//
//            TA0R = 0
//            while (ADC12MEM0 > 100); //Waits
//            time = TA0R;
//            UCA1TXBUF = time;
//
//    }
//
//}

