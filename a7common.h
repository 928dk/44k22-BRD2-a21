/* 
 * File:   common.h
 * Author: bg25382
 *
 * Created on October 26, 2012, 12:43 PM
 */

#ifndef COMMON_H
#define	COMMON_H

#pragma config FOSC = INTIO67   // Internal Oscilator block
#pragma config PLLCFG = ON      // PLLCFG Oscillator multiplied by 4
#pragma config PRICLKEN = ON    // Primary clock enabled
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Oscillator Switchover mode disabled
#pragma config WDTEN = OFF      // Watchdog Timer enabled = off
#pragma config BOREN = OFF      // Brown-out Reset disabled in hardware and software
#pragma config LVP = OFF        // Single supply ICSP Enabled = OFF
#pragma config DEBUG = ON       //
#pragma config PBADEN= OFF      // Port B AD converter off,
#pragma config PWRTEN = OFF      // Power Up Timer enabled (side 34)

// configword 0x300008
#pragma config CP0 = OFF //CP0: Code Protection bit 1 = Block 0 not code-protected 0 = Block 0 code-protected
#pragma config CP1 = OFF //CP1: Code Protection bit 1 = Block 1 not code-protected 0 = Block 1 code-protected

// configword 0x300009
#pragma config CPB = OFF //CPB: Boot Block Code Protection bit
#pragma config CPD = OFF //CPD: Data EEPROM Code Protection bit

// configword 0x30000a
#pragma config WRT0 = OFF //WRT0: Write Protection bit
#pragma config WRT1 = OFF //WRT1: Write Protection bit

// configword 0x30000b
#pragma config WRTB = OFF //WRTB:Boot Block Write Protection bit
#pragma config WRTC = OFF //WRTC: Configuration Register Write Protection bit
#pragma config WRTD = OFF //WRTD: Data EEPROM Write Protection bit

// configword 0x30000c
#pragma config EBTR0 = OFF //EBTR0: Table Read Protection bit
#pragma config EBTR1 = OFF //EBTR1: Table Read Protection bit

// configword 0x30000d
#pragma config EBTRB = OFF //Boot Block Table Read Protection bit

void InitTimer0(void);
void InitTimer1(void);
void InitTimer2(void);
void InitTimer3(void);
void InitUart1(void);
void InitUart2(void);
void Init_IO(void);

void ReStartTmr1(void);
void ReStartTmr2(void);
void ReStartTmr3(void);
void Init44k22(void);
void InitStatic(void);
void TimerTest(void);


//Capacitivt input (analog)
#define TRIS_K0        TRISAbits.TRISA0
#define TRIS_K1        TRISBbits.TRISB4
#define TRIS_K2        TRISDbits.TRISD1

//Uart 1
#define TRIS_RX  TRISCbits.TRISC7
#define TRIS_TX  TRISCbits.TRISC6
#define PORT_RX  PORTCbits.RC7
#define PORT_TX  PORTCbits.RC6
#define SPBRG1_VAL 8
//SPBRG1 = 8; //8: 115200 @ 64MHz,
//SPBRG1 = 51; //51: 19200 @ 64MHz

//Uart 2
#define TRIS_RX2 TRISDbits.TRISD7
#define TRIS_TX2 TRISDbits.TRISD6
#define PORT_RX2 PORTDbits.RD7
#define PORT_TX2 PORTDbits.RD6
#define SPBRG2_VAL 8
//SPBRG2 = 8; //8: 115200 @ 64MHz,
//SPBRG2 = 51; //51: 19200 @ 64MHz

#define PORT_CTS PORTCbits.RC3  //markered med clk / forbundet med RTS på BT-modul
#define PORT_RTS PORTCbits.RC4 //markered med cmd  / forbundet med CTS på BT-modul

#define TRIS_CTS TRISCbits.TRISC3 //markered med clk  / forbundet med RTS på BT-modul
#define TRIS_RTS TRISCbits.TRISC4 //markered med cmd / forbundet med CTS på BT-modul

//Leds
#define	TRIS_RED	TRISAbits.TRISA3
#define	TRIS_GREEN	TRISEbits.TRISE1
#define	TRIS_BLUE	TRISEbits.TRISE2

#define	PORT_RED	PORTAbits.RA3
#define	PORT_GREEN	PORTEbits.RE1
#define	PORT_BLUE	PORTEbits.RE2

int debugmsg = 1;

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

volatile char uart_buf_char; //en byte / char volatile fordi den kan ændre sig i løbet af afviklingen
char uart_buf[128];

volatile char uart2_buf_char; //en byte
char uart2_buf[128];

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* COMMON_H */

