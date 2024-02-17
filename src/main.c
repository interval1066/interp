#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include "intrinsic.h"
#include "support.h"
#include "parser.h"

extern int noCmds;
extern int help(char*);
extern bool run_cmd(int, char*);
extern bool proc_cmds(char**, int);
struct user_ctx user;

/**
 * @file    main.c
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief	Probably pretty portable CLI interpreter
 *
 * @section	DESCRIPTION
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

static int
init(void)
{
    char tmp[16] = { 0 };
    memset(user.prompt, 0, sizeof(user.prompt));
    strcpy(tmp, get_keyvalue("prompt", ""));

    if(strlen(tmp) == 0)
        strcpy(tmp, get_keyvalue("prompt", "> "));

#ifndef _MSC_VER
    int len2 = (int)strlen(tmp);
    tmp[len2 - 1] = '\0';
#endif
    char banner_path[MAXBUF], cfg_path[MAXBUF];
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
    config_setting_t* setting;
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));

    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif
    config_t cfg;

    config_init(&cfg);
    config_set_options(&cfg, (CONFIG_OPTION_SEMICOLON_SEPARATORS
        | CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
        | CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

    config_read_file(&cfg, cfg_path);
    setting = config_lookup(&cfg, "prompt");
    user.loglevel = 0;

    user.admin = false;
    strcpy(user.prompt, config_setting_get_string(setting));
    config_destroy(&cfg);

    return CMD_OK;
}

static int
writeconfig(void)
{
    config_setting_t* setting;
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));

    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif
    config_t cfg;

    config_init(&cfg);
    config_set_options(&cfg, (CONFIG_OPTION_SEMICOLON_SEPARATORS
        | CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
        | CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

    config_read_file(&cfg, cfg_path);
    setting = config_lookup(&cfg, "prompt");
    config_setting_set_string(setting, user.prompt);

    if (!config_write_file(&cfg, cfg_path)) {
        config_destroy(&cfg);
        return CMD_IOERR;
    }

    config_destroy(&cfg);

    return CMD_OK;
}

/**
 * main.c, pretty self explanitory I hope.
 * Will be changed to take command line options eventually.
 */
int
main(int argc, char** argv)
{
    int size;
    bool bDo = true;
    static size_t len = 0;

    init();
    readconfig();

	do {
		len = 0;
		char* cmd_string = NULL;
		printf("%s", user.prompt);
		
		/* Es ist lächerlich, dass es keine gute Möglichkeit
		gibt, eine Art Metacode zu erstellen, um Tabulatoren,
		Leerzeichen und andere nicht druckbare Zeichen
		einheitlich zu machen. */
		getline(&cmd_string, &len, stdin);
		char** splitresult = split(cmd_string, ' ', &size);

		bDo = proc_cmds(splitresult, size);
        free(&splitresult[0]);
	} while (bDo);

    writeconfig();

	return EXIT_SUCCESS;
}
