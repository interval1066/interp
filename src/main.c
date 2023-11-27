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
#include "utils/huff.h"
#include "utils/filesys.h"
#include "foo1.h"
#ifdef _MSC_VER
#include <io.h>
#include "winunistd.h"
#define STRLWR _strlwr
extern size_t getline(char**, size_t*, FILE*);
#else
#include <unistd.h>
#include <libconfig.h>
#define STRLWR strlwr
//
extern char* strlwr(char*);
#endif
extern const char* strstrip(char*);

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
                            "time2",
                            "?" };


int (*table[])() = {
     aaa, alist, amp, app, arp, badl, batch, bert, help, motd, prompt, quit, date, list, time2
};

int noCmds = *(&table + 1) - table;

/**
 * @file    main.c
 * @author  Tim O'Neil
 * @date    3/9/2018
 *
 * @brief	Probably pretty portable CLI interperter
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
 * @brief		command runner
 *
 * @details		Runs a command function by invoking
 *				it as an entry on a jump table along with any
 * 				parameters required. Both run_cmd and proc_cmds
 *				should be moved to a more common module.
 *
 * @param		n the command index
 * @param		full_cmd the command with params
 * @return		boolean success/failure flag, also signals when to
 *             bail.
 */
static bool
run_cmd(int nCmd, char* full_cmd)
{
    int n = 0;

    if(nCmd == CMD_ERR) {
        printf("Command error.\n");
		return true;
	}
	// If help is invoked with '?'
    if(nCmd == noCmds) nCmd = 8;
	if((nCmd == 8) && (strlen(full_cmd) < 5)) {
		printf("\n");

		while(strchr(*(commands + n++), '?') == NULL)
			printf("- %s\n", *(commands + n));

		printf("\n");
	}

    int nStatus = CMD_ERR, (**p)(char*);
    p = table;

    // command found, execute it.
    nStatus = (*p[nCmd])((char*)strstrip(full_cmd));
    // if its the 'special' quit command bail.
	
	if (nStatus == CMD_QUIT)
		return false;

	return true;
}

/**
 * @brief		Process the commands rejecting those that aren't on the list
 *
 * @param		char**	inp The string to process
 * @param		int		size The number of command elements
 * @return		boolean	returns the status of the run_cmd
 *				function, which is only false if we
 *				process a quit command.
 */
static bool
proc_cmds(char** inp, int size)
{
    int n = 0, nCmd = 0;
    bool bFound = false;
    char full_cmd[200], cmd[40];

    memset(full_cmd, '\n', sizeof(full_cmd));
    memset(cmd, '\n', sizeof(cmd));

    for(n = 0; n <= noCmds; n++) {
        if(strncmp(inp[0],
            *(commands + n),
            strlen(strstrip(STRLWR(inp[0])))) == 0) {
            bFound = true;
        }
        if(bFound) {
            nCmd = n;
            strcpy(full_cmd, *(commands + n));

            for(int m = 1; m < size; m++) {
                strcat(full_cmd, " ");
                strcat(full_cmd, inp[m]);
            }
            return run_cmd(nCmd, full_cmd);
        }
    }
    return run_cmd(CMD_ERR, NULL);
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
	int len2;

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
        //getline(&cmd_string, &(int)len, stdin);
        getline(&cmd_string, &len, stdin);

		char** splitresult = split(cmd_string, ' ', &size);
		bDo = proc_cmds(splitresult, size);
	} while (bDo);

	return EXIT_SUCCESS;
}
