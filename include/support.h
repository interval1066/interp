#pragma once

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 5945 )
#include <conio.h>
#define GETCH _getch
#else
#include <termios.h>
#define GETCH getch
#endif

#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif

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
//typedef enum {false, true} bool;

struct uinfo {
    struct passwd* info;
};

struct user_ctx
{
    int loglevel;
    bool admin;
    char prompt[16];
};

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma warning( pop )
#endif

