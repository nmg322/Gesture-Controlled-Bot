#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif

void USART0_Init(void) {
	uint16_t UBRRVAL = ((F_CPU)/(16UL*BAUD) - 1);
	UBRR0H = (uint8_t)(UBRRVAL>>8);
	UBRR0L = (uint8_t)UBRRVAL;
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B=(1<<RXEN0)|(1<<TXEN0);
}

void SerialWrite(uint8_t u8Data) {
    while(!(UCSR0A&(1<<UDRE0)));
    UDR0 = u8Data; 
}

uint8_t SerialRead(void) {
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}
