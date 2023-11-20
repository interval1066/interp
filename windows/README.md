# Building interp on Windows

I configured this project with Visual Studio 2023, I hope you have few problems, I've been noticing
over the last few years Microsoft has been pretty good about making visual studio projects back rev
compatible, if you have problems would love to hear about them, send reports to
interval1066@gmail.com.

If you haven't done it yet configure vcpkg to work with vs2023 or your preferred version of VS, I
understand versions after 2017 can do this with varying degrees of success.

Follow the instructions here for installation and configuration of vcpckg:
https://devblogs.microsoft.com/cppblog/vcpkg-is-now-included-with-visual-studio/

After issuing "vcpkg integrate install" and restarting visual studio install libconfig:

D:\blap\dorp\blop> vcpkg install libconfig:x64-windows

That should be all you need to do. In visual studio look at the include list in filesys.h; line
7 should be the include for linconfig.h. If its not underlined then the project is probably
ready to build.
