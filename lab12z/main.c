#include <msp430.h> //this file provides the code with all the relevant names
                    //of the registers and their corresponding codes

/**
 * main.c
 */

void main(int time)



{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
                                //from some kinds of software
                                //bugs. We just want to disable it for now. )


    time = 1234; // set counter time(max is 9999)
    P6DIR = 0b00001111; //Set pins 0,1,2,3 of port 6 to output
    P4DIR = 0b00000011; //Set pins 0,1 of port 4 to output
    P2DIR = 0b00000001; //Set pin 0 of port 2 to output


    // starting every display at zero
    // Using decimal instead of binary (keeps it easy)

    // far right display
    P2OUT = 1; //P2OUT = 0b00000001;
    P4OUT = 0; //P4OUT = 0b00000000;
    P6OUT = 0; //P6OUT = 0b00000100;
    P2OUT = 0; //P2OUT = 0b00000000;


    // middle right display
    P2OUT = 1;
    P4OUT = 1;
    P6OUT = 0;
    P2OUT = 0;


    // middle left
    P2OUT = 1;
    P4OUT = 2;
    P6OUT = 0;
    P2OUT = 0;

    // far left
    P2OUT = 1;
    P4OUT = 3;
    P6OUT = 0;
    P2OUT = 0;


    int i;


    for (i = 1 ; i <= time; i++){

        _delay_cycles(50000); //_delay_cycles (1000000) this value is one sec delay


        if (i % 1000 == 0){

                P2OUT = 1;
                P4OUT = 3;
                P6OUT = i/1000;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 2;
                P6OUT = 0;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 1;
                P6OUT = 0;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 0;
                P6OUT = 0;
                P2OUT = 0;

        } else if (i % 100 == 0){

                P2OUT = 1;
                P4OUT = 2;
                P6OUT = (i/100) % 10;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 1;
                P6OUT = 0;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 0;
                P6OUT = 0;
                P2OUT = 0;

        } else if (i % 10 == 0){

                P2OUT = 1;
                P4OUT = 1;
                P6OUT = (i/10) % 10;
                P2OUT = 0;

                P2OUT = 1;
                P4OUT = 0;
                P6OUT = 0;
                P2OUT = 0;

        } else{
                P2OUT = 1;
                P4OUT = 0;
                P6OUT = i % 10;
                P2OUT = 0;
        }

    }


}


