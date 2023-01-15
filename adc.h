/*
 * adc.h
 *
 * Created: 12/01/2023 02:52:30 p. m.
 *  Author: axel9
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init();
uint16_t read_adc(uint8_t ch);

#endif /* ADC_H_ */