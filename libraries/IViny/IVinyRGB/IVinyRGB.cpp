#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "IVinyRGB.h"
#include "Arduino.h"

#define set(x) |= (1<<x) 
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)

#define BLUE_CLEAR (pinlevelB &= ~(1 << BLUE)) // map BLUE to PB2
#define GREEN_CLEAR (pinlevelB &= ~(1 << GREEN)) // map BLUE to PB2
#define RED_CLEAR (pinlevelB &= ~(1 << RED)) // map BLUE to PB2
#define PORTB_MASK  (1 << PB0) | (1 << PB1) | (1 << PB2)
#define BLUE PB2
#define GREEN PB1
#define RED PB0


unsigned char IVinyPWMcompare[3]; 
volatile unsigned char IVinyPWMcompbuff[3];

void IVinyRGBBegin() {                

  pinMode(2, OUTPUT); 
  pinMode(1, OUTPUT); 
  pinMode(0, OUTPUT); 
  //CLKPR = (1 << CLKPCE);        // enable clock prescaler update
  //CLKPR = 0;                    // set clock to maximum (= crystal)


  IVinyPWMcompare[0] = 0x00;// set default PWM values
  IVinyPWMcompare[1] = 0x00;// set default PWM values
  IVinyPWMcompare[2] = 0x00;// set default PWM values
  IVinyPWMcompbuff[0] = 0x00;// set default PWM values
  IVinyPWMcompbuff[1] = 0x00;// set default PWM values
  IVinyPWMcompbuff[2] = 0x00;// set default PWM values
  

  TIFR = (1 << TOV0);           // clear interrupt flag
  TIMSK = (1 << TOIE0);         // enable overflow interrupt
  TCCR0B = (1 << CS00);         // start timer, no prescale

  sei(); 
}

void IVinyRGB(int pin,int value){
	IVinyPWMcompbuff[pin] = value;
}

void IVinyRGBDelay(int ms) {
  while (ms) {
    _delay_ms(1);
    ms--;
  }
}

ISR (TIM0_OVF_vect) {
  static unsigned char pinlevelB=PORTB_MASK;
  static unsigned char softcount=0xFF;

  PORTB = pinlevelB;            // update outputs
  
  if(++softcount == 0){         // increment modulo 256 counter and update
                                // the compare values only when counter = 0.
    IVinyPWMcompare[0] = IVinyPWMcompbuff[0]; // verbose code for speed
    IVinyPWMcompare[1] = IVinyPWMcompbuff[1]; // verbose code for speed
    IVinyPWMcompare[2] = IVinyPWMcompbuff[2]; // verbose code for speed

    pinlevelB = PORTB_MASK;     // set all port pins high
  }
  // clear port pin on compare match (executed on next interrupt)
  if(IVinyPWMcompare[0] == softcount) RED_CLEAR;
  if(IVinyPWMcompare[1] == softcount) GREEN_CLEAR;
  if(IVinyPWMcompare[2] == softcount) BLUE_CLEAR;
}

