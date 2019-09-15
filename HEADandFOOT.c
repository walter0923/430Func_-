/*
 * HEADandFOOT.c
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

uint32_t HeadStepCnt;
uint16_t HeadStepTC10us;
uint16_t HeadStepTC1ms;
uint16_t LastMotion;
uint16_t HeadNowPotition;
uint16_t FootNowPotition;
uint16_t TargetPosition;

void HeadFootInit(void){
	HeadSetpCntInit();
	HeadInit();
}

void HeadInit(void){
	P3DIR |= HeadGrup;
	MotoSTOP();				//make sure motor not move

	//P3OUT &= ~HeadDownPin;		//move head motor to lowest dead point
	//HeadNotMoveDetc();			// wait move to dead point
}

void HeadSetpCntInit(void){
	P2DIR &= ~HeadStepCntPin;
	P2REN |= HeadStepCntPin;                            // Enable P1.4 internal resistance
	P2OUT |= HeadStepCntPin;                            // Set P1.4 as pull-Up resistance
	P2IE  |= HeadStepCntPin;                             // P1.4 interrupt enabled
	P2IES &= ~HeadStepCntPin;                            // P1.4 Hi/Lo edge
	P2IFG &= ~HeadStepCntPin;                           // P1.4 IFG cleared
}


void NoMoveDetc(void){
	if(HeadStepTC1ms > 200){
		MotoSTOP();			//stop move
		/*switch(NowFunc){
			case HEAD_UP:
				HeadNowPotition = FULLSTEP;
				break;

			case FOOT_UP:
				FootNowPotition = FULLSTEP;
				break;

			case HEAD_DOWN:
				HeadNowPotition = 0;
				break;

			case FOOT_DOWN:
				FootNowPotition = 0;
				break;
		}
		NowFunc = 0x00;*/
	}
	/*
	if((HeadStepTC1ms % 100) == 0){
		HeadStepCnt = 0;
		MotoSTOP();			//stop move
		switch(NowFunc){
			case HEAD_UP:
				HeadNowPotition = FULLSTEP;
				break;

			case FOOT_UP:
				FootNowPotition = FULLSTEP;
				break;

			case HEAD_DOWN:
				HeadNowPotition = 0;
				break;

			case FOOT_DOWN:
				FootNowPotition = 0;
				break;
		}
		NowFunc = 0x00;
	}*/
}

void HeadUpDown(uint8_t ud){
	MotoSTOP();
	HeadStepCnt = 0;			//reset step cnt
	HeadStepTC1ms = 0;
	if(ud != LastMotion){
		MotoProtectDelay();
		HeadStepCnt = 0;
	}

	if(ud){
		P3OUT &= ~HeadUpPin;

	}else{
		P3OUT &= ~HeadDownPin;
	}

	LastMotion = ud;
}

void MotoProtectDelay(void){
	HeadStepTC1ms = 0;
	while(HeadStepTC1ms < 10){;}
	HeadStepTC10us = 0;
	HeadStepTC1ms = 0;
}

void MotoSTOP(void){
	P3OUT |= HeadGrup;			//make sure motor not move
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
	if(P2IFG & HeadStepCntPin){
		HeadStepTC1ms = 0;
		if(LastMotion == UP){
			HeadNowPotition ++;
		}else if(LastMotion == DOWN){
			if(HeadNowPotition > 0){
				HeadNowPotition --;
			}
		}

		if(HeadNowPotition == TargetPosition){
			MotoSTOP();
		}
		/*switch(NowFunc){
			case HEAD_UP:
				//HeadStepCnt++;
				HeadNowPotition ++;
				break;

			case HEAD_DOWN:
				//HeadStepCnt--;
				if(HeadNowPotition > 0){
					HeadNowPotition --;
				}
				break;

			case FOOT_UP:
				break;

			case FOOT_DOWN:
				break;

			case HFOFF:
				if(LastMotion == HEAD_UP){
					HeadNowPotition ++;
				}else if(LastMotion == HEAD_DOWN){
					if(HeadNowPotition > 0){
						HeadNowPotition --;
					}
				}
				break;

			case TV:
				if(HeadNowPotition > TvHeadPosition){
					//HeadStepCnt--;
					if(HeadNowPotition > 0){
						HeadNowPotition --;
					}
				}else if(HeadNowPotition < TvHeadPosition){
					//HeadStepCnt++;
					HeadNowPotition ++;
				}

				if(HeadNowPotition == TvHeadPosition){
					MotoSTOP();
				}
				break;

			case ZG:
				if(HeadNowPotition > ZgHeadPosition){
					//HeadStepCnt--;
					if(HeadNowPotition > 0){
						HeadNowPotition --;
					}
				}else if(HeadNowPotition < ZgHeadPosition){
					//HeadStepCnt++;
					HeadNowPotition ++;
				}

				if(HeadNowPotition == ZgHeadPosition){
					MotoSTOP();
				}
				break;

			case FLAT:
				if(HeadNowPotition > 0){
					//HeadStepCnt--;
					HeadNowPotition --;
				}

				if(HeadNowPotition == 0){
					//MotoSTOP();
				}
				break;
		}*/

		//HeadNowPotition += HeadStepCnt;
		P2IFG &= ~HeadStepCntPin;                           // P1.4 IFG cleared
	}/*else if(){
		switch(NowFunc){
		case HEAD_UP:
			HeadStepCnt++;
			break;

		case HEAD_DOWN;
			HeadStepCnt--;
			break;
		}
		P2IFG &= ~HeadStepCntPin;                           // P1.4 IFG cleared
	}*/
	HeadStepTC1ms = 0;

}
