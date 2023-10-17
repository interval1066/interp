#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

#define SURROGATE_LOW_BITS 0x7FF
#define MAX_SURROGATE     0xDFFF
#define MAX_FOUR_BYTE   0x10FFFF
#define ONE_BYTE_BITS          7
#define TWO_BYTE_BITS         11
#define TWO_BYTE_PREFIX     0xC0
#define THREE_BYTE_BITS       16
#define THREE_BYTE_PREFIX   0xE0
#define FOUR_BYTE_PREFIX    0xF0
#define CONTINUATION_BYTE   0x80
#define CONTINUATION_MASK   0x3F

int find_cfgfile(const char*, char*, bool);
int create_cfgfile(const char*);
void get_userdir(char*);

int read_motd(const char*);
const char* get_value(const char*);
int set_value(const char*, char*);

bool file_exists(char*);
