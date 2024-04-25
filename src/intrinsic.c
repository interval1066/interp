#include "intrinsic.h"

extern struct user_ctx user;
extern int writeconfig();

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4090 )
#pragma warning( disable : 594 )
#endif

int
help(const char* opts)
{
    int size;
    int retcode;
	char** splitresult = split(opts, ' ', &size);

	if(size == 1)
        retcode = find_help_section(opts);
	else
        retcode = find_help_section(splitresult[1]);

	free(&splitresult[0]);

    return retcode;
}

int
find_help_section(const char* section)
{
	bool found = false;
	FILE* fp = NULL;
    char cfg_path[MAXBUF];
    char chunk[MAXBUF];

    memset(cfg_path, 0, sizeof(cfg_path));
    get_userdir(cfg_path);
#ifndef _MSC_VER
	strcat(cfg_path, "/.interp.hlp");
#else
    strcat(cfg_path, "\\.interp.hlp");
#endif

	fp = fopen(cfg_path, "r");
    if(!fp) return CMD_FILEEXST;

	while(fgets(chunk, sizeof(chunk), fp) != NULL) {
		int n = strncmp(section, chunk, strlen(section));

		if(n == 0) {
			replace_char(chunk, '|', '\n');
			fputs(chunk, stdout);
			found = true;
		}
	}

	if((!found) && strncmp(section, "?", (size_t)1) != 0)
		printf("Keyword not found\n");

	if(fp) fclose(fp);
	
	return CMD_OK;
}

int
motd(const char* string)
{
    char cfg_path[MAXBUF];
    char mot_path[MAXBUF];

    if(strlen(string) < 3)
        return CMD_ARGS;

    if(strchr(string, '"') == NULL)
        return CMD_QUOTES;

    memset(cfg_path, 0, sizeof(cfg_path));
    get_userdir(cfg_path);
    strcpy(mot_path, cfg_path);

    remove_first(mot_path, ".interp.ini");
#ifndef _MSC_VER
    strcat(mot_path, "/.motd");
#else
    strcat(mot_path, "\\.motd");
#endif
    char newm[MAXMOTD];
    memset(newm, '\0', MAXMOTD);
    mid(string, 6, find_ch_index(string, '"'), newm, strlen(string));

    remove_first(newm, "\"");
    encode(mot_path, newm);

    return CMD_OK;
}

int
prompt(const char* opts)
{
    char *buf;

    int n = countc(opts, '\"');
    if (n < 2)
        return CMD_ARGS;

    substr(opts, '\"', &buf);
    memset(user.prompt, 0, strlen(user.prompt));
    strcpy(user.prompt, buf);

    free(buf);

    return CMD_OK;
}

int
quit(const char* opts)
{
    writeconfig();
    return CMD_QUIT;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

