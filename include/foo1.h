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

int dummy(const char*);

int aaa(const char*);
int alist(const char*);
int amp(const char*);

int app(const char*);
int arp(const char*);
int badl(const char*);

int batch(const char*);
int bert(const char*);
int date(const char*);

int list(const char*);
int time2(const char*);
int loglevel(const char*);

int filet(const char*);

#ifdef __cplusplus
}
#endif

