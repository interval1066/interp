#pragma once

#include <stdio.h>
#include "help.h"

/**
 * Internal objects ONLY
 */
#define MAXMOTD 512
#define MAXCMDS 15
#define MAXBUF 256

#ifndef SIZEARRAY
#define SIZEARRAY(a)  (sizeof(a) / sizeof((a)[0]))
#endif

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

typedef enum
{
    CMD_INITNF          = -9,
    CMD_HELPERR         = -8,
    CMD_QUOTES          = -7,
    CMD_IOERR           = -6,
    CMD_BANNERPTH       = -5,
    CMD_FILEEXST        = -4,
    CMD_FILENF          = -3,
    CMD_ARGS            = -2,
    CMD_ERR             = -1,
    CMD_OK              = 0,
	CMD_QUIT			= 1
} STATUS_CODE;

typedef int (*command_object)(char*);

struct uinfo {
    struct passwd* info;
};
