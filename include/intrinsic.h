#pragma once

#include <string.h>
#include "utils/huff.h"
#include "utils/filesys.h"

extern char dateout[16];
extern char timeout[20];
extern const char* commands[];
extern int noCmds;

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _WIN32
#include "utils/filesys.h"
#endif
#include "utils/huff.h"
#include "simple_strlib.h"

#ifdef __cplusplus
extern "C" {
#endif

int help(char*);
int find_help_section(char*);

#ifdef __cplusplus
}
#endif

