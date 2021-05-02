/*
 * MiniProject1.c
 *
 *  Created on: May 2, 2021
 *      Author: Youssef Fahmy
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char hours1 = 0, hours10 = 0, minutes1 = 0, minutes10 = 0, seconds1 = 0, seconds10 = 0, flag =0;

void INT0_Init(void)
{
	DDRD  &= ~(1<<DDD2);                   // INT0/PD2 input pin
	PORTD |= (1<<PD2);                     // Enable Pull-up resistor
	MCUCR |= (1<<ISC01);
	MCUCR &= ~(1<<ISC00);
	GICR  |= (1<<INT0);
	SREG  |= (1<<7);
}

ISR(INT0_vect)
{
	seconds1 = 0;
	seconds10 = 0;
	minutes1 = 0;
	minutes10 = 0;
	hours1 = 0;
	hours10 = 0;
}

void INT1_Init(void)
{
	DDRD  &= ~(1<<DDD3);                   // INT1/PD3 input pin
	MCUCR |= (1<<ISC11) | (1<<ISC10);      // Trigger interrupt on rising edge
	GICR  |= (1<<INT1);
	SREG  |= (1<<7);
}

ISR(INT1_vect)
{
	TCCR1B &= ~(1<<CS11) & ~(1<<CS10); // NO clock source for timer1

}

void INT2_Init(void)
{
	DDRB   &= ~(1<<DDB2);                   // INT2/PB2 input pin
	PORTB  |= (1<<PB2);                     // Enable Pull-up resistor
	MCUCSR &= ~(1<<ISC2);
	GICR   |= (1<<INT2);
	SREG   |= (1<<7);
}

ISR(INT2_vect)
{
	TCCR1B |= (1<<CS11) | (1<<CS10);
}

void Timer1_Init(void)
{
	TCCR1A = (1<<FOC1A);
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10); // CTC mode with 64 pre-scalar
	TCNT1  = 0;
	OCR1A  = 15625;
	TIMSK  = (1<<OCIE1A);
	SREG  |= (1<<7);
}

ISR(TIMER1_COMPA_vect)
{
	flag = 1;
}

int main(void)
{
	DDRC = 0x0F;
	DDRA = 0x3F;

	INT0_Init();
	INT1_Init();
	INT2_Init();
	Timer1_Init();

	while(1)
	{
		//seconds1
		PORTA = (1<<PA0);
		PORTC = (PORTC & 0xF0) | (seconds1 & 0x0F);
		_delay_ms(5);

		//seconds10
		PORTA = (1<<PA1);
		PORTC = (PORTC & 0xF0) | (seconds10 & 0x0F);
		_delay_ms(5);

		//minutes1
		PORTA = (1<<PA2);
		PORTC = (PORTC & 0xF0) | (minutes1 & 0x0F);
		_delay_ms(5);

		//minutes10
		PORTA = (1<<PA3);
		PORTC = (PORTC & 0xF0) | (minutes10 & 0x0F);
		_delay_ms(5);

		//hours1
		PORTA = (1<<PA4);
		PORTC = (PORTC & 0xF0) | (hours1 & 0x0F);
		_delay_ms(5);

		//hours10
		PORTA = (1<<PA5);
		PORTC = (PORTC & 0xF0) | (hours10 & 0x0F);
		_delay_ms(5);

		if(flag == 1)
		{
			seconds1++;
			if (seconds1 > 9)
			{
				seconds1 = 0;
				seconds10++;
			}
			if (seconds10 > 5)
			{
				seconds10 = 0;
				minutes1++;
			}
			if (minutes1 > 9)
			{
				minutes1 = 0;
				minutes10++;
			}
			if (minutes10 > 5)
			{
				minutes10 = 0;
				hours1++;
			}
			if (hours1 > 9)
			{
				hours1 = 0;
				hours10++;
			}
			if (hours10 > 9)
			{
				hours10 = 0;
			}
			flag = 0;
		}

	}

}

