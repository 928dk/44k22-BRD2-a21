
/*
 * File:   uart2.c
 * Author: bg25382
 *
 * Created on November 23, 2012, 10:05 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f44k22.h>
#include "common.h"
#include "blueradios.h"
#include "uart2.h"

char UART2RxBuf[30];
char UART2TxBuf[30];

char*   Rx2Fifo_Start;
char*   Rx2Fifo_End;
char*   Rx2Fifo_Read;
char*   Rx2Fifo_Write;

char*   Tx2Fifo_Start;
char*   Tx2Fifo_End;
char*   Tx2Fifo_Read;
char*   Tx2Fifo_Write;

void UART2_Init(void)
{

    Tx2Fifo_Start = (char*)UART2RxBuf;
    Tx2Fifo_End   = (char*)UART2RxBuf + sizeof(UART2RxBuf);
    Tx2Fifo_Read  = (char*)UART2RxBuf;
    Tx2Fifo_Write = (char*)UART2RxBuf;

    Rx2Fifo_Start = (char*)UART2TxBuf;
    Rx2Fifo_End   = (char*)UART2TxBuf + sizeof(UART2TxBuf);
    Rx2Fifo_Read  = (char*)UART2TxBuf;
    Rx2Fifo_Write = (char*)UART2TxBuf;

}

void UART2_Read(char* pBuffer, char wCount )
{

    while( wCount-- > 0 )
    {
        // read from the FIFO, and pointe to the next
        *pBuffer++ = *Rx2Fifo_Read;
        DISABLEINT;            // disable high level priority interrupt
        Rx2Fifo_Read++;
        ENABLEINT;            // enable high level priority interrupt
        // check if it is the bottom of FIFO
        if( Rx2Fifo_Read >= Rx2Fifo_End )
        {
            DISABLEINT;            // disable high level priority interrupt
            Rx2Fifo_Read = Rx2Fifo_Start;
            ENABLEINT;            // enable high level priority interrupt
        }
    }

}


void UART2_Write(char* pBuffer,char wCount )
{

    while( wCount-- > 0 )
    {
        // write to the FIFO, and pointe to the next
        *Tx2Fifo_Write = *pBuffer++;
        DISABLEINT;            // disable high level priority interrupt
        Tx2Fifo_Write++;
        ENABLEINT;            // enable high level priority interrupt
        // check if it is the bottom of FIFO
        if( Tx2Fifo_Write >= Tx2Fifo_End )
        {
            DISABLEINT;            // disable high level priority interrupt
            Tx2Fifo_Write = Tx2Fifo_Start;
            ENABLEINT;            // enable high level priority interrupt
        }
    }
   PIE3bits.TX2IE = 1;             // enable


}


char UART2_BlankNum(void)
{

    char wBlankNum;
    DISABLEINT;            // disable high level priority interrupt
    if( Tx2Fifo_Write == Tx2Fifo_Read )
        wBlankNum = Tx2Fifo_End - Tx2Fifo_Start - 1;
    else if( Tx2Fifo_Write > Tx2Fifo_Read )
        wBlankNum = Tx2Fifo_End - Tx2Fifo_Start + Tx2Fifo_Read - Tx2Fifo_Write - 1;
    else
        wBlankNum = Tx2Fifo_Read - Tx2Fifo_Write - 1;
    ENABLEINT;            // enable high level priority interrupt
    return wBlankNum;

}

char UART2_HoldNum(void)
{
    char wHoldNum;
    DISABLEINT;            // disable high level priority interrupt
    if( Rx2Fifo_Write == Rx2Fifo_Read )
        wHoldNum = 0;
    else if( Rx2Fifo_Write > Rx2Fifo_Read )
        wHoldNum = Rx2Fifo_Write - Rx2Fifo_Read;
    else
        wHoldNum = Rx2Fifo_End - Rx2Fifo_Start + Rx2Fifo_Write - Rx2Fifo_Read;
    ENABLEINT;            // enable high level priority interrupt
    return wHoldNum;
}
