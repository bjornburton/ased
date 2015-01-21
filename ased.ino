#define F_CPU 8000000UL \
 \

#define ON 1
#define OFF 0
#define SET 1
#define CLEAR 0 \

#define NOWAVETIME 500U
#define ARMTHRESHOLD 1200U
#define WAVETHRESHOLD 15U
#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \
 \

#define WAVEHOLDOFFTIME 100 \
 \

/*2:*/
#line 63 "./ased.w"

/*5:*/
#line 80 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 
# include <stdint.h> 

/*:5*/
#line 64 "./ased.w"

/*6:*/
#line 90 "./ased.w"

typedef struct{
uint8_t wavelesswait;
uint16_t armwait;
uint8_t armed;
const uint8_t nowavecount;
}statestruct;


/*:6*/
#line 65 "./ased.w"

/*7:*/
#line 99 "./ased.w"



/*:7*/
#line 66 "./ased.w"

/*8:*/
#line 112 "./ased.w"

void(*handleirq)(statestruct*)= NULL;


/*:8*/
#line 67 "./ased.w"



/*:2*//*9:*/
#line 118 "./ased.w"


int main(void)
{

/*:9*//*11:*/
#line 133 "./ased.w"

statestruct s_state= {
.nowavecount= (uint8_t)(256-(NOWAVETIME/1000U)*(F_CPU/16384U))
};

/*:11*//*12:*/
#line 141 "./ased.w"

/*30:*/
#line 309 "./ased.w"

{

DDRB|= (1<<DDB1);

DDRB|= (1<<DDB0);

PCMSK|= (1<<PCINT3);

GIMSK|= (1<<PCIE);
}

/*:30*/
#line 142 "./ased.w"


/*:12*//*13:*/
#line 147 "./ased.w"

ledcntl(ON);

/*:13*//*14:*/
#line 152 "./ased.w"

/*34:*/
#line 373 "./ased.w"

{
TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));

TIMSK|= (1<<TOIE1);

}


/*:34*/
#line 153 "./ased.w"



/*:14*//*15:*/
#line 162 "./ased.w"

/*35:*/
#line 407 "./ased.w"

{
ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);
DIDR0|= ((1<<AIN1D)|(1<<AIN0D));
ACSR|= (1<<ACBG);
ACSR|= (1<<ACIS1);
ACSR|= (1<<ACIE);
}

/*:35*/
#line 163 "./ased.w"


/*:15*//*16:*/
#line 168 "./ased.w"

sei();
/*:16*//*17:*/
#line 174 "./ased.w"

/*36:*/
#line 422 "./ased.w"

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}

/*:36*/
#line 175 "./ased.w"



/*:17*//*18:*/
#line 180 "./ased.w"

s_state.armwait= ARMTHRESHOLD;


/*:18*//*19:*/
#line 188 "./ased.w"

s_state.wavelesswait= WAVETHRESHOLD;

/*:19*//*20:*/
#line 194 "./ased.w"

for(;;)
{

/*:20*//*21:*/
#line 200 "./ased.w"

sleep_mode();

/*:21*//*22:*/
#line 209 "./ased.w"

if(handleirq!=NULL)
{
handleirq(&s_state);
/*37:*/
#line 433 "./ased.w"

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}

/*:37*/
#line 213 "./ased.w"

handleirq= NULL;
}

}


return 0;

}

/*:22*//*23:*/
#line 233 "./ased.w"

void waveaction(statestruct*s_now)
{
s_now->wavelesswait= 
(s_now->wavelesswait)?s_now->wavelesswait-1:0;


if(!s_now->wavelesswait)
{
ledcntl(ON);

if(!s_now->armed)chirp(ON);
s_now->armwait= ARMTHRESHOLD;
TCNT1= s_now->nowavecount;
}
}

/*:23*//*24:*/
#line 253 "./ased.w"

void nowaveaction(statestruct*s_now)
{
ledcntl(OFF);
chirp(OFF);
s_now->wavelesswait= WAVETHRESHOLD;

s_now->armwait= (s_now->armwait)?s_now->armwait-1:0;

if(!s_now->armwait)(s_now->armed= SET);
}
/*:24*//*25:*/
#line 267 "./ased.w"

void clear(statestruct*s_now)
{
s_now->armwait= ARMTHRESHOLD;
s_now->armed= CLEAR;
}


/*:25*//*26:*/
#line 280 "./ased.w"


ISR(TIMER1_OVF_vect)
{
handleirq= &nowaveaction;
}

/*:26*//*27:*/
#line 289 "./ased.w"


ISR(ANA_COMP_vect)
{
handleirq= &waveaction;
}

/*:27*//*28:*/
#line 298 "./ased.w"


ISR(PCINT0_vect)
{
handleirq= NULL;
}

/*:28*//*31:*/
#line 335 "./ased.w"

void chirp(uint8_t state)
{
static uint8_t count= CHIRPLENGTH;

count= (count)?count-1:CHIRPPERIOD;
sirencntl((count> CHIRPLENGTH||state==OFF)?OFF:ON);
}
/*:31*//*32:*/
#line 347 "./ased.w"

void ledcntl(uint8_t state)
{
PORTB= state?PORTB|(1<<PORTB1):PORTB&~(1<<PORTB1);
}

/*:32*//*33:*/
#line 355 "./ased.w"

void sirencntl(uint8_t state)
{
PORTB= state?PORTB|(1<<PORTB0):PORTB&~(1<<PORTB0);
}

/*:33*/
