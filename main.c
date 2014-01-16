/*
 * File:   Low energy 4.0 dual mode
 * Author: bg25382
 *
 * Created on November 14, 2012, 8:32 AM
 *
 *
 *
 *
 *
 *
 */

#include <p18f44k22.h>
#include <stdio.h>      // for uart/io etc getc putc gets puts scanf sprintf mfl
#include <stdlib.h>     //standart bibliothek,  atof atoi atol itoa utoa mfl
#include <htc.h>        //htc compiler definitioner
#include <stdint.h>     //standard integer types per ISO/IEC 9899:1999
#include "mtouch.h"
#include "delays.h"
//#include "uart1.h"
//#include "uart2.h"
#include "blueradios.h"
#include "common.h"
//#include "menu.h"

#include "wiegand.h"

//#include "UARTIntC.h"
#include "UART2IntC.h"



int main(void)
{
Init44k22();
Init_HW();
Init_IO();

InitBlue();
//UART_Init();
//UART2_Init();
UART2IntInit();

//MENU.B = 1;

ENABLEGINT; //enable general interrupts
ENABLEPINT; //enable port interrupts

u16 counter = 0; //(maks 65535)
int counter2 = 0;

unsigned char chartemp;
unsigned char btbuffer[64]; //bluetooth buffer
unsigned char bt = 0; //en byte fra bluetooth (char)
unsigned char index = 0; //indeks // tæller

unsigned char rxstate=0; //modtage status
unsigned char dataok =0; //status for data

CheckBlueR2();

//SetPowerBlue(1);
Delay10x(10);

do //mainloop ... stuff runs forever in a circle
{
counter++;

//GetAddrR2();
//PORT_GREEN = !PORT_GREEN;

if (counter == 16383)//1/4 to max of counter
    {

    }


if (counter == 32767)//halfway to max of counter (sprintf/uart laver overflow med xc8 == -32737)
    {
     
    }

if (counter == 49151)// 3/4 to max of counter
    {
   counter2++;
        if (counter2 == 10) //kører hver 655 350 gang
        {
          
         //GetAddrR2();
         counter2 = 0;
        }
    }

if (counter == 65534) //almost at max
        {
       
//        ConnectBlue();
//        GetAddrR2();
//        CheckBlueR2();
        
        //ShowBlueConfig();
           

        }



if (!dataok)
                {
                bt = UART2IntGetChar(&chartemp);
                }
            else
                bt= 0;
       if(bt)
       {
           //Send_Wiegand(chTemp);
           //PORT_BLUE = !PORT_BLUE;
            switch (rxstate)
            {
                   case 0:
                          if (chartemp == 0x0D) //\r 0x0D CR
                            {
                            rxstate = 1;
                            }

                          break;
                    case 1:
                           if (chartemp == 0x0A) //\n 0x0A  LF
                            {
                            rxstate = 2;

                            }
                           else
                           {
                               rxstate = 0;
                           }
                           break;
                    case 2:
                    {
                         btbuffer[index] = chartemp; //overfør til buffer
                         if ((btbuffer[index -1] == 0x0D) && (btbuffer[index] == 0x0A) ) //\r 0x0D CR //\n 0x0A  LF
                            {
                             dataok = 1;
                             index = 0;
                             rxstate = 0;
                             break;
                         }

                         index++; // naeste placering

                    }
                    break;
             }
           }
        

if (dataok)
{

    do
    {

    Send_Wiegand(btbuffer[index]);
    index++;

    }
    while (btbuffer[index] != 0x0A);

    Send_Wiegand(btbuffer[index]);
    index = 0;
    dataok = 0;
}



if (counter == 65535) //counter has reached max
        {
        counter = 0;
        }

ClrWdt();

} while(1);

//forhaabentligt kommer vi aldrigt ud af while loekken
}


void interrupt Interrupt_High(void)
{
unsigned char c1;
unsigned char c2;

c1 = PRODL;
c2 = PRODH;

//UARTIntISR();
UART2IntISR();
PORT_GREEN = !PORT_GREEN;


PRODL = c1;
PRODH = c2;
}


