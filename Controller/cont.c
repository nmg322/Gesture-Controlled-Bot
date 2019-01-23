#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

#define LEFT 0x98
#define RIGHT 0xBA
#define BACK 0xDC
#define FRONT 0xFE
#define STOP 0x00
#define SYN 0xAA

extern uint16_t analogRead(uint8_t);
extern void delay(uint8_t, uint8_t, uint8_t);

void init(void) {
	USART0_Init();
}

void SendPacket(uint8_t power, uint8_t mov) {
	SerialWrite(SYN);
	SerialWrite(power);
	SerialWrite(mov);
}

int main(void) {
	SREG = 0;
	SPL = (uint8_t)(RAMEND);
	SPH = (uint8_t)(RAMEND>>8);
	init();

	while(1) {
		uint16_t x = analogRead(0);
		uint16_t y = analogRead(1);
		uint8_t p = analogRead(2)/4;

		if(x>400) {
			SendPacket(p, LEFT);
		}
		else if(x<340) {
			SendPacket(p, RIGHT);
		}
		else if(y>400) {
			SendPacket(p, BACK);
		}
		else if(y<340) {
			SendPacket(p, FRONT);
		}
		else {
			SendPacket(0x00, STOP);
		}
	}
	return 0;
}
