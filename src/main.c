#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include "simple_strlib.h"
#include "support.h"
#include "parser.h"
#include "utils/huff.h"
#include "utils/filesys.h"

extern int noCmds;
extern bool run_cmd(int, char*);
extern bool proc_cmds(char**, int);

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
 * Anticipate all signals
 *
 * no signals we need to handle as far as we
 * know right now. May change in the future.
 */
void
sig_handler(int sign)
{

}

/**
 * main.c, pretty self explanitory I hope.
 * Will be changed to take command line options eventually.
 */
int
main(int argc, char** argv)
{
    int size, len2;
	bool bDo = true;
	static size_t len = 0;

	char main_prompt[16], tmp[16];
	memset(main_prompt, '\0', sizeof(main_prompt));
	memset(tmp, '\0', sizeof(tmp));

	strcpy(tmp, get_keyvalue("prompt", "> "));
	len2 = (int)strlen(tmp);
#ifndef _MSC_VER
	tmp[len2 - 1] = '\0';
#endif
	char banner_path[MAXBUF], cfg_path[MAXBUF], prompt_buf[32];
	signal(SIGINT, sig_handler);

	memset(cfg_path, 0, sizeof(cfg_path));
	memset(banner_path, 0, sizeof(banner_path));
	memset(prompt_buf, 0, sizeof(prompt_buf));

	get_userdir(cfg_path);
	strcpy(banner_path, cfg_path);
#ifndef _MSC_VER
	strcat(banner_path, "/.motd");
	strcat(cfg_path, "/.interp.ini");
#else
	strcat(banner_path, "\\.motd");
	strcat(cfg_path, "\\.interp.ini");
#endif
	strcpy(main_prompt, tmp);
	if (access(banner_path, 0) == 0)
		read_motd(banner_path);

	do {
		len = 0;
		char* cmd_string = NULL;
		printf("%s", main_prompt);
		
		/* Es ist lächerlich, dass es keine gute Möglichkeit
		gibt, eine Art Metacode zu erstellen, um Tabulatoren,
		Leerzeichen und andere nicht druckbare Zeichen
		einheitlich zu machen. */
		getline(&cmd_string, &len, stdin);
		char** splitresult = split(cmd_string, ' ', &size);

		bDo = proc_cmds(splitresult, size);
        free(&splitresult[0]);
	} while (bDo);

	return EXIT_SUCCESS;
}
