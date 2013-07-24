//##########################################################################
//
// *** This file is linked to Merlin's github account ***
// *** Please do not copy and paste ***
//
// FILE:    5ph_IMC
//
// TITLE:   Modulation scheme for 5 phase indirect matrix converter
// 
//       Watch Variables:
//          CpuTimer0.InterruptCount
//          CpuTimer1.InterruptCount
//          CpuTimer2.InterruptCount
//
//    Configures the 2833x GPIO into two different configurations
//    This code is verbose to illustrate how the GPIO could be setup.
//    In a real application, lines of code can be combined for improved
//    code size and efficency.
//
//    This example only sets-up the GPIO.. nothing is actually done with
//    the pins after setup.
//
//    In general:
//
//       All pullup resistors are enabled.  For ePWMs this may not be desired.
//       Input qual for communication ports (eCAN, SPI, SCI, I2C) is asynchronous
//       Input qual for Trip pins (TZ) is asynchronous
//       Input qual for eCAP and eQEP signals is synch to SYSCLKOUT
//       Input qual for some I/O's and interrupts may have a sampling window

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "iqmathlib.h"			// iqmath library is included to compate with dq-transformation
#include "math.h"				// To perform mathematical functions
#include <stdlib.h>				// Contains malloc()


// Definitions for constants and registries
#define pi 		3.141592654
#define alpha	1.256637061
#define LED1 	GpioDataRegs.GPBDAT.bit.GPIO60
#define	LED2 	GpioDataRegs.GPBDAT.bit.GPIO61

// Prototype statements for functions found within this file.
interrupt void cpu_timer0_isr(void);
interrupt void cpu_timer1_isr(void);
interrupt void cpu_timer2_isr(void);
void Gpio_setup(void);
void configtestled(void);
float *FivePhaseClarke(float *abc);


void main(void)
{
  	
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
	InitSysCtrl();
     
// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//	InitGpio();
	InitXintf16Gpio();


// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;
   
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
	InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &cpu_timer0_isr;
	PieVectTable.XINT13 = &cpu_timer1_isr;
	PieVectTable.TINT2 = &cpu_timer2_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. This function can be
//         found in DSP2833x_CpuTimers.c
	InitCpuTimers();   // For this example, only initialize the Cpu Timers

	// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
	// 150MHz CPU Freq, 1 second Period (in uSeconds)
	ConfigCpuTimer(&CpuTimer0, 150, 200000);	// Changed to 0.2s for LED blinking
	ConfigCpuTimer(&CpuTimer1, 150, 1000000);
	ConfigCpuTimer(&CpuTimer2, 150, 1000000);
	   
	// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
	// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
	// below settings must also be updated.
	
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0

// Step 5. User specific code, enable interrupts:


// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
// which is connected to CPU-Timer 1, and CPU int 14, which is connected
// to CPU-Timer 2:
	IER |= M_INT1;
	IER |= M_INT13;
	IER |= M_INT14;

// Enable TINT0 in the PIE: Group 1 interrupt 7
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
   
// Setup GPIO
//	Gpio_setup();
	
// LED setup
	configtestled();
	LED1 = 0;
	LED2 = 0;

// Step 6. IDLE loop. Just sit and loop forever (optional):
	for(;;);

}

// Interrupt for cpu_timer0 is used to change LED state
interrupt void cpu_timer0_isr(void)
{
	CpuTimer0.InterruptCount++;

	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	
	// Copied frmo LED code
	CpuTimer0Regs.TCR.bit.TIF=1;
    CpuTimer0Regs.TCR.bit.TRB=1;

	LED1=~LED1;
	LED2=~LED2;
}

interrupt void cpu_timer1_isr(void)
{
	CpuTimer1.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

interrupt void cpu_timer2_isr(void)
{  
	EALLOW;
	CpuTimer2.InterruptCount++;
   // The CPU acknowledges the interrupt.
	EDIS;
}

void Gpio_setup(void)
{
   	// Basic Pinout.
   	// This basic pinout includes:
   	// PWM1-3, ECAP1, ECAP2, TZ1-TZ4, SPI-A, EQEP1, SCI-A, I2C
   	// and a number of I/O pins

   	// These can be combined into single statements for improved
   	// code efficiency.

   	// Enable PWM1-3 on GPIO0-GPIO5
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;   // Enable pullup on GPIO1
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;   // Enable pullup on GPIO2
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;   // Enable pullup on GPIO3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;   // Enable pullup on GPIO4
 	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;   // Enable pullup on GPIO5
 	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;  // GPIO0 = PWM1A
   	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;  // GPIO1 = PWM1B
   	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;  // GPIO2 = PWM2A
   	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;  // GPIO3 = PWM2B
   	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;  // GPIO4 = PWM3A
   	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;  // GPIO5 = PWM3B

   	// Enable an GPIO output on GPIO6, set it high
   	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;   // Enable pullup on GPIO6
   	GpioDataRegs.GPASET.bit.GPIO6 = 1;   // Load output latch
   	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  // GPIO6 = GPIO6
   	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO6 = output

   	// Enable eCAP1 on GPIO7
   	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;   // Enable pullup on GPIO7
   	GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0; // Synch to SYSCLOUT
   	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;  // GPIO7 = ECAP2

   	// Enable GPIO outputs on GPIO8 - GPIO11, set it high
   	GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pullup on GPIO8
   	GpioDataRegs.GPASET.bit.GPIO8 = 1;   // Load output latch
   	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;  // GPIO8 = GPIO8
   	GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;   // GPIO8 = output

   	GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pullup on GPIO9
   	GpioDataRegs.GPASET.bit.GPIO9 = 1;   // Load output latch
   	GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 0;  // GPIO9 = GPIO9
   	GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;   // GPIO9 = output

   	GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;  // Enable pullup on GPIO10
   	GpioDataRegs.GPASET.bit.GPIO10 = 1;  // Load output latch
   	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0; // GPIO10 = GPIO10
   	GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;   // GPIO10 = output

   	GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  // Enable pullup on GPIO11
   	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; // GPIO11 = GPIO11
   	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  // GPIO11 = output	

   	// Enable Trip Zone inputs on GPIO12 - GPIO15
   	GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;   // Enable pullup on GPIO12
   	GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;   // Enable pullup on GPIO13
   	GpioCtrlRegs.GPAPUD.bit.GPIO14 = 0;   // Enable pullup on GPIO14
   	GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pullup on GPIO15
   	GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL1.bit.GPIO13 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL1.bit.GPIO14 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 3; // asynch input
   	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // GPIO12 = TZ1
   	GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 1;  // GPIO13 = TZ2
   	GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 1;  // GPIO14 = TZ3
   	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;  // GPIO15 = TZ4

   	// Enable SPI-A on GPIO16 - GPIO19
   	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   // Enable pullup on GPIO16
   	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   // Enable pullup on GPIO17
   	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   // Enable pullup on GPIO18
   	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   // Enable pullup on GPIO19
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // asynch input
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // asynch input
   	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;  // GPIO16 = SPICLKA
   	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;  // GPIO17 = SPIS0MIA
   	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;  // GPIO18 = SPICLKA
   	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1;  // GPIO19 = SPISTEA	

   	// Enable EQEP1 on GPIO20 - GPIO23
   	GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pullup on GPIO20
   	GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pullup on GPIO21
   	GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pullup on GPIO22
   	GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pullup on GPIO23
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0; // Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0; // Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0; // Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0; // Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;  // GPIO20 = EQEP1A
   	GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;  // GPIO21 = EQEP1B
   	GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;  // GPIO22 = EQEP1S
   	GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;  // GPIO23 = EQEP1I

   	// Enable eCAP1 on GPIO24
   	GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pullup on GPIO24
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT
   	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // GPIO24 = ECAP1

   	// Set input qualifcation period for GPIO25 & GPIO26
   	GpioCtrlRegs.GPACTRL.bit.QUALPRD3=1;  // Qual period = SYSCLKOUT/2
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO25=2;   // 6 samples
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO26=2;   // 6 samples

   	// Make GPIO25 the input source for Xint1
   	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;  // GPIO25 = GPIO25
   	GpioCtrlRegs.GPADIR.bit.GPIO25 = 0;   // GPIO25 = input
   	GpioIntRegs.GPIOXINT1SEL.all = 25;    // Xint1 connected to GPIO25

   	// Make GPIO26 the input source for XINT2
   	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;  // GPIO26 = GPIO26
   	GpioCtrlRegs.GPADIR.bit.GPIO26 = 0;   // GPIO26 = input
   	GpioIntRegs.GPIOXINT2SEL.all = 26;    // XINT2 connected to GPIO26

   	// Make GPIO27 wakeup from HALT/STANDBY Low Power Modes
   	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // GPIO27 = GPIO27
   	GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;  // GPIO27 = input
   	GpioIntRegs.GPIOLPMSEL.bit.GPIO27=1; // GPIO27 will wake the device
   	SysCtrlRegs.LPMCR0.bit.QUALSTDBY=2;  // Qualify GPIO27 by 2 OSCCLK
                                         // cycles before waking the device
                                         // from STANDBY

   	// Enable SCI-A on GPIO28 - GPIO29
   	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;   // Enable pullup on GPIO28
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3; // Asynch input
   	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;  // GPIO28 = SCIRXDA
   	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;   // Enable pullup on GPIO29
   	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;  // GPIO29 = SCITXDA

   	// Enable CAN-A on GPIO30 - GPIO31
   	GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;   // Enable pullup on GPIO30
   	GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 1;  // GPIO30 = CANTXA
   	GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO31
   	GpioCtrlRegs.GPAQSEL2.bit.GPIO31 = 3; // Asynch input
   	GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 1;  // GPIO31 = CANRXA


   	// Enable I2C-A on GPIO32 - GPIO33
   	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;   // Enable pullup on GPIO32
   	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;  // GPIO32 = SDAA
   	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
   	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;   // Enable pullup on GPIO33
   	GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3; // Asynch input
   	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;  // GPIO33 = SCLA

   	// Make GPIO34 an input
   	GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;  // Enable pullup on GPIO34
   	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0; // GPIO34 = GPIO34
   	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 0;  // GPIO34 = input
   	EDIS;
}

// Set inital LED states
void configtestled(void)
{
   EALLOW;
   GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0; // GPIO60 = GPIO60
   GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1; 
   GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0; // GPIO61 = GPIO61
   GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;
   EDIS;
}

// Function to perform five phase Clarke's transformation
float *FivePhaseClarke(float *abc)
{
	float* dq = (float*) malloc(sizeof(float)*5);
	
	dq[0] = (2/5)*(1*abc[1] + cos(1*alpha)*abc[2] + cos(2*alpha)*abc[3] + cos(3*alpha)*abc[4] + cos(4*alpha)*abc[5]);
	dq[1] = (2/5)*(0*abc[1] + sin(1*alpha)*abc[2] + sin(2*alpha)*abc[3] + sin(3*alpha)*abc[4] + sin(4*alpha)*abc[5]);
	dq[2] = (2/5)*(1*abc[1] + cos(2*alpha)*abc[2] + cos(4*alpha)*abc[3] + cos(6*alpha)*abc[4] + cos(8*alpha)*abc[5]);
	dq[3] = (2/5)*(0*abc[1] + sin(2*alpha)*abc[2] + sin(4*alpha)*abc[3] + sin(6*alpha)*abc[4] + sin(8*alpha)*abc[5]);
	dq[4] = (2/5)*(0.5*abc[1] + 0.5*abc[2] + 0.5*abc[3] + 0.5*abc[4] + 0.5*abc[5]);
	
	return dq;
}

//===========================================================================
// No more.
//===========================================================================


