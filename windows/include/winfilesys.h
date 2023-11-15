#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <locale.h>
#include <Shlobj.h>
#include <io.h>
#include "support.h"
#include "simple_strlib.h"
#include "libconfig.h"

#define F_OK 0
#define access _access

static LPCSTR sk = "SOFTWARE\\Spooge\\blah\\poop";
PHKEY hk;
char str_data[36];

bool file_exists(const char*);

int find_cfgfile(const char*, char*, bool);
int create_cfgfile(const char*);
void get_userdir(char*);

int read_motd(const char*);
const char* get_keyvalue(const char*, const char*);
int set_keyvalue(const char*, const char*);
