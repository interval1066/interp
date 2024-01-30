#include "intrinsic.h"

int
help(char* opts)
{
    int size, retcode;
	char** splitresult = split(opts, ' ', &size);
	
	if(size == 1)
        retcode = find_help_section(opts);
	else
        retcode = find_help_section(splitresult[1]);

	free(&splitresult[0]);

    return retcode;
}

int
find_help_section(char* section)
{
	bool found = false;
	FILE* fp = NULL;
	char cfg_path[MAXBUF], chunk[MAXBUF];

	memset(cfg_path, 0, sizeof(cfg_path));
#ifndef _MSC_VER
	get_userdir(cfg_path);
	strcat(cfg_path, "/.interp.hlp");
#else
	get_userdir(cfg_path);
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
motd(char* string)
{
    char cfg_path[MAXBUF], mot_path[MAXBUF];

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
    write_motd(mot_path, string);

    return CMD_OK;
}

int
prompt(char* opts)
{
    if(strlen(opts) > 24) return CMD_ARGS;
    char buf[16] = { 0 };
    strncpy(buf,
            right(opts, (int)strlen(opts) - 9),
            strlen(opts) - 2);

#ifndef _MSC_VER
    set_keyvalue("prompt", buf);
#endif

    return CMD_OK;
}

int
quit(char* opts)
{
    return CMD_QUIT;
}
