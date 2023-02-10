# interp
Simple command interpeter for embedded projects in C. Several reasons for this; I wrote this as a replacement for a cpu that was a micronized PDP 10 machine that was the driver for an internet applicance, won't say which one, think of it as a Cisco-like router. The C compiler was ported from GCC, but the company only put as much effort into it to have it emit MACRO 10 (Digital's assembly language for PDP 10's) from compiling C, a full C++ implementations was too expensive and not considered nessessary I guess. As such; requires ISO/IEC 9899:1999 (C99).

The command shell for this applicance was crap; long chains of if-then-else statements, like it was written by high school students. I set out to re-write the shell (or interpreter) using proper C module paradigms like pointer tables and so on. The result can be a little hard to follow but is much simpler to use, and results in a much smaller compiled image. Its very easy to add new commands to it, the parsing functionality is already there and doesn't need to be modified in anyway. The new commands simply need to be added to the structures in the commands.h file, and the functionality added to foo.c, or new translation units, new unit modules are probably the preferred method. This is just a demo.

Commands are arbitrary; there's no such thing as a "bert" device, was the first thing that came into my head while writing it. I also favor how commands are parsed in this; its a first match system. "quit" for example will work with "q", "qu", "qui", and so on, and will work with any new command added, no algorithmic changes are needed. Just read and follow the code. I'll add an instructional readme when I can. I promise, it works really well, better than I thought when I first wrote it.

I'm developing it using qt creator so some qt ide meta files are included, will probably work for most. You'll also need to add libconfig to your development machine with your distro's package manager; HOWEVER, just typing "make" should result in a debug version of the project. If you want to make a release version just type "make optim". QT Creator should do the same thing, including producing a stripped exectable image.

Porting this to ARM shouldn't be a huge climb either. If there is a problem doing this I'd appreciate a note. It also compiles into very small code as is, under 35K. Obviously adding more comprehensive commands is going to increase the size, but probably not by much. I would add really comprehensive commands that require heavy computing power to the framework as shared libs or static libs. Not that will keep the size small, but will make it more manageable. Never the less, the framework can be kept to a really managable size using logical architechtecture choices, in my opinion. Give me your thoughts!

The help file reader method needs work right now. Changing it from a line reader to a characer reader. Also still to do is add an error handler. All (90%) of the methods return an error code, the intention is to have the error code interpreted by a top-level (presentation, or "UI" level) module.

Also should change all integer, longs, chars, and so on to fixed sized numbers out of stdint.h. The Huffman module is included so that one can encrypt the Message of the Day file, and any other file if one wanted, and it does work. Right now I'm concentrated on getting the main functionality working. Will add encrypting any text file later. Also; input needs scrubbing. Haven't had time to have the code check for bad or nefarious input.

I'm a little impressed with myself that within 10 days of comitting this code over 35 people cloned it. Must be a need for something like this.

In my install I'm putting all the meta files (.hlp, .ini, motd) in the user's home directory as dot files. I'll try to make this more flexible, but this will involve creating a more involved install procedure and that may mean writing a more comprehensive make file, or a bash script, not sure what and not really worried about it until I get near the end of development.

That makefile is pretty generic; if you stick to separating header files in "include" and imple files into "src" it should work for any project pretty much. Hope you find this project useful.

Any and all comments would really be appreciated, send to interval1066@gmail.com, and thanks.
