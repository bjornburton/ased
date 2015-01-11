#define F_CPU 8000000UL \

#define ARMCLEAR PORTB3
#define ARMCLEAR_DD DDB3 \
 \

#define ON 1
#define OFF 0
#define SET 1
#define CLEAR 0 \
 \

#define NOWAVES 2
#define WAVES 1
#define ARM 0 \
 \

#define WAVETHRESHOLD 15 \
 \
 \

#define TIMESTART 12 \
 \
 \
 \

#define WAVEHOLDOFFTIME 100 \
 \

#define ARMTHRESHOLD 1200 \
 \
 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \
 \

#define LED_RED PORTB1
#define LED_RED_DD DDB1 \
 \

#define SIREN PORTB0
#define SIREN_DD DDB0 \
 \

/*1:*/
#line 97 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 

/*:1*//*4:*/
#line 121 "./ased.w"

/*2:*/
#line 104 "./ased.w"

void ledcntl(char state);
void sirencntl(char state);
void chirp(char state);

/*:2*/
#line 122 "./ased.w"

/*3:*/
#line 113 "./ased.w"

volatile unsigned char f_state= 0;



/*:3*/
#line 123 "./ased.w"


int main(void)
{

/*13:*/
#line 225 "./ased.w"

{

DDRB|= (1<<LED_RED_DD);


DDRB|= (1<<SIREN_DD);


PCMSK|= (1<<PCINT3);


GIMSK|= (1<<PCIE);
}


/*:13*/
#line 128 "./ased.w"


/*:4*//*5:*/
#line 133 "./ased.w"


ledcntl(ON);

/*:5*//*6:*/
#line 139 "./ased.w"


/*15:*/
#line 283 "./ased.w"

{

TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));


TIMSK|= (1<<TOIE1);
}


/*:15*/
#line 141 "./ased.w"


/*:6*//*7:*/
#line 149 "./ased.w"


/*16:*/
#line 317 "./ased.w"

{

ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);

DIDR0|= ((1<<AIN1D)|(1<<AIN0D));

ACSR|= (1<<ACBG);

ACSR|= (1<<ACIS1);

ACSR|= (1<<ACIE);
}

/*:16*/
#line 151 "./ased.w"


/*:7*//*8:*/
#line 156 "./ased.w"


sei();
/*:8*//*9:*/
#line 163 "./ased.w"

/*17:*/
#line 337 "./ased.w"

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}


/*:17*/
#line 164 "./ased.w"


/*:9*//*10:*/
#line 170 "./ased.w"

for(;;)
{
static unsigned char nowaves= WAVETHRESHOLD;
static unsigned int armwait= ARMTHRESHOLD;

/*:10*//*11:*/
#line 178 "./ased.w"

sleep_mode();

/*:11*//*12:*/
#line 183 "./ased.w"

if(f_state&(1<<WAVES))
{
nowaves= (nowaves)?nowaves-1:0;

if(!nowaves)
{
ledcntl(ON);

if(f_state&(1<<ARM))
chirp(ON);

TCNT1= TIMESTART;
}

f_state&= ~(1<<WAVES);

}
else if(f_state&(1<<NOWAVES))
{
ledcntl(OFF);
nowaves= WAVETHRESHOLD;

chirp(OFF);

armwait= (armwait)?armwait-1:0;

if(!armwait&&~f_state&(1<<ARM))
f_state|= (1<<ARM);


f_state&= ~(1<<NOWAVES);
}

/*18:*/
#line 344 "./ased.w"

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}

/*:18*/
#line 217 "./ased.w"

}

return 0;
}



/*:12*//*14:*/
#line 249 "./ased.w"

void chirp(char state)
{
static unsigned char count= CHIRPLENGTH;

count= (count)?count-1:CHIRPPERIOD;

if(count> CHIRPLENGTH||state==OFF)
sirencntl(OFF);
else
sirencntl(ON);

}


void ledcntl(char state)
{
PORTB= state?PORTB|(1<<LED_RED):PORTB&~(1<<LED_RED);
}


void sirencntl(char state)
{
PORTB= state?PORTB|(1<<SIREN):PORTB&~(1<<SIREN);
}

/*:14*//*19:*/
#line 356 "./ased.w"


ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}


/*:19*//*20:*/
#line 368 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}


/*:20*//*21:*/
#line 378 "./ased.w"


ISR(PCINT0_vect)
{
if(PORTB&(1<<ARMCLEAR))
f_state&= ~(1<<ARM);
}
/*:21*/
