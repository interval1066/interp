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

#ifdef __cplusplus
extern "C"{
#endif

typedef int (*command_object)(char*);

struct uinfo {
    struct passwd* info;
};

struct user_ctx {
    int loglevel;
    bool admin;
	char prompt[16];
};

#ifdef __cplusplus
}
#endif
