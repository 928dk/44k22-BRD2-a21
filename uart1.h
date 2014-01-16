/* 
 * File:   uart1.h
 * Author: bg25382
 *
 * Created on October 23, 2012, 10:06 AM
 */

#ifndef UART1_H
#define	UART1_H

void UART_Init(void);
void UART_Write(char* pBuffer, char wCount);
void UART_Read(char* pBuffer, char wCount );
char UART_BlankNum(void);
char UART_HoldNum(void);

extern char UARTRxBuf[64];
extern char UARTTxBuf[10];

extern char*   RxFifo_Start;
extern char*   RxFifo_End;
extern char*   RxFifo_Read;
extern char*   RxFifo_Write;

extern char*   TxFifo_Start;
extern char*   TxFifo_End;
extern char*   TxFifo_Read;
extern char*   TxFifo_Write;


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */


