# interp
Simple command interpeter for embedded projects in C. I needed to re-write a very badly written command shell for an internet appliance once. Too bad that company elected not to use it; "would cost to much to replace." Bad idea and I hope you're not using that product, it was a security nightmare. Also, for various technical reasons, this had to be written in linear C, not C++. Which is not really a bad way to go with some embedded platforms.

Although by no means useful as is, the design is really quite modular and loosely coupled; adding new commands to this is a simple matter of adding them to "commands" and "table" static members of the main module<sup>1</sup>, then adding their definitions to either the "foo1" translation unit or a completely new one, just add the new files with your functionality defined in them.

The "huff" module is a simple huffman encryption C implementation you can use to encrypt plain text, like the message of the day included example command. Use it to do just that or maybe a list of passwords or whatever, or completly remove it and make the app even smaller. Warning: its just that; a simple huffman encoding implementaion. Please use AES or something like that for really sensitive data. Its meant soley as a way to make non-critical data readable only through the app.

Action is a first match, arbitrary length thing; q, qu, and qui will all "quit" the interpreter, but quib will not. The logic that implements this is tiny (pretty terse pointer magic) and all contained in the main module<sup>1</sup> (but not in the main function, there's like two or three static functions in the main module that handle all this. It shouldn't be a huge climb to follow. That same magic extends to commands as parameters to the help module; simply typing "h a" will return info on the arp command, simply being entered into the "commands" and "table" tables is snough to have the application treat them like any other command.

As is the code compiles down to under 35K bytes<sup>3</sup>, filled out with some actually useful commands, stripped release, and an embedded clib, I figure you can have a board that can do things via this interpreter for well under 100KB or possibly less if you really watch your memory usage.

Builds its own command menu automgically, no need to update that. Detailed descriptions will need updating in extra/interp.hlp however. Rename to your actual application name and place in the $USER home directory.

Autoconf automatically provides an "install" command but there's no point in installing this. I'm going to remove the autoconf directive. You are welcome to use the autoconf install command if you want but its really kind of pointless. I would add that in your own finished package that uses this code.

As well as typical scripts for autotools there's a qtcreator project file and a visual studio 2022 project configuration just for fun.

Builds an ARMhf 32 bit target using the generic makefile in the linux subdirectory as long as you have the GCC ARMhf compiler installed on your system, 
can probably target other platforms using GCC or LLVM.

To initiate an autotools build just run autogen.sh and follow the instructions, make sure that the execute bit is set on the automake and clean scripts. To build using the qtcreator project file load the project and select your build kit of choice. To build on Windows you'll need to reconfigure the project for your Win SDK, obviously. I'm on visual studio 2022, so you may need to create a project for your version and add the source modules manually. For visual studio code I have no idea, I rarely use that ide. For eclipse? Lift the voodoo curse off yourself and stop using it, you know that thing was originally written by IBM??

autoclean.sh should reset the entire source directory to the "ground state." See "newcmds.md" for instruction on adding commands to the interpreter. Take special note
of the user context struct, its key for makeing changes to the shell's environment without needing to re-start it.

Again, and probably can't be stressed enough; this project is a "starter" project for your own command line processor engine or shell utiity; the included commands in the foo1 source are just examples; all of them need to be replaced with your required functionality and the extra/interp.help updated with actual descriptions of your new commands. MAKE INSTALL will do NOTHING USEFUL, but you can use it if for some reason you must. Never the less this is fully functioning code (the foo commands don't do anything though, not really) I simply consider it bad form to provide broken example code. That said, there maybe be some "slightly" broken code here and there. Pleaase write me about it or submit your own patch if you like.

Depends on libconfig, barely. Can be easily removed if needed.

7/12/2024 Fixed flaw with the help code.
---
1. The code now counts the number of members in the table static global member automatically, no need for this constant anymore. Also, the "commands" & "table" structs have been moved to include/parser.h.<br>
2. This has been eliminated in subsequent versions.
3. Under 25K on windows.

9/11/2024 Uncovered some serious issues
---
Turns out libconfig sucks. You can't put arbitrary characters in the ini files, it either needs to have legitmate alphanumeric characters or no file. If it encounters, say stars or hashbangs it spews core. Unacceptable. So I'm going back to my original idea of writing my own ini parser. When I can. Really busy right now.

10/26/2024 Removed the libconfig dependancy
---
Got the above done.
