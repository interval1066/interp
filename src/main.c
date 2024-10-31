#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include "utils/config.h"
#include "intrinsic.h"
#include "support.h"
#include "parser.h"
#include "error_info.h"
#include "logger.h"

extern const int noCmds;
extern int help(const char*);
extern int StartLogger(int);
extern bool proc_cmds(char**, int);
struct user_ctx user;
char str[1024];

#define MAX_LINE 1024

/**
 * @file    main.c
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief	Probably pretty portable CLI interpreter
 *
 * @section	DESCRIPTION test
 *
 * Alternate command line interpreter prototype.
 */

/**
 * Anticipate ctrl + c
 *
 * no signals we need to handle as far as we
 * know right now. May change in the future.
 */
void
sig_handler(int sign)
{
    signal(SIGINT, sig_handler);
}

/**
* buffer sanitizer, on hold for now
*/
static int
sanitize_buf()
{
    static char ok_chars[] = "abcdefghijklmnopqrstuvwxyz"
                             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                             "1234567890_-.@";

    char user_data[] = "Bad char 1:} Bad char 2:{";
    char *cp = user_data; // Cursor into string
    const char *end = user_data + strlen(user_data);

    for (cp += strspn(cp, ok_chars); cp != end; cp += strspn(cp, ok_chars))
        *cp = '_';

    return CMD_OK;
}

static void
reverse(char s[])
{
    size_t i, j;
    char c;

    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static void
myitoa(int n, char s[])
{
    size_t i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

/**
 * initial state
 *
 * set defaults including prompt which is a "> " (greater than + space), can be changed
 * via the 'prompt' intrinsic command.
 */
static int
init(void)
{
    char tmp[16] = { 0 };
    memset(user.prompt, 0, sizeof(user.prompt));
    strcpy(tmp, get_keyvalue("prompt", ""));

    if(strlen(tmp) == 0)
        strcpy(tmp, get_keyvalue("prompt", ">"));

#ifndef _MSC_VER
    int len2 = (int)strlen(tmp);
    tmp[len2 - 1] = '\0';
#endif
    char banner_path[MAXBUF];
    char cfg_path[MAXBUF];
    signal(SIGINT, sig_handler);
    memset(cfg_path, 0, sizeof(cfg_path));

    memset(banner_path, 0, sizeof(banner_path));
    get_userdir(cfg_path);
    strcpy(banner_path, cfg_path);

#ifndef _MSC_VER
    strcat(banner_path, "/.motd");
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(banner_path, "\\.motd");
    strcat(cfg_path, "\\.interp.ini");
#endif

    if (access(banner_path, 0) == 0) {
        decode(banner_path);
        printf("\n");
    }
    return CMD_OK;
}

static int
readconfig(void)
{
    user.admin = 0;
    char adminperm[10] = { 0 };
    char cfg_path[MAXBUF] = { 0 };

    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif
    ini_table_s* config = ini_table_create();
    if(ini_table_read_from_file(config, cfg_path)) {

        strcpy(user.prompt, ini_table_get_entry(config, "Main", "prompt"));
        user.loglevel = atoi(ini_table_get_entry(config, "Main", "loglevel"));
        strcpy(adminperm, ini_table_get_entry(config, "Main", "admin"));

        if(strcmp(adminperm, "true") == 0)
            user.admin = 1;
    }
    ini_table_destroy(config);

    return CMD_OK;
}

static int
writeconfig(void)
{
    char cfg_path[MAXBUF] = { 0 };
    char astr[10] = { 0 };
    get_userdir(cfg_path);

#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif

    ini_table_s* config = ini_table_create();
    if(ini_table_read_from_file(config, cfg_path)) {

        ini_table_create_entry(config, "Main", "prompt", user.prompt);
        myitoa(user.loglevel, astr);
        ini_table_create_entry(config, "Main", "loglevel", astr);

        if(user.admin == 1)
            ini_table_create_entry(config, "Main", "admin", "true");
        else
            ini_table_create_entry(config, "Main", "admin", "false");

        ini_table_write_to_file(config, cfg_path);
    }

    ini_table_destroy(config);

    return CMD_OK;
}

#ifdef _MSV_VER
char*
get_cmdln(void)
{
    char ch;
    int i = 0, flag = 0;

    for (i = 0; i < MAX_LINE && flag == 0; ++i) {
        ch = _getch();
        switch (ch) {
        case 13:
            str[i] = '\0';
            flag = 1;
            break;

        case '\b':
            if (i > 0) i--;
            str[i--] = '\0';
            printf("\b \b");
            break;

        default:
            str[i] = ch;
            printf("%c", ch);
        }
    }
    str[strlen(str)] = '\0';

    return &str[0];
}
#endif

/**
 * main.c, pretty self explanitory I hope.
 * Will be changed to take command line options eventually.
 */
int
main(int argc, char** argv)
{
	size_t size, len;
	bool bDo = true;
	//char* cmd_string = NULL;

	init();
	readconfig();

	do {
		len = 0;
		char* cmd_string = NULL;
		printf("%s ", user.prompt);

#ifdef _MSV_VER
		cmd_string = get_cmdln();
#else
		getline(&cmd_string, &len, stdin);
#endif
		size = (size_t)strlen(cmd_string);
		char** splitresult = split(cmd_string, ' ', &size);
		bDo = proc_cmds(splitresult, size);

		free(&splitresult[0]);
	} while (bDo);

	writeconfig();

	return EXIT_SUCCESS;
}

