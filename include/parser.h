#pragma once

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

bool
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
 *              This needs to be moved to another translation unit.
 *
 * @param		char**	inp The string to process
 * @param		int		size The number of command elements
 * @return		boolean	returns the status of the run_cmd
 *				function, which is only false if we
 *				process a quit command.
 */
bool
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
