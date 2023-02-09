# interp
Simple command interpeter for embedded projects in C. Several reasons for this; I wrote this as a replacement for a cpu that was a micronized PDP 10 machine that was the driver for an internet applicance, won't say which one, think of it as a Cisco-like router. The C compiler was ported from GCC, but the company only put as much effort into it to have it emit MACRO 10 (Digital's assembly language for PDP 10's) from compiling C, a full C++ implementations was too expensive and not considered nessessary I guess.

The command shell for this applicance was crap; long chains of if-then-else statements, like it was written by high school students. I set out to re-write the shell (or interpreter) using proper C module paradigms like pointer tables and so on. The result can be a little hard to follow but is much simpler to use, and results in a much smaller compiled image. Its very easy to add new commands to it, the parsing fucntionality is already there and doesn't need to be modified in anyway. The new commands simply need to be added to the structures in the commands.h file, and the functionality added to foo.c, or new translation units, wouldn't be hard.

Commands are arbitraty; there's no such thing as a "bert" device, was the first thing that came into my head while writing it. I also favor how commands are parsed in this; its a first match system. "quit" for example will work with "q", "qu", "qui", and so on, and will work with any new command added, no algorithmic changes are needed. Just read and follow the code. I'll add an instructional readme when I can. I promise, it works really well, better than I thought when I wrote it.

I'm developing it using qt creator so some qt ide meta files are included, will probably work for most. You'll also need to add libconfig to your development machine with your distro's package manager; HOWEVER, just typing "make" should result in a debug version of the project. If you want to make a release version just type "make optim". QT Creator should do the same thing, including producing a stripped exectable image.

Porting this to ARM shouldn't be a huge clime either. If there is a problem doing this I'd appreciate a note.


The help file reader method needs work right now. Changing it from a line reader to a characer reader. Also still to do is add an error handler. All (90%) of the methods return an error code, the intention is to have the error code interpreted by a top-level (presentation, or "UI" level) module.

Also should change all integer, longs, chars, and so on to fixed size numbers out of stdint.h.

I'm a little impressed with myself that within 10 days of comitting this code over 35 people cloned it. Must be a need for something like this.
