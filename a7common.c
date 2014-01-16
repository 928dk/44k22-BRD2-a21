/*
 * File:   common.c
 * Author: bg25382
 *
 * Created on November 29, 2012, 6:39 AM
 */
#include "common.h"
#include <p18f44k22.h>
#include "customserial.h"
#include "blueradios.h"
#include "mtouch.h"

extern volatile char connected;     // hentes fra blueradios.h (derfor extern)
extern volatile char remoteaddr[13];// hentes fra blueradios.h (derfor extern)
extern char defaultaddr[13];        // hentes fra blueradios.h (derfor extern)
extern char masteraddr[13];         // hentes fra blueradios.h (derfor extern)
extern volatile char kode[4];       // hentes fra blueradios.h (derfor extern)
extern char kode0[4];               // hentes fra blueradios.h (derfor extern)
extern char kode1[4] ;              // hentes fra blueradios.h (derfor extern)

near union{struct
 {
u1 VI:1;    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
u1 ER:1;    //error - ja/nej ? (visuel indikation ? rød diode blinker)
u1 TX:1;    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
u1 RE:1;    //ready - ready/not ready (visuel indikation ? rød diode konstant)
u1 CO:1;    //connected - forbundet ? bluetooth ja/nej (visuel indikation - lysdiode grøn)
u1 PW:2;    //power - power level  - niveau 0-3 ? 2bit? (ingen visuel indikation)
u1 MG:1;    //message
 };u8 Flag;
}BT;//Bluetooth ------------------------------


void Init44k22(void)
{
//OSC int 16MHz (62.5ns/inst.)
OSCCONbits.IRCF2 = 1;
OSCCONbits.IRCF1 = 1;
OSCCONbits.IRCF0 = 1;
while(!OSCCONbits.HFIOFS); //wait until ready

//Uart1
ANSELCbits.ANSC7 = 0; //Port C7 select som digital port
ANSELCbits.ANSC6 = 0; //Port C6 select som digital port

//Uart2
ANSELDbits.ANSD7 = 0; //Port D7 select som digital port
ANSELDbits.ANSD6 = 0; //Port D6 select som digital port

//Leds
ANSELAbits.ANSA3 = 0; //Port A3 select som digital port Red
ANSELEbits.ANSE1 = 0; //Port E1 select som digital port Green
ANSELEbits.ANSE2 = 0; //Port E2 select som digital port Blue

//InitTimer0();
InitTimer1();
//InitTimer2();
InitTimer3();

InitUart1();
InitUart2();

Init_IO();
}

void Init_IO(void)
{
//Tris vælger om det er input(1) eller output (0)
//Med Port kan man skrive 0 eller 1 hvis pin er valgt som output
//hvis port er valgt som input kan man læse om der er 0 eller 1 på pin

//Leds
TRIS_RED = 0; //output
TRIS_GREEN = 0;//output
TRIS_BLUE = 0;//output
PORT_RED = 1; //sæt høj
PORT_GREEN = 1;//sæt høj
PORT_BLUE = 1;//sæt høj

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
TRIS_TX2 = 0;//Output

TRIS_RTS = 0; //Output
TRIS_CTS = 1; //Input

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
T3CONbits.TMR3CS = 1;   //Clk = Fosc
T3CONbits.T3CKPS = 0b10;   //PreScaler
T3CONbits.T3RD16 = 0;   //16 bits = 0 = 8bits
T3CONbits.TMR3ON = 1;   //timer 3 on

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
SPBRG1 = SPBRG1_VAL;


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
SPBRG2 = SPBRG2_VAL;

IPR3bits.TX2IP = 0;// high prio
IPR3bits.RC2IP = 0;// high prio

PIR3bits.TX2IF = 0; // Clear interrupt flag
PIR3bits.RC2IF = 0; // Clear interrupt flag

PIE3bits.RC2IE = 1;     // Set RX interrupt enable
PIE3bits.TX2IE = 0;     // TX interrupt disable

RCSTA2bits.SPEN2 = 1;
}

void InitStatic() //Sw-restart, set vars to a known value
{

/*
 * Til Bluetooth
 */
//    extern union BTflags;
//
//u1 VI:1;    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
//u1 ER:1;    //error - ja/nej ? (visuel indikation ? rød diode blinker)
//u1 TX:1;    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
//u1 RE:1;    //ready - ready/not ready (visuel indikation ? rød diode konstant)
//u1 CO:1;    //connected - forbundet ? bluetooth ja/nej (visuel indikation - lysdiode grøn)
//u1 PW:2;    //power - power level  - niveau 0-3 ? 2bit? (ingen visuel indikation)
//u1 MG:1;    //message

BT.VI=0;
BT.ER=0;
BT.TX=0;
BT.RE=0;
BT.CO=0;
BT.PW=00;
BT.MG=0;

BT.Flag=0;

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
 *Til  bluetooth / pc debug
 */
uart_buf_char = 0; //
uart2_buf_char = 0;
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