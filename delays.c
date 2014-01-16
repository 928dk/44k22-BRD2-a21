/* 
 * File:   delays.c
 * Author: bg25382
 *
 * Created on October 23, 2012, 10:02 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */

void Delayx(int y){
    int x=0;
        for (x=0; x<y; x=x+1) {
            asm("nop ");
     }
}

void Delay10x(int y){
    int x=0;
        for (x=0; x<y; x=x+1) {
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
            asm("nop ");
    }
}
