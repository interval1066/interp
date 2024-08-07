# interp
Super simple arbitrary length, "first match", command interpeter for embedded projects in C11.<br><br>"Q", "qu", "qUi" (case insensitive and normalized to lower case), and "quit" will all exit the interpreter, for example. Generates its own menu, super light, and highly portable. Only depends on libconfig, and even that can be removed with little effort. See the "newcmds" markdown file for info on customizing and adding new commands.

Have been getting a lot of positive reviews; as I said its VERY flexible and parses a treat with very little code. Needs more testing, but so far
I'm seeing that the first match action on this is great; say you have a command "get door". If both get and door are registered as a command and a parameter "g d" works fine, as long as they appear first in the command/parameter list. If not then again, next match. If "gummy door" is next in the list it will pick that up. Try it!
