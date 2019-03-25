#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "adc_intr.h"

//#define ADC_1	2 // x-axis
//#define ADC_2 	3 // y-axis



volatile uint16_t adc_val=0;

volatile uint16_t adc_flag=0;

void adc_init(void)
{
	// set PORTA as input
	DDRA = 0x00; //~BV(ADC_CHANNEL);
	PORTA = 0xFF; // BV(ADC_CHANNEL);

	// enable adc and adc interrupt
	ADCSRA = BV(ADEN) | BV(ADIE);
	// enable global interrupt
	sei();
}

int adc_select(int chan)
{	
	ADMUX = 0x00; //clear the ADMUX
	if(chan==2)
	{	
		ADMUX = 0x62; //BV(MUX0) | BV(MUX1) | BV(ADLAR) | BV(REFS0); //select ADC2
		ADCSRA |= BV(ADSC); //start conversion
		return 1;
	}

	else if(chan==3)
	{
		ADMUX = 0x63; //BV(MUX2) | BV(ADLAR) | BV(REFS0); //select ADC3
		ADCSRA |= BV(ADSC); //start conversion
		return 2;
	}
}



uint16_t adc_read(void)
{
	// read value from adc
	uint16_t val = ADCH;
	//decide for left and right
	

	return val;
}

ISR(ADC_vect)
{
	adc_val = adc_read();
	adc_flag = 1;
}


