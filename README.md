# interp
Simple command interpeter for embedded projects in C. I needed to re-write a very badly written command shell for an internet appliance once. Too bad the company elected not to use it; "would cost to much to replace." Bad idea and I hope you're not using that product, it was a security nightmare.<br>
As well as typical scripts for autotools there's a qtcreator project file and a visual studio 2022 project configuration just for fun.
Coming is a file to explain how to add new commands and a few other things when I can get to them.

If anyone manages to port this to ARM (32, 64, hf, lf, whatever) I'd love to hear from you.

To initiate an autotools build just run autogen.sh and follow the instructions. To build using the qtcreator project file load the project and select your build kit of choice. To build on Windows you'll need to reconfigure the project for your Win SDK, obviously. I'm on visual studio 2022, so you may need to create a project for your version and add the source modules manually. For visual stuido code I have no idea, I rarely use that ide. For eclipse? Lift the voodoo curse off yourself and stop using it, you know that thing was originally written by IBM??
