#pragma once

#include <stdio.h>

const char* error_strings[] = { "Couldn't allocate needed memory",
                                "Init file not found",
                                "Help file not found",
                                "Argument needs quotes",
                                "IO Error",
                                "Argument is missing path",
                                "File exists",
                                "File not found",
                                "Bad arguments",
                                "There was a general error" };

#ifdef __cplusplus
extern "C"{
#endif

static void
GetErrorStr(int n)
{

}

#ifdef __cplusplus
}
#endif
