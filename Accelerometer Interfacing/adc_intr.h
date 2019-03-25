#ifndef __ADC_INTR_H
#define __ADC_INTR_H

void adc_init(void);
uint16_t adc_read(void);
int adc_select(int chan);

extern volatile uint16_t adc_val;
extern volatile uint16_t adc_flag;

#define BV(bit) (1<<(bit))

#endif

