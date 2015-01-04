/**************************************
ASED
Version 1.0.0
Ancillary Service Electric Detector
2015-01-01
Bjorn Burton

Just for fun.
**************************************/

# include "ased.h"


int main(void)
{
 /* set the led port direction */
  DDRB |= (1<<LED_RED_DD);

 /* turn the led off */
  ledcntl(ON); 

 /* set up the timer */
  initTimerCounter1();

 /* set up the comparator */
   initComparator();

 /* Global Int Enable */
  sei();

 /* configure sleep_mode() to go to "idle". Idle allows
    the counters and comparator to continue during sleep. */
  MCUCR &= ~(1<<SM1); 
  MCUCR &= ~(1<<SM0);

 for (;;) // forever
  {
   static char nowaves = WAVETHRESHOLD;
      
  _delay_us(100); // hold-off for 0.1 ms
  f_overflow = CLEAR; //reset int flag
  f_sinewave = CLEAR;
  /* now we wait in idle for any interrupt event */
  sleep_mode();


  /* some interrupt was detected! Let's see which one */
  if(f_sinewave) 
    {
     nowaves = (nowaves)?nowaves-1:0;
     
     if(!nowaves)
       {
        ledcntl(ON);
        TCNT1 = TIMESTART;
       }
    }
     else if(f_overflow)
    {
     ledcntl(OFF); 
     nowaves = WAVETHRESHOLD; 
    }
  }  

return 0; // it's the right thing to do!
}


/* simple led control */
void ledcntl(char state)
{
  PORTB = state ? PORTB | (1<<LED_RED) : PORTB & ~(1<<LED_RED);
}


/* configure the timer interrupt */
void initTimerCounter1(void)
{
 /* set a very long prescal of 16384 counts */
 TCCR1 = ((1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13));

 /* Timer/counter 1 f_overflow interupt enable */
 TIMSK |= (1<<TOIE1);

}


/* configure the comparator */
void initComparator(void)
{
 /* Setting bit ACME of port ADCSRB to enable the MUX input ADC1 */
 ADCSRB |= (1<<ACME);

 /* ADC1 is set by setting bit MUX0 of register ADMUX */
 ADMUX |= (1<<MUX0);

 /* Disable digital inputs to save power */
 DIDR0  |= ((1<<AIN1D)|(1<<AIN0D));
 
 /* Connect the + input to the band-gap reference */
 ACSR |= (1<<ACBG);
 
 /* Trigger on falling edge only */
 ACSR |= (1<<ACIS1);
 
 /* Enable the analog comparator interrupt */
 ACSR |= (1<<ACIE);

}


/* Timer ISR */
ISR(TIMER1_OVF_vect)
{
  f_overflow = SET; 
}

/* Comparator ISR */
ISR(ANA_COMP_vect)
{
 f_sinewave = SET;
}


