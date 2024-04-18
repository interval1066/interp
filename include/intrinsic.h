#pragma once

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils/filesys.h"
#include "utils/huff.h"
#include "error_info.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4090 )
#pragma warning( disable : 594 )
#pragma warning( disable : 542 )
#endif

extern const char dateout[16];
extern const char timeout[20];
extern const char* commands[];
extern const int noCmds;

#ifdef __cplusplus
extern "C" {
#endif

int help(const char*);
int find_help_section(const char*);
int motd(const char*);

int prompt(const char*);
int quit(const char*);

#ifdef _MSC_VER
#pragma warning ( pop )
#endif

#ifdef __cplusplus
}
#endif

