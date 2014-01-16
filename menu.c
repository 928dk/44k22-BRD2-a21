#include "common.h"
#include "uart1.h"
#include "uart2.h"
#include "blueradios.h"
#include <stdio.h>
#include "menu.h"

void PrintFlags(void)
{
pc_tx_buffer[0] = 0x0C;
pc_txchar_function(pc_tx_buffer,1);// clear screen

//pc_txchar_function(char* pBuffer,char wCount )

if (MENU.P)
    {
    sprintf(pc_tx_buffer, stars"\r\n");
    //SendToPc;
    sprintf(pc_tx_buffer, "er vi klar til kommunikation ? "  bt_ok "\r\n" );//SendToPc;
    }

if (BT.CO)
    {
    if (MENU.P)
        {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, "char 0 fra modul = O ""\r\n" );//SendToPc;
    }
    }

if (BT.CO != 1)
   {
    if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "ikke forbundet \r\n" );//SendToPc;

                }
   }

if (BT.VI == 1)    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
    {
        if (MENU.P)
                {
            sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "der er enheder i naerheden \r\n" );
                //SendToPc;

                }
    }

if (BT.VI != 1)    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
    {   if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "der er ikke enheder i naerheden \r\n" );
                //SendToPc;

                }
    }

if (BT.ER == 1)    //error - ja/nej ? (visuel indikation ? rød diode blinker)
    {  if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "der er fejl \r\n" );
                //SendToPc;

                }
    }

if (BT.ER != 1)    //error - ja/nej ? (visuel indikation ? rød diode blinker)
    {  if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "der er ikke fejl \r\n" );
                //SendToPc;

                }
    }

if (BT.RE == 1)    //ready - ready/not ready (visuel indikation ? rød diode konstant)
        {  if (MENU.P)
                {
            sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "vi er i ready state \r\n" );
                //SendToPc;

                }
        }

if (BT.RE != 1)    //ready - ready/not ready (visuel indikation ? rød diode konstant)
    {if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "vi er i ikke ready state \r\n" );
                //SendToPc;

                }
    }

if (BT.TX == 1)    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
    {if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "sender til bt \r\n" );
                //SendToPc;

                }
    }

if (BT.TX != 1 )    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
    {if (MENU.P)
                {
        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "sender ikke til BT lige nu \r\n" );
                //SendToPc;

                }
    }

//if (BT.PW)    //power - power level  - niveau 0-3 ? 2bit? (ingen visuel indikation)
if (MENU.P)
                {
    sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "power niveau er %d \r\n", BT.PW);
                //SendToPc;

                }


if (BT.MG == 1)    //message
    {

    if ((bt_rx_buffer[0] == 0x4F) && (bt_rx_buffer[1] == 0x4B)) //OK
    {
        PORT_YELLOW = 0;
         }
    else
    {   PORT_YELLOW=1;

    }


    if (MENU.P)
                {

        sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
                sprintf(pc_tx_buffer, "besked flag er sat \r\n");
                //SendToPc;

                  }
    }

if (BT.MG != 1)    //message
    {
//    if (MENU.P)
//                {
//        sprintf(pc_tx_buffer, "***********************************************\r\n");//SendToPc;
//                sprintf(pc_tx_buffer, "besked flag er ikke sat \r\n");
//                //SendToPc;
//
//                }
    }

MENU.P = !MENU.P; //only run once 1

}

void PrintChoice(void)
{
UART2_Read(UART2RxBuf,1 );

if ((UART2RxBuf[0] == 0x41) || (UART2RxBuf[0] == 0x61)) //a eller A
        {
        sprintf(pc_tx_buffer,choicea "\r\n ");//SendToPc;
        MENU.A=!MENU.A;
        }

 //PutcUart2(pc_tx_buffer[0]); //echo tilbage //del af original uart2 kode
if ((UART2RxBuf[0] == 0x42) || (UART2RxBuf[0] == 0x62)) //b eller B
        {
        sprintf(pc_tx_buffer,choiceb);//SendToPc;
        sprintf(pc_tx_buffer,"\r\n");//SendToPc;

        MENU.B=!MENU.B;
        }

if ((UART2RxBuf[0] == 0x43) || (UART2RxBuf[0] == 0x63)) // c
        {
        sprintf(pc_tx_buffer,choicec "\r\n ");//SendToPc;
        
        
        sprintf(pc_tx_buffer, "char 0 %s \r\n",bt_rx_buffer[0]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 1 %s \r\n",bt_rx_buffer[1]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 2 %s \r\n",bt_rx_buffer[2]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 3 %s \r\n",bt_rx_buffer[3]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 4 %s \r\n",bt_rx_buffer[4]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 61 %s \r\n",bt_rx_buffer[61]);
        //SendToPc;

       sprintf(pc_tx_buffer, "char 62 %s \r\n",bt_rx_buffer[62] );
        //SendToPc;

        sprintf(pc_tx_buffer, "char 63 %s \r\n",bt_rx_buffer[63]);
        //SendToPc;

      MENU.C=!MENU.C;
        }

if ((UART2RxBuf[0] == 0x44) || (UART2RxBuf[0] == 0x64))//d
        {
        sprintf(pc_tx_buffer, choiced "\r\n");//SendToPc;
        MENU.D = !MENU.D;
        }

if ((UART2RxBuf[0] == 0x45) || (UART2RxBuf[0] == 0x65)) // e
        {
        sprintf(pc_tx_buffer,choicee "\r\n ");//SendToPc;
        MENU.E=!MENU.E;
        }

if ((UART2RxBuf[0] == 0x46) || (UART2RxBuf[0] == 0x66)) // f
        {
        sprintf(pc_tx_buffer,choicef "\r\n ");//SendToPc;
        MENU.F=!MENU.F;
        }

if ((UART2RxBuf[0] == 0x47) || (UART2RxBuf[0] == 0x67)) // g
        {
        sprintf(pc_tx_buffer,choiceg "\r\n ");//SendToPc;

         sprintf(pc_tx_buffer, "char 0 %d \r\n",bt_rx_buffer[0]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 1 %d \r\n",bt_rx_buffer[1]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 2 %d \r\n",bt_rx_buffer[2]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 3 %d \r\n",bt_rx_buffer[3]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 4 %d \r\n",bt_rx_buffer[4]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 61 %d \r\n",bt_rx_buffer[61]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 62 %d \r\n",bt_rx_buffer[62]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 63 %d \r\n",bt_rx_buffer[63]);
        //SendToPc;

        MENU.G=!MENU.G;
        }

if ((UART2RxBuf[0] == 0x48) || (UART2RxBuf[0] == 0x68)) // h
        {
        sprintf(pc_tx_buffer,choiceh "\r\n ");//SendToPc;
        MENU.H=!MENU.H;
        }

if ((UART2RxBuf[0] == 0x49) || (UART2RxBuf[0] == 0x69)) // i
        {
        sprintf(pc_tx_buffer,choicei "\r\n ");//SendToPc;
        MENU.I=!MENU.I;
        }

if ((UART2RxBuf[0] == 0x4A) || (UART2RxBuf[0] == 0x6A)) // j
        {
        sprintf(pc_tx_buffer,choicej "\r\n ");//SendToPc;
        MENU.J=!MENU.J;
        }

if ((UART2RxBuf[0] == 0x4B) || (UART2RxBuf[0] == 0x6B)) // 0x4B = K 0x6B = k
        {
        sprintf(pc_tx_buffer,choicek "\r\n ");//SendToPc;
        MENU.K=!MENU.K;
        }

if ((UART2RxBuf[0] == 0x4C) || (UART2RxBuf[0] == 0x6C)) // l
        {
        sprintf(pc_tx_buffer,choicel "\r\n ");//SendToPc;
            MENU.L=!MENU.L;
        }

if ((UART2RxBuf[0] == 0x4D) || (UART2RxBuf[0] == 0x6D))// m eller M
        {
        sprintf(pc_tx_buffer, choicem "\r\n");//SendToPc;
        MENU.M = !MENU.M;
        }

if ((UART2RxBuf[0] == 0x4E) || (UART2RxBuf[0] == 0x6E)) // n
        {
        sprintf(pc_tx_buffer,choicen "\r\n ");//SendToPc;
        MENU.N=!MENU.N;
        }

if ((UART2RxBuf[0] == 0x4F) || (UART2RxBuf[0] == 0x6F)) // o
        {

        //UART_Read(bt_rx_buffer,4 );
        sprintf(pc_tx_buffer, choiceo "\r\n ");//SendToPc;



        sprintf(pc_tx_buffer, "char 0 %d \r\n",bt_rx_buffer[0]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 1 %d \r\n",bt_rx_buffer[1]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 2 %d \r\n",bt_rx_buffer[2]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 3 %d \r\n",bt_rx_buffer[3]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 4 %d \r\n",bt_rx_buffer[4]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 61 %d \r\n",bt_rx_buffer[61]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 62 %d \r\n",bt_rx_buffer[62]);
        //SendToPc;

        sprintf(pc_tx_buffer, "char 63 %d \r\n",bt_rx_buffer[63]);
        //SendToPc;
       

        MENU.O=!MENU.O;
        }

if ((UART2RxBuf[0] == 0x50) || (UART2RxBuf[0] == 0x70)) // p
        {
        sprintf(pc_tx_buffer,choicep "\r\n ");//SendToPc;
        MENU.P=!MENU.P;
        }

if ((UART2RxBuf[0] == 0x51) || (UART2RxBuf[0] == 0x71)) // q
        {
        sprintf(pc_tx_buffer,choiceq "\r\n ");//SendToPc;
            MENU.Q=!MENU.Q;
        }

if ((UART2RxBuf[0] == 0x52) || (UART2RxBuf[0] == 0x72)) // r
        {
        sprintf(pc_tx_buffer,choicer "\r\n ");//SendToPc;
            MENU.R=!MENU.R;
        }

if ((UART2RxBuf[0] == 0x53) || (UART2RxBuf[0] == 0x73)) // s
        {
        sprintf(pc_tx_buffer,choices "\r\n ");//SendToPc;

        //sprintf(pc_tx_buffer, "Vaerdi retur fra CheckBlueR2 %x \r", bt_rx_buffer[0]);
        ////SendToPc;
        //PutsUart2((char *)uart_buf);

        MENU.S=!MENU.S;
        }

if ((UART2RxBuf[0] == 0x54) || (UART2RxBuf[0] == 0x74)) // t
        {
        
        sprintf(pc_tx_buffer,choicet "\r\n ");//SendToPc;
        
        sprintf(pc_tx_buffer, "Taeller trigger 65634"); //SendToPc;
         sprintf(pc_tx_buffer,"timer 1 value: %d \r", TMR1L); //SendToPc;

        MENU.T=!MENU.T;
        }

if ((UART2RxBuf[0] == 0x55) || (UART2RxBuf[0] == 0x75)) // u
        {
        sprintf(pc_tx_buffer,choiceu "\r\n ");//SendToPc;
            MENU.U=!MENU.U;
        }

if ((UART2RxBuf[0] == 0x56) || (UART2RxBuf[0] == 0x76)) // v
        {
        sprintf(pc_tx_buffer,choicev "\r\n ");//SendToPc;
            MENU.V=!MENU.V;
        }

//if ((UART2RxBuf[0] == 0x57) || (UART2RxBuf[0] == 0x77)) // w
//        {
//            MENU.W=!MENU.W;
//        }

if ((UART2RxBuf[0] == 0x58) || (UART2RxBuf[0] == 0x78)) // x
        {
        sprintf(pc_tx_buffer,choicex "\r\n ");//SendToPc;
            //MENU.X=!MENU.X;
        }

if ((UART2RxBuf[0] == 0x59) || (UART2RxBuf[0] == 0x79)) // y
        {
        sprintf(pc_tx_buffer,choicey "\r\n ");//SendToPc;
            MENU.Y=!MENU.Y;
        }

}

void PrintMenu(void)
{
pc_tx_buffer[0] = 0x0C;// clear screen
pc_txchar_function((char*) pc_tx_buffer,1 );

        sprintf(pc_tx_buffer, stars );//SendToPc; sprintf(pc_tx_buffer, stars "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menutitel1 );//SendToPc; sprintf(pc_tx_buffer, menutitel2 "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuspace );//SendToPc; sprintf(pc_tx_buffer,menuspace "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menua);//SendToPc; sprintf(pc_tx_buffer, menun "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menub);//SendToPc; sprintf(pc_tx_buffer, menuo "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuc);//SendToPc; sprintf(pc_tx_buffer, menup "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menud);//SendToPc; sprintf(pc_tx_buffer, menuq "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menue);//SendToPc; sprintf(pc_tx_buffer, menur "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuf);//SendToPc; sprintf(pc_tx_buffer, menus "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menug);//SendToPc; sprintf(pc_tx_buffer, menut "\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuh);//SendToPc; sprintf(pc_tx_buffer, menuu"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menui);//SendToPc; sprintf(pc_tx_buffer, menuv"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuj);//SendToPc; sprintf(pc_tx_buffer, menux"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuk);//SendToPc; sprintf(pc_tx_buffer, menuy"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menul);//SendToPc; sprintf(pc_tx_buffer, menuspace"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menum);//SendToPc; sprintf(pc_tx_buffer, menuspace"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, menuspace);//SendToPc; sprintf(pc_tx_buffer,menuspace"\r\n");//SendToPc;
        sprintf(pc_tx_buffer, stars);//SendToPc; sprintf(pc_tx_buffer, stars"\r\n");//SendToPc;
        //MENU.M = !MENU.M;// så bliver menu kun vist 1 gang
}

