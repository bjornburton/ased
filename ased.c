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
<<<<<<< HEAD
 \

#define WAVEHOLDOFFTIME 100 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \

#define NOWAVETIME 500U \

#define ARMTHRESHOLD 1200 \
 \

#define WAVETHRESHOLD 15 \
 \
 \
=======

#define WAVETHRESHOLD 15 \
 \

#define NOWAVETIME 500U \
 \

#define WAVEHOLDOFFTIME 100 \

#define ARMTHRESHOLD 1200 \

#define CHIRPLENGTH 7
#define CHIRPPERIOD 200 \
>>>>>>> origin/testing

/*2:*/
#line 63 "./ased.w"

<<<<<<< HEAD
/*8:*/
#line 94 "./ased.w"
=======
/*11:*/
#line 106 "./ased.w"
>>>>>>> origin/testing

# include <avr/io.h>  
# include <util/delay.h>  
# include <avr/interrupt.h>  
# include <avr/sleep.h>  
# include <stdlib.h> 
# include <stdint.h> 


<<<<<<< HEAD
/*:8*/
#line 64 "./ased.w"

/*9:*/
#line 103 "./ased.w"
=======
/*:11*/
#line 64 "./ased.w"

/*12:*/
#line 115 "./ased.w"
>>>>>>> origin/testing

void ledcntl(uint8_t state);
void sirencntl(uint8_t state);
void chirp(uint8_t state);

<<<<<<< HEAD
/*:9*/
#line 65 "./ased.w"

/*10:*/
#line 112 "./ased.w"

volatile uint8_t f_state= 0;

/*:10*/
=======
/*:12*/
#line 65 "./ased.w"

/*13:*/
#line 124 "./ased.w"

volatile uint8_t f_state= 0;

/*:13*/
>>>>>>> origin/testing
#line 66 "./ased.w"




<<<<<<< HEAD
/*:2*//*11:*/
#line 118 "./ased.w"
=======
/*:2*//*14:*/
#line 130 "./ased.w"
>>>>>>> origin/testing


int main(void)
{

/*28:*/
<<<<<<< HEAD
#line 278 "./ased.w"
=======
#line 275 "./ased.w"
>>>>>>> origin/testing

{

DDRB|= (1<<DDB1);

DDRB|= (1<<DDB0);

PCMSK|= (1<<PCINT3);

GIMSK|= (1<<PCIE);
}

/*:28*/
<<<<<<< HEAD
#line 123 "./ased.w"


/*:11*//*12:*/
#line 128 "./ased.w"

ledcntl(ON);

/*:12*//*13:*/
#line 133 "./ased.w"

/*30:*/
#line 329 "./ased.w"
=======
#line 135 "./ased.w"


/*:14*//*15:*/
#line 140 "./ased.w"

ledcntl(ON);

/*:15*//*16:*/
#line 145 "./ased.w"

/*30:*/
#line 326 "./ased.w"
>>>>>>> origin/testing

{
TCCR1= ((1<<CS10)|(1<<CS11)|(1<<CS12)|(1<<CS13));

TIMSK|= (1<<TOIE1);

}


/*:30*/
<<<<<<< HEAD
#line 134 "./ased.w"


/*:13*//*15:*/
#line 144 "./ased.w"
=======
#line 146 "./ased.w"


/*:16*//*17:*/
#line 153 "./ased.w"
>>>>>>> origin/testing

const int8_t nowavecount= (2^8)-((NOWAVETIME/1000U)*(F_CPU/16384U));


<<<<<<< HEAD
/*:15*//*16:*/
#line 154 "./ased.w"

/*31:*/
#line 362 "./ased.w"
=======
/*:17*//*18:*/
#line 163 "./ased.w"

/*31:*/
#line 359 "./ased.w"
>>>>>>> origin/testing

{
ADCSRB|= (1<<ACME);

ADMUX|= (1<<MUX0);
DIDR0|= ((1<<AIN1D)|(1<<AIN0D));
ACSR|= (1<<ACBG);
ACSR|= (1<<ACIS1);
ACSR|= (1<<ACIE);
}

/*:31*/
<<<<<<< HEAD
#line 155 "./ased.w"


/*:16*//*17:*/
#line 160 "./ased.w"

sei();
/*:17*//*18:*/
#line 166 "./ased.w"

/*32:*/
#line 377 "./ased.w"
=======
#line 164 "./ased.w"


/*:18*//*19:*/
#line 169 "./ased.w"

sei();
/*:19*//*20:*/
#line 175 "./ased.w"

/*32:*/
#line 374 "./ased.w"
>>>>>>> origin/testing

{
MCUCR&= ~(1<<SM1);
MCUCR&= ~(1<<SM0);
}

/*:32*/
<<<<<<< HEAD
#line 167 "./ased.w"


/*:18*//*21:*/
#line 183 "./ased.w"
=======
#line 176 "./ased.w"


/*:20*//*21:*/
#line 181 "./ased.w"
>>>>>>> origin/testing

for(;;)
{
static uint8_t waveless= WAVETHRESHOLD;
static uint16_t armwait= ARMTHRESHOLD;

/*:21*//*22:*/
<<<<<<< HEAD
#line 191 "./ased.w"
=======
#line 189 "./ased.w"
>>>>>>> origin/testing

sleep_mode();

/*:22*//*23:*/
<<<<<<< HEAD
#line 210 "./ased.w"

=======
#line 208 "./ased.w"
>>>>>>> origin/testing

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
<<<<<<< HEAD
#line 384 "./ased.w"
=======
#line 380 "./ased.w"
>>>>>>> origin/testing

{

ACSR&= ~(1<<ACIE);
_delay_us(WAVEHOLDOFFTIME);

ACSR|= (1<<ACIE);
}


/*:33*/
<<<<<<< HEAD
#line 240 "./ased.w"
=======
#line 237 "./ased.w"
>>>>>>> origin/testing

}

return 0;
}


/*:23*//*24:*/
<<<<<<< HEAD
#line 250 "./ased.w"
=======
#line 247 "./ased.w"
>>>>>>> origin/testing


ISR(TIMER1_OVF_vect)
{
f_state|= (1<<NOWAVES);
}

/*:24*//*25:*/
<<<<<<< HEAD
#line 259 "./ased.w"
=======
#line 256 "./ased.w"
>>>>>>> origin/testing


ISR(ANA_COMP_vect)
{
f_state|= (1<<WAVES);
}

/*:25*//*26:*/
<<<<<<< HEAD
#line 268 "./ased.w"
=======
#line 265 "./ased.w"
>>>>>>> origin/testing


ISR(PCINT0_vect)
{
if(PORTB&(1<<PORTB3))
f_state&= ~(1<<ARM);
}

/*:26*//*29:*/
<<<<<<< HEAD
#line 298 "./ased.w"
=======
#line 295 "./ased.w"
>>>>>>> origin/testing

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
