#define __SFR_OFFSET 0
#include <avr/io.h>

.global analogRead
.global delay

.section .text

analogRead:
	ORI R24, 0B01000000
	STS ADMUX, R24
	LDI R24, 0B11000111
	STS ADCSRA, R24
wait:
	LDS R24, ADCSRA
	SBRS R24, ADIF
	RJMP wait
	LDI R24, 0B00010000
	STS ADCSRA, R24
	LDS R24, ADCL
	LDS R25, ADCH
	RET

delay:
	DEC R24
	BRNE delay
	DEC R22
	BRNE delay
	DEC R20
	BRNE delay
	RET
