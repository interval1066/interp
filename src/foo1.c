#include <string.h>
#include "foo1.h"
#include "utils/filesys.h"

const char dateout[16];
const char timeout[20];
extern const char* commands;
extern const int noCmds;
extern struct user_ctx user;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 836 )
#pragma warning( disable : 594 )
#pragma warning( disable : 4090 )
#pragma warning( disable : 859 )
#endif

/**
 * Command objects. Normally these would go into separate translation units.
 * Quit is a special command that has its own return status, needed to signal
 * to main that we are exiting.
 * Callee functions are responsible for parsing and converting the opts string
 * for any necessary arguments.
 */
int
dummy(const char* opts)
{
	return CMD_OK;
}

int
aaa(const char* opts)
{
	int size;
	char** splitresult = split(opts, ' ', &size);

	if(size < 2)
		printf("%s called with no options.\n", splitresult[0]);

	for(int n = 1; n < size; n++)
		printf("%s called with option %s.\n", splitresult[0], splitresult[n]);
    
	free(splitresult);
	
	return CMD_OK;
}

int
alist(const char* opts)
{
	int size;
	char** splitresult = split(opts, ' ', &size);

	for(int n = 1; n < size; n++)
		printf("access_lists  called with option %s.\n", splitresult[n]);

    free(splitresult);

	return CMD_OK;
}

int
amp(const char* opts)
{
	printf("amp called with %s\n", opts);

	return CMD_OK;
}

int
app(const char* opts)
{
	printf("app called with %s\n", opts);
	return CMD_OK;
}

int
arp(const char* opts)
{
	printf("arp called with %s\n", opts);
	return CMD_OK;
}

int
badl(const char* opts)
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
batch(const char* opts)
{
	printf("batch called with %s\n", opts);
	return CMD_OK;
}

int
bert(const char* opts)
{
	printf("bert called with %s\n", opts);
	return CMD_OK;
}

int
get_date(const char* opts)
{
    sprintf(opts, "%s\n", __DATE__);
	return CMD_OK;
}

int
date(const char* opts)
{
    memset((const char*)dateout, '\0', sizeof(dateout));
    get_date(dateout);
    printf("%s\n", dateout);

    return CMD_OK;
}

int
get_time(const char* opts)
{
    sprintf(opts, "%s\n", __TIME__);
    return CMD_OK;
}

int
time2(const char* opts)
{
    memset((const uint64_t*)timeout, '\0', sizeof(timeout));
    get_time(timeout);
    printf("%s\n", timeout);
    return CMD_OK;
}

int
list(const char* opts)
{
    FILE* f = NULL;
	char buf[16] = { 0 };
	char dev[16] = { 0 };

	strncpy(buf, right(opts, (int)strlen(opts) - 6), strlen(opts) - 2);
	if(strlen(buf) == 2)
		return CMD_ARGS;

	printf("%s\n", buf);
	if(strcmp(buf, "all") == 0) {
		badl(NULL);
		return CMD_OK;
	}

	printf("Adding new device %s to list.\n", buf);
    f = fopen("./list.dev", "w");
	if(f == NULL)
		return CMD_IOERR;

	do {
		scanf("%15s", dev);
		if(strcmp(dev, ".") != 0)
			fwrite(&dev, strlen(dev), 1, f);
		fprintf(f, "\n");
	} while(strlen(dev) > 1);

    if(f) fclose(f);

	return CMD_OK;
}

int
loglevel(const char* opts)
{
    int size;
    char** splitresult = split((const char*)opts, ' ', &size);

	if(size == 1) {
        printf("Current log level: %i\n", user.loglevel);
		free(splitresult);
        return CMD_OK;
    }

    int m = atoi(splitresult[1]);
    if((m < 0) && m > 4)
        return CMD_ARGS;

    user.loglevel = m;
    free(splitresult);

    return CMD_OK;
}

int
filet(const char* opts)
{
	return CMD_OK;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

