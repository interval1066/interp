#pragma once

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _WIN32
#include "utils/filesys.h"
#endif
#include "utils/huff.h"
//#include "support.h"
#include "simple_strlib.h"

int find_help_section(char*);
int aaa(char*);
int alist(char*);

int amp(char*);
int app(char*);
int arp(char*);

int badl(char*);
int batch(char*);
int bert(char*);

int help(char*);
int motd(char*);
int prompt(char*);

int quit(char*);
int date(char*);
int list(char*);

int time2(char*);
int loglevel(char*);
