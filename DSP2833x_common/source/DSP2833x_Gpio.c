// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
void InitGpio(void)
{
   EALLOW;
   
   // Each GPIO pin can be: 
   // a) a GPIO input/output
   // b) peripheral function 1
   // c) peripheral function 2
   // d) peripheral function 3
   // By default, all are GPIO Inputs 
   GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
   GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
   GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO39
   GpioCtrlRegs.GPBMUX2.all = 0x0000;     // GPIO functionality GPIO48-GPIO63
   GpioCtrlRegs.GPCMUX1.all = 0x0000;     // GPIO functionality GPIO64-GPIO79
   GpioCtrlRegs.GPCMUX2.all = 0x0000;     // GPIO functionality GPIO80-GPIO95

   GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are inputs
   GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO63 are inputs   
   GpioCtrlRegs.GPCDIR.all = 0x0000;      // GPI064-GPIO95 are inputs

   // Each input can have different qualification
   // a) input synchronized to SYSCLKOUT
   // b) input qualified by a sampling window
   // c) input sent asynchronously (valid for peripheral inputs only)
   GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT 
   GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
   GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO39 Synch to SYSCLKOUT 
   GpioCtrlRegs.GPBQSEL2.all = 0x0000;    // GPIO48-GPIO63 Synch to SYSCLKOUT 

   // Pull-ups can be enabled or disabled. 
   GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
   GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO63
   GpioCtrlRegs.GPCPUD.all = 0x0000;      // Pullup's enabled GPIO64-GPIO79

   //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
   //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO34
   //GpioCtrlRegs.GPCPUD.all = 0xFFFF     // Pullup's disabled GPIO64-GPIO79

   EDIS;

}	

void InitLogicIO(void)
{

	int16 i;

	EALLOW;
	// Test program - lowest 18 bits of GPIOA is used as I/O output

//	GpioCtrlRegs.GPADIR.all= 0x0003ffff;
	
	// Test program - GPIOA's 24-27 are output
	// GPIOB's 48-61 are output
//	GpioCtrlRegs.GPADIR.bit.GPIO24=1;	
//	GpioCtrlRegs.GPADIR.bit.GPIO25=1;		
//	GpioCtrlRegs.GPADIR.bit.GPIO26=1;
//	GpioCtrlRegs.GPADIR.bit.GPIO27=1;

//	GpioCtrlRegs.GPBDIR.all=0x3fff0000;

	// Test RS485 communication chip
	GpioCtrlRegs.GPADIR.bit.GPIO21=1;
	GpioCtrlRegs.GPADIR.bit.GPIO22=1;

	// Test CAN communication chip
	GpioCtrlRegs.GPADIR.bit.GPIO19=1;


/*
// IE - Enable protection is enable low; initial state is high,  protection disabled
      GpioDataRegs.GPBSET.bit.GPIO53= 1;   // Initial state high
      GpioCtrlRegs.GPBPUD.bit.GPIO53= 0;   // Enable pullup on GPIO53
      GpioCtrlRegs.GPBMUX2.bit.GPIO53= 0;  // GPIO53=GPIO53 
      GpioCtrlRegs.GPBDIR.bit.GPIO53= 1;   // Output

// LE - DSP automatically locks PWM, enable high; initial state is high
      GpioDataRegs.GPBSET.bit.GPIO52= 1;   // Initial state is high
      GpioCtrlRegs.GPBPUD.bit.GPIO52= 0;   // Enable pullup on GPIO52
      GpioCtrlRegs.GPBMUX2.bit.GPIO52= 0;  // GPIO52=GPIO52 
      GpioCtrlRegs.GPBDIR.bit.GPIO52= 1;   // Output

// DSP - DSP internal software protection, enable low; initial state is high
      GpioDataRegs.GPBSET.bit.GPIO55= 1;   // Initial state is high
      GpioCtrlRegs.GPBPUD.bit.GPIO55= 0;   // Enable pullup on GPIO55
      GpioCtrlRegs.GPBMUX2.bit.GPIO55= 0;  // GPIO55=GPIO55
      GpioCtrlRegs.GPBDIR.bit.GPIO55= 1;   // Output

// Relay1 - Input relay, enable low; initial state is high
      GpioDataRegs.GPBSET.bit.GPIO50= 1;   // Initial state is high
      GpioCtrlRegs.GPBPUD.bit.GPIO50= 0;   // Enable pullup on GPIO50
      GpioCtrlRegs.GPBMUX2.bit.GPIO50= 0;  // GPIO50=GPIO50
      GpioCtrlRegs.GPBDIR.bit.GPIO50= 1;   // Output
      
 // Relay2 - Output relay, enable low; initial state is high
      GpioDataRegs.GPBSET.bit.GPIO51= 1;   // Initial state is high
      GpioCtrlRegs.GPBPUD.bit.GPIO51= 0;   // Enable pullup on GPIO51
      GpioCtrlRegs.GPBMUX2.bit.GPIO51= 0;  // GPIO51=GPIO51
      GpioCtrlRegs.GPBDIR.bit.GPIO51= 1;   // Output

   // Enable I2C-A on GPIO32 - GPIO33
	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

//LED1-4
    GpioDataRegs.GPBSET.bit.GPIO60= 1;   // Initial state is high
    GpioCtrlRegs.GPBPUD.bit.GPIO60= 0;   // Enable pullup on GPIO60
    GpioCtrlRegs.GPBMUX2.bit.GPIO60= 0;  // GPIO60=GPIO60
    GpioCtrlRegs.GPBDIR.bit.GPIO60= 1;   // Output

    GpioDataRegs.GPBSET.bit.GPIO61= 1;   // Initial state is high
    GpioCtrlRegs.GPBPUD.bit.GPIO61= 0;   // Enable pullup on GPIO61
    GpioCtrlRegs.GPBMUX2.bit.GPIO61= 0;  // GPIO61=GPIO61
    GpioCtrlRegs.GPBDIR.bit.GPIO61= 1;   // Output
  
    GpioDataRegs.GPBSET.bit.GPIO58= 1;   // Initial state is high
    GpioCtrlRegs.GPBPUD.bit.GPIO58= 0;   // Enable pullup on GPIO58
    GpioCtrlRegs.GPBMUX2.bit.GPIO58= 0;  // GPIO58=GPIO58
    GpioCtrlRegs.GPBDIR.bit.GPIO58= 1;   // Output

    GpioDataRegs.GPBSET.bit.GPIO59= 1;   // Initial state is high
    GpioCtrlRegs.GPBPUD.bit.GPIO59= 0;   // Enable pullup on GPIO59
    GpioCtrlRegs.GPBMUX2.bit.GPIO59= 0;  // GPIO59=GPIO59
    GpioCtrlRegs.GPBDIR.bit.GPIO59= 1;   // Output


// 2. input
	// Input identification: ignore inteference that is less than 6*100ns
	GpioCtrlRegs.GPBCTRL.bit.QUALPRD2=0x5;    // Set period: 10ns*10
	GpioCtrlRegs.GPBCTRL.bit.QUALPRD3=0x5;

	GpioCtrlRegs.GPBDIR.bit.GPIO54=0;   // F2
	GpioCtrlRegs.GPBDIR.bit.GPIO57=0;   // F1
	GpioCtrlRegs.GPBDIR.bit.GPIO56=0;   // F0

	GpioCtrlRegs.GPBQSEL2.bit.GPIO54=2; // Enable for 6 periods
	GpioCtrlRegs.GPBQSEL2.bit.GPIO57=2;
	GpioCtrlRegs.GPBQSEL2.bit.GPIO56=2;

// Switch 1-2
	// Input identification: ignore inteference that is less than 6*100ns
	GpioCtrlRegs.GPACTRL.bit.QUALPRD3=0x5;    // Set period: 10ns*10

	GpioCtrlRegs.GPADIR.bit.GPIO27=0;   // S1
	GpioCtrlRegs.GPBDIR.bit.GPIO48=0;   // S2

	// Input identification: ignore inteference that is less than 6*100ns
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27=2;         // Enable for 6 periods
	GpioCtrlRegs.GPBQSEL2.bit.GPIO48=2;

// PLLA,PLLB,PLLC
	GpioCtrlRegs.GPADIR.bit.GPIO26=0;   // PLLA		
	GpioCtrlRegs.GPADIR.bit.GPIO25=0;   // PLLB
	GpioCtrlRegs.GPADIR.bit.GPIO24=0;   // PLLC

	GpioCtrlRegs.GPAQSEL2.bit.GPIO26=2;         // Enable for 6 periods¨
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25=2;         // Enable for 6 periods
	GpioCtrlRegs.GPAQSEL2.bit.GPIO24=2;         // Enable for 6 periods
*/
	
//  GPI29  are inputs
   GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO29 = 0;          // input
   GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 2;        // XINT2 Qual using 6 samples
   GpioCtrlRegs.GPACTRL.bit.QUALPRD3 = 0x5;   	// Each sampling window is 10*SYSCLKOUT 

// Two reset pins in the FPGA
// When needed, reset the value of each register:
// XA18 to reset digital I/O
// XA17 to reset PWM

   GpioDataRegs.GPASET.bit.GPIO30=1;
   GpioCtrlRegs.GPADIR.bit.GPIO30=1;

   GpioDataRegs.GPASET.bit.GPIO31=1;
   GpioCtrlRegs.GPADIR.bit.GPIO31=1;


   EDIS;

// GPIO29 is XINT1
   EALLOW;
   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 29;   // Xint1 is GPI29
//   GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
   EDIS;

// Configure XINT1
   XIntruptRegs.XINT1CR.bit.POLARITY = 1;      // Rising edge interrupt
//   XIntruptRegs.XINT2CR.bit.POLARITY = 1;      // Rising edge interrupt
   
// Enable XINT1 and XINT2   
   XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable Xint1
 //  XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2

//3, for EI :initialize after delay, 0 is enable protection; 1 is hardware initialize: turn off epwm
	for(i=0;i<30000;i++)
		{
			asm("nop");
		}

	EDIS;
}

//===========================================================================
// End of file.
//===========================================================================
