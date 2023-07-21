#include <foo1.h>

char dateout[16];
char timeout[20];

/**
 * Command objects. Normally these would go into separate translation units.
 * Quit is a special command that has its own return status, needed to signal
 * to main that we are exiting.
 * Callee functions are responsible for parsing and converting the opts string
 * for any nessessary arguments.
 */
int
aaa(char* opts)
{
	int size;
	char** splitresult = split(opts, ' ', &size);

	if(size < 2)
		printf("%s called with no options.\n", splitresult[0]);

	for(int n = 1; n < size; n++)
		printf("%s called with option %s.\n", splitresult[0], splitresult[n]);

	return CMD_OK;
}

int
alist(char* opts)
{
	int size;
	char** splitresult = split(opts, ' ', &size);

	for(int n = 1; n < size; n++)
		printf("access_lists  called with option %s.\n", splitresult[n]);

    free(splitresult);

	return CMD_OK;
}

int
amp(char* opts)
{
	printf("amp called with %s\n", opts);

	return CMD_OK;
}

int
app(char* opts)
{
	printf("app called with %s\n", opts);
	return CMD_OK;
}

int
arp(char* opts)
{
	printf("arp called with %s\n", opts);
	return CMD_OK;
}

int
badl(char* opts)
{
	int n = 0;
	char line[100];
	FILE* fp = fopen("./list.dev", "r");

	if(!fp) {
		printf("No lists have been created yet\n");
		return CMD_FILEEXST;
	}

	while(fgets(line, sizeof(line), fp))
		if(strlen(line) > 1) printf("%d - %s", ++n, line);

	fclose(fp);
	return CMD_OK;
}

int
batch(char* opts)
{
	printf("batch called with %s\n", opts);
	return CMD_OK;
}

int
bert(char* opts)
{
	printf("bert called with %s\n", opts);
	return CMD_OK;
}

int
help(char* opts)
{
	char** keywd;
	int size;
	int retcode = CMD_ERR;

	remove_first(opts, "help ");
	remove_first(opts, "? ");

	for(int n = 0; n < MAXCMDS; n++) {
		keywd = split(opts, ' ', &size);
		if(strcmp(keywd[0], *(commands + n)) == 0) {

			find_help_section(keywd[0]);
            memset(opts, '\0', 1);
            return CMD_OK;
        }
    }
    if((retcode == CMD_ERR) && (strcmp(keywd[0], "?") != 0))
        printf("Command not found\n");

    return retcode;
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

	strcat(mot_path, "/.motd");
	write_motd(mot_path, string);

	return CMD_OK;
}

int
prompt(char* opts)
{
    if(strlen(opts) > 24) return CMD_ARGS;
    char buf[16] = { 0 };
    strncpy(buf, right(opts, strlen(opts) - 9), strlen(opts) - 2);

    set_value("prompt", buf);
    return CMD_OK;
}

int
quit(char* opts)
{
	return CMD_QUIT;
}

int
get_date(char* opts)
{
    sprintf(opts, "%s\n", __DATE__);
	return CMD_OK;
}

char*
date(void)
{
    memset(dateout, '\0', sizeof(dateout));
    get_date(dateout);
    printf("%s\n", dateout);
	 return "";
}

int
get_time(char* opts)
{
    sprintf(opts, "%s\n", __TIME__);
    return CMD_OK;
}

int
time2(char* opts)
{
    memset(timeout, '\0', sizeof(timeout));
    get_time(timeout);
    printf("%s\n", timeout);
    return CMD_OK;
}
int
list(char* opts)
{
	char buf[16] = { 0 }, dev[16] = { 0 };
	strncpy(buf, right(opts, strlen(opts) - 6), strlen(opts) - 2);

	if(strlen(buf) == 2)
		return CMD_ARGS;

	printf("%s\n", buf);
	if(strcmp(buf, "all") == 0) {
		badl(NULL);
		return CMD_OK;
	}

	printf("Adding new device %s to list.\n", buf);
	FILE* f = fopen("./list.dev", "w");
	if(f == NULL)
		return CMD_IOERR;

	do {
		scanf("%s", dev);
		if(strcmp(dev, ".") != 0)
			fwrite(&dev, strlen(dev), 1, f);
		fprintf(f, "\n");
	} while(strlen(dev) > 1);

	fclose(f);

	return CMD_OK;
}
