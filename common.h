/*
 * File:   common.h
 * Author: bg25382
 *
 * Created on October 26, 2012, 12:43 PM
 */

#ifndef COMMON_H
#define	COMMON_H


void InitTimer0(void);
void InitTimer1(void);
void InitTimer2(void);
void InitTimer3(void);
void InitUart1(void);
void InitUart2(void);
void Init_IO(void);
void Init_HW(void);

void ReStartTmr1(void);
void ReStartTmr2(void);
void ReStartTmr3(void);
void Init44k22(void);
void InitStatic(void);
void TimerTest(void);

void WriteSUart2(char *data,char size);

extern char UART2RxBuf[3];
extern char UART2TxBuf[30];

//Capacitivt input (analog)
#define TRIS_K0        TRISDbits.TRISD0
#define TRIS_K1        TRISDbits.TRISD1
#define TRIS_K2        TRISDbits.TRISD2

//Uart 1
#define TRIS_RX  TRISCbits.TRISC7
#define TRIS_TX  TRISCbits.TRISC6
#define PORT_RX  PORTCbits.RC7
#define PORT_TX  PORTCbits.RC6
//#define SPBRG1_VAL 8
//SPBRG1 = 8; //8: 115200 @ 64MHz,
//SPBRG1 = 51; //51: 19200 @ 64MHz

//Uart 2
#define TRIS_RX2 TRISDbits.TRISD7 //pin 5
#define TRIS_TX2 TRISDbits.TRISD6 //pin 4
#define PORT_RX2 PORTDbits.RD7
#define PORT_TX2 PORTDbits.RD6
//#define SPBRG2_VAL 51
//SPBRG2 = 8; //8: 115200 @ 64MHz,
//SPBRG2 = 51; //51: 19200 @ 64MHz

#define PORT_CTS PORTAbits.RA7  //markered med clk / forbundet med RTS på BT-modul
#define PORT_RTS PORTAbits.RA0 //markered med cmd  / forbundet med CTS på BT-modul

#define TRIS_CTS TRISAbits.TRISA7 //markered med clk  / forbundet med RTS på BT-modul
#define TRIS_RTS TRISAbits.TRISA0 //markered med cmd / forbundet med CTS på BT-modul

//Leds
#define	TRIS_YELLOW	TRISAbits.TRISA3
#define	TRIS_GREEN	TRISEbits.TRISE1
#define	TRIS_RED	TRISEbits.TRISE2

#define	PORT_YELLOW	PORTAbits.RA3
#define	PORT_GREEN	PORTEbits.RE1
#define	PORT_RED	PORTEbits.RE2

//wiegand
#define TRIS_O1  TRISCbits.TRISC0
#define TRIS_O2  TRISAbits.TRISA6
#define PORT_O1  PORTCbits.RC0
#define PORT_O2  PORTAbits.RA6

#define  ENABLEINT      (INTCONbits.GIEH = 1)       // enable high level priority interrupt
#define  DISABLEINT     (INTCONbits.GIEH = 0)       //disable  high level priority interrupt

#define ENABLEGINT (INTCONbits.GIE = 1) //tilføjet i a15 04-12-2012
#define DISABLEGINT (INTCONbits.GIE = 1) //tilføjet i a15 04-12-2012

#define ENABLEPINT (INTCONbits.PEIE = 1) //tilføjet i a15 04-12-2012
#define DISABLEPINT (INTCONbits.PEIE = 1) //tilføjet i a15 04-12-2012

#define cr "\r" //Carriage Return (enter) \r
#define CR "\r" //samme med store bogstaver

#define cr_lf "\r\n" //Carriage Return (enter) + Line Feed \r\n

//#define pc_tx_buffer UART2TxBuf /*her kan man definere hilken buffer man vil bruge som midlertidig lager til pc beskeder*/

#define bt_tx_buffer UART2TxBuf /*her kan man definere hvilken buffer man vil bruge som midlertidig lager til bt transmit beskeder*/

#define bt_rx_buffer UART2RxBuf[60]; /*her kan man definere hvilken buffer man vil bruge som midlertidig lager til bt recieve beskeder*/

UART2_WriteString(char* data);

char UART2TxBuf[30];

#define SendToBt UART2_WriteString(&bt_tx_buffer)
//#define SendToPc UART2_Write((char*) UART2TxBuf,1 )

#define bt_txchar_function UART_Write

#define pc_txchar_function UART2_Write  /*her kan man definere hvilken funktion man vil bruge til
                                          at skrive en char til pc'en seriel port*/

//#define SendToPc meh(pc_tx_buffer) //funktion til at skrive strenge til pc

//void meh(char *data){}

#define DisableUARTTxInt() PIE1bits.TXIE = 0
#define EnableUARTTxInt() PIE1bits.TXIE = 1

#define DisableUARTRxInt() PIE1bits.RCIE = 0
#define EnableUARTRxInt() PIE1bits.RCIE = 1

#define SetUARTRxIntHighPrior() \
				RCONbits.IPEN = 1;\
				IPR1bits.RCIP = 1

#define SetUARTRxIntLowPrior() IPR1bits.RCIP = 0

#define SetUARTTxIntHighPrior()\
				RCONbits.IPEN = 1;\
				IPR1bits.TXIP = 1

#define SetUARTTxIntLowPrior()	IPR1bits.TXIP = 0


#define SetUART_BRGHHigh() TXSTAbits.BRGH = 1
#define SetUART_BRGHLow() TXSTAbits.BRGH = 0

#define SetUART_SPBRG(iBRGValue)\
				RCSTAbits.SPEN = 0;\
				SPBRG = iBRGValue;\
				RCSTAbits.SPEN = 1

#define SetUARTBaud(iBaudRate)\
		do{\
			#define SPBRG_V11  (UART_CLOCK_FREQ / UARTINTC_BAUDRATE)\
			#define SPBRG_V21  SPBRG_V11/16\
			#define SPBRG_VAL  (SPBRG_V21 - 1)\
			#if (SPBRG_VAL > 255)\
			  #error Calculated SPBRG value is out of range\
			#elif (SPBRG_VAL < 10)\
			  #error Calculated SPBRG value is out of range\
			#endif\
			RCSTAbits.SPEN = 0;\
			SPBRG = iBaudRate;\
			RCSTAbits.SPEN = 1;\
		}while(false)



/*
char                8-bit  (signed by default)
signed char         8-bit (signed)
unsigned char       8-bit (unsigned)
int                 16 bit (signed)
unsigned int        16-bit (unsigned)
short               Same as int
unsigned short      Same as unsigned int
short long          24-bit (signed)
unsigned short long 24-bit (unsigned)
long                32-bit (signed)
unsigned long       32-bit (unsigned)

 * Signed kan holde  + og - (eks -128 til 128)
 * Unsigned kan kun holde positive værdier (eks 0 til 255)
 */

typedef unsigned		u1;
//typedef unsigned short char     u4;     //nibble, semioctet
typedef unsigned char		u8;     //byte,octet,char 0 - 256
typedef unsigned short		u16;    //unsigned int,halfword,word,short 0 - 65535
typedef unsigned short long	u24;    //0 - 16777215 == 16 Mega
typedef unsigned long		u32;    //word,long 0 - 4294967296
typedef unsigned long long      u64;    //long long, quad, quadword, int6 0 - 18446744073709551616
//typedef unsigned double double  u128;   //octaword, double quadword (nonstandart)

//typedef signed                  s1;
//typedef signed short char       s4;     //nibble, semioctet
typedef signed char		s8;     //byte,octet
typedef signed short		s16;    //signed int,halfword,word,short
typedef signed short long	s24;
typedef signed long		s32;    //word,long
typedef signed long long        s64;    //long long, quad, quadword, int6
//typedef signed double double    s128;   //octaword, double quadword (nonstandart)

near union{struct
 {
u1 A:1;    //
u1 B:1;    // Blink / hello world / i'm alive
u1 C:1;    //
u1 D:1;    // Debug beskeder fra BT
u1 E:1;    //
u1 F:1;    //
u1 G:1;    //
u1 H:1;    //
u1 I:1;    //
u1 J:1;    //
u1 K:1;    //
u1 L:1;    //
u1 M:1;    // vis hovedmenu
u1 N:1;    //
u1 O:1;    //ok/at besked
u1 P:1;    // print flag
u1 Q:1;    //
u1 R:1;    //set power
u1 S:1;    //show config
u1 T:1;    // Trigger / timer 1 beskeder
u1 U:1;    //
u1 V:1;
//u1 W:1;//
u1 X:1;    //
u1 Y:1;
//u1 Z:1;//

};u24 Flag;
}MENU;//Bluetooth ------------------------------

extern near union MENU MENUFLAG; //exporterer unionen

near union{struct 
{
unsigned VI:1;    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
unsigned ER:1;    //error - ja/nej ? (visuel indikation ? rød diode blinker)
unsigned TX:1;    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
unsigned RE:1;    //ready - ready/not ready (visuel indikation ? rød diode konstant)
unsigned CO:1;    //connected - forbundet ? bluetooth ja/nej (visuel indikation - lysdiode grøn)
unsigned PW:2;    //power - power level  - niveau 0-3 ? 2bit? (ingen visuel indikation)
unsigned MG:1;    //message
 };u8 Flag;
}BT;

extern near union BT BTFLAG; //exporterer unionen
 
//near union {struct
// {
//u1 VI:1;    //vicinity - enheder i nærheden ? ja/nej - (ingen visuel indikation)
//u1 ER:1;    //error - ja/nej ? (visuel indikation ? rød diode blinker)
//u1 TX:1;    //transmit  - igang/afsluttet (visuel indikation - lysdiode blå)
//u1 RE:1;    //ready - ready/not ready (visuel indikation ? rød diode konstant)
//u1 CO:1;    //connected - forbundet ? bluetooth ja/nej (visuel indikation - lysdiode grøn)
//u1 PW:2;    //power - power level  - niveau 0-3 ? 2bit? (ingen visuel indikation)
//u1 MG:1;    //message
// };u8 Flag;
//}BT;//Bluetooth ------------------------------






/*
 * AND bits for at clear (nul/0/lav) e.k.s. trisb & 0b01111 1111 for at clear msb til output
 * OR bits for at sætte (et/1/høj) e.k.s. trisb | 0b11111 1111 for at sætte msb til input (alle i dette tilfælde)
 * XOR bits for at invertere bits for at toggle trisb ^ 0b1000000 ofr at toggle msb (invertere)
*/

/*
 * "static" variabler bliver brugt i funktioner (globalt aktive)
 * Functions and global variables that are private to a module are not put in the include file and are declared static.
 * "extern" variabler beskriver at variablen bliver oprettet/init i en anden header/source code
 * "volatile" variabler er vigtige i interrupt baserede funktioner og IO routiner, fortæller compiler at variablen kan ændre sig under runtime
 * "const" kan ikke ændres når det/de først er sat
 *
 *
 *
 */

//hvis det er en int (større end 8 bit) så skal det være unsigned int/long af typen

// Bit makroer (manipulation)
#define BIT(x)   (1 << (x))
#define SETBIT(p,b) (p) |= BIT(b)
#define CLRBIT(p,b) (p) &= ~BIT(b)
#define TOGBIT(p,b) (p) ^= BIT(b)
#define TSTBIT(p,b) (p) & BIT(b)

//char i = 0x80; // In binary, i is: 10000000
//i = i >> 1; // Shift right by 1 bit: 01000000
//i = i >> 5; // Shift right by 5 bits: 00000010
//i = i >> 3; // Shift right by 3 bits: 00000000
#define SHIFT_RIGHT i = i >> 1 //dividerer med 2 x antal gange

#define HALFOF(x) x/2
#define SQUARED(x) x*x

#define BIT_AND &
#define BIT_XOR ^
#define BIT_OR |

#define ADDRESS_OF &
#define POINTER_DEREFERENCE *

//
//#define SET = //SET bliver brugt i generictypedefs.h
#define AND &&
#define OR  ||
#define NOT !
#define SET_TO =
#define EQUALS ==
#define EQUAL_TO ==
#define NOT_EQUAL !=
#define LESS_THAN <
#define GREATER_THAN >

#define LOW 0
#define HIGH 1
//#define TRUE 1 // bliver brugt i generictypedefs.h
//#define FALSE 0 // bliver brugt i generictypedefs.h

#define INCREMENT ++
#define DECREMENT --
#define FOREVER while(1)

//#define max(x,y) ((x) > (y) ? (x) : (y)) //findes også i stdlib
//#define min(x,y) ((x) < (y) ? (x) : (y)) //findes også i stdlib
#define abs(x) ((x) >= 0 ? (x) : -(x)) //absolute værdi

#define sgn(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0)) //signum function

#define TRACE { printf(?Executing %s line %d\n?, __FILE__, __LINE__); }

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)

//<
//>
//<=
//>=
//== (equality, note double-equals)
//!= (non-equality)

//[]        //Array dereference
//()        //Function call
//.         //Structure member dereference
//->        //Structure pointer dereference
//++        //Postincrement
//--        //Postdecrement
//
//++prefix  //Preincrement      //Right-to-left
//--prefix  //Predecrement
//sizeof()  //Size in bytes of given type or variable
//&         //Address-of
//*         //Pointer dereference
//+         //Unary positive
//-         //Unary negative
//~         //One?s complement
//!         //Logical complement
//
//(type)        //Cast operator Right-to-left
//*, /, %       //Multiply, divide, modulo Left-to-right
//+, -          //Addition, subtraction Left-to-right
//<<, >>        //Bit shifts Left-to-right
//<, >, <=, >=  //Comparison operators Left-to-right
//==, !=        //Comparison operators Left-to-right
//&             //Bitwise AND Left-to-right
//^             //Bitwise XOR Left-to-right
//|             //Bitwise OR Left-to-right
//&&            //Logical AND Left-to-right
//||            //Logical OR Left-to-right
//?:                        //Conditional operator (if-then-else) Right-to-left
//=, *=, /=, %=, +=, -=,    //Assignment operators Right-to-left
//<<=, >>=, &=, ^=, |=      //Assignment operators Right-to-left
//,                         //Comma operator Left-to-right

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

