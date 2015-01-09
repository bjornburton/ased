/*3:*/
#line 48 "./ased.w"


#define F_CPU 8000000UL





# define ARMCLEAR PORTB3 
# define ARMCLEAR_DD DDB3


# define LED_RED PORTB1  
# define LED_RED_DD DDB1


# define SIREN PORTB0 
# define SIREN_DD DDB0


# define ON 1
# define OFF 0
# define SET 1
# define CLEAR 0


# define NOWAVES 2 
# define WAVES   1 
# define ARM     0 


# define WAVETHRESHOLD 15



# define TIMESTART 12     




# define WAVEHOLDOFFTIME 100 


# define ARMTHRESHOLD 1200 



# define CHIRPLENGTH 7 
# define CHIRPPERIOD 200 



void ledcntl(char state);
void sirencntl(char state);
void chirp(char state);
void initnowavetimer(void);
void initwavedetector(void);
void waveholdoff(void);



volatile unsigned char f_state= 0x00;

/*4:*/
#line 119 "./ased.w"

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 


/*:4*/
#line 111 "./ased.w"


/*:3*//*5:*/
#line 128 "./ased.w"

int main(void)
{

DDRB|= (1<<LED_RED_DD);


DDRB|= (1<<SIREN_DD);


PCMSK|= (1<<PCINT3);


GIMSK|= (1<<PCIE);

/*:5*//*6:*/
#line 145 "./ased.w"


ledcntl(ON);

/*:6*//*7:*/
#line 150 "./ased.w"


initnowavetimer();

/*:7*//*9:*/
#line 163 "./ased.w"


sei();
/*:9*//*10:*/
#line 169 "./ased.w"



MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);

/*:10*//*11:*/
#line 177 "./ased.w"

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

/*:11*//*12:*/
#line 233 "./ased.w"


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
/*:12*//*13:*/
#line 286 "./ased.w"


ADCSRB|= (1<<ACME);


ADMUX|= (1<<MUX0);

/*:13*//*14:*/
#line 296 "./ased.w"


DIDR0|= ((1<<AIN1D)|(1<<AIN0D));
/*:14*//*15:*/
#line 303 "./ased.w"


ACSR|= (1<<ACBG);

/*:15*//*16:*/
#line 310 "./ased.w"


ACSR|= (1<<ACIS1);
/*:16*//*17:*/
#line 315 "./ased.w"


ACSR|= (1<<ACIE);

}

/*:17*//*18:*/
#line 328 "./ased.w"


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

/*:18*//*19:*/
#line 354 "./ased.w"


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}


ISR(PCINT0_vect)
{
if(PORTB&(1<<ARMCLEAR))
f_state&= ~(1<<ARM);
}

/*:19*/
