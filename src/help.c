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
	if(!section)
		return CMD_ARGS;

	char cfg_path[MAXBUF], chunk[MAXBUF];
	memset(cfg_path, 0, sizeof(cfg_path));
	get_userdir(cfg_path);

	strcat(cfg_path, "/.interp.hlp");
	FILE *fp = fopen(cfg_path, "r");

	if(!fp) printf("Couldn't open help file");
	while(fgets(chunk, sizeof(chunk), fp) != NULL) {
		int n = strncmp(section, chunk, strlen(section));
		if(n == 0) {
			replace_char(chunk, '|', '\n');
			fputs(chunk, stdout);
		}
	}
	printf("\n");

	fclose(fp);

	return CMD_OK;
}
