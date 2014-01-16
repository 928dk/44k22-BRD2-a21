/* 
 * File:   uart1.c
 * Author: bg25382
 *
 * Created on November 23, 2012, 10:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f44k22.h>
#include "common.h"
#include "blueradios.h"
#include "uart1.h"

char UARTRxBuf[64];
char UARTTxBuf[10];

char*   RxFifo_Start;
char*   RxFifo_End;
char*   RxFifo_Read;
char*   RxFifo_Write;

char*   TxFifo_Start;
char*   TxFifo_End;
char*   TxFifo_Read;
char*   TxFifo_Write;

void UART_Init(void)
{

    TxFifo_Start = (char*)UARTRxBuf;
    TxFifo_End   = (char*)UARTRxBuf + sizeof(UARTRxBuf);
    TxFifo_Read  = (char*)UARTRxBuf;
    TxFifo_Write = (char*)UARTRxBuf;

    RxFifo_Start = (char*)UARTTxBuf;
    RxFifo_End   = (char*)UARTTxBuf + sizeof(UARTTxBuf);
    RxFifo_Read  = (char*)UARTTxBuf;
    RxFifo_Write = (char*)UARTTxBuf;

}

void UART_Read(char* pBuffer, char wCount )
{

    while( wCount-- > 0 )
    {
        // read from the FIFO, and pointe to the next
        *pBuffer++ = *RxFifo_Read;
        DISABLEINT;            // disable high level priority interrupt
        RxFifo_Read++;
        ENABLEINT;            // enable high level priority interrupt
        // check if it is the bottom of FIFO
        if( RxFifo_Read >= RxFifo_End )
        {
            DISABLEINT;            // disable high level priority interrupt
            RxFifo_Read = RxFifo_Start;
            ENABLEINT;            // enable high level priority interrupt
        }
    }

}


void UART_Write(char* pBuffer,char wCount )
{

    while( wCount-- > 0 )
    {
        // write to the FIFO, and pointe to the next
        *TxFifo_Write = *pBuffer++;
        DISABLEINT;            // disable high level priority interrupt
        TxFifo_Write++;
        ENABLEINT;            // enable high level priority interrupt
        // check if it is the bottom of FIFO
        if( TxFifo_Write >= TxFifo_End )
        {
            DISABLEINT;            // disable high level priority interrupt
            TxFifo_Write = TxFifo_Start;
            ENABLEINT;            // enable high level priority interrupt
        }
    }
   PIE1bits.TX1IE = 1;             // enable

}


char UART_BlankNum(void)
{

    char wBlankNum;
    DISABLEINT;            // disable high level priority interrupt
    if( TxFifo_Write == TxFifo_Read )
        wBlankNum = TxFifo_End - TxFifo_Start - 1;
    else if( TxFifo_Write > TxFifo_Read )
        wBlankNum = TxFifo_End - TxFifo_Start + TxFifo_Read - TxFifo_Write - 1;
    else
        wBlankNum = TxFifo_Read - TxFifo_Write - 1;
    ENABLEINT;            // enable high level priority interrupt
    return wBlankNum;

}

char UART_HoldNum(void)
{
    char wHoldNum;
    DISABLEINT;            // disable high level priority interrupt
    if( RxFifo_Write == RxFifo_Read )
        wHoldNum = 0;
    else if( RxFifo_Write > RxFifo_Read )
        wHoldNum = RxFifo_Write - RxFifo_Read;
    else
        wHoldNum = RxFifo_End - RxFifo_Start + RxFifo_Write - RxFifo_Read;
    ENABLEINT;            // enable high level priority interrupt
    return wHoldNum;
}