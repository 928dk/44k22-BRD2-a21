/* 
 * File:   RfBufRlf.h
 * Author: bg25382
 *
 * Created on September 3, 2012, 5:41 PM
 */

#ifndef RFBUFRLF_H
#define	RFBUFRLF_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* RFBUFRLF_H */

void RfBufRlf(void)//(CY)
{
  Rlcf(RfBuf+0,0,0)//Cy
  Rlcf(RfBuf+7,1,0);
  Rlcf(RfBuf+6,1,0);
  Rlcf(RfBuf+5,1,0);
  Rlcf(RfBuf+4,1,0)
  Rlcf(RfBuf+3,1,0)
  Rlcf(RfBuf+2,1,0)
  Rlcf(RfBuf+1,1,0)
  Rlcf(RfBuf+0,1,0)
}