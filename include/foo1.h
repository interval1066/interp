#pragma once

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef _WIN32
#include "utils/filesys.h"
#endif
#include "utils/huff.h"
#include "support.h"
#include "simple_strlib.h"
#include "help.h"

const char* commands[] = {  "aaa",
                            "access-lists",
                            "amplifiers",
                            "app",
                            "arp",
                            "badl",
                            "batch",
                            "bert",
                            "help",
                            "motd",
                            "prompt",
                            "quit",
                            "date",
                            "lists",
                            "time",
                            "?" };
