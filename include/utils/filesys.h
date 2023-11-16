#pragma once

#include <sys/types.h>
#include <stdlib.h>
#include <utils/filesys.h>
#include <sys/stat.h>
#include <libconfig.h>
#include <stdbool.h>
#include <stdio.h>
#ifndef _MSC_VER
#include <pwd.h>
#include <unistd.h>
#else
#include <io.h>
#include <Shlobj.h>
#endif
#include "support.h"
#include "simple_strlib.h"


#define MAXSIZE 256

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file    filesys.h
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief System-specific & near system-specific utilities
 *
 * @section DESCRIPTION
 *
 * Collection of functions that will be more system specific
 * and non-portable (mostly file systems utils and such).
 */
int find_cfgfile(const char*, char*, bool);
int create_cfgfile(const char*);
void get_userdir(char*);

int write_motd(char*, const char*);
int read_motd(const char*);
const char* get_keyvalue(const char*, const char*);

int set_keyvalue(const char*, const char*);
bool file_exists(const char*);
//int write_config(config_t*, char*);

#ifdef __cplusplus
}
#endif
