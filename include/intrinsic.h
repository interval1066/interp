#pragma once

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/filesys.h"
#include "utils/huff.h"

extern char dateout[16];
extern char timeout[20];
extern const char* commands[];
extern int noCmds;

#ifdef __cplusplus
extern "C" {
#endif

int help(char*);
int find_help_section(char*);
int motd(char*);

int prompt(char*);
int quit(char*);

#ifdef __cplusplus
}
#endif

