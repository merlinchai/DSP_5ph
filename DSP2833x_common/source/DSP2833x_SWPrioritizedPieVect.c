// TI File $Revision: /main/2 $
// Checkin $Date: April 4, 2007   14:25:31 $
//###########################################################################
//
// FILE:   DSP2833x_SWPiroritizedPieVect.c
//
// TITLE:  DSP2833x Devices SW Prioritized PIE Vector Table Initialization.
//
//###########################################################################
// 
// Original Source by A.T.
//
// $TI Release: DSP2833x/DSP2823x C/C++ Header Files V1.31 $
// $Release Date: August 4, 2009 $
//###########################################################################

#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_SWPrioritizedIsrLevels.h" 

// original below
const struct PIE_VECT_TABLE PieVectTableInit = {

      PIE_RESERVED,  // 0  Reserved space
      PIE_RESERVED,  // 1  Reserved space 
      PIE_RESERVED,  // 2  Reserved space 
      PIE_RESERVED,  // 3  Reserved space 
      PIE_RESERVED,  // 4  Reserved space 
      PIE_RESERVED,  // 5  Reserved space 
      PIE_RESERVED,  // 6  Reserved space 
      PIE_RESERVED,  // 7  Reserved space 
      PIE_RESERVED,  // 8  Reserved space 
      PIE_RESERVED,  // 9  Reserved space 
      PIE_RESERVED,  // 10 Reserved space 
      PIE_RESERVED,  // 11 Reserved space 
      PIE_RESERVED,  // 12 Reserved space 


// Non-Peripheral Interrupts
      INT13_ISR,     // XINT13 or CPU-Timer 1
      INT14_ISR,     // CPU-Timer2
      DATALOG_ISR,   // Datalogging interrupt
      RTOSINT_ISR,   // RTOS interrupt
      EMUINT_ISR,    // Emulation interrupt
      NMI_ISR,       // Non-maskable interrupt
      ILLEGAL_ISR,   // Illegal operation TRAP
      USER1_ISR,     // User Defined trap 1
      USER2_ISR,     // User Defined trap 2
      USER3_ISR,     // User Defined trap 3
      USER4_ISR,     // User Defined trap 4
      USER5_ISR,     // User Defined trap 5
      USER6_ISR,     // User Defined trap 6
      USER7_ISR,     // User Defined trap 7
      USER8_ISR,     // User Defined trap 8
      USER9_ISR,     // User Defined trap 9
      USER10_ISR,    // User Defined trap 10
      USER11_ISR,    // User Defined trap 11
      USER12_ISR,    // User Defined trap 12

// Group 1 PIE Vectors
      SEQ1INT_ISR,     // 1.1 ADC  
      SEQ2INT_ISR,     // 1.2 ADC  
      rsvd_ISR,        // 1.3
      XINT1_ISR,       // 1.4     
      XINT2_ISR,       // 1.5
      ADCINT_ISR,      // 1.6 ADC
      TINT0_ISR,       // 1.7 Timer 0
      WAKEINT_ISR,     // 1.8 WD, Low Power

// Group 2 PIE Vectors
      EPWM1_TZINT_ISR, // 2.1 EPWM-1 Trip Zone
      EPWM2_TZINT_ISR, // 2.2 EPWM-2 Trip Zone
      EPWM3_TZINT_ISR, // 2.3 EPWM-3 Trip Zone
      EPWM4_TZINT_ISR, // 2.4 EPWM-4 Trip Zone
      EPWM5_TZINT_ISR, // 2.5 EPWM-5 Trip Zone
      EPWM6_TZINT_ISR, // 2.6 EPWM-6 Trip Zone                        
      rsvd_ISR,        // 2.7
      rsvd_ISR,        // 2.8
      
// Group 3 PIE Vectors
      EPWM1_INT_ISR,   // 3.1 EPWM-1 Interrupt
      EPWM2_INT_ISR,   // 3.2 EPWM-2 Interrupt
      EPWM3_INT_ISR,   // 3.3 EPWM-3 Interrupt
      EPWM4_INT_ISR,   // 3.4 EPWM-4 Interrupt
      EPWM5_INT_ISR,   // 3.5 EPWM-5 Interrupt
      EPWM6_INT_ISR,   // 3.6 EPWM-6 Interrupt                        
      rsvd_ISR,        // 3.7
      rsvd_ISR,        // 3.8
      
// Group 4 PIE Vectors
      ECAP1_INT_ISR,   // 4.1 ECAP-1
      ECAP2_INT_ISR,   // 4.2 ECAP-2
      ECAP3_INT_ISR,   // 4.3 ECAP-3
      ECAP4_INT_ISR,   // 4.4 ECAP-4            
      ECAP5_INT_ISR,   // 4.5 ECAP-5     
      ECAP6_INT_ISR,   // 4.6 ECAP-6          
      rsvd_ISR,        // 4.7      
      rsvd_ISR,        // 4.8      
      
// Group 5 PIE Vectors
      EQEP1_INT_ISR,   // 5.1 EQEP-1
      EQEP2_INT_ISR,   // 5.2 EQEP-2
      rsvd_ISR,        // 5.3      
      rsvd_ISR,        // 5.4           
      rsvd_ISR,        // 5.5      
      rsvd_ISR,        // 5.6      
      rsvd_ISR,        // 5.7      
      rsvd_ISR,        // 5.8   


// Group 6 PIE Vectors
      SPIRXINTA_ISR,   // 6.1 SPI-A
      SPITXINTA_ISR,   // 6.2 SPI-A
      MRINTA_ISR,      // 6.3 McBSP-A
      MXINTA_ISR,      // 6.4 McBSP-A
      MRINTB_ISR,      // 6.5 McBSP-B
      MXINTB_ISR,      // 6.6 McBSP-B
      rsvd_ISR,        // 6.7 
      rsvd_ISR,        // 6.8                  

      
// Group 7 PIE Vectors
      DINTCH1_ISR,     // 7.1  DMA channel 1    
      DINTCH2_ISR,     // 7.2  DMA channel 2
      DINTCH3_ISR,     // 7.3  DMA channel 3      
      DINTCH4_ISR,     // 7.4  DMA channel 4           
      DINTCH5_ISR,     // 7.5  DMA channel 5      
      DINTCH6_ISR,     // 7.6  DMA channel 6      
      rsvd_ISR,        // 7.7      
      rsvd_ISR,        // 7.8   

// Group 8 PIE Vectors
      I2CINT1A_ISR,    // 8.1  I2C    
      I2CINT2A_ISR,    // 8.2  I2C
      rsvd_ISR,        // 8.3      
      rsvd_ISR,        // 8.4           
      SCIRXINTC_ISR,   // 8.5  SCI-C
      SCITXINTC_ISR,   // 8.6  SCI-C      
      rsvd_ISR,        // 8.7      
      rsvd_ISR,        // 8.8    
      
// Group 9 PIE Vectors     
      SCIRXINTA_ISR,   // 9.1 SCI-A
      SCITXINTA_ISR,   // 9.2 SCI-A
      SCIRXINTB_ISR,   // 9.3 SCI-B
      SCITXINTB_ISR,   // 9.4 SCI-B
      ECAN0INTA_ISR,   // 9.5 eCAN-A
      ECAN1INTA_ISR,   // 9.6 eCAN-A
      ECAN0INTB_ISR,   // 9.7 eCAN-B
      ECAN1INTB_ISR,   // 9.8 eCAN-B
      
// Group 10 PIE Vectors
      rsvd_ISR,        // 10.1      
      rsvd_ISR,        // 10.2
      rsvd_ISR,        // 10.3      
      rsvd_ISR,        // 10.4           
      rsvd_ISR,        // 10.5      
      rsvd_ISR,        // 10.6      
      rsvd_ISR,        // 10.7      
      rsvd_ISR,        // 10.8    
            
// Group 11 PIE Vectors
      rsvd_ISR,        // 11.1      
      rsvd_ISR,        // 11.2
      rsvd_ISR,        // 11.3      
      rsvd_ISR,        // 11.4           
      rsvd_ISR,        // 11.5      
      rsvd_ISR,        // 11.6      
      rsvd_ISR,        // 11.7      
      rsvd_ISR,        // 11.8
        
// Group 12 PIE Vectors
      XINT3_ISR,       // 12.1      
      XINT4_ISR,       // 12.2
      XINT5_ISR,       // 12.3      
      XINT6_ISR,       // 12.4           
      XINT7_ISR,       // 12.5      
      rsvd_ISR,        // 12.6      
      LVF_ISR,         // 12.7      
      LUF_ISR,         // 12.8   
};

//const struct PIE_VECT_TABLE PieVectTableInit = {
//
//      PIE_RESERVED,       // Reserved space
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//      PIE_RESERVED,       // reserved
//
//// Non-Peripheral Interrupts:
//      #if (INT13PL != 0)
//      INT13_ISR,    // XINT13
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//      
//      #if (INT14PL != 0)
//      INT14_ISR,     // CPU-Timer2
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//      
//      #if (INT15PL != 0)
//      DATALOG_ISR,   // Datalogging interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (INT16PL != 0)
//      RTOSINT_ISR,   // RTOS interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,      // reserved interrupt
//      NMI_ISR,       // Non-maskable interrupt
//      ILLEGAL_ISR,   // Illegal operation TRAP
//      USER1_ISR,     // User Defined trap 1
//      USER2_ISR,     // User Defined trap 2
//      USER3_ISR,     // User Defined trap 3
//      USER4_ISR,     // User Defined trap 4
//      USER5_ISR,     // User Defined trap 5
//      USER6_ISR,     // User Defined trap 6
//      USER7_ISR,     // User Defined trap 7
//      USER8_ISR,     // User Defined trap 8
//      USER9_ISR,     // User Defined trap 9
//      USER10_ISR,    // User Defined trap 10
//      USER11_ISR,    // User Defined trap 11
//      USER12_ISR,    // User Defined trap 12
//
//// Group 1 PIE Vectors:
//      #if (G11PL != 0)
//      SEQ1INT_ISR,   // ADC
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G12PL != 0)
//      SEQ2INT_ISR,   // ADC 
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//
//      #if (G14PL != 0)
//      XINT1_ISR,     // External
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G15PL != 0)
//      XINT2_ISR,     // External
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G16PL != 0)
//      ADCINT_ISR,    // ADC
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G17PL != 0)
//      TINT0_ISR,     // Timer 0
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G18PL != 0)
//      WAKEINT_ISR,   // WD & Low Power
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//// Group 2 PIE Vectors:
//      #if (G21PL != 0)
//      EPWM1_TZINT_ISR,   // ePWM1 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G22PL != 0)
//      EPWM2_TZINT_ISR,   // ePWM2 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G23PL != 0)
//      EPWM3_TZINT_ISR,   // ePWM3 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G24PL != 0)
//      EPWM4_TZINT_ISR,   // ePWM4 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G25PL != 0)
//      EPWM5_TZINT_ISR,   // ePWM5 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G26PL != 0)
//      EPWM6_TZINT_ISR,   // ePWM6 Trip Zone
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//      rsvd_ISR,
//      
//// Group 3 PIE Vectors:
//      #if (G31PL != 0)
//      EPWM1_INT_ISR,     // ePWM1 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G32PL != 0)
//      EPWM2_INT_ISR,     // ePWM2 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G33PL != 0)
//      EPWM3_INT_ISR,     // ePWM3 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G34PL != 0)
//      EPWM4_INT_ISR,     // ePWM4 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G35PL != 0)
//      EPWM5_INT_ISR,     // ePWM5 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G36PL != 0)
//      EPWM6_INT_ISR,     // ePWM6 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//      rsvd_ISR,
//      
//// Group 4 PIE Vectors:
//      #if (G41PL != 0)
//      ECAP1_INT_ISR,     // eCAP1 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G42PL != 0)
//      ECAP2_INT_ISR,     // eCAP2 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G43PL != 0)
//      ECAP3_INT_ISR,     // eCAP3 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G44PL != 0)
//      ECAP4_INT_ISR,     // eCAP4 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G45PL != 0)
//      ECAP5_INT_ISR,     // eCAP5 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G46PL != 0)
//      ECAP6_INT_ISR,     // eCAP6 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//      rsvd_ISR,          
//     
//// Group 5 PIE Vectors:
//      #if (G51PL != 0)
//      EQEP1_INT_ISR,     // eQEP1 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G52PL != 0)
//      EQEP2_INT_ISR,     // eQEP2 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//      rsvd_ISR,
//      rsvd_ISR,
//      rsvd_ISR,
//      rsvd_ISR,
//      rsvd_ISR,            
//
//// Group 6 PIE Vectors:
//      #if (G61PL != 0)
//      SPIRXINTA_ISR,  // SPI-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G62PL != 0)
//      SPITXINTA_ISR,  // SPI-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G63PL != 0)
//      MRINTB_ISR,     // McBSP-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G64PL != 0)
//      MXINTB_ISR,     // McBSP-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G65PL != 0)
//      MRINTA_ISR,     // McBSP-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G66PL != 0)
//      MXINTA_ISR,     // McBSP-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//	  rsvd_ISR,
//      
//// Group 7 PIE Vectors:
//      #if (G71PL != 0)
//      DINTCH1_ISR,     // DMA-Channel 1 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G72PL != 0)
//      DINTCH2_ISR,     // DMA-Channel 2 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G73PL != 0)
//      DINTCH3_ISR,     // DMA-Channel 3 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G74PL != 0)
//      DINTCH4_ISR,     // DMA-Channel 4 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G75PL != 0)
//      DINTCH5_ISR,     // DMA-Channel 5 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G76PL != 0)
//      DINTCH6_ISR,     // DMA-Channel 6 Interrupt
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//      rsvd_ISR,         
//
//// Group 8 PIE Vectors:
//      #if (G81PL != 0)
//      I2CINT1A_ISR,    // I2C-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G82PL != 0)
//      I2CINT2A_ISR,    // I2C-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//           
//      rsvd_ISR,     
//      rsvd_ISR,  
//         
//      #if (G85PL != 0)
//      SCIRXINTC_ISR,    // SCI-C
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G86PL != 0)
//      SCITXINTC_ISR,    // SCI-C
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//          
//      rsvd_ISR,     
//      rsvd_ISR,     
//      
//// Group 9 PIE Vectors:
//      #if (G91PL != 0)
//      SCIRXINTA_ISR,    // SCI-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G92PL != 0)
//      SCITXINTA_ISR,    // SCI-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G93PL != 0)
//      SCIRXINTB_ISR,    // SCI-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G94PL != 0)
//      SCITXINTB_ISR,    // SCI-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G95PL != 0)
//      ECAN0INTA_ISR,    // eCAN-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G96PL != 0)
//      ECAN1INTA_ISR,   // eCAN-A
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G97PL != 0)
//      ECAN0INTB_ISR,   // eCAN-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G98PL != 0)
//      ECAN1INTB_ISR,   // eCAN-B
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//      
//// Group 10 PIE Vectors
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//            
//// Group 11 PIE Vectors
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//      rsvd_ISR,     
//
//// Group 12 PIE Vectors
//      #if (G121PL != 0)
//      XINT3_ISR,       // External interrupt 3
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G122PL != 0)
//      XINT4_ISR,       // External interrupt 4
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G123PL != 0)
//      XINT5_ISR,       // External interrupt 5
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G124PL != 0)
//      XINT6_ISR,       // External interrupt 6
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G125PL != 0)
//      XINT7_ISR,       // External interrupt 7
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      rsvd_ISR,
//
//      #if (G127PL != 0)
//      LVF_ISR,         // Latched overflow flag  
//      #else
//      INT_NOTUSED_ISR,
//      #endif
//
//      #if (G128PL != 0)
//      LUF_ISR,         // Latched underflow flag
//      #else
//      INT_NOTUSED_ISR,
//      #endif   
//};

//---------------------------------------------------------------------------
// InitPieVectTable: 
//---------------------------------------------------------------------------
// This function initializes the PIE vector table to a known state.
// This function must be executed after boot time.
//

void InitPieVectTable(void)
{
   int16 i;
   Uint32 *Source = (void *) &PieVectTableInit;
   Uint32 *Dest = (void *) &PieVectTable;

   EALLOW;
   for(i=0; i < 128; i++) {
      *Dest++ = *Source++;
   }
   EDIS;
   
   // Enable the PIE Vector Table
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
}

//===========================================================================
// No more.
//===========================================================================
