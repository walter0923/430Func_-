/*
 * MEMORY.c
 *
 *  Created on: 2019/8/10
 *      Author: Unier
 */
#include <msp430.h>
#include "KEYSCAN.h"
#include "Rf.h"
#include "IO.h"
#include "HeadandFOOT.h"
#include "MEMORY.h"

uint16_t SaveFlag = 0;
uint8_t hb,lb;
void MemoryWrite(char* add, uint16_t pbuff){
	hb = pbuff >> 8;
	lb = pbuff;
	char * Flash_ptr;                         // Initialize Flash pointer
	Flash_ptr = add;

	__disable_interrupt();                    // 5xx Workaround: Disable global

	FCTL3 = FWKEY;                            // Clear Lock bit
	FCTL1 = FWKEY+ERASE;                      // Set Erase bit
	*(unsigned int *)Flash_ptr = 0;           // Dummy write to erase Flash seg
	FCTL1 = FWKEY+WRT;                        // Set WRT bit for write operation

	*Flash_ptr = hb;
	*Flash_ptr ++;
	*Flash_ptr = lb;
	//for(i = 0; i < 6; i += 2){
		//char
	//}

	FCTL1 = FWKEY;                            // Clear WRT bit
	FCTL3 = FWKEY+LOCK;                       // Set LOCK bit

	ScanDelay10us(10);
	__bis_SR_register(GIE);
}

