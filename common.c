/*
 * File:   common.c
 * Author: bg25382
 *
 * Created on November 29, 2012, 6:39 AM
 */

#include "common.h"
#include <p18f44k22.h>
#include "UART2IntC.h"
#include "blueradios.h"
#include "mtouch.h"

extern volatile char connected;     // hentes fra blueradios.h (derfor extern)
extern volatile char remoteaddr[13];// hentes fra blueradios.h (derfor extern)
extern char defaultaddr[13];        // hentes fra blueradios.h (derfor extern)
extern char masteraddr[13];         // hentes fra blueradios.h (derfor extern)
extern volatile char kode[4];       // hentes fra blueradios.h (derfor extern)
extern char kode0[4];               // hentes fra blueradios.h (derfor extern)
extern char kode1[4];              // hentes fra blueradios.h (derfor extern)


void Init44k22(void)
{
#pragma config FOSC = INTIO67   // Oscillator Selection bits (Internal oscillator block)
#pragma config PLLCFG = ON      // 4X PLL Enable (Oscillator multiplied by 4)
#pragma config PRICLKEN = OFF   // Primary clock enable bit (Primary clock can be disabled by software)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit (Power up timer disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 190       // Brown Out Reset Voltage bits (VBOR set to 1.90 V nominal)

// CONFIG2H
#pragma config WDTEN = ON       // Watchdog Timer Enable bits (WDT is always enabled. SWDTEN bit has no effect)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<5:0> pins are configured as digital I/O on Reset)
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit (P3A/CCP3 input/output is multiplexed with RB5)
#pragma config HFOFST = OFF     // HFINTOSC Fast Start-up (HFINTOSC output and ready status are delayed by the oscillator stable status)
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit (T3CKI is on RC0)
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit (P2B is on RD2)
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit (MCLR pin enabled, RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled if MCLRE is also 1)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (002000-003FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (002000-003FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)





}

void Init_HW(void)
{
    /*******************OSC Setup***********************/

//	OSCCON  = 0b01100011; //8mhz
//        OSCCON  = 0b01110011; //16mhz
        OSCCON  = 0b01110000; //64mhz 00

	OSCCON2 = 0b00000000;
	OSCTUNE = 0b11000000;
	while(!OSCCONbits.HFIOFS);

	/********************* Interupt **********************/
	INTCON  = 0b00000000; //INTERRUPT CONTROL
	INTCON2 = 0b11110101;
	INTCON3 = 0b00000000;

	PIR1	= 0b00000000; //PERIPHERAL INTERRUPT (FLAG)
	PIR2	= 0b00000000;
	PIR3	= 0b00000000;
	PIR4	= 0b00000000;
	PIR5	= 0b00000000;

	PIE1	= 0b00000000; //PERIPHERAL INTERRUPT ENABLE
	PIE2	= 0b00000000;
	PIE3	= 0b00000000;
	PIE4	= 0b00000000;
	PIE5	= 0b00000000;

	IPR1	= 0b00000000; //PERIPHERAL INTERRUPT PRIORITY
	IPR2	= 0b00000000;
	IPR3	= 0b00000000;
	IPR4	= 0b00000000;
	IPR5	= 0b00000000;

	/*******************PORT SETUP**********************/

	TRISA = 0b00100000;
	TRISB = 0b11000000;
	TRISC = 0b10000000;
	TRISD = 0b00000000;
	TRISE = 0b00001001;

	PORTA = 0b01000000;
	PORTB = 0b00000000;
	PORTC = 0b00000001;
	PORTD = 0b00000000;
	PORTE = 0b00000000;

        ANSELA = 0;
        ANSELB = 0;
        ANSELC = 0;
        ANSELD = 0;
        ANSELE = 0;

}

void Init_IO(void)
{



        /****************** EUSART Setup **********************/
        T3CON = 0b00010100; //Wiegand

	/****************** EUSART Setup **********************/
	TXSTA1 	 = 0b00100100;
	RCSTA1 	 = 0b10010000;
	BAUDCON1 = 0b00000000;
        BAUDCON1bits.RXCKP = 1;
        


//Tris vælger om det er input(1) eller output (0)
//Med Port kan man skrive 0 eller 1 hvis pin er valgt som output
//hvis port er valgt som input kan man læse om der er 0 eller 1 på pin

//Leds
TRIS_RED = 0; //output
TRIS_GREEN = 0;//output
TRIS_YELLOW = 0;//output
PORT_RED = 0; //sæt høj
PORT_GREEN = 0;//sæt høj
PORT_YELLOW = 0;//sæt høj

//Keypad
TRIS_K0 = 1; //input
TRIS_K1 = 1; //input
TRIS_K2 = 1; //input

//Uart1
//PORT_RX = 0;
//PORT_TX = 0;
TRIS_RX = 1;//Input
TRIS_TX = 0;//Output

//Uart2
//PORT_RX2 = 0;
//PORT_TX2 = 0;
TRIS_RX2 = 1; //Input
TRIS_TX2 = 1;//

TRIS_RTS = 0; //Output
TRIS_CTS = 1; //Input

//Uart1
ANSELCbits.ANSC7 = 0; //Port C7 select som digital port
ANSELCbits.ANSC6 = 0; //Port C6 select som digital port

//Uart2
ANSELDbits.ANSD7 = 0; //Port D7 select som digital port
ANSELDbits.ANSD6 = 0; //Port D6 select som digital port

//Leds
ANSELAbits.ANSA3 = 0; //Port A3 select som digital port LED
ANSELEbits.ANSE1 = 0; //Port E1 select som digital port LED
ANSELEbits.ANSE2 = 0; //Port E2 select som digital port LED


}

void InitTimer0(void)
{
T0CON	=0xC1;  //at:1100001 em:1100010// clr(LATC,2);
T0CONbits.T08BIT = 0;
T0CONbits.T0CS = 1;
T0CONbits.T0PS = 0b10;
T0CONbits.T0SE = 1;
T0CONbits.TMR0ON =1;
//T0CONbits.PSA = 1;
}

void InitTimer1(void)
{
TMR1L = 0x00;
T1CONbits.TMR1CS = 1;   //Clk = Fosc
T1CONbits.T1CKPS = 0b10;   //PreScaler
T1CONbits.T1RD16 = 0;   //16 bits = 0 = 8bits
T1CONbits.TMR1ON = 1;   //timer 1 on
PIR1bits.TMR1IF = 0;    //timer 1 interrupt flag (clear = 0)
PIE1bits.TMR1IE = 1;    //timer 1 interrupt enable
}

void InitTimer2(void)
{

    T2CON=0x1D;  //FCA 4Khz PWM (buz), 1ms TMR2IF (eco)
    T2CONbits.T2CKPS = 0b10;
    T2CONbits.TMR2ON = 1;
}

void InitTimer3(void)
{


TMR3L = 0x00;
/****************** EUSART Setup **********************/
        T3CON = 0b00010100; //Wiegand
//PIR2bits.TMR3IF = 0;
//PIR2bits.
PIR3bits.TMR3GIF = 0;    //timer 3 interrupt flag (clear = 0)
PIE3bits.TMR3GIE = 1;    //timer 3 interrupt enable

}

void InitUart1(void)
{
RCSTA1bits.SPEN = 0; //disable serial port
PIE1bits.TXIE = 0; //tx interrupt enable

TXSTA1bits.TX9 = 0; //tx not 9 bit (8bits)
TXSTA1bits.TXEN = 1; //Enable transmit
TXSTA1bits.SYNC = 0; //Async
TXSTA1bits.BRGH = 1; //High speed

RCSTA1bits.RX9 = 0; //8bits rx
RCSTA1bits.CREN = 1; //Continuous reception

BAUDCON1bits.BRG16 = 0; //1 = 16bits
//SPBRG1 = SPBRG1_VAL;


PIR1bits.RCIF = 0; //interrupt flag clear
PIR1bits.TXIF = 0; //interrupt flag clear

PIE1bits.RCIE = 1; //rx interrupt enable
PIE1bits.TXIE = 0; //tx interrupt enable

RCSTA1bits.SPEN = 1; //Enable serial port
}

void InitUart2(void)
{
RCSTA2bits.SPEN = 0;    //disable uart 2
PIE3bits.TX2IE = 0;     // TX interrupt disable

TXSTA2bits.TX9 = 0;     //tx not 9 bit (8bits)
TXSTA2bits.TXEN = 1;    //Enable tx
TXSTA2bits.SYNC = 0;    //Async
TXSTA2bits.BRGH = 1;    //High speed prescale /16

RCSTA2bits.RX9 = 0;     //8bits rx
RCSTA2bits.CREN = 1;    //Continuous rx enavle

BAUDCON2bits.BRG16 = 0; //1 = 16bits
//SPBRG2 = SPBRG2_VAL;

IPR3bits.TX2IP = 0;// high prio
IPR3bits.RC2IP = 0;// high prio

PIR3bits.TX2IF = 0; // Clear interrupt flag
PIR3bits.RC2IF = 0; // Clear interrupt flag

PIE3bits.RC2IE = 1;     // Set RX interrupt enable
PIE3bits.TX2IE = 0;     // TX interrupt disable

RCSTA2bits.SPEN2 = 1;
}

//Sw-restart, set vars to a known value
void InitStatic(void)
{

char remoteaddr[13] = "001D98438C41"; //gammel nokia telefon
char defaultaddr[13] = "FFFFFFFFFFFF"; // alle telefoner
char masteraddr[13]= "001D98438C41"; //gammel nokia telefon;

char kode[4] = "FFFF"; //konfigurerbar kode / password
char kode0[4] = "1234"; //
char kode1[4] = "0000";
/*
 *
 */




/*
 * til mtouch
 */
b1 = 0; //init static after system reboot
b2 = 0;//init static after system reboot
b1cal = 0;
b2cal = 0;
b1tot = 0;
b2tot = 0;
b1avg = 0;
b2avg = 0;
b1CTMUI = 0;
b2CTMUI = 0;
/*
 *
 */


BT.Flag=0;

MENU.Flag = 0;

}

void ClearSettings(void)
{
    /*
 * til mtouch
 */
b1 = 0; //init static after system reboot
b2 = 0;//init static after system reboot
b1cal = 0;
b2cal = 0;
b1tot = 0;
b2tot = 0;
b1avg = 0;
b2avg = 0;
b1CTMUI = 0;
b2CTMUI = 0;
/*
 *
 */


BT.Flag=0;

MENU.Flag = 0;

}

void ReStartTmr1()
{
TMR1L=0x00;
TMR1H=0x00;
}

void ReStartTmr2()
{
TMR2=0x00;

}

void ReStartTmr3()
{
TMR3=0x00;

}

//void WriteSUart2(char *data)
//{
//        do
//        {  // Transmit a byte
//                while(!TXSTA2bits.TRMT); //tilføjet i a14 03-12-2012, alle char bliver nu skrevet til pc'en
//                UART2_Write((char*)data,1);
//        } while( *data++ );
//}

//void WriteSUart2(char *data,char size)
//{
//        do
//        {  // Transmit a byte
//                //while(!TXSTA2bits.TRMT); //tilføjet i a14 03-12-2012, alle char bliver nu skrevet til pc'en
//                UART2IntPutChar(data);
//        } while( *data++ );
//}

UART2_WriteString(char* data)
{
do

        {

    // Transmit a byte
                //while(!TXSTA2bits.TRMT); //tilføjet i a14 03-12-2012, alle char bliver nu skrevet til pc'en
                UART2IntPutChar(data);
                *data ++;
        } while( *data != 0x0A );

        UART2IntPutChar(0x0A);

}

