#define F_CPU 8000000UL \
 \

#define ON 1
#define OFF 0
#define SET 1
#define CLEAR 0 \
 \

#define NOWAVES 2
#define WAVES 1
#define ARM 0 \

#define WAVETHRESHOLD 15 \
 \

#define TIMESTART 12 \

#define WAVEHOLDOFFTIME 100 \

#define ARMTHRESHOLD 1200 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \

/*14:*/
#line 124 "./ased.w"


/*11:*/
#line 101 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 

/*:11*/
#line 126 "./ased.w"

/*12:*/
#line 108 "./ased.w"

void ledcntl(char state);
void sirencntl(char state);
void chirp(char state);

/*:12*/
#line 127 "./ased.w"

/*13:*/
#line 117 "./ased.w"

volatile unsigned char f_state= 0;


/*:13*/
#line 128 "./ased.w"


int main(void)
{

/*24:*/
#line 227 "./ased.w"

{

DDRB|= (1<<DDB1);

DDRB|= (1<<DDB0);

PCMSK|= (1<<PCINT3);

GIMSK|= (1<<PCIE);
}


/*:24*/
#line 133 "./ased.w"


/*:14*//*15:*/
#line 138 "./ased.w"


ledcntl(ON);

/*:15*//*16:*/
#line 144 "./ased.w"

/*26:*/
#line 278 "./ased.w"

{

TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));


TIMSK|= (1<<TOIE1);
}


/*:26*/
#line 145 "./ased.w"


/*:16*//*17:*/
#line 153 "./ased.w"

/*27:*/
#line 311 "./ased.w"

{

ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);

DIDR0|= ((1<<AIN1D)|(1<<AIN0D));

ACSR|= (1<<ACBG);

ACSR|= (1<<ACIS1);

ACSR|= (1<<ACIE);
}

/*:27*/
#line 154 "./ased.w"


/*:17*//*18:*/
#line 159 "./ased.w"

sei();
/*:18*//*19:*/
#line 165 "./ased.w"

/*28:*/
#line 331 "./ased.w"

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}


/*:28*/
#line 166 "./ased.w"


/*:19*//*20:*/
#line 171 "./ased.w"

for(;;)
{
static unsigned char waveless= WAVETHRESHOLD;
static unsigned int armwait= ARMTHRESHOLD;

/*:20*//*21:*/
#line 179 "./ased.w"

sleep_mode();

/*:21*//*22:*/
#line 187 "./ased.w"

if(f_state&(1<<WAVES))
{
waveless= (waveless)?waveless-1:0;

if(!waveless)
{
ledcntl(ON);

if(f_state&(1<<ARM))chirp(ON);

TCNT1= TIMESTART;
}

f_state&= ~(1<<WAVES);

}
else if(f_state&(1<<NOWAVES))
{
ledcntl(OFF);
waveless= WAVETHRESHOLD;

chirp(OFF);

armwait= (armwait)?armwait-1:0;

if(!armwait&&~f_state&(1<<ARM))f_state|= (1<<ARM);


f_state&= ~(1<<NOWAVES);
}

/*29:*/
#line 338 "./ased.w"

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}

/*:29*/
#line 219 "./ased.w"

}

return 0;
}

/*:22*//*25:*/
#line 248 "./ased.w"

void chirp(char state)
{
static unsigned char count= CHIRPLENGTH;

count= (count)?count-1:CHIRPPERIOD;

if(count> CHIRPLENGTH||state==OFF)sirencntl(OFF);
else sirencntl(ON);
}

void ledcntl(char state)
{
PORTB= state?PORTB|(1<<PORTB1):PORTB&~(1<<PORTB1);
}


void sirencntl(char state)
{
PORTB= state?PORTB|(1<<PORTB0):PORTB&~(1<<PORTB0);
}

/*:25*//*30:*/
#line 350 "./ased.w"


ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}


/*:30*//*31:*/
#line 362 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}


/*:31*//*32:*/
#line 372 "./ased.w"


ISR(PCINT0_vect)
{
if(PORTB&(1<<PORTB3))
f_state&= ~(1<<ARM);
}
/*:32*/
