#pragma once

#define MAINKEY "SOFTWARE"
#define SUBKEY	"New World Computing"
#define SUBKEY2	"Might and Magic VII"
#define VERKEY	"1.0"

int __fastcall ReadWindowsRegistryInt(const char*, int);
void __fastcall WriteWindowsRegistryString(const char*, const char*);
void __fastcall ReadWindowsRegistryString(const char*, char*, int, const char*);
void __fastcall WriteWindowsRegistryInt(const char*, int);
