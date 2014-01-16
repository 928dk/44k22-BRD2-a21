/* 
 * File:   RfTrig.h
 * Author: bg25382
 *
 * Created on September 3, 2012, 11:40 AM
 */

#ifndef RFTRIG_H
#define	RFTRIG_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RFTRIG_H */

//L1Rfid#################################
void RfTrig(){
 {pCFE1=1; RfState=0; RfEdgCnt=0;
  if(RD.EM){T0CON=0xC2;pPrLP=1;}//em4102
  else     {T0CON=0xC1;pPrLP=0;}//at5530
  INTCON=0xA4;//GIE+TMR0IE+TMR0IF
}}

