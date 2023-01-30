# interp
Simple command interpeter for embedded projects in C. Several reasons for this; I wrote this as a replacement for a cpu that was a micronized PDP 10 machine that was the driver for an internet applicance, won't say which one, think of it as a Cisco-like router. The C compiler was ported from GCC, but the company only put as much effort into it to have it emit MACRO 10 (Digital's assembly language for PDP 10's) from compiling C, a full C++ implementations was too expensive and not considered nessessary I guess.

The command shell for this applicance was crap; long chains of if-then-else statements, like it was written by high school students. I set out to re-write the shell (or interpreter) using proper C module paradigms like pointer tables and so on. The result can ba a little hard to follow but is much simpler  to use, and rsults in a much smaller comiled image. Its very easy to add new coommands to it, the parsing fcuntionality is already there and doesn't need to be modified in anyway. The new commands simply need to be added to the structures in the commands.h file, and the functionality added to foo.c.

I'm developing it using qt creator so some qt ide meta files are included, will probably work for most. You'll also need to add libconfig to your development machine with your distro's package manager.

The help file reader method needs work right now. CHanging it from a line reader to a characer reader.
