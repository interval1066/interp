#pragma once

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/filesys.h"

extern char dateout[16];
extern char timeout[20];
extern const char* commands[];
extern int noCmds;

#ifdef __cplusplus
extern "C" {
#endif

int help(char*);
int find_help_section(char*);

#ifdef __cplusplus
}
#endif

