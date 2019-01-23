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

#define Lp 3
#define Ln 5
#define Rp 6
#define Rn 11

extern void pwmSetup(void);
extern void analogWrite(uint8_t, uint8_t);
extern void delay(uint8_t, uint8_t, uint8_t);

void init(void) {
	DDRD |= (1<<3)|(1<<5)|(1<<6);
	DDRB |= (1<<3);
	PORTD = 0;
	PORTB = 0;
	USART0_Init();
	pwmSetup();
}

int main(void) {
	SREG = 0;
	SPL = (uint8_t)(RAMEND);
	SPH = (uint8_t)(RAMEND>>8);
	init();

	while(1) {
		uint8_t data = SerialRead();
		if(data==SYN) {
			uint8_t p = SerialRead();
			uint8_t mov = SerialRead();
			if(mov==FRONT) {
				analogWrite(Lp, p);
				analogWrite(Ln, 0);
				analogWrite(Rp, p);
				analogWrite(Rn, 0);
			}
			else if(mov==BACK) {
				analogWrite(Lp, 0);
				analogWrite(Ln, p);
				analogWrite(Rp, 0);
				analogWrite(Rn, p);
			}
			else if(mov==RIGHT) {
				analogWrite(Lp, p);
				analogWrite(Ln, 0);
				analogWrite(Rp, 0);
				analogWrite(Rn, p);
			}
			else if(mov==LEFT) {
				analogWrite(Lp, 0);
				analogWrite(Ln, p);
				analogWrite(Rp, p);
				analogWrite(Rn, 0);
			}
			else if(mov==STOP) {
				analogWrite(Lp, 0);
				analogWrite(Ln, 0);
				analogWrite(Rp, 0);
				analogWrite(Rn, 0);
			}
		}
		else {
			analogWrite(Lp, 0);
			analogWrite(Ln, 0);
			analogWrite(Rp, 0);
			analogWrite(Rn, 0);
		}
	}
	return 0;
}
