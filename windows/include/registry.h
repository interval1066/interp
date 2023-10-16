#pragma once

int __fastcall ReadWindowsRegistryInt(const char*, int);
void __fastcall WriteWindowsRegistryString(const char*, const char*);
void __fastcall ReadWindowsRegistryString(const char*, char*, int, const char*);
void __fastcall WriteWindowsRegistryInt(const char*, int);
