/* LCD library Display Demo
 *
 * Copyright (c) 2015, Manolis Kiagias
 *
 * LCD Library demo, based on original OutOfBox demo app by Texas Instruments
 * All rights reserved.
 * Distributed under the BSD License
 *
 * --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************/

#include <driverlib.h>

#include "LCDLibrary.h"

#define STARTUP_MODE         0
volatile unsigned char mode = STARTUP_MODE;
volatile int flashmode=0;

// Initialization calls
void Init_GPIO(void);
void Init_Clock(void);

int main(void) {
    WDTCTL = WDT_ADLY_250;                    // WDT 1000ms, ACLK, interval timer
	SFRIE1 |= WDTIE;                          // Enable WDT interrupt
    PMM_unlockLPM5();

    // Initializations
    Init_GPIO();
    Init_Clock();
    Init_LCD();
    volatile int i=0;

    //enable interrupts
     __enable_interrupt();

    while (1) {

    	// displayText shows text without scrolling
    	// anything above six chars is truncated

    	displayText("HELLO");
        __delay_cycles(2000000);

        displayText("FR6989");
        __delay_cycles(2000000);

        // displayScrollText as used in the OutOftheBox demo by TI

        displayScrollText("ON BOARD LCD DISPLAY LIBRARY DEMO");
        __delay_cycles(500000);

        // displayTMR shows the timer symbol

        displayTMR(1);
        displayScrollText("TIMER SYMBOL ON");
        __delay_cycles(500000);

        // Hide the timer symbol

        displayTMR(0);

        // displayEXC show the exclamation symbol

        displayEXC(1);
        displayScrollText("EXCLAMATION SYMBOL ON");
        __delay_cycles(500000);

        // Hide the exclamation symbol

        displayEXC(0);

        // displayREC shows the record symbol

        displayREC(1);
        displayScrollText("RECORD SYMBOL ON");
        __delay_cycles(500000);

        // Hide the record symbol

        displayREC(0);

        // displayANT, displayTX, displayRX show the Antenna, TX, RX symbols

        displayANT(1);
        displayTX(1);
        displayRX(1);
        displayScrollText("ANTENNA AND TX RX SYMBOLS ON");
        __delay_cycles(500000);

        // Hide the ANT, TX, RX symbols

        displayANT(0);
        displayTX(0);
        displayRX(0);

        // displayBattery shows the battery symbol
        // If the argument is zero, an empty battery is shown
        // An argument of -1 hides the battery symbol completely
        // Positive arguments from 1 to 6 show corresponding bars

        displayBattery(0);
        displayScrollText("BATTERY SYMBOL ON");
        __delay_cycles(500000);

        displayText("LEVELS");
        for (i=1; i<=6; i++) {
        	displayBattery(i);
        	__delay_cycles(500000);
        }
        for (i=5; i>=0; i--) {
        	displayBattery(i);
        	__delay_cycles(500000);
        }

        displayTMR(1);
        displayEXC(1);
        displayREC(1);
        displayANT(1);
        displayTX(1);
        displayRX(1);
        displayBattery(6);
        displayScrollText("ALL SYMBOLS ON");
        __delay_cycles(500000);
        displayTMR(0);
        displayEXC(0);
        displayREC(0);
        displayANT(0);
        displayTX(0);
        displayRX(0);
        displayBattery(-1);
        displayScrollText("SYMBOLS OFF");
        __delay_cycles(100000);
    }
}
// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) WDT_ISR (void)
#else
#error Compiler not supported!
#endif
{
	  // The interrupt routine calls subroutines
	  // Probably a bad idea, but OK for the demo I guess

	  if (flashmode == 0)
	    {
	        displayHRT(1);
	        flashmode=1;
	    } else
	    {
	    	displayHRT(0);
			flashmode=0;
	    }
}

/*
 * GPIO Initialization
 */
void Init_GPIO()
{
    // Set all GPIO pins to output low to prevent floating input and reduce power consumption
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    //GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);
    // Set P4.1 and P4.2 as Secondary Module Function Input, LFXT.
    GPIO_setAsPeripheralModuleFunctionInputPin(
           GPIO_PORT_PJ,
           GPIO_PIN4 + GPIO_PIN5,
           GPIO_PRIMARY_MODULE_FUNCTION
           );
}

/*
 * Clock System Initialization
 */
void Init_Clock()
{
    // Set DCO frequency to default 8MHz
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);

    // Configure MCLK and SMCLK to default 2MHz
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_8);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_8);

    // Intializes the XT1 crystal oscillator
    CS_turnOnLFXT(CS_LFXT_DRIVE_3);
}
