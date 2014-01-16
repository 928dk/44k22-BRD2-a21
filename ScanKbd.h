/* 
 * File:   ScanKbd.h
 * Author: bg25382
 *
 * Created on September 3, 2012, 11:47 AM
 */

#ifndef SCANKBD_H
#define	SCANKBD_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SCANKBD_H */

//kb1#######################################################
#include "global.h"
#include "unitmap.h"

void ScanKbd()
{u8 temp,fw,bw,*pbuf,rb0,rb1,rb2,rc0,rc1,rc2;
 JO.KBD=0; fw=bw=0xFF;//scan fwd then bw
 temp =TRISA;//push indic Pa2,3,4
 pCOL0=1;pCOL1=1;pCOL2=1;
 pCOL0=0;rb0=PORTB;rc0=PORTC;pCOL0=1;//Col 1-4-7-@
 pCOL1=0;rb1=PORTB;rc1=PORTC;pCOL1=1;//Col 2-5-8-0
 pCOL2=0;rb2=PORTB;rc2=PORTC;pCOL2=1;//Col 3-6-9-#
 TRISA=temp;//pop indic
 if(!(rb2&0x10))fw=11;if(!(rb2&0x20))fw=9;
 if(!(rc2&0x10))fw=6; if(!(rc2&0x20))fw=3;
 if(!(rb1&0x10))fw=0; if(!(rb1&0x20))fw=8;
 if(!(rc1&0x10))fw=5; if(!(rc1&0x20))fw=2;
 if(!(rb0&0x10))fw=10;if(!(rb0&0x20))fw=7;
 if(!(rc0&0x10))fw=4; if(!(rc0&0x20))fw=1;
 if(!(rc0&0x20))bw=1; if(!(rc0&0x10))bw=4;
 if(!(rb0&0x20))bw=7; if(!(rb0&0x10))bw=10;
 if(!(rc1&0x20))bw=2; if(!(rc1&0x10))bw=5;
 if(!(rb1&0x20))bw=8; if(!(rb1&0x10))bw=0;
 if(!(rc2&0x20))bw=3; if(!(rc2&0x10))bw=6;
 if(!(rb2&0x20))bw=9; if(!(rb2&0x10))bw=11;
 if(fw==bw)DigitLast =fw; else //dbltast
 { L3BufClr(1);}
//DigitCheck
 if(DigitLast!=DigitPrev)//dublet
 {if(0xFF==DigitLast)//break: check # and @
  {if(11==DigitPrev) EV.COD=1;
   if(10==DigitPrev) EV.BEL=1;
  }else//keep?, make FFxx needed for valid key
   {if( 0xFF==DigitPrev)
     EV.KEY=1;
   if((0xFF==DigitPrev)&&(DigitLast<=9))
   {if(8>DigitCnt)//Qenter
    {if(0==DigitCnt)L3BufClr(0);
     pbuf=(u8*)&L3Buf[(DigitCnt>>1)];
     DigitPrev = *pbuf;
     if(DigitCnt&1) //2nd
     {DigitPrev = (DigitPrev & 0xF0)| DigitLast;
     }else DigitPrev=(DigitLast<<4)|0x0F;
     *pbuf = DigitPrev;
     EvTimer=10;   DigitCnt++;
    }else//bufclr,cnERR?KeyQueFullErr:;
    {L3BufClr(1);// Indic(0x20+bG+bR);
  }}}//~make
  DigitPrev=DigitLast;//keep
}}//~dublet
//~kbd#################################
