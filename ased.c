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

#define NOWAVETIME 500U \
 \

#define WAVEHOLDOFFTIME 100 \

#define ARMTHRESHOLD 1200 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \

/*2:*/
#line 63 "./ased.w"

/*11:*/
#line 106 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 
# include <stdint.h> 


/*:11*/
#line 64 "./ased.w"

/*12:*/
#line 115 "./ased.w"

void ledcntl(uint8_t state);
void sirencntl(uint8_t state);
void chirp(uint8_t state);

/*:12*/
#line 65 "./ased.w"

/*13:*/
#line 124 "./ased.w"

volatile uint8_t f_state= 0;

/*:13*/
#line 66 "./ased.w"




/*:2*//*14:*/
#line 130 "./ased.w"


int main(void)
{

/*28:*/
#line 275 "./ased.w"

{

DDRB|= (1<<DDB1);

DDRB|= (1<<DDB0);

PCMSK|= (1<<PCINT3);

GIMSK|= (1<<PCIE);
}

/*:28*/
#line 135 "./ased.w"


/*:14*//*15:*/
#line 140 "./ased.w"

ledcntl(ON);

/*:15*//*16:*/
#line 145 "./ased.w"

/*30:*/
#line 326 "./ased.w"

{
TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));

TIMSK|= (1<<TOIE1);

}


/*:30*/
#line 146 "./ased.w"


/*:16*//*17:*/
#line 153 "./ased.w"

const int8_t nowavecount= (2^8)-((NOWAVETIME/1000U)*(F_CPU/16384U));


/*:17*//*18:*/
#line 163 "./ased.w"

/*31:*/
#line 359 "./ased.w"

{
ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);
DIDR0|= ((1<<AIN1D)|(1<<AIN0D));
ACSR|= (1<<ACBG);
ACSR|= (1<<ACIS1);
ACSR|= (1<<ACIE);
}

/*:31*/
#line 164 "./ased.w"


/*:18*//*19:*/
#line 169 "./ased.w"

sei();
/*:19*//*20:*/
#line 175 "./ased.w"

/*32:*/
#line 374 "./ased.w"

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}

/*:32*/
#line 176 "./ased.w"


/*:20*//*21:*/
#line 181 "./ased.w"

for(;;)
{
static uint8_t waveless= WAVETHRESHOLD;
static uint16_t armwait= ARMTHRESHOLD;

/*:21*//*22:*/
#line 189 "./ased.w"

sleep_mode();

/*:22*//*23:*/
#line 208 "./ased.w"

if(f_state&(1<<WAVES))
{
waveless= (waveless)?waveless-1:0;

if(!waveless)
{
ledcntl(ON);

if(f_state&(1<<ARM))chirp(ON);

TCNT1= nowavecount;
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

/*33:*/
#line 380 "./ased.w"

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}


/*:33*/
#line 237 "./ased.w"

}

return 0;
}


/*:23*//*24:*/
#line 247 "./ased.w"


ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}

/*:24*//*25:*/
#line 256 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}

/*:25*//*26:*/
#line 265 "./ased.w"


ISR(PCINT0_vect)
{
if(PORTB&(1<<PORTB3))
f_state&= ~(1<<ARM);
}

/*:26*//*29:*/
#line 295 "./ased.w"

void chirp(uint8_t state)
{
static uint8_t count= CHIRPLENGTH;

count= (count)?count-1:CHIRPPERIOD;

if(count> CHIRPLENGTH||state==OFF)sirencntl(OFF);
else sirencntl(ON);
}

void ledcntl(uint8_t state)
{
PORTB= state?PORTB|(1<<PORTB1):PORTB&~(1<<PORTB1);
}

void sirencntl(uint8_t state)
{
PORTB= state?PORTB|(1<<PORTB0):PORTB&~(1<<PORTB0);
}

/*:29*/
