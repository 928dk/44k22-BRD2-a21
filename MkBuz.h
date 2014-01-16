/* 
 * File:   MkBuz.h
 * Author: bg25382
 *
 * Created on September 3, 2012, 11:50 AM
 */

#ifndef MKBUZ_H
#define	MKBUZ_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* MKBUZ_H */


void MkBuz()
{if(RF.BuzIN)
 {if(!RF.BuzEX){TRISBbits.TRISB3=0;}//ON intern
  else{TRISBbits.TRISB3=1;}         //Pause
 } //ON intern
 else //4kHz PS2=4 PR2=7C
 {if(RF.BuzEX){TRISBbits.TRISB3=0;} //ON extern
  else{TRISBbits.TRISB3=1;}//4kHz; PS2=1 PR2=7C OFF
}}
