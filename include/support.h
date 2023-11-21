#pragma once

#include <stdio.h>

/**
 * Internal objects ONLY
 */
#define MAXMOTD 512
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
	CMD_MEMERR			= -10,
	CMD_INITNF			= -9,   // initialization file not found
	CMD_HELPERR			= -8,   // problem with help subsystem
	CMD_QUOTES			= -7,   // argument not enclosed in quotes
	CMD_IOERR			= -6,   // io error
	CMD_BANNERPTH			= -5,   //
	CMD_FILEEXST			= -4,   // file exists
	CMD_FILENF			= -3,   // file not found
	CMD_ARGS			= -2,   // error with command arguments
	CMD_ERR				= -1,   // non-specific error
	CMD_OK				= 0,    // recognized command
	CMD_QUIT				= 1,    // exit application
	CMD_NOOP				= 2     // no operation
} RET_CODE;

typedef int (*command_object)(char*);

struct uinfo {
    struct passwd* info;
};

