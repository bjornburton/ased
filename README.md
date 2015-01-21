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
using the gnu compiler, arv-gcc along with avr-libc. It should also compile in
the Arduino IDE as a "Sketch", with some modification. An issue with the
Arduino IDE is that the modern C99/C11 way of using a designator to initialize
structure components does not work.  A Second issue is that the IDE mucks around
with the order of the code, putting function declarations ahead of typedefs. (It
looks intentional, but I can't understand why it would do that.) Since the IDE
is generally weak, error/warning reporting is poor, documentation is lacking,
 strange workarounds are needed for many things and it adds a layer of
complexity and uncertainty, I won't pursue it. 


There is a simple Makefile to build it with, but it may need to be tweaked to
suit you system. You will need cweave, ctangle, avr-gcc as well as pdftex, if
you want nice documentation. 

* The Fun Reason
Firstly, I wrote this for fun and not out of any real need. I wanted to learn a bit about git's branching, merging, refspec, etc. Also to brush-up on my C-skills, poor as they are. Programming on bare-metal (no OS) and on a tiny microprocessor to boot, are firsts for me. And I've been wanting to try Literate Programming in Donald Knuth's Cweb, just to see what it's like. 

* Practical Reason:
With my emergency generator connected through an interlocked load-center, it's
hard to tell when the Ancillary Service has been restored. The neighbor's
lights offer a clue at night, but aren't reliable. Switching back to Main, from
the genny, requires shutting everything off for a moment. It would be good to
know if main, or Ancillary Service, is live before switching back to it.

The obvious method is to measure the voltage at the main-breaker's input, using
a meter. One safety concern is that it's not breaker-protected making for a
massive fault-current, should insulation be breached or the circuit shorted.
Also, installation of a simple meter is somewhat involved, having to tap into
live lines and, ideally, providing some form of isolation. The obvious solution
is to have a high-impedance connection very near to the source. A small
capacitance would do. Simple capacitive coupling can be had with a "gimmick"; a
technique used since the 1920s. This may be several turns of THHN around the
large-gage insulated incoming line. Since the voltage is with respect to
neutral, and neutral is bonded to ground, just the one wire is needed to get a
"sample". No need to mess with live conductors, just coupling to the electric
field through the insulation already present. Installation still has some risk,
but much less. This is still not Double insulated, so whatever gizmo is
connected should provide an additional level of protection, but it's better
than a copper connection.

With access to this signal, a circuit can be built to detect the difference
between having AC and not having AC, providing a signal to indicate that state.
The signal provided to the generator-operator could be a lamp or buzzer.  

I have seven Ada Fruit Trinkets just laying around. They use the Atmel ATTINY85
processor. The analog inputs are about 100 M ohms. Not great, but I think it
should be good enough. 

