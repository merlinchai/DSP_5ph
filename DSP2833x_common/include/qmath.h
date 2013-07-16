/* =================================================================================
File Name:  qmath.h

Originator: Digital Control Systems Group
        Texas Instruments

Description:
Header file containing function prototypes for the Fixed Point Math Functions

===================================================================================*/

#ifndef __QMATH_H__
#define __QMATH_H__

int qsin(int x);
int qcos(int x);
int qatan(long int x);
unsigned int qsqrt(unsigned long x);
int qlog10(unsigned long x);
int qlogn(unsigned long x);
int qsinlt(int x);
int qcoslt(int x);
long qinv1(int x);
int qinv2(int x); 
long qdiv(int x, int y);

#endif




