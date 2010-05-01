#include <hal.h>

inline void InitAll(void)
{
	//InitUSART
//	UBRRL = UBRRL_GET_VALUE;
//	UBRRH = UBRRH_GET_VALUE;
//	UCSRA = 0x00;
//	UCSRB = (1<<RXEN) | (1<<TXEN) | (0<<RXCIE) | (0<<TXCIE);
//	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	PORTA = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;

	DDRA = 0xff;
	DDRB = 0xff;
	DDRD = 0xff;
}



