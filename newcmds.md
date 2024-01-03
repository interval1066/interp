### Adding New Commands to the Interpreter

<p>The code consists of intrinsic commands and add-on commands. Intrinsic commands shouldn't be modified
or expanded. As of now there's really only one intrinsic command, `help` that prints the list of all
the commands and details each command when fed as a parameter.</p>
<p>Add-on commands are all the other commands you can see in the "foo1" source file. Add-ons can be added to
those existing sources, added to an entirely new translation unit, to a static library or a shared lib, whatever
makes the most sense for your application. You're also welcome to remove all of those commands and add your own, of course.</p>

#### Adding a Log Level Command

<p>In this example, we'll add a new command called `loglevel` that will set the logging level of the of the
interpreter. There are lots of descisions to make in developing a loggng facility to an application; mostly
its scope, where it'll be written and its persistence, but since we won't actually implement a working logging
facility we'll just worry about adding the command to the interpreter.</p>

<p>Let's add the command "loglevel" with an integer parameter 0-4. 0 will mean logging off, and 4 is the highest
level of verbosity:</p>

1. Add our new command "loglevel" to the "commands" double array in the "parser.h" file. The question mark must be the last command in the array:
 ``` c
 const char* commands[] = {  "aaa",
                             "access-lists",
                             "amplifiers",
                             "app",
                             <...>
                             "loglevel",
                             "?" };
```
2. Add a "loglevel" token to the "table" double array. Note, this is just a numeric token, not a string.
Importance is its place in the table, not its value:
``` c
int (*table[])() = {
    aaa, alist, amp, app, arp, badl, batch, bert, help, motd, prompt, quit, date, list, time2, loglevel
};
```
3. For statically linked commands define the function(s) for your new command in either foo1.c or add a new source file to the project. Add the new function prototypes to the appropriate header files. Use a pointer to the command invocation for access to parameters and delimeter processing; for example; if you want to use posix-style parameter marking ('-' & '--', and etc) define that in your new translation unit and pass all paramters through it before routing to the actual command definition. Look to the command examples in foo1.c for examples.

4. Add a useful description of the new command the help file.

No modification of the parser code should be required for the UTF-8 charcter set-based projects. If you do see a problem a report would be appreciated. interval1066@gmail.com.
