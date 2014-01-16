#include "p18f44k22.h"

#define Rd 0
#define Wr 1

#define EEAdr  EEADR
#define EEData EEDATA
#define WREN   EECON1bits.WREN
#define EECon2 EECON2
#define WR	   EECON1bits.WR
#define WR_ERR EECON1bits.WRERR

#define RD	   EECON1bits.RD

enum Cnf_EE
{
	Cnf_WiegandKey,
	Cnf_WiegandCard,
	Cnf_SingleKey,
	Cnf_Facil,
	Cnf_Indic,
	Cnf_Key
};
unsigned char EEPROM_RW(unsigned char Adr, unsigned char Data, unsigned char RW);
