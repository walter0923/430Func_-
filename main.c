#include <msp430.h>
#include "KEYSCAN.h"
#include "Rf.h"
#include "IO.h"
#include "HeadandFOOT.h"
#include "MEMORY.h"

void MainFunction(uint16_t func);

uint8_t a[2];
uint16_t ShakeDuty = 512 - 1;
uint16_t NowFunc;

void ClockInit(void){
	if(CALBC1_1MHZ == 0xFF){
		while(1);
	}

	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
}

void main(void){
//uint16_t i,j;

    WDTCTL = WDTPW + WDTHOLD;
    ClockInit();
    SightInit();
    TorchInit();
    ScanInit();
    IicInit();
#if IIC_MODE
#else
    GpioInit();
    ShakeInit();
    HeadFootInit();
#endif

    __bis_SR_register(GIE);

    ScanDelay10us(1000);

#if IIC_MODE
#else
    NowFunc = HEAD_DOWN;
    MainFunction(NowFunc);   //reset Head & Foot position
#endif

    RfInit();

#if RF_TEST
    P4DIR |= BIT1 | BIT2 | BIT3 | BIT4 | BIT5;	//for test
    P4OUT |= BIT1 | BIT2 | BIT3 | BIT4 | BIT5;

#endif

    while(1){
#if IIC_MODE
    	KeyProc();
    	//RfDataSend(0xAC);
#else
    	IiCFirstByteWrite(IIC_ADDW, 0x25);
    	IiCNextByteWrite(0x80);
    	IiCFinishByteWrite(0x80);
    	IiCFirstByteWrite(IIC_ADDW, 0x00);
    	IiCNextByteWrite(0x40);
    	IiCFinishByteWrite(0x0A);
		a[0] = 0x00;
		a[1] = 0x00;
		while(1){
			IiCRead(0x16, a, 2);
			if(a[1] & 0x40){
				break;
			}
		}
		a[0] = 0x00;
		a[1] = 0x00;
		IiCRead(0x28, a, 2);
		MainFunction(a[1]);

		P4OUT |= BIT1 | BIT2 | BIT3 | BIT4 | BIT5;
		P8OUT |= BIT1;
		P4OUT &= ~(a[1] << 1);

		if(a[1] == 0x01){
			P4DIR |= 0x02;
			P4OUT &= ~0x02;
		}
#endif

    }
}
#if IIC_MODE
#else
void MainFunction(uint16_t func){
	NowFunc = func;
	switch(NowFunc){
		case G_LIGHT:
			GLight();
			break;

		case SHAKE:
			Shake_On();
			break;

		case OFF:
			Shake_Off();
			break;

		case HEAD_UP:
			TargetPosition = 0xFF;
			HeadUpDown(UP);
			break;

		case HEAD_DOWN:
			TargetPosition = 0xFF;
			HeadUpDown(DOWN);
			break;

		case HFOFF:

			MotoSTOP();
			break;

		case TV:
			TargetPosition = TvHeadPosition;
			if(HeadNowPotition > TvHeadPosition){
				HeadUpDown(DOWN);
			}else if(HeadNowPotition < TvHeadPosition){
				HeadUpDown(UP);
			}

			/*  foot move here*/
			break;

		case ZG:
			TargetPosition = ZgHeadPosition;
			if(HeadNowPotition > ZgHeadPosition){
				HeadUpDown(DOWN);
			}else if(HeadNowPotition < ZgHeadPosition){
				HeadUpDown(UP);
			}
			/*  foot move here*/
			break;

		case FLAT:
			TargetPosition = 0;
			//if(HeadNowPotition > 0){
				HeadUpDown(DOWN);
			//}
			/*  foot move here*/
			break;

		case SET:
			/*
			SaveFlag = 1;
			MemoryWrite((char *)M_OneAdd, HeadNowPotition);*/
			break;

		case M_ONE:/*
			TargetPosition |= M_OneAdd;
			TargetPosition <<= 8;
			TargetPosition |= M_OneAdd + 1;*/
			break;
	}
}
#endif
