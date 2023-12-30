#pragma once
#ifdef _MSVC_VER
#include <winunistd.h>
#endif

/**
 * @file			simple_strlib.h
 * @brief           Some additions that seem to be missing or
 *					are missing from the clib port.
 *
 *	@details		We've rolled our own string functions, they
 *					were either missing or I didn't like the way
 *					they worked. (I tend to favor in-place string
 *					manips for embedded work.) Needs to be tested
 *					for thread safety.
 *
 * @author          t.o.
 * @bug
 */

#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#ifndef _WIN32
#include <sys/param.h>
#endif
//#include "support.h"

/**
 * @brief		strlwr
 *
 * @details		My own version of strlwr, becuase clib
 * 				doesn't appear to have one.
 *
 * @param		s The string to convert
 * @return		pointer to the modified string
 */
inline char*
strlwr(char* s)
{
    char* p = (char*)s;

    while(*p) {
        *p = tolower((uint8_t)*p);
        p++;
    }
    return s;
}

/**
 * @brief		countc
 *
 * @details     Count the number of occurrences of c in s
 *
 * @param		s The target string
 * @param		c The character to count
 * @return		the count
 */
static inline int
countc(const char* s, char c)
{
    int n = 0;

    while(*s++ != '\0') {
        if(*s == c)
            n++;
    }
    return n;
}

/**
 * @brief		Strip trailing whitespace from s inplace
 *
 * @param		s The string to trim
 * @return 		the modified string
 */
inline const char*
strstrip(char* s)
{
    size_t size = strlen(s);
    if (!size)
        return s;

    char* end;
    end = s + size - 1;
    while(end >= s && isspace(*end))
        end--;

    *(end + 1) = '\0';
    while(*s && isspace(*s))
        s++;

    return s;
}

/**
 * @brief		Split the string at delimiters using a zero-copy in-place algorithm
 *
 * @param		s The string to split (every delimiter will be replaced by NULL)
 * @param		delimiter The delimiter character to split at
 * @param		size The size of the return array w
 * @return		A list of char* (size stored in *size), pointing to all split results in order
 *				don't forget to free the returned array in the caller
 */
static inline char**
split(char* s, char delimiter, int* size)
{
    int numdelimiters = countc((const char*)s, delimiter);
    char** splitresult = (char**)malloc((numdelimiters + 1) * sizeof(char*));

    splitresult[0] = s;
    int i = 1;
    char* hit = s;

    while((hit = strchr(hit, delimiter)) != NULL) {
        *hit++ = '\0';
        splitresult[i++] = hit;
    }
    *size = numdelimiters + 1;

    return splitresult;
}

/**
 * @breif		Remove the substring matched. Operates
 *					in-place.
 *
 * @param		the string to operate on
 * @param		the character sequence to remove
 */
static inline void
remove_first(char* str, const char* str_remove)
{
    size_t i, j, len, remove_len;
    int found = 0;

    len = strlen(str);
    remove_len = strlen(str_remove);

    for(i = 0; i < len; i++) {
        found = 1;
        for(j = 0; j < remove_len; j++) {
            if(*(str + i + j) != *(str_remove + j)) {
                found = 0;
                break;
            }
        }
        // If word has been found then remove it by shifting characters
        if(found == 1) {
            for(j = i; j <= len - remove_len; j++)
                *(str + j) = *(str + j + remove_len);

            // Terminate from loop so only first occurrence is removed
            break;
        }
    }
}

/**
 * @brief		find first index of character in string
 *
 * @param		string string to operate on
 * @param		char char to find index of
 * @return		integer index of the first occurance of char
 */
static inline int
find_ch_index(const char* string, char ch)
{
    int i = 0;

    while(*(string + i) && *(string + i) != ch) i++;

    return *(string + i) == ch ? -1 : i;
}

/**
 * @brief		pass a substring of the source string through an i/o parameter
 *
 * @param		char pointer source string
 * @param		start index of starting character for subsctring in source
 * @param		length of source string
 * @param		char pointer to destination string buffer
 * @param		length of destination string buffer
 */
static inline void
mid(const char* src, size_t start, size_t length, char* dst, size_t dstlen)
{
    //size_t len = MIN(dstlen - 1, length);
	size_t len = MIN(dstlen, length);

    strncpy(dst, src + start, len);
    // zero terminate because strncpy() didn't ?
    if(len < length)
        dst[dstlen - 1] = 0;
}

static char*
right(char* string, int size)
{
    while(*string++);

    return(string - size - 2);
}

static char*
replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

