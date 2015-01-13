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

#define NOWAVETIME 12 \

#define WAVEHOLDOFFTIME 100 \

#define ARMTHRESHOLD 1200 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \

/*14:*/
#line 120 "./ased.w"


/*11:*/
#line 97 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 

/*:11*/
#line 122 "./ased.w"

/*12:*/
#line 104 "./ased.w"

void ledcntl(char state);
void sirencntl(char state);
void chirp(char state);

/*:12*/
#line 123 "./ased.w"

/*13:*/
#line 113 "./ased.w"

volatile unsigned char f_state= 0;


/*:13*/
#line 124 "./ased.w"


int main(void)
{

/*27:*/
#line 261 "./ased.w"

{

DDRB|= (1<<DDB1);

DDRB|= (1<<DDB0);

PCMSK|= (1<<PCINT3);

GIMSK|= (1<<PCIE);
}

/*:27*/
#line 129 "./ased.w"


/*:14*//*15:*/
#line 134 "./ased.w"


ledcntl(ON);

/*:15*//*16:*/
#line 140 "./ased.w"

/*29:*/
#line 311 "./ased.w"

{

TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));


TIMSK|= (1<<TOIE1);
}


/*:29*/
#line 141 "./ased.w"


/*:16*//*17:*/
#line 149 "./ased.w"

/*30:*/
#line 344 "./ased.w"

{

ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);

DIDR0|= ((1<<AIN1D)|(1<<AIN0D));

ACSR|= (1<<ACBG);

ACSR|= (1<<ACIS1);

ACSR|= (1<<ACIE);
}

/*:30*/
#line 150 "./ased.w"


/*:17*//*18:*/
#line 155 "./ased.w"

sei();
/*:18*//*19:*/
#line 161 "./ased.w"

/*31:*/
#line 364 "./ased.w"

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}

/*:31*/
#line 162 "./ased.w"


/*:19*//*20:*/
#line 167 "./ased.w"

for(;;)
{
static unsigned char waveless= WAVETHRESHOLD;
static unsigned int armwait= ARMTHRESHOLD;

/*:20*//*21:*/
#line 175 "./ased.w"

sleep_mode();

/*:21*//*22:*/
#line 194 "./ased.w"

if(f_state&(1<<WAVES))
{
waveless= (waveless)?waveless-1:0;

if(!waveless)
{
ledcntl(ON);

if(f_state&(1<<ARM))chirp(ON);

TCNT1= NOWAVETIME;
}

f_state&= ~(1<<WAVES);

}
else if(f_state&(1<<NOWAVES))
{
ledcntl(OFF);
chirp(OFF);
waveless= WAVETHRESHOLD;

armwait= (armwait)?armwait-1:0;
if(!armwait&&~f_state&(1<<ARM))f_state|= (1<<ARM);

f_state&= ~(1<<NOWAVES);
}

/*32:*/
#line 370 "./ased.w"

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}


/*:32*/
#line 223 "./ased.w"

}

return 0;
}


/*:22*//*23:*/
#line 233 "./ased.w"


ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}

/*:23*//*24:*/
#line 242 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}

/*:24*//*25:*/
#line 251 "./ased.w"


ISR(PCINT0_vect)
{
if(PORTB&(1<<PORTB3))
f_state&= ~(1<<ARM);
}

/*:25*//*28:*/
#line 281 "./ased.w"

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

/*:28*/
