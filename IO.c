/*
 * IO.c
 *
 *  Created on: 2019/8/9
 *      Author: Unier
 */
#include <msp430.h>
#include "KEYSCAN.h"
#include "Rf.h"
#include "IO.h"
#include "HeadandFOOT.h"
#include "MEMORY.h"

uint16_t DutyStep = 1;
uint16_t MOnePosition = 0;
void SightInit(void){
	P2SEL &= ~BIT6;
	P2DIR |= BIT6;
	P2OUT |= BIT6;
}

void SightOnOff(void){
	P2OUT &= ~BIT6;
	ScanDelay10us(1000);
	P2OUT |= BIT6;
}

void TorchInit(void){
	P1DIR |= BIT5;
	P1OUT &= ~BIT5;
}

void TorchOnOff(void){
	P1OUT ^= BIT5;
}
/*
void GpioInit(void){
	P8DIR |= BIT3;
	P8OUT |= BIT3;
}

void GLight(void){
	P8OUT ^= BIT3;
}

void ShakeInit(void){
	P8DIR |= BIT4;                            // P2.2 and P2.3 output
	P8SEL |= BIT4;                            // P2.2 and P2.3 options select
	//P8OUT |= BIT4;
	TA0CCR0 = 512-1;                          // PWM Period
	TA0CCTL4 = OUTMOD_7;                      // CCR1 reset/set
	TA0CCR4 = 512 - 1;                            // CCR1 PWM duty cycle
	TA0CTL = TASSEL_2 + MC_1 + TACLR;         // SMCLK, up mode, clear TAR
}

void Shake_Off(void){
	DutyStep = 1;
	ShakeDuty = 512 - 1;
	Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, ShakeDuty);
}

void Shake_On(void){
	switch(DutyStep){
		case 1:
			ShakeDuty = 180;
			DutyStep = 2;
			break;

		case 2:
			ShakeDuty = 80;
			DutyStep = 3;
			break;

		case 3:
			ShakeDuty = 15;
			DutyStep = 1;
			break;
	}
	Timer_A_setCompareValue(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_4, ShakeDuty);
}*/
