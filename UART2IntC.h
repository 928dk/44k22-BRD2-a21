/*********************************************************************
 *
 *   This file implements the library functionality of UART.
 *   It adds Transmit and receive functionality , circular buffer and 
 *	 interrupt functionality.
 *   
 *********************************************************************
 * FileName:        UART2INTC.h
 * Dependencies:    UART2INTC.def
 * Processor:       PIC18XXX
 * Compiler:		MCC18
 * Assembler:       MPASMWIN 03.20.07
 * Linker:          MPLINK 3.20
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the "Company") is intended and supplied to you, the Company’s
 * customer, for use solely and exclusively with products manufactured
 * by the Company. 
 *
 * The software is owned by the Company and/or its supplier, and is 
 * protected under applicable copyright laws. All rights are reserved. 
 * Any use in violation of the foregoing restrictions may subject the 
 * user to criminal sanctions under applicable laws, as well as to 
 * civil liability for the breach of the terms and conditions of this 
 * license.
 
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES, 
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT, 
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR 
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Reddy TE			Sept. 19,2003		Original Release
 * 
 * Reddy TE			Sept. 24,2003		Changed return values of func-
 *										tions to unsigned char
 ********************************************************************/


//#ifndef _UART2INTC_H
#define	_UART2INTC_H

#include "UART2IntC.def"

/* Constants found in .def file are given readable names*/
#define TX2_BUFFER_SIZE UART2INTC_TX_BUFFER_SIZE
#define RX2_BUFFER_SIZE UART2INTC_RX_BUFFER_SIZE

#ifdef UART2INTC_TXON
  #define TX2ON 1
#elif UART2INTC_TXOFF
  #define TX2ON 0
#endif

#ifdef UART2INTC_RXON
  #define RX2ON 1
#elif UART2INTC_RXOFF
  #define RX2ON 0
#endif

#define TX2ON_AND_RX2ON ((TX2ON) & (RX2ON))
#define	TX2OFF_AND_RX2ON ((!(TX2ON)) & (RX2ON))


// User can change the following values and accordingly
// the ISR location in the main application.
//   Can they be MPAM module parameters?		
#define BRGH2_VAL 1
#define	TX2_PRIORITY_ON	0
#define	RX2_PRIORITY_ON	0

// More error check to be done and the following
// code can be modified.
// If SPBRG is out of range, it won't let the 
// main application be compiled and linked.
#define SPBRG2_V1  (UART2_CLOCK_FREQ / UART2INTC_BAUDRATE)
#define SPBRG2_V2  SPBRG2_V1/16
#define SPBRG2_VAL  (SPBRG2_V2 - 1)
# if (SPBRG2_VAL > 255)
  #error Calculated SPBRG value is out of range
#elif (SPBRG2_VAL < 10)
  #error Calculated SPBRG value is out of range
#endif

struct status2
{
	unsigned UART2IntTxBufferFull  :1;
	unsigned UART2IntTxBufferEmpty :1;
	unsigned UART2IntRxBufferFull  :1;
	unsigned UART2IntRxBufferEmpty :1;
	unsigned UART2IntRxOverFlow :1;
	unsigned UART2IntRxError:1;
};

extern struct status2 vUART2IntStatus;

//  variables representing status of transmission buffer and 
//  transmission buffer it self are declared below

#if TX2ON
extern unsigned char vUART2IntTxBuffer[TX2_BUFFER_SIZE];
extern unsigned char vUART2IntTxBufDataCnt;
extern unsigned char vUART2IntTxBufWrPtr;
extern unsigned char vUART2IntTxBufRdPtr;
#endif

// variables referring the status of receive buffer.

#if	RX2ON
extern unsigned char vUART2IntRxBuffer[RX2_BUFFER_SIZE];
extern unsigned char vUART2IntRxBufDataCnt;
extern unsigned char vUART2IntRxBufWrPtr;
extern unsigned char vUART2IntRxBufRdPtr;
#endif

//  functions offered by this module
#if	RX2ON
// function returns a character from receive buffer
unsigned char UART2IntGetChar(unsigned char*);

// function returns the number of characters in receive buffer
unsigned char UART2IntGetRxBufferDataSize(void);

#endif

#if	TX2ON
// function to put a character in Transmit buffer
unsigned char UART2IntPutChar(unsigned char);

// function returns size of the empty section of Transmit buffer
unsigned char UART2IntGetTxBufferEmptySpace(void);
#endif

// Initialisation of the module
void UART2IntInit(void);
// Interrupt service routine supplied by the module.This need to be 
// called from ISR of the main program.
void UART2IntISR(void);


// Other useful macros

#define mDisableUART2TxInt()				PIE3bits.TX2IE = 0
#define mEnableUART2TxInt()				PIE3bits.TX2IE = 1

#define mDisableUART2RxInt() 			PIE3bits.RC2IE = 0
#define mEnableUART2RxInt()  			PIE3bits.RC2IE = 1

#define mSetUART2RxIntHighPrior() \
										RCONbits.IPEN = 1;\
										IPR3bits.RC2IP = 1
#define mSetUART2RxIntLowPrior() 		IPR3bits.RC2IP = 0

#define mSetUART2TxIntHighPrior()\
										RCONbits.IP2EN = 1;\
										IPR3bits.TX2IP = 1

#define mSetUART2TxIntLowPrior()			IPR3bits.TX2IP = 0


#define mSetUART2_BRGHHigh()				TXSTA2bits.BRGH2 = 1
#define mSetUART2_BRGHLow()				TXSTA2bits.BRGH2 = 0

#define mSetUART2_SPBRG(iBRGValue)\
										RCSTA2bits.SPEN = 0;\
										SPBRG2 = iBRGValue2;\
										RCSTA2bits.SPEN = 1

#define mSetUART2Baud(iBaudRate)\
		do{\
			#define SPBRG2_V11  (UART2_CLOCK_FREQ / UART2INTC_BAUDRATE)\
			#define SPBRG2_V21  SPBRG2_V11/16\
			#define SPBRG2_VAL  (SPBRG2_V21 - 1)\
			#if (SPBRG2_VAL > 255)\
			  #error Calculated SPBRG value is out of range\
			#elif (SPBRG2_VAL < 10)\
			  #error Calculated SPBRG value is out of range\
			#endif\
			RCSTA2bits.SPEN = 0;\
			SPBRG2 = iBaudRate2;\
			RCSTA2bits.SPEN = 1;\
		}while(false)
