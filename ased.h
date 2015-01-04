/**************************************
ASED
Version 1.0.0
Ancillary Service Electric Detector
2015-01-01
Bjorn Burton

Just for fun.
**************************************/

/* AVR clock frequency in Hz, used by util/delay.h */
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <util/delay.h> // need to delay
# include <avr/interrupt.h> // have need of an interrupt
# include <avr/sleep.h> // have need of sleep
# include <stdlib.h>

/**** Defines *****/
 /* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
 /* Bool*/
# define ON 1
# define OFF 0
# define SET 1
# define CLEAR 0

 /* Parameters */
# define WAVETHRESHOLD 15 // wave count debounce; 15 waves is "good"
/* About 250 ms. Don't take too long or time will run out */

# define TIMESTART 12     // preset for the timer counter
/* Prescaler is set to clk/16484. 
0.5 seconds *(8e6/16384) is 244.14.
256-244 = 12, leaving 500 ms to time-out */


/**** Function Declarations ****/
void ledcntl(char state);
void initTimerCounter1(void); // sets up timer
void initComparator(void); // sets up comparator

/**** Global variables ****/
volatile char f_overflow = CLEAR; 
volatile char f_sinewave = CLEAR; 

