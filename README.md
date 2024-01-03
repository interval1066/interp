# interp
Simple command interpeter for embedded projects in C. I needed to re-write a very badly written command shell for an internet appliance once. Too bad the company elected not to use it; "would cost to much to replace." Bad idea and I hope you're not using that product, it was a security nightmare. Also, for various technical reasons, this had to be written in linear C, not C++. Which is not really a bad way to go with some embedded platforms.

Although by no means useful as is, the design is really quite modular and loosely coupled; adding new commands to this is a simple matter of adding them to "commands" and "table" static members of the main module<sup>1</sup>, then adding their definitions to either the "foo1" translation unit or a completely new one, just add the new files with your functionality defined in them.

Also update MAXCMDS in support.h.<sup>2</sup> In the near future I'm going to see if I can do away with this magic little number (its actually is just a constant representing the total number of commands but let's do away with it anyway.)

Action is a first match, arbitrary length thing; q, qu, and qui will all "quit" the interpreter, but quib will not. The logic that implements this is tiny and all contained in the main module (but not in the main function, there's like two or three static functions in the main module that handle all this. It shouldn't be a huge climb to follow.)

As is the code compiles down to under 35K bytes<sup>3</sup>, filled out with some actually useful commands, stripped release, and an embedded clib, I figure you can have a board that can do things via this interpreter for well under 100KB or possibly less if you really watch your memory usage.

As well as typical scripts for autotools there's a qtcreator project file and a visual studio 2022 project configuration just for fun.
Coming is a file to explain how to add new commands and a few other things when I can get to them.

If anyone manages to port this to ARM (32, 64, hf, lf, whatever) I'd love to hear from you.

To initiate an autotools build just run autogen.sh and follow the instructions, make sure that the execute bit is set on the automake and clean scripts. To build using the qtcreator project file load the project and select your build kit of choice. To build on Windows you'll need to reconfigure the project for your Win SDK, obviously. I'm on visual studio 2022, so you may need to create a project for your version and add the source modules manually. For visual studio code I have no idea, I rarely use that ide. For eclipse? Lift the voodoo curse off yourself and stop using it, you know that thing was originally written by IBM??

autoclean.sh should reset the entire source directory to the "ground state." See "newcmds.md" for instruction on adding commands to the interpreter. There is a user context struct but its not in use in this version.

Depends on libconfig.

Stand by for my port to Raspberry PI, working on it now.
 
---
1. The code now counts the number of members in the table static global member automatically, no need for this constant anymore.<br>
2. This has been eliminated in subsequent versions.
3. Under 20K on windows.

