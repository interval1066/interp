#include "intrinsic.h"

int
help(char* opts)
{
    int size;
    char** splitresult = split(opts, ' ', &size);

    if(size == 1)
        find_help_section(opts);
    else
        find_help_section(splitresult[1]);

    free(&splitresult[0]);

    return CMD_OK;
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
    if(!fp)
        return CMD_FILEEXST;

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
