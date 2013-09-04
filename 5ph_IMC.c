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


#include "DSP28x_Project.h"     	// Device Headerfile and Examples Include File
#include "DSP2833x_Device.h"		// DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   	// DSP2833x Examples Include File
#include "math.h"					// To perform mathematical functions
#include "CommonDefine.h"			// Global definitions

#include <stdlib.h>					// Contains malloc()

// Definitions for constants
#define PI 		3.141592654
#define alpha	1.256637061

// Definitons for registries
#define LED1 	GpioDataRegs.GPADAT.bit.GPIO22	// Double LEDs
#define	LED2 	GpioDataRegs.GPADAT.bit.GPIO19	// Single LED

// Determine when the shift to right justify the data takes place
// Only one of these should be defined as 1.
// The other two should be defined as 0.
#define POST_SHIFT   0		// Shift results after the entire sample table is full
#define INLINE_SHIFT 1		// Shift results as the data is taken from the results regsiter
#define NO_SHIFT     0  	// Do not shift the results

// ADC parameters
EALLOW;
#define ADC_MODCLK 0x3		// HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 150/(2*3)		= 25.0 MHz
EDIS;

#define ADC_CKPS   0x0		// ADC module clock = HSPCLK/1      = 25.5MHz/(1)   = 25.0 MHz
#define ADC_SHCLK  0x1		// S/H width in ADC module periods                  = 2 ADC cycle
#define AVG        1000		// Average sample limit
#define ZOFFSET    0x00		// Average Zero offset
#define BUF_SIZE   16		// Sample buffer size

// Global variable for ADC
int16 *SampleTable;		// Actual ADC reading - 4096 for 3V
float SampleValue[16];	// Scaled for actual voltage


// Prototype statements
// Interrupts
interrupt void cpu_timer0_isr(void);
interrupt void cpu_timer1_isr(void);
//interrupt void cpu_timer2_isr(void);
interrupt void xint1_isr(void);

// Other functions
void configtestled(void);
float *FivePhaseClarke(float *abc);


void main(void)
{

// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the DSP2833x_SysCtrl.c file.
	InitSysCtrl();

    
// Step 2. Initalize GPIO:
	// Initialize all GPIO as input
	// Input sampling is type 1
	// Enable all pull-ups
	// Disable ePWM pull-ups
	InitGpio();
	
	// Custom I/O initialization
	// For external interrupt from FPGA for PWM data
	InitLogicIO();
	
//	InitXintf16Gpio();


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
//	PieVectTable.TINT2 = &cpu_timer2_isr;
	PieVectTable.XINT1 = &xint1_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. 
	// Initialize flash control registers
	InitFlash();
	
	// Initialize external interface
   	InitXintf();
   	
   	*FPGA_PWMA_Wait5=5000;
	*FPGA_PWMA_Duty5=5000;
	
	// Specific ADC setup for this example:
	InitAdc();
	SetupAdc();	
	
	// This function can be found in DSP2833x_CpuTimers.c
	InitCpuTimers();   // For this example, only initialize the Cpu Timers

	// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
	// 150MHz CPU Freq; 1000000 = 1 sec
	ConfigCpuTimer(&CpuTimer0, 150, 500000);
	ConfigCpuTimer(&CpuTimer1, 150, 1000000);
//	ConfigCpuTimer(&CpuTimer2, 150, 1000000);
	   
	// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
	// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
	// below settings must also be updated.
	CpuTimer0Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	CpuTimer1Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
//	CpuTimer2Regs.TCR.all = 0x4001; // Use write-only instruction to set TSS bit = 0
	
	// Define ADCCLK clock frequency ( less than or equal to 25 MHz )
	// Assuming InitSysCtrl() has set SYSCLKOUT to 150 MHz
   	EALLOW;
   	SysCtrlRegs.HISPCP.all = ADC_MODCLK;
   	EDIS;
   	
   	
	
   	


// Step 5. User specific code, enable interrupts:

	// Enable CPU int1 which is connected to CPU-Timer 0,
	// CPU int13 which is connected to CPU-Timer 1, and 
	// CPU int 14, which is connectedto CPU-Timer 2:
	IER |= M_INT1;
	IER |= M_INT13;
	IER |= M_INT14;

	// Enable TINT0 in the PIE
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;	// Group 1 interrupt 7 for timer0

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
   
	// Setup GPIO
	//Gpio_setup();
	
	// LED setup
	// 1 is OFF; 0 is ON
	configtestled();
	LED1 = 0;
	LED2 = 1;
	


// Step 6. IDLE loop. Just sit and loop forever (optional):
	for(;;)
	{
		
	}	
	
}

// Interrupt for cpu_timer0 is used to change LED state
interrupt void cpu_timer0_isr(void)
{
	CpuTimer0.InterruptCount++;

	// Acknowledge this interrupt to receive more interrupts from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
	
	// Copied from LED code
	CpuTimer0Regs.TCR.bit.TIF=1;
    CpuTimer0Regs.TCR.bit.TRB=1;

	LED1=~LED1;

}

// Interrupt for cpu_timer1
interrupt void cpu_timer1_isr(void)
{
	int i;
	
	CpuTimer1.InterruptCount++;
	// The CPU acknowledges the interrupt.
	EDIS;
	
	// Copied from LED code
	CpuTimer1Regs.TCR.bit.TIF=1;
    CpuTimer1Regs.TCR.bit.TRB=1;
    
    LED2=~LED2;	
    
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
    SampleTable = InquireAdc();
    
    for (i = 0; i < 16; i++)
    {
    	SampleValue[i] = SampleTable[i]*3.0/4096;	
    }
    
}

// Interrupt for cpu_timer2
//interrupt void cpu_timer2_isr(void)
//{  
//	EALLOW;
//	CpuTimer2.InterruptCount++;
//   // The CPU acknowledges the interrupt.
//	EDIS;
//}


// Interrupt for external interrupt from FPGA
interrupt void xint1_isr(void)
{
//	GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
//	Xint1Count++;
//	GpioDataRegs.GPATOGGLE.bit.GPIO24=1;
		*FPGA_PWMA_Wait1=1000;
		*FPGA_PWMA_Duty1=0;

		*FPGA_PWMA_Wait2=1000;
		*FPGA_PWMA_Duty2=0;

		*FPGA_PWMA_Wait3=1000;
		*FPGA_PWMA_Duty3=0;

		*FPGA_PWMA_Wait4=1000;
		*FPGA_PWMA_Duty4=0;

		*FPGA_PWMA_Wait5=1000;
		*FPGA_PWMA_Duty5=1000;

		*FPGA_PWMA_Wait6=1000;
		*FPGA_PWMA_Duty6=2000;

		*FPGA_PWMA_Wait7=1000;
		*FPGA_PWMA_Duty7=3000;

		*FPGA_PWMA_Wait8=4000;
		*FPGA_PWMA_Duty8=4000;

		*FPGA_PWMA_Wait9=5000;
		*FPGA_PWMA_Duty9=5000;

		*FPGA_PWMA_Wait10=6000;
		*FPGA_PWMA_Duty10=6000;

		*FPGA_PWMA_Wait11=7000;
		*FPGA_PWMA_Duty11=7000;

		*FPGA_PWMA_Wait12=8000;
		*FPGA_PWMA_Duty12=8000;

		*DAC1=1024;
		*DAC2=1024;
		*DAC3=1024;
		*DAC4=1024;

	// GpioDataRegs.GPATOGGLE.bit.GPIO24=1;
	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


// Set inital LED states
void configtestled(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0; // GPIO19 = GPIO19
   GpioCtrlRegs.GPADIR.bit.GPIO19 = 1; 
   GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0; // GPIO22 = GPIO22
   GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;
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


