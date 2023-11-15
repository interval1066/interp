# Building interp on Windows

I configured this project with Visual Studio 2022, I hope you have few problems, I've been noticing
over the last few years Microsoft has been pretty good about making visual studio projects back rev
compatible, if you have problems would love ot hear about them, send reports to
interval1066@gmail.com.

1) Build libconfig using one of the visual studio project files it comes with.

2) Copy the appropriate libconfig header and lib files for your project into
	interp/extra; interp's default project configuration anticipates
	libconfig.h/...++.h & .lib files existing in $(ProjectDir)..\extra,
	modify the project macro "$(InterpExtra)" to point into any directory
	on your build system that contains the header and lib files.

Refer to the libconfig license for how you can distribute with your interp-based
Windows application, I don't think its very restrictive.
