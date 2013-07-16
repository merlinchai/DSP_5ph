/* =================================================================================
File name:       ICLARKE.H  (IQ version)                  
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: 
Header file containing constants, data type definitions, and 
function prototypes for the ICLARKE.
=====================================================================================
 History:
-------------------------------------------------------------------------------------
 04-15-2005	Version 3.20                                                   
------------------------------------------------------------------------------*/
#ifndef __ICLARKE_H__
#define __ICLARKE_H__

typedef struct {     _iq  As;  		// Output: phase-a stator variable
				  _iq  Bs;	        // Output: phase-b stator variable 
                             _iq  Cs;              // Output: phase-c stator variable
				  _iq  Alpha;		// Input: stationary d-axis stator variable 
				  _iq  Beta;		// Input: stationary q-axis stator variable
		 	 	  void  (*calc)();	// Pointer to calculation function
				 } ICLARKE;	            

typedef ICLARKE *ICLARKE_handle;
/*-----------------------------------------------------------------------------
Default initalizer for the ICLARKE object.
-----------------------------------------------------------------------------*/                     
#define ICLARKE_DEFAULTS { 0, \
                           0, \
                           0, \
                           0, \
                           0, \
              			  (void (*)(Uint32))iclarke_calc }

/*------------------------------------------------------------------------------
Prototypes for the functions in ICLARKE.C
------------------------------------------------------------------------------*/
void iclarke_calc(ICLARKE_handle);

#endif // __ICLARKE_H__
