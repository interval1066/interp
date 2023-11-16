# Building interp on Windows

I configured this project with Visual Studio 2022, I hope you have few problems, I've been noticing
over the last few years Microsoft has been pretty good about making visual studio projects back rev
compatible, if you have problems would love ot hear about them, send reports to
interval1066@gmail.com.

1) Make sure your have vcpkg installed and configured for your visual studio environment.

2) Use vcpkg to install libconfig.

3) Start developing your shell.

That's it. If you'd prefer not to use vcpkg you'll need to download libconfig from
http://hyperrealm.github.io/libconfig/, build it, install it, and copy libconfig.lib & libconfig.h
into the "extra" folder in the interp source tree.

Refer to the libconfig license for how you can distribute with your interp-based
Windows application, I don't think its very restrictive.
