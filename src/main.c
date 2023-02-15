#if (__STDC_VERSION__ >= 201112L)
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <commands.h>
#include <simple_strlib.h>
#include <support.h>
#include <huff.h>
#include <filesys.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <libconfig.h>

extern const char* strstrip(char*);
extern char* strlwr(char*);

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
 * no signals we need to handle as far aws we
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
 *              bail.
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
    if(nCmd == MAXCMDS) nCmd = 8;
	if((nCmd == 8) && (strlen(full_cmd) < 5)) {
        while(strchr(*(commands + n++), '?') == NULL)
            printf("- %s\n", *(commands + n));

        printf("\n");
    }

    int nStatus = CMD_ERR, (**p)(char*);
    p = table;

    // command found, execute it.
    nStatus = (*p[nCmd])((char*)strstrip(full_cmd));
    // if its the 'special' quit command bail.
    if(nStatus == CMD_QUIT) return false;

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

    for(n = 0; n <= MAXCMDS; n++) {
        if(strncmp(inp[0],
            *(commands + n),
            strlen(strstrip(strlwr(inp[0])))) == 0) {
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

/*static int
init(void)
{
    return CMD_OK;
}*/

/**
 * main.c, pretty self explanitory I hope.
 * Will be changed to take command line options eventually.
 */
int
main(__attribute__((unused))int argc, __attribute__((unused))char** argv)
{
	int size;
	bool bDo = true;
	size_t len = 0;

    char main_prompt[16], tmp[16];
    memset(main_prompt, '\0', sizeof(main_prompt));
    memset(tmp, '\0', sizeof(tmp));
    strcpy(tmp, get_value("prompt"));

    if(strlen(tmp) == 0) strcpy(main_prompt, ">");
	char banner_path[MAXBUF], cfg_path[MAXBUF], prompt_buf[32];
	signal(SIGINT, sig_handler);

	memset(cfg_path, 0, sizeof(cfg_path));
	memset(banner_path, 0, sizeof(banner_path));
	memset(prompt_buf, 0, sizeof(prompt_buf));

	get_userdir(cfg_path);
	strcpy(banner_path, cfg_path);
	strcat(banner_path, "/.motd");

    mid(tmp, 0, strlen(tmp) - 1, main_prompt, strlen(main_prompt));
	read_motd(banner_path);
	printf("\n");

	while(bDo) {
		char* cmd_string = NULL;
		// will eventually be a configurable prompt.
        printf("%s ", main_prompt);

		getline(&cmd_string, &len, stdin);
		char** splitresult = split(cmd_string, ' ', &size);
		bDo = proc_cmds(splitresult, size);

		free(splitresult);
	}
	return EXIT_SUCCESS;
}

#else
#error "Only ISO/IEC 9899:2011 or greater supported"
#endif
