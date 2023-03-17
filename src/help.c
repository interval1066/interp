#include <help.h>

extern int strhav(const char*, const char*);
extern void get_userdir(char*);

/**
 * help.c
 *
 * The interpreter expects to find the help file
 * in the user directory along with all the other
 * ancillary files. This is usually the users $HOME
 * directory, and they are all dot files.
 *
 */
int
find_help_section(char* section)
{
    char buffer[MAXBUF], cfg_path[MAXBUF];
    memset(cfg_path, '\0', sizeof(cfg_path));
    get_userdir(cfg_path);

    strcat(cfg_path, "/.interp.hlp");
    FILE* fp = fopen(cfg_path, "r");

    if (fp == NULL)
        return CMD_FILENF;
    printf("\n");

    while(buffer[0] != '0') {
        while(fgets(buffer, MAXBUF, fp) && strcmp(buffer, "%%@---") != 0) {
            //const char* p = strstr(buffer, section);
            while(fscanf(fp, "%s", section) == 1) {
                if(strstr(buffer, section) != 0) {
                    puts(buffer);
                    memset(buffer, '\0', sizeof(buffer));
                }
            }
        }
    }

    printf("\n");
    printf("Commands can be partially entered with any number of characters. For example, entering \"acc\" will be enough to list all the access lists.\n");
    fclose(fp);

    return CMD_OK;
}
