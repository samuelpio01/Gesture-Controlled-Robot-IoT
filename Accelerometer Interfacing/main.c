#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "adc_intr.h"

volatile uint16_t adc_val1=0;
volatile uint16_t adc_val2=0;

volatile uint16_t adc_flag1=0;
volatile uint16_t adc_flag2=0;
volatile int ch=0;




void func(int x);
void print();

char str[20];

void func(int x)
{
		if(x==0)
	{	
		if(adc_flag)
		{
			_delay_ms(100);
			adc_val1 = adc_val;
			adc_flag = 0;
			adc_flag1 = 0;
			adc_flag2 = 1;
			
		}
		else
		{
			
			//sprintf(cnt_str, "adc intr (%02d)", cnt++);
			//lcd_putstring(0, cnt_str);	
		}
	}
		else if(x==1)
	{
		if(adc_flag)
		{
			_delay_ms(100);
			adc_val2 = adc_val;
			adc_flag = 0;
			adc_flag2= 0;
			adc_flag1 = 1;			
		}
		else
		{
			
			//sprintf(cnt_str, "adc intr (%02d)", cnt++);
			//lcd_putstring(0, cnt_str);	
		}
		
	}
		_delay_ms(200);
		
}

void print()
{
	
	if(adc_val1<=152 && adc_val1>=147)
		ch=2;
	else if(adc_val1>=159 && adc_val1<=163)
		ch=1;
	if(adc_val2<=152 && adc_val2>=147)
		ch=4;
	else if(adc_val2>=159 && adc_val2<=163)
		ch=3;
	else if (adc_val1<=159 && adc_val1>=152 && adc_val2<=159 && adc_val2>=152)
		ch=0;
	
	
	sprintf(str, "Move: %d", ch);
	lcd_putstring(0, str);
	//sprintf(str, "val1:%4d",adc_val1);
	//lcd_putstring(0, str);
	//sprintf(str, "val2:%4d",adc_val2);
	//lcd_putstring(1, str);
}


int main(void)
{
	
	lcd_init();
	adc_init();
	int ADC_1=2; // x-axis
	int ADC_2=3; // y-axis
	
	while(1)
	{	
		

		if(adc_flag2==0)
		{	
		adc_flag1 = adc_select(ADC_1);
		func(0);
		} 	
		else
		_delay_ms(200); // need this delay so as to select ADC 2
		
		
		if(adc_flag1==0){
		adc_flag2 = adc_select(ADC_2);
		func(1);
		}
		else
		_delay_ms(200);


		print(); //print both the ADC obtained value
	}

	return 0;
}
