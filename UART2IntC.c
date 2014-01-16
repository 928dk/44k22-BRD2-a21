/*********************************************************************
 *
 *   This file implements the functionality of UART with user defined 
 *	 circular buffer. It has the implementation of functions namely 
 *	 UARTIntPutChar, UARTIntGetChar and UARTIntISR . These functions 
 *	 are the core part of UART MPAM module. Additional functions will
 *   be added in future as more desired functionality is identified.
 *   
 *********************************************************************
 * FileName:        UARTIntC.C
 * Dependencies:    UARTIntC.h
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

#include "UART2IntC.h"
#include <p18f44k22.h>

// status flags of receive and transmit buffers
struct status2 vUART2IntStatus;
		
// variable definitions
#if TX2ON
unsigned char vUART2IntTxBuffer[TX2_BUFFER_SIZE];
unsigned char vUART2IntTxBufDataCnt;
unsigned char vUART2IntTxBufWrPtr;
unsigned char vUART2IntTxBufRdPtr;
#endif

#if RX2ON
unsigned char vUART2IntRxBuffer[RX2_BUFFER_SIZE];
unsigned char vUART2IntRxBufDataCnt;
unsigned char vUART2IntRxBufWrPtr;
unsigned char vUART2IntRxBufRdPtr;
#endif

/*********************************************************************
 * Function:        	void UARTIntInit(void)
 * PreCondition:    	None
 * Input:           	None
 * Output:          	None
 * Side Effects:    	None
 * Stack Requirements:	1 level deep
 * Overview:        	This function initialises UART peripheral.This
 *						function need to be called before using 
 *						UARTIntPutChar and UARTIntGetChar functions to 
 *                      send and receive the characters.
 ********************************************************************/
void UART2IntInit(void)
{
	// Intialising the status variables and circular buffer 
	// variables .
	#if TX2ON
		vUART2IntStatus.UART2IntTxBufferFull = 0;
		vUART2IntStatus.UART2IntTxBufferEmpty = 1;
		vUART2IntTxBufDataCnt = 0;
		vUART2IntTxBufWrPtr = 0;
		vUART2IntTxBufRdPtr = 0;
	#endif
	#if	RX2ON
		vUART2IntStatus.UART2IntRxBufferFull = 0;
		vUART2IntStatus.UART2IntRxBufferEmpty = 1;
		vUART2IntStatus.UART2IntRxError = 0;
		vUART2IntStatus.UART2IntRxOverFlow = 0;
		vUART2IntRxBufDataCnt = 0;
		vUART2IntRxBufWrPtr = 0;
		vUART2IntRxBufRdPtr = 0;
	#endif	
	    
    /* Initialising BaudRate value */
		SPBRG2 = SPBRG2_VAL;
		TXSTA2bits.BRGH = BRGH2_VAL;

	/* Initialising TX/RX port pins */
//                #define TRIS_RX2 TRISDbits.TRISD7
//                #define TRIS_TX2 TRISDbits.TRISD6
	#if	TX2ON
		TRISDbits.TRISD6 = 0; //pin 4
	#endif	
	#if RX2ON
		TRISDbits.TRISD7 = 1; //pin 5
	#endif

	/* Setting priority */
	#if	TX2_PRIORITY_ON
		RCON2bits.IPEN = 1;
		IPR3bits.TX2IP = 1;
	#else
		IPR1bits.TXIP = 0;
	#endif					
	#if	RX2_PRIORITY_ON
		RCON2bits.IPEN = 1;
		IPR3bits.RC2IP = 1;
	#else
		IPR3bits.RC2IP = 0;
	#endif 		

	/* Enabling Transmitter or Receiver */
	#if	TX2ON
		TXSTA2bits.TXEN = 1;
	#endif	
	#if	RX2ON
		RCSTA2bits.CREN = 1;
	#endif
	
	/* Enabling Serial Port	*/
	RCSTA2bits.SPEN = 1;
	
	/* Enable the TX and RX. Interrupt */
	#if	TX2ON
		PIE3bits.TX2IE = 1;
        #endif
	#if	RX2ON
		PIE3bits.RC2IE = 1;
	#endif

	/* Setting Global interrupt pins */	
	#if ((TX2_PRIORITY_ON)|(RX2_PRIORITY_ON))
	INTCONbits.GIEH = 1;
	INTCONbits.GIEL = 1;
	#else
	INTCONbits.GIE = 1;
        INTCONbits.PEIE = 1;
	#endif
}

/*********************************************************************
 * Function:        	unsigned char UARTIntPutChar(unsigned char)
 * PreCondition:    	UARTIntInit()function should have been called.
 * Input:           	unsigned char
 * Output:          	unsigned char
 *							  0 - single character is successfully 
 *								  added to transmit buffer.
 *							  1 - transmit buffer is full and the 
 *								  character could not be added to 
 *								  transmit buffer.
 *								  
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:        	This function puts the data in to transmit 
 *						buffer. Internal implementation wise , 
 *						it places the argument data in transmit buffer
 *						and updates the data count and write pointer 
 *						variables. 
 *
 ********************************************************************/
#if	TX2ON
unsigned char UART2IntPutChar(unsigned char chCharData2)
{
	/* check if its full , if not add one */
	/* if not busy send data */
	
	if(vUART2IntStatus.UART2IntTxBufferFull)
		return 0;
   
    //critical code	, disable interrupts
	PIE3bits.TX2IE = 0;
	vUART2IntTxBuffer[vUART2IntTxBufWrPtr] = chCharData2;
	vUART2IntStatus.UART2IntTxBufferEmpty = 0;
	vUART2IntTxBufDataCnt ++;
	if(vUART2IntTxBufDataCnt == TX2_BUFFER_SIZE)
	vUART2IntStatus.UART2IntTxBufferFull = 1;
	vUART2IntTxBufWrPtr++;
	if(vUART2IntTxBufWrPtr == TX2_BUFFER_SIZE)
		vUART2IntTxBufWrPtr = 0;
	PIE3bits.TX2IE = 1;
	
	return 1;
}

/*********************************************************************
 * Function:          unsigned char UARTIntGetTxBufferEmptySpace(void)
 * PreCondition:    	UARTIntInit()function should have been called.
 * Input:           	None
 * Output:          	unsigned char
 *								 0  - There is no empty space in 
 *								       transmit buffer.                  
 *							  number - the number of bytes of empty
 *								       space in transmit buffer. 
 *								                  
 *								  
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:        	This function returns the number of bytes
 *						of free space left out in transmit buffer at
 *						the calling time of this function. It helps  
 *						the user to further write data in to transmit
 *						buffer at once, rather than checking transmit
 *                      buffer is full or not with every addition of
 *                      data in to the transmit buffer.
 ********************************************************************/
unsigned char UART2IntGetTxBufferEmptySpace(void)
{
	if(vUART2IntTxBufDataCnt < TX2_BUFFER_SIZE)
	  	return(TX2_BUFFER_SIZE-vUART2IntTxBufDataCnt);
  	else
  		return 0;
}

#endif

/*********************************************************************
 * Function:        	unsigned char UARTIntGetChar(unsigned char*)
 * PreCondition:    	UARTIntInit()function should have been called.
 * Input:           	unsigned char*
 * Output:          	unsigned char
 *							  0 - receive buffer is empty and the 
 *								  character could not be read from
 *								  the receive buffer.
 *							  1 - single character is successfully 
 *							      read from receive buffer.
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:        	This function reads the data from the receive
 *						buffer. It places the data in to argument and
 *						updates the data count and read pointer 
 *						variables of receive buffer.
 *
 ********************************************************************/
#if	RX2ON
unsigned char UART2IntGetChar(unsigned char *chTemp2)
{
	
	if( vUART2IntStatus.UART2IntRxBufferEmpty)
		return 0;

	//critical code, disabling interrupts here keeps the
	//access pointer values proper.
	PIE3bits.RC2IE = 0;
	vUART2IntStatus.UART2IntRxBufferFull = 0;
	*chTemp2 = vUART2IntRxBuffer[vUART2IntRxBufRdPtr];
	vUART2IntRxBufDataCnt--;
	if(vUART2IntRxBufDataCnt == 0 )
		vUART2IntStatus.UART2IntRxBufferEmpty = 1;
	vUART2IntRxBufRdPtr++;
	if(vUART2IntRxBufRdPtr == RX2_BUFFER_SIZE)
		vUART2IntRxBufRdPtr = 0;
	PIE3bits.RC2IE = 1;
	return 1;
}

/*********************************************************************
 * Function:        	unsigned char UARTIntGetRxBufferDataSize(void)
 * PreCondition:    	UARTIntInit()function should have been called.
 * Input:           	None
 * Output:          	unsigned char 
 *								        number - the number of bytes
 *								             of data in receive buffer. 
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:        	This function returns the number of bytes
 *						of data available in receive buffer at
 *						the calling time of this function. It helps  
 *						the user to read data from receive buffer
 *						at once, rather than checking receive buffer
 *                      is empty or not with every read of data from
 *                      receive buffer.
 ********************************************************************/
unsigned char UART2IntGetRxBufferDataSize(void)
{
	return vUART2IntRxBufDataCnt;
}

#endif

/*********************************************************************
 * Function:        	void UARTIntISR(void)
 * PreCondition:    	UARTIntInit() function should have been called.
 * Input:           	None
 * Output:          	None 
 * Side Effects:    	None
 * Stack Requirements: 	2 level deep
 * Overview:        	This is the Interrupt service routine which is
 *						called in the user application's ISR portion.
 *						This function actually sends the data from
 *						transmit buffer to USART and updates the data
 *						count and read pointer variables of transmit 
 *						buffer. For the receive portion, it reads the
 *						data from USART and places the data in to 
 *						receive buffer (if no errors occured) and
 *						updates data count and write pointer variables
 *						of receive buffer. If the receive buffer is 
 *						full and it receives more data error flag is 
 *						set.If frame errors(FERR) occur	it sets the
 *						error flag. If over flow errors(OERR) occurs,
 *						it clears and sets the CREN bit, so that
 *						USART can receive further data.
 ********************************************************************/
void UART2IntISR(void)
{
	#if	RX2ON
		unsigned char chTemp2;
	#endif
	#if TX2ON
		if((PIR3bits.TX2IF & PIE3bits.TX2IE)&&(BAUDCON2bits.RCIDL))
		{			
			if(!vUART2IntStatus.UART2IntTxBufferEmpty)
			{
							
				TXREG2 = vUART2IntTxBuffer[vUART2IntTxBufRdPtr];
				if(vUART2IntStatus.UART2IntTxBufferFull) vUART2IntStatus.UART2IntTxBufferFull = 0;
				vUART2IntTxBufDataCnt--;
				if(vUART2IntTxBufDataCnt == 0)
				vUART2IntStatus.UART2IntTxBufferEmpty = 1;
				vUART2IntTxBufRdPtr++;
				if(vUART2IntTxBufRdPtr == TX2_BUFFER_SIZE) vUART2IntTxBufRdPtr = 0;
				while(!TXSTA2bits.TRMT);
							
			}
			else
			{   
				PIE3bits.TX2IE = 0;
			}
		}
	#endif	
	#if	TX2ON_AND_RX2N
		else if( PIR3bits.RC2IF & PIE3bits.RC2IE)
	#elif TX2OFF_AND_RX2ON
		if( PIR3bits.RC2IF & PIE3bits.RC2IE)
	#endif
	    #if	RX2ON
			{	
				if(RCSTA2bits.FERR)   /* FERR error condition */
				{ 
					chTemp2 = RCREG2;
					vUART2IntStatus.UART2IntRxError = 1;
				}
				else if (RCSTA2bits.OERR) /* OERR error condition */
				{					
					RCSTA2bits.CREN = 0;
					RCSTA2bits.CREN = 1;
					chTemp2 = RCREG2;
					vUART2IntStatus.UART2IntRxError = 1;
				}
				else if ( vUART2IntStatus.UART2IntRxBufferFull)
				{ 
					chTemp2 = RCREG2;
					vUART2IntStatus.UART2IntRxOverFlow = 1;
				}		 
				else if(!vUART2IntStatus.UART2IntRxBufferFull)
				{	
					vUART2IntStatus.UART2IntRxOverFlow = 0;
					vUART2IntStatus.UART2IntRxBufferEmpty = 0;
					vUART2IntRxBuffer[vUART2IntRxBufWrPtr] = RCREG2;
					vUART2IntRxBufDataCnt ++;
					if(vUART2IntRxBufDataCnt == RX2_BUFFER_SIZE) vUART2IntStatus.UART2IntRxBufferFull = 1;
					vUART2IntRxBufWrPtr++;
					if(vUART2IntRxBufWrPtr == RX2_BUFFER_SIZE) vUART2IntRxBufWrPtr = 0;
				}	
				
			}
  		#endif		
}
