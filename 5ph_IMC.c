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
#define PI 		3.141592654
#define alpha	1.256637061
#define LED1 	GpioDataRegs.GPBDAT.bit.GPIO60
#define	LED2 	GpioDataRegs.GPBDAT.bit.GPIO61

#if (CPU_FRQ_150MHZ)     // Default - 150 MHz SYSCLKOUT
  #define ADC_MODCLK 0x3 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)   = 25.0 MHz
#endif
#if (CPU_FRQ_100MHZ)
  #define ADC_MODCLK 0x2 // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*2)   = 25.0 MHz
#endif

// Prototype statements for functions found within this file.
interrupt void cpu_timer0_isr(void);
interrupt void cpu_timer1_isr(void);
interrupt void cpu_timer2_isr(void);
interrupt void adc_isr(void);

void configtestled(void);
float *FivePhaseClarke(float *abc);


void main(void)
{
  	
// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
	InitSysCtrl();
    
    // Define ADCCLK clock frequency ( less than or equal to 25 MHz )
	// Assuming InitSysCtrl() has set SYSCLKOUT to 150 MHz
   	EALLOW;
   	SysCtrlRegs.HISPCP.all = ADC_MODCLK;
   	EDIS;
    
    
// Step 2. Initalize GPIO:
	// This example function is found in the DSP2833x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	//InitGpio();
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
//	PieVectTable.XINT13 = &cpu_timer1_isr;
//	PieVectTable.TINT2 = &cpu_timer2_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. 
	// This function can be found in DSP2833x_CpuTimers.c
	InitCpuTimers();   // For this example, only initialize the Cpu Timers

	// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
	// 150MHz CPU Freq, 1 second Period (in uSeconds)
	ConfigCpuTimer(&CpuTimer0, 150, 200000);	// Changed to 0.2s for LED blinking
//	ConfigCpuTimer(&CpuTimer1, 150, 1000000);
//	ConfigCpuTimer(&CpuTimer2, 150, 1000000);
	   
	// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
	// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
	// below settings must also be updated.
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	
	// This function is found in DSP2833x_InitPeripherals.c
	//InitPeripherals(); 	// Not required for this example
	InitAdc();			// For this example, init the ADC

// Step 5. User specific code, enable interrupts:

	// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
	// which is connected to CPU-Timer 1, and CPU int 14, which is connected
	// to CPU-Timer 2:
	IER |= M_INT1;
	IER |= M_INT13;
	IER |= M_INT14;

	// Enable TINT0 and ADCINT in the PIE
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Group 1 interrupt 7 for timer0
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	// Group 1 interrupt 6 for ADC

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
   
	// Setup GPIO
	//Gpio_setup();
	
	// LED setup
	configtestled();
	LED1 = 0;
	LED2 = 1;

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

// Interrupt for cpu_timer1
//interrupt void cpu_timer1_isr(void)
//{
//	CpuTimer1.InterruptCount++;
//    The CPU acknowledges the interrupt.
//	EDIS;
//}

// Interrupt for cpu_timer2
//interrupt void cpu_timer2_isr(void)
//{  
//	EALLOW;
//	CpuTimer2.InterruptCount++;
//   // The CPU acknowledges the interrupt.
//	EDIS;
//}

// Interrupt for ADC
interrupt void adc_isr(void)
{

//  	Voltage1[ConversionCount] = AdcRegs.ADCRESULT0 >>4;
//  	Voltage2[ConversionCount] = AdcRegs.ADCRESULT1 >>4;
//
//  	// If 40 conversions have been logged, start over
//  	if(ConversionCount == 9)
//  	{
//  		ConversionCount = 0;
//  	}
//  	else ConversionCount++;

  	// Reinitialize for next ADC sequence
  	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1
  	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit
  	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

  	return;
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


