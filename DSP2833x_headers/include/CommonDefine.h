// Definitions

#ifndef CommonDefine_H
#define CommonDefine_H

//--------------------------------------------
// Declaration of data address for FPGA
//--------------------------------------------

// PWM module definition
// PWMA on the actual hardware is misaligned
// Recommend to use PWMB,C,D,E instead
#define FPGA_PWMA_Period (unsigned int *)0x210000
#define FPGA_PWMA_Wait1 (unsigned int *)0x210001
#define FPGA_PWMA_Duty1 (unsigned int *)0x210002
#define FPGA_PWMA_Wait2 (unsigned int *)0x210003
#define FPGA_PWMA_Duty2 (unsigned int *)0x210004
#define FPGA_PWMA_Wait3 (unsigned int *)0x210005
#define FPGA_PWMA_Duty3 (unsigned int *)0x210006
#define FPGA_PWMA_Wait4 (unsigned int *)0x210007
#define FPGA_PWMA_Duty4 (unsigned int *)0x210008
#define FPGA_PWMA_Wait5 (unsigned int *)0x210009
#define FPGA_PWMA_Duty5 (unsigned int *)0x21000a
#define FPGA_PWMA_Wait6 (unsigned int *)0x21000b
#define FPGA_PWMA_Duty6 (unsigned int *)0x21000c
#define FPGA_PWMA_Wait7 (unsigned int *)0x21000d
#define FPGA_PWMA_Duty7 (unsigned int *)0x21000e
#define FPGA_PWMA_Wait8 (unsigned int *)0x21000f
#define FPGA_PWMA_Duty8 (unsigned int *)0x210010
#define FPGA_PWMA_Wait9 (unsigned int *)0x210011
#define FPGA_PWMA_Duty9 (unsigned int *)0x210012
#define FPGA_PWMA_Wait10 (unsigned int *)0x210013
#define FPGA_PWMA_Duty10 (unsigned int *)0x210014
#define FPGA_PWMA_Wait11 (unsigned int *)0x210015
#define FPGA_PWMA_Duty11 (unsigned int *)0x210016
#define FPGA_PWMA_Wait12 (unsigned int *)0x210017
#define FPGA_PWMA_Duty12 (unsigned int *)0x210018

#define FPGA_PWMB_Period (unsigned int *)0x210020
#define FPGA_PWMB_Wait1 (unsigned int *)0x210021
#define FPGA_PWMB_Duty1 (unsigned int *)0x210022
#define FPGA_PWMB_Wait2 (unsigned int *)0x210023
#define FPGA_PWMB_Duty2 (unsigned int *)0x210024
#define FPGA_PWMB_Wait3 (unsigned int *)0x210025
#define FPGA_PWMB_Duty3 (unsigned int *)0x210026
#define FPGA_PWMB_Wait4 (unsigned int *)0x210027
#define FPGA_PWMB_Duty4 (unsigned int *)0x210028
#define FPGA_PWMB_Wait5 (unsigned int *)0x210029
#define FPGA_PWMB_Duty5 (unsigned int *)0x21002a
#define FPGA_PWMB_Wait6 (unsigned int *)0x21002b
#define FPGA_PWMB_Duty6 (unsigned int *)0x21002c
#define FPGA_PWMB_Wait7 (unsigned int *)0x21002d
#define FPGA_PWMB_Duty7 (unsigned int *)0x21002e
#define FPGA_PWMB_Wait8 (unsigned int *)0x21003f
#define FPGA_PWMB_Duty8 (unsigned int *)0x210030
#define FPGA_PWMB_Wait9 (unsigned int *)0x210031
#define FPGA_PWMB_Duty9 (unsigned int *)0x210032
#define FPGA_PWMB_Wait10 (unsigned int *)0x210033
#define FPGA_PWMB_Duty10 (unsigned int *)0x210034
#define FPGA_PWMB_Wait11 (unsigned int *)0x210035
#define FPGA_PWMB_Duty11 (unsigned int *)0x210036
#define FPGA_PWMB_Wait12 (unsigned int *)0x210037
#define FPGA_PWMB_Duty12 (unsigned int *)0x210038

#define FPGA_PWMC_Period (unsigned int *)0x210040
#define FPGA_PWMC_Wait1 (unsigned int *)0x210041
#define FPGA_PWMC_Duty1 (unsigned int *)0x210042
#define FPGA_PWMC_Wait2 (unsigned int *)0x210043
#define FPGA_PWMC_Duty2 (unsigned int *)0x210044
#define FPGA_PWMC_Wait3 (unsigned int *)0x210045
#define FPGA_PWMC_Duty3 (unsigned int *)0x210046
#define FPGA_PWMC_Wait4 (unsigned int *)0x210047
#define FPGA_PWMC_Duty4 (unsigned int *)0x210048
#define FPGA_PWMC_Wait5 (unsigned int *)0x210049
#define FPGA_PWMC_Duty5 (unsigned int *)0x21004a
#define FPGA_PWMC_Wait6 (unsigned int *)0x21004b
#define FPGA_PWMC_Duty6 (unsigned int *)0x21004c
#define FPGA_PWMC_Wait7 (unsigned int *)0x21004d
#define FPGA_PWMC_Duty7 (unsigned int *)0x21004e
#define FPGA_PWMC_Wait8 (unsigned int *)0x21005f
#define FPGA_PWMC_Duty8 (unsigned int *)0x210050
#define FPGA_PWMC_Wait9 (unsigned int *)0x210051
#define FPGA_PWMC_Duty9 (unsigned int *)0x210052
#define FPGA_PWMC_Wait10 (unsigned int *)0x210053
#define FPGA_PWMC_Duty10 (unsigned int *)0x210054
#define FPGA_PWMC_Wait11 (unsigned int *)0x210055
#define FPGA_PWMC_Duty11 (unsigned int *)0x210056
#define FPGA_PWMC_Wait12 (unsigned int *)0x210057
#define FPGA_PWMC_Duty12 (unsigned int *)0x210058

#define FPGA_PWMD_Period (unsigned int *)0x210060
#define FPGA_PWMD_Wait1 (unsigned int *)0x210061
#define FPGA_PWMD_Duty1 (unsigned int *)0x210062
#define FPGA_PWMD_Wait2 (unsigned int *)0x210063
#define FPGA_PWMD_Duty2 (unsigned int *)0x210064
#define FPGA_PWMD_Wait3 (unsigned int *)0x210065
#define FPGA_PWMD_Duty3 (unsigned int *)0x210066
#define FPGA_PWMD_Wait4 (unsigned int *)0x210067
#define FPGA_PWMD_Duty4 (unsigned int *)0x210068
#define FPGA_PWMD_Wait5 (unsigned int *)0x210069
#define FPGA_PWMD_Duty5 (unsigned int *)0x21006a
#define FPGA_PWMD_Wait6 (unsigned int *)0x21006b
#define FPGA_PWMD_Duty6 (unsigned int *)0x21006c
#define FPGA_PWMD_Wait7 (unsigned int *)0x21006d
#define FPGA_PWMD_Duty7 (unsigned int *)0x21006e
#define FPGA_PWMD_Wait8 (unsigned int *)0x21006f
#define FPGA_PWMD_Duty8 (unsigned int *)0x210070
#define FPGA_PWMD_Wait9 (unsigned int *)0x210071
#define FPGA_PWMD_Duty9 (unsigned int *)0x210072
#define FPGA_PWMD_Wait10 (unsigned int *)0x210073
#define FPGA_PWMD_Duty10 (unsigned int *)0x210074
#define FPGA_PWMD_Wait11 (unsigned int *)0x210075
#define FPGA_PWMD_Duty11 (unsigned int *)0x210076
#define FPGA_PWMD_Wait12 (unsigned int *)0x210077
#define FPGA_PWMD_Duty12 (unsigned int *)0x210078


#define FPGA_PWME_Period (unsigned int *)0x210080
#define FPGA_PWME_Wait1 (unsigned int *)0x210081
#define FPGA_PWME_Duty1 (unsigned int *)0x210082
#define FPGA_PWME_Wait2 (unsigned int *)0x210083
#define FPGA_PWME_Duty2 (unsigned int *)0x210084
#define FPGA_PWME_Wait3 (unsigned int *)0x210085
#define FPGA_PWME_Duty3 (unsigned int *)0x210086
#define FPGA_PWME_Wait4 (unsigned int *)0x210087
#define FPGA_PWME_Duty4 (unsigned int *)0x210088
#define FPGA_PWME_Wait5 (unsigned int *)0x210089
#define FPGA_PWME_Duty5 (unsigned int *)0x21008a
#define FPGA_PWME_Wait6 (unsigned int *)0x21008b
#define FPGA_PWME_Duty6 (unsigned int *)0x21008c
#define FPGA_PWME_Wait7 (unsigned int *)0x21008d
#define FPGA_PWME_Duty7 (unsigned int *)0x21008e
#define FPGA_PWME_Wait8 (unsigned int *)0x21008f
#define FPGA_PWME_Duty8 (unsigned int *)0x210090
#define FPGA_PWME_Wait9 (unsigned int *)0x210091
#define FPGA_PWME_Duty9 (unsigned int *)0x210092
#define FPGA_PWME_Wait10 (unsigned int *)0x210093
#define FPGA_PWME_Duty10 (unsigned int *)0x210094
#define FPGA_PWME_Wait11 (unsigned int *)0x210095
#define FPGA_PWME_Duty11 (unsigned int *)0x210096
#define FPGA_PWME_Wait12 (unsigned int *)0x210097
#define FPGA_PWME_Duty12 (unsigned int *)0x210098

// I/O module
// Each number corresponds to an I/O port
// 0 is low, non-0 is high
// 1 is output, 0 is input

#define FPGA_IO1_DATA (unsigned int *)0x2100a0
#define FPGA_IO2_DATA (unsigned int *)0x2100a1
#define FPGA_IO3_DATA (unsigned int *)0x2100a2
#define FPGA_IO4_DATA (unsigned int *)0x2100a3
#define FPGA_IO5_DATA (unsigned int *)0x2100a4
#define FPGA_IO6_DATA (unsigned int *)0x2100a5
#define FPGA_IO7_DATA (unsigned int *)0x2100a6
#define FPGA_IO8_DATA (unsigned int *)0x2100a7
#define FPGA_IO9_DATA (unsigned int *)0x2100a8
#define FPGA_IO10_DATA (unsigned int *)0x2100a9
#define FPGA_IO11_DATA (unsigned int *)0x2100aa
#define FPGA_IO12_DATA (unsigned int *)0x2100ab
#define FPGA_IO13_DATA (unsigned int *)0x2100ac
#define FPGA_IO14_DATA (unsigned int *)0x2100ad
#define FPGA_IO15_DATA (unsigned int *)0x2100ae
#define FPGA_IO16_DATA (unsigned int *)0x2100af
#define FPGA_IO17_DATA (unsigned int *)0x2100b0
#define FPGA_IO18_DATA (unsigned int *)0x2100b1
#define FPGA_IO19_DATA (unsigned int *)0x2100b2
#define FPGA_IO20_DATA (unsigned int *)0x2100b3
#define FPGA_IO21_DATA (unsigned int *)0x2100b4
#define FPGA_IO22_DATA (unsigned int *)0x2100b5
#define FPGA_IO23_DATA (unsigned int *)0x2100b6
#define FPGA_IO24_DATA (unsigned int *)0x2100b7
#define FPGA_IODIR_LOW (unsigned int *)0x2100b8
#define FPGA_IODIR_HIGH (unsigned int *)0x2100b9

// DAC module
#define DAC1 (unsigned int *)0x2100e0
#define DAC2 (unsigned int *)0x2100e1
#define DAC3 (unsigned int *)0x2100e2
#define DAC4 (unsigned int *)0x2100e3

#define FPGA_DATA_Test_length 8

// Inverter space vectors
// Space vectors -15 to 15, then 0
extern int SpaceVectorsInv[32][5];

// Rectifier space vectors			
// Space vectors -3 to 3, then 0					  
extern int SpaceVectorsRec[9][2];

#endif    // end of Commondefine.h definition




 



