/*
 * HEADandFOOT.h
 *
 *  Created on: 2019/8/10
 *      Author: Unier
 */

#ifndef HEADANDFOOT_H_
#define HEADANDFOOT_H_

#define FULLSTEP 1429

#define UP 0
#define DOWN 1
#define HeadUpPin	BIT5
#define HeadDownPin	BIT4

#define HeadGrup (HeadUpPin | HeadDownPin)
#define HeadStepCntPin BIT0

#define TvHeadPosition	1001
#define TvFootPosition	429

#define ZgHeadPosition	429
#define ZgFootPosition	715


extern uint32_t HeadStepCnt;
extern uint16_t HeadStepTC10us;
extern uint16_t HeadStepTC1ms;
extern uint16_t LastMotion;
extern uint16_t HeadNowPotition;
extern uint16_t FootNowPotition;
extern uint16_t TargetPosition;
void HeadSetpCntInit(void);
void HeadFootInit(void);
void HeadInit(void);
void HeadUpDown(uint8_t ud);

void NoMoveDetc(void);
void MotoProtectDelay(void);
void MotoSTOP(void);

#endif /* HEADANDFOOT_H_ */
