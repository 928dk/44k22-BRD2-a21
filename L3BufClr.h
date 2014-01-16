/* 
 * File:   L3BufClr.h
 * Author: bg25382
 *
 * Created on September 3, 2012, 11:47 AM
 */

#ifndef L3BUFCLR_H
#define	L3BUFCLR_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* L3BUFCLR_H */

void L3BufClr(u8 ind)
{if(ind)Indic(iCLR);
 DigitCnt=0;// EvTimer=0;
 L3Buf[0]=0xFF;L3Buf[1]=0xFF;L3Buf[2]=0xFF;
 L3Buf[3]=0xFF;L3Buf[4]=0xFF;
 BinKey=0;
}
