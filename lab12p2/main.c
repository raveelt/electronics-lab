#include <msp430.h> //this file provides the code with all the relevant names
                    //of the registers and their corresponding codes

/**
 * main.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
                                //from some kinds of software
                                //bugs. We just want to disable it for now. )


//	P6DIR = 0b00001111; //Set pins 0,1,2,3 of port 6 to output
//	P4DIR =  0b00000011; //Set pins 0,1 of port 4 to output
//	P4OUT = 0b00000000; //Set pins 0,1 of port 4 to low, this will correspond
//	                    //to choosing a least significant digit in a 7 segment display


	P6DIR = 0b00001111;
	P4DIR = 0b00000011;
	P2DIR = 0b00000001;

    // far right display

	P2OUT = 1; //P2OUT = 0b00000001;
	P4OUT = 0; //P4OUT = 0b00000000;
	P6OUT = 5; //P6OUT = 0b00000100;
	P2OUT = 0; //P2OUT = 0b00000000;


    // middle right display
    P2OUT = 0b00000001;
    P4OUT = 0b00000001;
    P6OUT = 0b00000100;
    P2OUT = 0b00000000;


	// middle left
    P2OUT = 0b00000001;
    P4OUT = 0b00000010;
    P6OUT = 0b00000001;
    P2OUT = 0b00000000;

    // far left
    P2OUT = 0b00000001;
    P4OUT = 0b00000011;
    P6OUT = 0b00000111;
    P2OUT = 0b00000000;


}
//To decide which pin is output or input we set it to 1 or 0. It means
//sending a binary number to the port. Binary numbers are represented with the
//prefix 0b as shown above. Notice that this binary representation might not
//work in all C compilers.






