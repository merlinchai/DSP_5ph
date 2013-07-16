/* ==================================================================
File name       : IIR.H                     

Originator      : Advanced Embeeded Control (AEC)
                  Texas Instruments Inc.

Description:  
Header file containing object definitions, proto type declaration and 
default object initializers for IIR Filter.
===================================================================
 History:
-------------------------------------------------------------------
12-05-2003    Release Rev 1.0                                                  
-------------------------------------------------------------------*/

#ifndef __IIR_H__
#define __IIR_H__
#define     NULL    0

 
/*----------------------------------------------------------------
Define the structure of the IIR5BIQ16 Filter Module 
-----------------------------------------------------------------*/
typedef struct { 
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    int *coeff_ptr;         /* Pointer to Filter coefficient */
    int *dbuffer_ptr;       /* Delay buffer ptr              */
    int nbiq;               /* No of biquad                  */
    int input;              /* Latest Input sample           */
    int isf;                /* Input Scale Factor            */ 
    int qfmat;              /* Q format of coeff             */
    int output;             /* Filter Output                 */
    }IIR5BIQ16;    


/*---------------------------------------------------------------
Define the structure of the IIR5BIQ32 Filter Module
-----------------------------------------------------------------*/
typedef struct {
    void (*init)(void *);   /* Ptr to init fn                */
    void (*calc)(void *);   /* Ptr to calc fn                */ 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long *dbuffer_ptr;      /* Delay buffer ptr              */
    int nbiq;               /* No of biquad                  */
    int input;              /* Latest Input sample           */
    long isf;               /* Input Scale Factor            */ 
    long output32;          /* Filter Output (Q30)           */
    int output16;           /* Filter Output (Q14)           */
    int qfmat;              /* Q format of coeff             */
    }IIR5BIQ32;
               
 
/*---------------------------------------------------------------
Define a Handles for the Filter Modules
-----------------------------------------------------------------*/
typedef IIR5BIQ16     *IIR5BIQ16_handle;
typedef IIR5BIQ32     *IIR5BIQ32_handle;    
        
          
#define IIR5BIQ16_DEFAULTS { (void (*)(void *))IIR5BIQ16_init,\
             (void (*)(void *))IIR5BIQ16_calc,\
             (int *)NULL,   \
             (int *)NULL,   \
             0,             \
             0,             \
             0,             \
             0,             \
             0}    

#define IIR5BIQ32_DEFAULTS { (void (*)(void *))IIR5BIQ32_init,\
             (void (*)(void *))IIR5BIQ32_calc, \
             (long *)NULL,   \
             (long *)NULL,   \
             0,             \
             0,             \
             0,             \
             0,             \
             0,             \
             0}                           


/*-------------------------------------------------------------
 Prototypes for the functions
---------------------------------------------------------------*/
void IIR5BIQ16_calc(void *);
void IIR5BIQ32_calc(void *);

/******** Sample IIR co-efficients ****************************/
 
void IIR5BIQ16_init(IIR5BIQ16 *);
void IIR5BIQ32_init(IIR5BIQ32 *);

/* LPF co-efficients for IIR16 module	*/
#define IIR16_LPF_COEFF {\
            -746,4846,1056,2111,1056,\
            -1032,5001,1120,2239,1120,\
            -1639,5330,1192,2385,1192,\
            -2647,5877,1211,2422,1211,\
            -4206,6722,872,1745,872,\
            -6573,8005,4861,9722,4861}
#define IIR16_LPF_ISF 4092
#define IIR16_LPF_NBIQ    6
#define IIR16_LPF_QFMAT   138

/* HPF co-efficients for IIR16 module	*/
#define IIR16_HPF_COEFF {\
            0,-2597,0,-3340,3340,\
            -2211,-2396,1746,-3492,1746,\
            -4745,2276,2007,-4014,2007,\
            -7046,5310,13685,-27370,13685}
#define IIR16_HPF_ISF 5595
#define IIR16_HPF_NBIQ    4
#define IIR16_HPF_QFMAT   13
                            
    
/* BPF co-efficients for IIR16 module	*/ 
#define IIR16_BPF_COEFF {\
            -1078,1437,-367,0,367,\
            -1395,935,713,43,713,\
            -1496,2176,594,-917,594,\
            -1855,994,1022,-329,1022,\
            -1890,2462,18610,-25359,18610}
#define IIR16_BPF_ISF     721
#define IIR16_BPF_NBIQ    5
#define IIR16_BPF_QFMAT   11 
           

/* BSF co-efficients for IIR16 module	*/
#define IIR16_BSF_COEFF {\
            -1532,1626,859,-781,859,\
            -1889,1374,2032,-1644,2032,\
            -1906,2168,22098,-22158,22098}
#define IIR16_BSF_ISF     366
#define IIR16_BSF_NBIQ    3
#define IIR16_BSF_QFMAT   11


/* LPF co-efficients for IIR32 module	*/
#define IIR32_LPF_COEFF {\
            -24444800,158794151,8647611,17295223,8647611,\
            -33805581,163869390,36741777,73483554,36741777,\
            -53695266,174653202,39535955,79071910,39535955,\
            -86750921,192575355,40880726,81761451,40880726,\
            -137806611,220256787,30931379,61862757,30931379,\
            -215373186,262311922,564004144,1128008289,564004144}

#define IIR32_LPF_ISF   134086103
#define IIR32_LPF_NBIQ  6
#define IIR32_LPF_QFMAT 28


/* HPF co-efficients for IIR32 module	*/
#define IIR32_HPF_COEFF {\
            0,-85096979,0,-29857202,29857202,\
            -72466417,-78522171,97363917,-194727833,97363917,\
            -155480100,74571693,88837952,-177675903,88837952,\
            -230891969,173985995,715131301,-1430262602,715131301}

#define IIR32_HPF_ISF   183338477
#define IIR32_HPF_NBIQ  4
#define IIR32_HPF_QFMAT 28


/* BPF co-efficients for IIR32 module	*/
#define IIR32_BPF_COEFF {\
            -70620977,94154018,-24080177,0,24080177,\
            -91416523,61304763,46717868,2819319,46717868,\
            -98072227,142585344,38933432,-60070942,38933432,\
            -121545500,65135203,66986143,-21532217,66986143,\
            -123895267,161346553,1219596683,-1661914443,1219596683}

#define IIR32_BPF_ISF   47247113
#define IIR32_BPF_NBIQ  5
#define IIR32_BPF_QFMAT 27


/* BSF co-efficients for IIR32 module	*/
#define IIR32_BSF_COEFF {\
            -100408845,106578277,56314524,-51161340,56314524,\
            -123814194,90035192,133182068,-107730821,133182068,\
            -124894576,142053666,1448196385,-1452129490,1448196385}

#define IIR32_BSF_ISF   23999390
#define IIR32_BSF_NBIQ  3
#define IIR32_BSF_QFMAT 27

//自己的定义的巴特沃思滤波器参数
//转折频率20，截止频率200,转折频率处3db,其后40db每十倍频程衰减
//#define IIR16_COEFF {\
//			-16095,32476,4392,8783,4392}

//#define IIR16_ISF	2
//#define IIR16_NBIQ	1
//#define IIR16_QFMAT	14

#define IIR16_COEFF {\
			-13345,29417,4471,8942,4471}

#define IIR16_ISF	286
#define IIR16_NBIQ	1
#define IIR16_QFMAT	14

//全局变量声明
extern const int IIR_coeff[5*IIR16_NBIQ];
 
#define IIR32_COEFF {\
			-523014183,1059778969,5658,11315,5658,\
			-531087547,1067851524,634124942,1268249884,634124942}

#define IIR32_ISF	106142
#define IIR32_NBIQ	2
#define IIR32_QFMAT	29

/* 滤波器设计的原则是首先保证50HZ时必要的衰减，
然后再看直流点小输入( <20 ) 附近增益是否稳定
ezIIR FILTER DESIGN SCRIPT
Butterworth       : 1
Chebyshev(Type 1) : 2
Chebyshev(Type 2) : 3
Elliptic          : 4
Select Any one of the above IIR Filter Type     : 1
Low pass          : 1
High Pass         : 2
Band Pass         : 3
Band Stop         : 4
Select Any one of the above Response            : 1
Enter the Sampling frequency                    : 10000
Enter the Pass band Ripples in dB(RP)           : 3
Enter the stop band Rippled in dB(RS)           : 20
Enter the pass band corner frequency(FP)        : 20
Enter the stop band corner frequency(FS)        : 40
Enter the name of the file for coeff storage    : lpf4.dat
 
Q format of the IIR filter coefficients:
    29

Input Scaling value:
  1.9770e-004

Number of Biquads:
     2
*/

//全局变量声明
extern const long IIR32_coeff[5*IIR32_NBIQ];


#endif 

