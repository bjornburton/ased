/**************************************
ASED
Version 1.1.0
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

 /* set the siren port direction */
  DDRB |= (1<<SIREN_DD);

 /* turn the led on */
  ledcntl(ON); 

 /* set up the nowave timer */
  initnowavetimer();

 /* set up the wave-event comparator */
  initwavedetector();

 /* Global Int Enable */
  sei();

 /* configure sleep_mode() to go to "idle". Idle allows
    the counters and comparator to continue during sleep. */
  MCUCR &= ~(1<<SM1); 
  MCUCR &= ~(1<<SM0);

 for (;;) // forever
  {
   static unsigned char nowaves = WAVETHRESHOLD;
   static unsigned int armwait = ARMTHRESHOLD;  
      
  /* hold-off to minimise noise susceptibilty */  
  waveholdoff(); 

  /* now we wait in idle for any interrupt event */
  sleep_mode();

  /* some interrupt was detected! Let's see which one */
  if(f_state & (1<<WAVES)) 
    {
     nowaves = (nowaves)?nowaves-1:0;

     if(!nowaves) // ancilliary electric service restored
       {
        ledcntl(ON);

        if(f_state & (1<<ARM))
           chirp(ON);
 
        TCNT1 = TIMESTART;  // reset the timer
       }

     f_state &= ~(1<<WAVES); //reset int flag
    
     }
     else if(f_state & (1<<NOWAVES))
         {
          ledcntl(OFF); 
          nowaves = WAVETHRESHOLD; 

          chirp(OFF);  // ASE dropped, stop alarm chirp
          
          armwait = (armwait)?armwait-1:0;

          if(!armwait && ~f_state & (1<<ARM) )
              f_state |= (1<<ARM);
     /* at this time the only way to disarm is a power cycle */

          f_state &= ~(1<<NOWAVES); //reset int flag
          }
  }  

return 0; // it's the right thing to do!
}


/* Alarm Pulsing function */
void chirp(char state)
{
static unsigned char count = CHIRPLENGTH;

 count = (count)?count-1:CHIRPPERIOD;
 
 if(count < CHIRPLENGTH)
    sirencntl(ON);
  else
    sirencntl(OFF);

}


/* simple led control */
void ledcntl(char state)
{
  PORTB = state ? PORTB | (1<<LED_RED) : PORTB & ~(1<<LED_RED);
}

/* simple siren control */
void sirencntl(char state)
{
  PORTB = state ? PORTB | (1<<SIREN) : PORTB & ~(1<<SIREN);
}


/* configure the no-wave timer */
void initnowavetimer(void)
{
 /* set a very long prescal of 16384 counts */
 TCCR1 = ((1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13));

 /* Timer/counter 1 f_overflow interupt enable */
 TIMSK |= (1<<TOIE1);

}


/* configure the the wave detection comparator */
void initwavedetector(void)
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

/* Wave detection Hold-Off or debounce */
void waveholdoff()
{
 /* Disable the analog comparator interrupt */
 ACSR &= ~(1<<ACIE);

 _delay_us(WAVEHOLDOFFTIME);
 
 /* Enable the analog comparator interrupt */
 ACSR |= (1<<ACIE);

}



/* Timer ISR */
ISR(TIMER1_OVF_vect)
{
  f_state |= (1<<NOWAVES); 
}

/* Comparator ISR */
ISR(ANA_COMP_vect)
{
 f_state |= (1<<WAVES);
}


