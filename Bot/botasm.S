#define __SFR_OFFSET 0
#include <avr/io.h>

.global pwmSetup
.global analogWrite
.global delay

.section .text

pwmSetup:
	LDI R24, 0B10100001
	OUT TCCR0A, R24
	STS TCCR2A, R24
	LDI R24, 0b00000001
	OUT TCCR0B, R24
	STS TCCR2B, R24
	RET

analogWrite:
	CPI R24, 3
	BREQ l3
	CPI R24, 5
	BREQ l5
	CPI R24, 6
	BREQ l6
	CPI R24, 11
	BREQ l11
	RET
l3:
	STS OCR2B, R22
	RET
l5:
	OUT OCR0B, R22
	RET
l6:
	OUT OCR0A, R22
	RET
l11:
	STS OCR2A, R22
	RET

delay:
	DEC R24
	BRNE delay
	DEC R22
	BRNE delay
	DEC R20
	BRNE delay
	RET
