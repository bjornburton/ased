/*3:*/
#line 41 "./ased.w"












# include "ased.h"

/*:3*//*4:*/
#line 56 "./ased.w"

int main(void)
{

DDRB|= (1<<LED_RED_DD);


DDRB|= (1<<SIREN_DD);


PCMSK|= (1<<PCINT3);


GIMSK|= (1<<PCIE);

/*:4*//*5:*/
#line 73 "./ased.w"


ledcntl(ON);

/*:5*//*6:*/
#line 78 "./ased.w"


initnowavetimer();

/*:6*//*8:*/
#line 91 "./ased.w"


sei();
/*:8*//*9:*/
#line 97 "./ased.w"



MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);

/*:9*//*10:*/
#line 105 "./ased.w"

for(;;)
{
static unsigned char nowaves= WAVETHRESHOLD;
static unsigned int armwait= ARMTHRESHOLD;


waveholdoff();


sleep_mode();


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
}

return 0;
}

/*:10*//*11:*/
#line 161 "./ased.w"


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



void initnowavetimer(void)
{

TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));


TIMSK|= (1<<TOIE1);

}




void initwavedetector(void)
{
/*:11*//*12:*/
#line 214 "./ased.w"


ADCSRB|= (1<<ACME);


ADMUX|= (1<<MUX0);

/*:12*//*13:*/
#line 224 "./ased.w"


DIDR0|= ((1<<AIN1D)|(1<<AIN0D));
/*:13*//*14:*/
#line 231 "./ased.w"


ACSR|= (1<<ACBG);

/*:14*//*15:*/
#line 238 "./ased.w"


ACSR|= (1<<ACIS1);
/*:15*//*16:*/
#line 243 "./ased.w"


ACSR|= (1<<ACIE);

}

/*:16*//*17:*/
#line 256 "./ased.w"


void waveholdoff()
{

ACSR&= ~(1<<ACIE);

_delay_us(WAVEHOLDOFFTIME);


ACSR|= (1<<ACIE);

}




ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}

/*:17*//*18:*/
#line 282 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}


ISR(PCINT0_vect)
{
if(PORTB&(1<<ARMCLEAR))
f_state&= ~(1<<ARM);
}

/*:18*/
