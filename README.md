ASED
=========
Ancillary Service Electric Detector

This is written within web using C99. Web is Literate Programming as
created by Donald Knuth. The program cweb creates C source, from the web
source, for use strictly by the compiler. The program cweave builds a TeX
source file for further processing by TeX or PDFTeX into a nice document.
  
This does not use Wiring and for this reason it will compile using the
gnu compiler, arv-gcc along with avr-libc.
It will also compile in the Arduino IDE as a "Sketch."

This is the firmware portion of an Ancillary Service Electric Detector or ASED.

With my emergency generator connected through an interlocked load-center,
it's hard to tell when the |Ancillary Service| has been restored.
The neighbor's lights offer a clue at night, but aren't reliable.
Switching back to Main, from the genny, requires shutting  everything down
for a moment. It would be good to know if main, or Ancillary Service, is live
before switching back to it.

The obvious method is to measure the voltage at the main-breaker's input, using
a meter. One safety concern is that it's not breaker-protected making for a
massive fault-current, should insulation be breached or the circuit shorted.
Also, installation of a simple meter is somewhat involved, having to tap into
live lines and, ideally, providing some form of isolation.

The obvious solution is to have a high-impedance connection very near to the
source. A small capacitance would do. Simple capacitive coupling can be had
with a ``gimmick''; a technique used since the 1920s. This may be several turns
of THHN around the large-gage insulated incomming line. Since the voltage is
with respect to neutral, and neutral is bonded to ground, just the one wire is
needed to get a ``sample''. No need to mess with live conductors, just coupling
to the electric field through the insulation already present. Installation
still has some risk, but much less. This is still not Double insulated, so
whatever gizmo is connected should provide an additional level of protection,
but it's better than a copper connection.

With access to this signal, a circuit can be built to detect the difference
between having AC and not having AC, providing a signal to indicate that state.
The signal provided to the generator-operator could be a lamp or buzzer.

I have seven Ada Fruit Trinkets just laying around. They use the Atmel 
ATTINY85 processor. The analog inputs are about 100 M ohms. Not great, but
I think it should be good enough. 
