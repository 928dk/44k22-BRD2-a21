#include "EEPROM_RW.h"

//**********************************************************************************//
//						 			EEPROM READ WRITE						   		//
//							PIC18F2xK22/F4xK22 256Byte EEPROM						//
//						 			Dean B Fjellerad								//
//	INPUT:																			//
// 	RW = 1 For at skrive og 0 for at læse											//
// 	Adr = Adressen på den palds der vil læses eller skrives til. Fra 0x00 til 0xFF	//
// 	Data = 1byte data der skal skrives til EEPROM under læsning er den ligegyldig	//
//  																				//
//	OUTPUT:																			//
//	RW = 1, Bliver der retuneret 1 for en skrivning der er gået godt, ellers 0 		//
//	RW = 0, Bliver der retuneret data for den angivet adresse						//
//**********************************************************************************//

unsigned char EEPROM_RW(unsigned char Adr, unsigned char Data, unsigned char RW)
{
	if(RW) //WRITE
	{
		EEAdr  = Adr;
		EEData = Data;
		WREN   = 1;
		EECon2 = 0x55;
		EECon2 = 0x0AA;
		WR 	   = 1;
		while(WR);
		WREN   = 0;
		EECON1bits.EEPGD = 0;
		RD = 1;
		if(EEData == Data) return 1;
		else return 0;
		
	}
	else //READ
	{
		EEAdr 		  = Adr;
		EECON1bits.EEPGD = 0;
		RD = 1;
		return EEDATA;		
	}
}
