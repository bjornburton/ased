/**************************************
ASED
Version 1.1.0
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
 /* clear-button port */
# define ARMCLEAR PORTB3 // Trinket's LED and pin #3
# define ARMCLEAR_DD DDB3

 /* LED port */
# define LED_RED PORTB1  // Trinket's LED and pin #1
# define LED_RED_DD DDB1

 /* siren port */
# define SIREN PORTB0 // Trinket's LED and pin #0
# define SIREN_DD DDB0

 /* Bool*/
# define ON 1
# define OFF 0
# define SET 1
# define CLEAR 0

 /* Flags for f_state */
# define NOWAVES 2 // no ASE detected for some time 
# define WAVES   1 // ASE detected
# define ARM     0 // ARM for Alarm

 /* Parameters */
# define WAVETHRESHOLD 15
/* Number of wave before considering the service on. Range to 255 */
/* About 250 ms. Don't take too long or time will run out */

# define TIMESTART 12     // preset for the timer counter. Range to 255 */
/* Prescaler is set to clk/16484. 
0.5 seconds *(8e6/16384) is 244.14.
256-244 = 12, leaving 500 ms to time-out */

# define WAVEHOLDOFFTIME 100 // Range to 255
/* hold-off time in us for wave detection */

# define ARMTHRESHOLD 1200 // Range to 65535
/* alarm arm delay in nowave counts*/

/* chirp parameters for alarm */
# define CHIRPLENGTH 7 // number of waves long
# define CHIRPPERIOD 200 // number of waves long


/**** Function Declarations ****/
void ledcntl(char state);
void sirencntl(char state); //alarm siren control
void chirp(char state); // alarm siren modulation
void initnowavetimer(void); // sets up timer
void initwavedetector(void); // sets up comparator
void waveholdoff(void); // for noise resistance...debounce

/**** Global variables ****/
volatile unsigned char f_state = 0x00; 

