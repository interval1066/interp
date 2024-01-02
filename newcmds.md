### Adding new commands to the interpreter
<p>The interpreter has two diccerent classes of commands, those that are custom and those that are 'intrinsic', or not meant to be
  maodified. Currently the only intrinsic command is help.</p>
  
  #### Adding a new command
  Let's add a logging option. This won't be an actual implementation- lots of ways to implement application logging in a linux, could
  be a systemd client or write its file, doesn't matter. All we'll be doing here is adding an on/off switch and levels 1-3 to the parser
  with no functionaliy.
