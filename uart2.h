/*
 * File:   uart2.h
 * Author: bg25382
 *
 * Created on October 23, 2012, 10:06 AM
 */

#ifndef UART2_H
#define	UART2_H

void UART2_Init(void);
void UART2_Write(char* pBuffer, char wCount);
void UART2_Read(char* pBuffer, char wCount );
char UART2_BlankNum(void);
char UART2_HoldNum(void);



extern char*   Rx2Fifo_Start;
extern char*   Rx2Fifo_End;
extern char*   Rx2Fifo_Read;
extern char*   Rx2Fifo_Write;

extern char*   Tx2Fifo_Start;
extern char*   Tx2Fifo_End;
extern char*   Tx2Fifo_Read;
extern char*   Tx2Fifo_Write;


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART2_H */


