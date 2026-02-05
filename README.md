# interp
Super simple arbitrary length, "first match", command interpeter for embedded projects in C11. I'm talking SIMPLE configuration, just try it. I'd be surprised if there's a easier to use parser than this one, unless it can be configured without re-compiling.<br><br>"Q", "qu", "qUi" (case insensitive and normalized to lower case), and "quit" will all exit the interpreter, for example. Generates its own menu, super light, and highly portable. Only depends on libconfig, and even that can be removed with little effort. See the "newcmds" markdown file for info on customizing and adding new commands.

Have been getting a lot of positive reviews; as I said its VERY flexible and parses a treat with very little code. Needs more testing, but so far
I'm seeing that the first match action on this is great; say you have a command "get door". If both get and door are registered as a command and a parameter "g d" works fine, as long as they appear first in the command/parameter list. If not then again, next match. If "gummy door" is next in the list it will pick that up. Try it!

Quick little update: I've successfully built this on Linux, Windows, and ARM based Linux. ALso, and I can't believe I haven't added this before; this is written in C11 as it was originally written for a device that had no C++ compiler. I also thought it might be a little more portable if it was in linear C.

(10/17/2024) Finally removed the dependancy on libconfig.<br>
(10/20/2024) Code now handles back spaces on Windows.


