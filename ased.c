/**************************************
ASED
Ancillary Service Electric Detector
2014-12-29
Bjorn Burton

Just for fun.
**************************************/
// AVR clock frequency in Hz, used by util/delay.h
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <avr/interrupt.h> // have need of an interrupt
# include <avr/sleep.h> // have need of sleep
# include <stdlib.h>

/* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
# define ON 1
# define OFF 0
# define TRUE 1
# define FALSE 0


/* Function Declarations */
void delay(unsigned intervals);
void ledcntl(char state);
void initTimerCounter1(void);
void initComparator(void);

/* Global variables */
volatile char overflow = 0; 

int main(void)
{

 /* set the led port direction */
  DDRB |= (1<<LED_RED_DD);

 /* turn the led on */
  ledcntl(ON);       //turn the LED on

 /* set up the timer */
  initTimerCounter1();

 /* set up the comparator */
   initComparator();

 /*** set pull-up temprarily ***/
  PORTB |= (1<<PB1);

 /* Global Int Enable */
  sei();

 /* configure sleep_mode() to go to "idle". Idle allows
    the counters and comparator to continue during sleep. */
  MCUCR &= ~(1<<SM1); 
  MCUCR &= ~(1<<SM0);

 for (;;) // forever
  {

  /* preset the counter at each itteration. Prescaler is clk/16484.
     0.5 *(8e6/16384) is 244.14. 256-244=12, so 12 is it */
  TCNT1 = 12;

  /* now we wait in idle for any interrupt event */
  sleep_mode();

  /* some interrupt was detected! Let's see which one */
  if(overflow == TRUE) 
    {
      static unsigned char intcount = 0; 
     
      /* each count is about 1/2 second */
      if(++intcount == 1) //toggle after about 1/2 second
        {
         static char toggle = 0;
         
         if( (toggle = (toggle)?0:1) ) ledcntl(ON);
           else ledcntl(OFF);
         
         /* since it toggled the int counter is reset */
         intcount = 0;
         }

    /* reset the flag */
    overflow = FALSE; //reset int flag
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
 /* General Timer/Counter Control Register we will leave default */
 //GTCCR = ;
 
 /* Timer/Counter Control Register A we will leave default */
 //TCCR0A = ;

 /* Timer/Counter1 Control Register we will leave default */
 //TCCR1 = ;
 //TCCR1 = ;

 /* set a very long prescal */
 TCCR1 = ((1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13));

 /* Timer/counter 1 overflow interupt enable */
 TIMSK |= (1<<TOIE1);

}


/* configure the comparator's interrupt */
void initComparator(void)
{

 /* Disable digital inputs to save power */
 DIDR0  |= ((1<<AIN1D)|(1<<AIN0D));
 
 /* Connect the + input to the band-gap reference */
 ACSR |= (1<<ACBG);
 
 /* Enable the interrupt */
 ACSR |= (1<<ACIE);

 /* Trigger on falling edge only */
 ACSR |= (1<<ACIS1);
 
}


/* this is not much of an ISR */
ISR(TIMER1_OVF_vect)
{
 overflow = TRUE;
}

/* Comparator ISR */
ISR(TIMER1_COMPA_vect)
{
}


