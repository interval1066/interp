#pragma once

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _WIN32
#include "utils/filesys.h"
#endif
#include "simple_strlib.h"
#include "error_info.h"

#ifdef __cplusplus
extern "C"{
#endif

int dummy(char*);

int aaa(char*);
int alist(char*);
int amp(char*);

int app(char*);
int arp(char*);
int badl(char*);

int batch(char*);
int bert(char*);
int date(char*);

int list(char*);
int time2(char*);
int loglevel(char*);

int filet(char*);

#ifdef __cplusplus
}
#endif

