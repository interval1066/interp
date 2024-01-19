# interp
Simple command interpeter for embedded projects in C. I needed to re-write a very badly written command shell for an internet appliance once. Too bad the company elected not to use it; "would cost to much to replace." Bad idea and I hope you're not using that product, it was a security nightmare. Also, for various technical reasons, this had to be written in linear C, not C++. Which is not really a bad way to go with some embedded platforms.

Although by no means useful as is, the design is really quite modular and loosely coupled; adding new commands to this is a simple matter of adding them to "commands" and "table" static members of the main module<sup>1</sup>, then adding their definitions to either the "foo1" translation unit or a completely new one, just add the new files with your functionality defined in them.

The "huff" module is a simple huffman enryption implementation you can use to encrypt plain text, like the message of the day included example command. I've not implemeted it. I had it implemented in the alpha version I originally wrote just to see it worked they way I wanted it to. Use it to do just that or maybe a list of passwords or whatever, or completly remove it and make the app even smaller. Warning: its just that; a simple huffman encoding implementaion. Please use AES or something like that for really sensitive data. Its meant soley as a was to make non-critical data readable only through the app.

Also update MAXCMDS in support.h.<sup>2</sup> In the near future I'm going to see if I can do away with this magic little number (its actually is just a constant representing the total number of commands but let's do away with it anyway.)

Action is a first match, arbitrary length thing; q, qu, and qui will all "quit" the interpreter, but quib will not. The logic that implements this is tiny and all contained in the main module (but not in the main function, there's like two or three static functions in the main module that handle all this. It shouldn't be a huge climb to follow.)

As is the code compiles down to under 35K bytes<sup>3</sup>, filled out with some actually useful commands, stripped release, and an embedded clib, I figure you can have a board that can do things via this interpreter for well under 100KB or possibly less if you really watch your memory usage.

Builds its own command menu automgically, no need to update that. Detailed descriptions will need updating in extra/interp.hlp however. 

As well as typical scripts for autotools there's a qtcreator project file and a visual studio 2022 project configuration just for fun.
Coming is a file to explain how to add new commands and a few other things when I can get to them.

If anyone manages to port this to ARM (32, 64, hf, lf, whatever) I'd love to hear from you.

To initiate an autotools build just run autogen.sh and follow the instructions, make sure that the execute bit is set on the automake and clean scripts. To build using the qtcreator project file load the project and select your build kit of choice. To build on Windows you'll need to reconfigure the project for your Win SDK, obviously. I'm on visual studio 2022, so you may need to create a project for your version and add the source modules manually. For visual studio code I have no idea, I rarely use that ide. For eclipse? Lift the voodoo curse off yourself and stop using it, you know that thing was originally written by IBM??

autoclean.sh should reset the entire source directory to the "ground state." See "newcmds.md" for instruction on adding commands to the interpreter. There is a user context struct but its not in use in this version.

Depends on libconfig.

Successfully built the code as is on Raspberry Pi using the older but more compatible ARMv6 32 bit insructions.
 
---
1. The code now counts the number of members in the table static global member automatically, no need for this constant anymore. Also, the "commands" & "table" structs have been moved to include/parser.h.<br>
2. This has been eliminated in subsequent versions.
3. Under 20K on windows.

