// TI File $Revision: /main/5 $
// Checkin $Date: October 23, 2007   13:34:09 $
//###########################################################################
//
// FILE:	DSP2833x_Adc.c
//
// TITLE:	DSP2833x ADC Initialization & Support Functions.
//
//###########################################################################
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     	// DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   	// DSP2833x Examples Include File

#include <stdlib.h>

#define ADC_usDELAY  5000L

//---------------------------------------------------------------------------
// InitAdc:
//---------------------------------------------------------------------------
// This function initializes ADC to a known state.
//
void InitAdc(void)
{
    extern void DSP28x_usDelay(Uint32 Count);


    // *IMPORTANT*
	// The ADC_cal function, which  copies the ADC calibration values from TI reserved
	// OTP into the ADCREFSEL and ADCOFFTRIM registers, occurs automatically in the
	// Boot ROM. If the boot ROM code is bypassed during the debug process, the
	// following function MUST be called for the ADC to function according
	// to specification. The clocks to the ADC MUST be enabled before calling this
	// function.
	// See the device data manual and/or the ADC Reference
	// Manual for more information.

	    EALLOW;
		SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
		ADC_cal();
		EDIS;


    // To powerup the ADC the ADCENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and ADC core.
    // Before the first conversion is performed a 5ms delay must be observed
	// after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
	// CPU_RATE define statement in the DSP2833x_Examples.h file must
	// contain the correct CPU clock period in nanoseconds.

    AdcRegs.ADCTRL3.all = 0x00E0;  // Power up bandgap/reference/ADC circuits
    DELAY_US(ADC_usDELAY);         // Delay before converting ADC channels
}

void SetupAdc(void)
{
	// Highest ADC clock speed is 12.5MHz
	AdcRegs.ADCTRL3.bit.ADCCLKPS = 0x0001;		// Core clock divider; HSPCLK = 25MHz for 150MHz SYSCLKOUT
												// ADCCLKPS = HSPCLK/(2*(ADCTRL[7]+1)) = 12.5MHz for 0x0001
	AdcRegs.ADCTRL1.bit.CPS = 0x0000;			// Core clock prescaler; not divided if 0
	
	// ADC period
	AdcRegs.ADCTRL1.bit.ACQ_PS = 0x000F;		// Acquisition window size = 16xADCLK period
	
	// Use sequential sampling
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;			// Sequential sampling, not concurrent
	
	// Cascade mode
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1; 			// Cascaded sequencer operation
												// SEQ1 and SEQ2 operate as a single 16-bit SEQ
	
	// Enable external interrupt 2 to trigger ADC
 	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0;		// Disable SEQ1 interrupt (every EOS)
   	AdcRegs.ADCTRL2.bit.EXT_SOC_SEQ1 = 1;  		// Enables ADC autoconversion sequence to be started by
												// a signal from the GPIO Port A pin (GPIO31-0) configured
												// as XINT2 in the GPIOXIN2SEL register
												// Enable EINT2 to start SEQ1
	
	// Maximum conversion is 15
	// 1 sample for each channel
	AdcRegs.ADCMAXCONV.all = 0x000F;
		
	// Start-stop mode
	// Sequencer stops after reaching EOS
	// On the next SOC, the sequencer starts from the state where it ended unless a sequencer reset is performed
	// Need to reset using software
	AdcRegs.ADCTRL1.bit.CONT_RUN = 0;

	// Setup all ADCINAx for SEQx conv.
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0000;   
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x0001;   
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x0002;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x0003;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x0004;   
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x0005;   
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x0006;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x0007;
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x0008;   
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x0009;   
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x000A;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x000B;
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0x000C;   
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0x000D;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0x000E;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0x000F; 
    
	// SEQ1 interrupt mode
	// INT_SEQ1 is set at the end of every SEQ1 sequence
	AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
}


int16 *InquireAdc(void)
{
//	int16 result00, result01, result02, result03, result04, result05, result06, result07;
//	int16 result08, result09, result10, result11, result12, result13, result14, result15;
	
	int16* result = (int16*) malloc(16*sizeof(int16));
	
	// Sample ADC until complete
	while (AdcRegs.ADCST.bit.INT_SEQ1 == 0){}
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;	// INT_SEQ1 = 1 indicates conversion of SEQ1 of ADC is complete
										// Clear interrupt flag bit INT_SEQ1

	result[0] = (int16)(AdcRegs.ADCRESULT0>>4);
	result[1] = (int16)(AdcRegs.ADCRESULT1>>4);
	result[2] = (int16)(AdcRegs.ADCRESULT2>>4);
	result[3] = (int16)(AdcRegs.ADCRESULT3>>4);
	result[4] = (int16)(AdcRegs.ADCRESULT4>>4);
	result[5] = (int16)(AdcRegs.ADCRESULT5>>4);
	result[6] = (int16)(AdcRegs.ADCRESULT6>>4);
	result[7] = (int16)(AdcRegs.ADCRESULT7>>4);
	result[8] = (int16)(AdcRegs.ADCRESULT8>>4);
	result[9] = (int16)(AdcRegs.ADCRESULT9>>4);
	result[10] = (int16)(AdcRegs.ADCRESULT10>>4);
	result[11] = (int16)(AdcRegs.ADCRESULT11>>4);
	result[12] = (int16)(AdcRegs.ADCRESULT12>>4);
	result[13] = (int16)(AdcRegs.ADCRESULT13>>4);
	result[14] = (int16)(AdcRegs.ADCRESULT14>>4);
	result[15] = (int16)(AdcRegs.ADCRESULT15>>4);	
	
//	result00 = (int16)(AdcRegs.ADCRESULT0>>4);
//	result01 = (int16)(AdcRegs.ADCRESULT1>>4);
//	result02 = (int16)(AdcRegs.ADCRESULT2>>4);
//	result03 = (int16)(AdcRegs.ADCRESULT3>>4);
//	result04 = (int16)(AdcRegs.ADCRESULT4>>4);
//	result05 = (int16)(AdcRegs.ADCRESULT5>>4);
//	result06 = (int16)(AdcRegs.ADCRESULT6>>4);
//	result07 = (int16)(AdcRegs.ADCRESULT7>>4);
//	result08 = (int16)(AdcRegs.ADCRESULT8>>4);
//	result09 = (int16)(AdcRegs.ADCRESULT9>>4);
//	result10 = (int16)(AdcRegs.ADCRESULT10>>4);
//	result11 = (int16)(AdcRegs.ADCRESULT11>>4);
//	result12 = (int16)(AdcRegs.ADCRESULT12>>4);
//	result13 = (int16)(AdcRegs.ADCRESULT13>>4);
//	result14 = (int16)(AdcRegs.ADCRESULT14>>4);
//	result15 = (int16)(AdcRegs.ADCRESULT15>>4);	
                           
	// Reset SEQ1 to state CONV00
	// Required before setting SOC_SEQ1
 	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
      
  	return result;
}

//===========================================================================
// End of file.
//===========================================================================
