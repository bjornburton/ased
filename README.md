ASED
=========
Ancillary Service Electric Detector


It's in C99 and so will compile using the gnu compiler, but also the
Arduino IDE.

What is does and Why:
With an emergency generator connected through an interlocked load-center,
it's hard to tell when the Ancillary Service has been restored. Switching
back to Main shuts everything down. The obvious method is to measure the
voltage at the main-breaker's input. The safety concern is that it's not
breaker-protected making for a massive fault-current, should insulation be
breached or the circuit shorted. Also, installation is somewhat involved,
having to tap into live lines and providing some form of isolation.

How: 
The obvious solution is to have a high-impedance capacitive connection. Simple
capacitive coupling can be had with a "gimmick"; a technique used since the
1920s. This may be several turns of THHN around the large-gage insulated
incomming line. Since the voltage is with respect to neutral, and neutral is
bonded to ground, just the one wire is needed.

With this signal, a circuit and be built to detect the difference between
having AC and having no AC, and provide a signal to indicate that state.
The signal provided to the generator-operator could be a lamp or buzzer.

The line-voltage is +/- 170 V peak, with respect to ground. The peaks will be
about 8.3 ms apart. The signal will be much less, depending on the circuit's
input impedance and capacitance.

The circuit would need a high input impedance, so as to see a strong enough
signal. The circuit would need a reference to ground to compare to. The input
may need a bit of protection from line transients, which could pass trough
the gimmick.

Implementation:
I have seven Ada Fruit Trinkets just laying around. They use the Atmel 
ATTINY85 processor. The analog inputs are about 100 M ohms. Not great, but
I think it should be good enough. If we can muster 1 pf of gimmick, we will
have 1/(2*pi*fc) of Xc. Ohms law indicates
100e6 * (170 / ( (2*pi*60*1e-12)^-1 + 100e6)) = 6.16 volts peak, ignoring
input pin capacitance. The steering diodes will keep the analog innards safe
since the current is so low. Supply voltage at "BAT" is 5.5 to 16 V and it has
a red LED on-board.

The Trinket runs at a speedy 8 MHz so the slow 60 Hz signal is no issue. One
could use the ADC but that doesn't make too much sense as the input may spend a
lot of time cliped. The inbuilt comparator seems like the right choice, for now.

Both comparator inputs have pins but AIN0 can be connected to a reference of
1.1 VDC, leaving AIN1 to the signal. The ref is selected by setting bit ACBG of
register ACSR. Input AN0 is PB0 marked "#0" on the Trinket.

Rather than burning loops, waiting for something to happen for 16 ms, the
comparator interrupt can be used. To enable this, set the ACIE bit of register
ACSR. It can be configured to trigger on rising, falling or toggle (default)
by clearing/setting bits ACIS[1:0] also on register ACSR. There is no need for
toggle, and falling is selected by simply setting ACIS1.

Of course, any interrupt function requires that bit I "Global Interrupt Enable"
is set; usualy done through calling sei().

The event can be checked by inspecting (then clearing) the ACI bit of the ACSR
register but the vector TIMER1_COMPA_vect is the simpler way.

A timer is needed to to encompase some number of waves so it can clearly discernon from off.


 

     
