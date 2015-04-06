ASED
=========
Ancillary Service Electric Detector


This is the firmware portion of an Ancillary Service Electric Detector or ASED.
It is written within Web using C99 (ISO/IEC 9899:1999). Web is a "system of
structured documentation" which supports Literate Programming, as created by
Donald Knuth. The program ctangle creates C source, from the web source, for
use strictly by the compiler. The program cweave builds a TeX source file for
further processing by TeX or PDFTeX into a nice document.

This does not rely on Arduino's IDE and for this reason the C code will compile
using the gnu compiler, avr-gcc along with avr-libc. It should also compile in
the Arduino IDE as a "Sketch", with some modification. One issue with the
Arduino IDE is that the usual  C99/C11 way of using a designator to initialize
structure components does not work as Arduino only supports C89.
A Second issue is that the IDE seems to muck around with the order of your code,
putting function declarations ahead of typedefs. Actually, what it really does 
it guess at what you want as function declarations and inserts those. To
aggravate the user further, the errors provided don't refer to the user's code,
but instead, to the broken code created by the Arduino IDE. Code whose existence
becomes clear only after "verbose output" is enabled. The official workaround is
to put typedefs into a header file.
   
Since the IDE is generally weak, error/warning reporting is poor, documentation
is lacking, strange workarounds are needed for many things, and it adds a layer
of complexity, I won't continue using it. I have enough to challenge me! 

There is a simple Makefile to build it with, but it may need to be tweaked to
suit your system.

You will need cweave, ctangle, avr-gcc as well as pdftex, if you want nice
documentation. TexLive seems to be the best.

# The Fun Reason
I wrote this for fun and not out of any *real* need. I wanted to learn a bit
about git's branching, merging, refspec, etc. Also to brush-up on my C-skills,
poor as they are. Programming on bare-metal (no OS) and on a tiny microprocessor
to boot, are exciting firsts for me. And I've been wanting to try Literate
Programming in Donald Knuth's Cweb, just to see what it's like. 

# The Practical Reason
With my emergency generator connected through an interlocked load-center, it's
hard to tell when the Ancillary Service has been restored. The neighbor's
lights offer a clue at night, but aren't reliable. Switching back to Main, from
the genny, requires shutting everything off for a moment. It would be good to
know if main, or Ancillary Service, is live before switching back to it.

The obvious method is to measure the voltage at the main-breaker's input, using
a meter. One safety concern is that it's not breaker-protected making for a
massive fault-current, should insulation be breached or the circuit shorted.
Also, installation of a simple meter is somewhat involved, having to tap into
live lines and, ideally, providing some form of isolation. 

The obvious solution is to have a high-impedance connection very near to the
source. A small capacitance could do, with a high impedance device.
Simple capacitive coupling can be had with a *gimmick*; a technique used since
the 1920s. This may be several turns of THHN around the large-gage insulated
incoming line. Since the voltage is with respect to neutral, and neutral is
bonded to ground, just the one wire is needed to get a *sample*. No need to mess
with live conductors, just coupling to the electric field through the insulation
already present. Installation still has some risk, but much less.

With access to this signal, a circuit can be built to detect the difference
between having AC and not having AC, providing a signal to indicate that state.
The signal provided to the generator-operator could be a lamp or buzzer.  

