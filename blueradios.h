/* 
 * File:   blueradios.h
 * Author: bg25382
 *
 * Created on November 23, 2012, 1:39 PM
 */
#include "p18f44k22.h"
//#include "common.h"


#ifndef BLUERADIOS_H
#define	BLUERADIOS_H

#define myname "BT1200"

//blueradios definitioner
//definitioner er udarbejdet på baggrund af quick start guide v3.1.0 og nBlue AT.s command set v 3.1.0


#define bt_ok "AT" //er der forbindelse til modulet (modulet skal svare (response) med OK)

#define bt_ok2 "AT\r\n" //er der forbindelse til modulet (modulet skal svare (response) med OK)\r\n

#define my_addr "ATA?" //egen bt adresse

#define discover_cb "ATDI" //find adresser på bt enheder: ATDI <cr>
//The ATDI command is used to start a Classic Bluetooth discovery.
//return er typisk: DISCOVERY,0,ECFE7E000000,000000,-034,0,0

#define connect_cb "ATDM" //opret forbindelse til klassisk BT: ATDM,adresse<cr>
//ATDM,001D98438C41

#define make_le_connection "ATDSLE" //opret low energy forbindelse

#define connect_le "ATDMLE"  //forbind til device:  ATDMLE,adresse<cr>

#define get_le_addr "ATDILE" //find adresse på enheder i nærheden (der kan være op til 2 enheder i nærheden)

#define discover_le "ATDILE" //The ATDILE command is used to start an LE discovery
//return er typisk DISCOVERY,2,ECFE7E000001,0,-045,4,020106-020A04-051208000800-1107796022A0BEAFC0BDDE487962F1842BDA

//modtagelse af paring request fra en anden mobil tlf
//typisk kommer der fra modulet  PAIR_REQ,ECFE7E000001,1
//første streng er  bt_addressen, sidste ciffer 0 = Classic Bluetooth 1 = Low Energy

#define command_mode "+++" //sætter modulet i command mode +++<cr>

#define disconnect "ATDH" //afbryder forbindelsen: ATDH,0<cr> (skal sættes i command mode først)

#define spg_pairing "PAIR_REQ"
//svar tilbage hvilken type pairing der skal fortages
#define ack_pairing "ATPLE" //ATPLE,0,1

#define sleep_mode "ATZ\r"  // Enables sleep mode.

#define ask_passkey "ATPLE" //spørger efter en passkey: ATPLE,0<cr>

#define compare_passkey "ATPKR" //sammenligner passkey og svarer ok hvis i orden ATPKR,ECFE7E000001,123456<cr> (123456 = passkey)

#define udskriv_config "ATCFG?" //udskriver samtlige indstillinger for chippen: Dumps the current configuration.

#define show_my_name "ATSN?" //viser friendly name

#define set_my_name "ATSN" // sætter eget friendly name
//ATSN,BT1200<cr> sætter BT1200 som navn

#define get_paired_name "ATGRU,0,2A00,5" //viser paired device friendly name

//Once connected, both modules will send a PAIRED event, followed by a CONNECT event, showing the
//address of the remote device.  An SPP event will also be sent, signaling that the modules are in SPP data
//mode.  At this point data can be sent by typing into either terminal.
//EVENT:   <cr_lf>PAIRED,ECFE7EXXXXXX,1<cr_lf>
//EVENT:   <cr_lf>CONNECT,0,0,0,ECFE7EXXXXXX<cr_lf>
//EVENT:   <cr_lf>SPP,0,1<cr_lf>

//eks set_power,0,1 (-23 dBm)
//eks set_power,1,1 (-6  dBm)
//eks set_power,2,1 (0 dBm)
//eks set_power,3,1 (4 dBm)
#define set_power "ATSPL" //Sets the transmit power and receive sensitivity of the module.


//prototyper
void ConnectBlue(void);
void SortBlue(void);
void SaveBlue(void);
void SetPowerBlue(char x);
void SetNameBlue(void);
void InitBlue(void);
void CheckBlue(void);
int CheckBlueR2(void);
void ShowBlueConfig (void);
void GetAddrR2(void);

volatile char connected;
volatile char remoteaddr[13]; //remoteaddressen på den pairede enhed .. denne er midlertidig da der er mange brugere
char defaultaddr[13]; //remote addressen på en pairede enhed FFFFFFFFFFFF svarer til alle telefoner
char masteraddr[13]; //denne adresse er autoriseret til at ændre system indstillinger, den skal kunne ændres

int s = 0;
volatile char kode[4]; //konfigurerbar kode
char kode0[4]; //kode 0  = 1234
char kode1[4]; //kode 1 = 0000

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BLUERADIOS_H */

