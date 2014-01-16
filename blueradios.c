/*
 * File:   blueradios.c
 * Author: bg25382
 *
 * Created on November 23, 2012, 13:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f44k22.h>
#include "common.h"
#include "blueradios.h"
#include <string.h>
#include "delays.h"
#include "UART2IntC.h"

near union BT BTFLAG;
//extern volatile union BT;
near union MENU MENUFLAG;

/*********************************************************************
 * Function: void InitBlue(void)
 * PreCondition: init porte
 * Input: nul
 * Output:nul
 *
 * Side Effects:    	delay
 * Stack Requirements: 	1 level deep
 * Overview: giver bluetooth modulet en chance for at starte op
 *
 * Power-up and Reset
 * There are no strict requirements for power up timing.
 * The module is ready to receive commands once the boot string is sent out of the UART,
 * approximately 165ms after power on on the single mode and 880ms on the dual mode.
 * To reset the module, the RESET line must be pulsed low for at least 1?S.
 *
 *
 ********************************************************************/
void InitBlue(void)
{
PORT_RTS=0;

Delay10x(6000);

PORT_RTS=1;
}

/*********************************************************************
 * Function: void ShowBlueConfig (void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview: ATCFG? for configuration dump.
 *
 ********************************************************************/
void ShowBlueConfig (void)
{

PORT_RTS=0;

sprintf(bt_tx_buffer,udskriv_config CR);
SendToBt;

Delay10x(600);

PORT_RTS=1;
}

/*********************************************************************
 * Function: void SpoergPassword(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:
 * //#define ask_passkey "ATPLE" //spørger efter en passkey: ATPLE,0<cr>
 ********************************************************************/
void SpoergPassword(void)
{

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "vis konfiguration "  ask_passkey "\r\n" );
    ////SendToPc;
    //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
    }

sprintf(bt_tx_buffer, ask_passkey ",0" cr); //spørger efter en passkey: ATPLE,0<cr>

SendToBt;

}

/*********************************************************************
 * Function: void CheckBlue(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:
 *
 ********************************************************************/
void CheckBlue(void)
{
    if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "er vi klar til kommunikation ? "  bt_ok "\r\n" );
    //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
    }

sprintf(bt_tx_buffer, bt_ok cr);
SendToBt;

//char c = bt_rx_buffer[0];
char c;

switch (c)
    {

    case 'O': //switcher på char nr 0 ("o" kun hvis OK)
            {
            if (MENU.D)
                {
                //sprintf(pc_tx_buffer , "modul siger ok ""\r\n" );
                //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
                }
            //do other stuff

            }
    default :
            {
            if (MENU.D)
                {
                //sprintf(pc_tx_buffer , "ikke forbundet \r\n" );
                //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
                }
            //do other stuff

            }
    }
}


/*********************************************************************
 * Function: int CheckBlueR2(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:
 *
 ********************************************************************/
int CheckBlueR2(void)
{

PORT_RTS=0;

Delay10x(30);

//sprintf(bt_tx_buffer,bt_ok2); //sprintf(bt_tx_buffer, bt_ok "\r\n");
UART2IntPutChar(0x41);
UART2IntPutChar(0x54);
UART2IntPutChar(0x0A);
UART2IntPutChar(0x0D);
//SendToBt;


Delay10x(30);

PORT_RTS=1;

}

/*********************************************************************
 * Function: void ConnectBlue(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview: //verify communication
 *
 ********************************************************************/
void ConnectBlue(void)
{

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "sender AT kommando til bt modul(er vi klar til kommunikation )"  bt_ok "\r\n" );
    //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
    }

sprintf(bt_tx_buffer, bt_ok cr);SendToBt;

Delayx(30);

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "sender discover kommando til bt modul "  discover_cb "\r\n" );
    //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
    }

sprintf(bt_tx_buffer, discover_cb cr);SendToBt;
//return er typisk: DISCOVERY,0,ECFE7E000000,000000,-034,0,0
Delayx(60);

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "sender disconnect kommando til bt modul "  disconnect "\r\n");
    //UART2_Write((char*) pc_tx_buffer ,sizeof pc_tx_buffer  );
    }

sprintf(bt_tx_buffer,command_mode cr);SendToBt;
Delayx(30);

sprintf(bt_tx_buffer,disconnect cr);SendToBt;
Delayx(30);

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "sender connect remoteaddr kommando til bt modul "  discover_cb "\r\n" );
    //SendToPc;
    }

//ATDM,001D98438C41
sprintf(bt_tx_buffer,connect_cb",%s",remoteaddr);
SendToBt;
Delayx(60);

//sprintf(bt_tx_buffer,remoteaddr[0]);
//
//sprintf(bt_tx_buffer, "%s",remoteaddr);
//SendToBt;
//sprintf(bt_tx_buffer, "%d \r", remoteaddr);SendToBt;

}

/*********************************************************************
 * Function: void SortBlue(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview: streng sortering
 *
 ********************************************************************/
void SortBlue(void)
{


//char c = bt_rx_buffer[0];
    char c;

switch (c) {

case 'O': //switcher på char nr 0 ("o" kun hvis OK)
        {
        //sprintf(pc_tx_buffer , "modul siger ok \r\n");
        //SendToPc;
        }
case ',': //switcher på char nr 0 ("komma" kun i CONNECT,<remoteaddr> beskeder)
        {
        //sprintf(pc_tx_buffer , "modul siger forbundet \r\n");
        //SendToPc;
        connected = 1;
        }

case 'S': //switcher på char nr 0 ("S" kun hvis DISCONNECT)
       {
        //sprintf(pc_tx_buffer , "modul siger disconnect \r\n");
        //SendToPc;
        }
case 'R': //switcher på char nr 0 ("R" kun hvis NO CARRIER og NO ANSWER)
       {
        //sprintf(pc_tx_buffer , "modul siger NO CARRIER/ANSWER \r\n");
        //SendToPc;
        }

 case 'E': //switcher på char nr 0 ("E" kun hvis ERROR)
        {
        //sprintf(pc_tx_buffer , "modul siger error \r\n");
        //SendToPc;
        }


//nedstående er kun error codes
//c = bt_rx_buffer[3]; //char nr 4

     if (c == '1') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 1 Invalid Parameters \r\n");
            //SendToPc;
            }
     if (c == '2') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 2 Invalid Role \r\n");
            //SendToPc;
            }
     if (c == '3') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 3 Invalid State \r\n");
            //SendToPc;
            }
     if (c == '4') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 4 Invalid Password \r\n");
            //SendToPc;
            }
     if (c == '5') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 5 Invalid Connection Handle \r\n");
            //SendToPc;
            }
     if (c == '6') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 6 Configuration Locked \r\n");
            //SendToPc;
           }
     if (c == '7') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 7 List Error \r\n");
            //SendToPc;
            }
     if (c == '8') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 8 Hardware Error \r\n");
            //SendToPc;
            }
     if (c == '9') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 9 No Address Stored \r\n");
            //SendToPc;
            }
    //c = bt_rx_buffer[4]; //char nr 5

    if (c == '0') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 10 Bluetooth Error \r\n");
            //SendToPc;
            }
    if (c == '1') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 11 Memory Allocation Error \r\n");
            //SendToPc;
            }
    if (c == '2') {
        //udfør kode
            //sprintf(pc_tx_buffer , "error nr 12 GATT Request Pending \r\n");
            //SendToPc;
            }

default :
            {
            //sprintf(pc_tx_buffer , "ikke forbundet \r\n" );
            //SendToPc;
            }

    } //end of switch



}//end of sortblue

/*********************************************************************
 * Function: void SetPowerBlue(char x)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:  sætter baseband / power niveau
 * eks set_power,0,1 (-23 dBm)
 * eks set_power,1,1 (-6  dBm)
 * eks set_power,2,1 (0 dBm)
 * eks set_power,3,1 (4 dBm)
 * COMMAND:  ATSPL,3,1<cr>
 *
 *
 ********************************************************************/
void SetPowerBlue(char x)
{

sprintf(bt_tx_buffer,set_power",%d,1\r" ,x);
SendToBt;

Delay10x(10);
}

/*********************************************************************
 * Function: void SetNameBlue(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:  sætter navn
 *
 ********************************************************************/
void SetNameBlue(void)
{

if (MENU.D)
    {
    //sprintf(pc_tx_buffer , "sender set navn kommando til bt modul "  set_my_name myname "\r\n" );
    //SendToPc;
    }

sprintf(bt_tx_buffer,set_my_name"," myname "\r");SendToBt;

}

/*********************************************************************
 * Function: void SaveBlue(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:  gemmer karakterer .. prototype
 *
 ********************************************************************/
void SaveBlue(void)
{


int s =0;
//char c = bt_rx_buffer[0];
char c;

if (connected)
    {
    // save only ASCII characters (ASCII 0 - 9) or (ASCII A - Z) or (ASCII a - z) :
    if ((c >= '0') && (c <= '9') || (c >= 'A') && (c <= 'Z') || (c >= 'a') && (c <= 'z')){
      //uart_buf[s] = uart_buf_char;
      s++;

    }

//    if (uart_buf_char == '*') //asterisk er slutningen af en streng
//    {
////      for (int c = 0; c < s; c++)
////        {// clear inhold
////        uart_buf[c] = 0;
////        }
//      s = 0;
//     }

    }

}



void setmaster(void)
{
//bruges til at sætte master remoteaddr
// kun prototype
}

/*********************************************************************
 * Function: void GetAddrR2(void)
 * PreCondition:
 * Input:
 * Output:
 *
 * Side Effects:    	None
 * Stack Requirements: 	1 level deep
 * Overview:  spørger efter adresse
 * 
 * ifølge quickstart guide returnerer LE forbindelse:  <cr_lf>DISCOVERY,6,ECFE7EXXXXXX,0,-045,2,SCAN_DATA<cr_lf>
 * klassisk svarer tilbage med :                       <cr_lf>DISCOVERY,1,ECFE7EXXXXXX,000000,-045,3,EIR_DATA<cr_lf>
 *                                                              9,1,12,6,3,1,8 = totalt 40 plus kommaer (6)
 *
 ********************************************************************/
void GetAddrR2(void)
{


    //sprintf(bt_tx_buffer, discover_cb cr);
sprintf(bt_tx_buffer,"ATDI\r");    SendToBt;

//return er typisk: DISCOVERY,0,ECFE7E000000,000000,-034,0,0
Delay10x(30); //dette delay er for at vente på ok

Delay10x(60);//dette delay er vent på at discovery er done

//remoteaddr[1] = bt_rx_buffer[24]; //kunne laves med en for løkke
//remoteaddr[2] = bt_rx_buffer[25];
//remoteaddr[3] = bt_rx_buffer[26];
//remoteaddr[4] = bt_rx_buffer[27];
//remoteaddr[5] = bt_rx_buffer[28];
//remoteaddr[6] = bt_rx_buffer[29];
//remoteaddr[7] = bt_rx_buffer[30];
//remoteaddr[8] = bt_rx_buffer[31];
//remoteaddr[9] = bt_rx_buffer[32];
//remoteaddr[10] = bt_rx_buffer[33];
//remoteaddr[11] = bt_rx_buffer[34];
//remoteaddr[12] = bt_rx_buffer[35];
//
// if(remoteaddr == defaultaddr)
//    {
//     //dvs hvis remoteadressen er FFFFFFFFFFF så er det laveste sikkerheds niveau
//
//    }
//
//
//    if(remoteaddr == defaultaddr)
//    {
//     //dvs hvis remoteadressen er FFFFFFFFFFF så er det laveste sikkerheds niveau
//    }
//
//    if(remoteaddr == masteraddr)
//    {
//    //dvs hvis
//    }

}
