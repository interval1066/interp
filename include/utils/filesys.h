#pragma once

#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include <support.h>
#include <stdbool.h>
#include <stdio.h>
#include <simple_strlib.h>

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
const char* get_value(const char*);

int set_value(const char*, char*);
bool file_exists(char*);
//int write_config(config_t*, char*);

#ifdef __cplusplus
}
#endif
