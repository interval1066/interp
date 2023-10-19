#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

LPCSTR sk = "SOFTWARE\\Spooge\\blah\\poop\\prompt";
PHKEY hk;
char str_data[36];

int find_cfgfile(const char*, char*, bool);
int create_cfgfile(const char*);
void get_userdir(char*);

int read_motd(const char*);
const char* get_value(const char*);
int set_value(const char*, char*);

bool file_exists(char*);
