#pragma once
#pragma warning( push )
#pragma warning( disable : 5945 )

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

typedef int (*command_object)(char*);

struct uinfo {
    struct passwd* info;
};

struct user_ctx
{
    int loglevel;
    bool admin;
	char prompt[16];
};

#pragma warning( pop )