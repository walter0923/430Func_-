/*
 * MEMORY.h
 *
 *  Created on: 2019/8/10
 *      Author: Unier
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include "KEYSCAN.h"

#define M_OneAdd	0x1880
#define M_TwoAdd	(0x1880 + 2)
#define M_Threeadd	(0x1880 + 4)
#define uint16_t	unsigned int
#define uint8_t		unsigned char
extern uint16_t SaveFlag;

void MemoryWrite(char* add, uint16_t pbuff);

#endif /* MEMORY_H_ */
