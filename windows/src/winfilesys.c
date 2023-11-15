#include "winfilesys.h"

int 
find_cfgfile(const char* file_name, char* path_found, bool bUseDot)
{
	return CMD_NOOP;
}

int
create_cfgfile(const char* file_path)
{
	return CMD_NOOP;
}

void
get_userdir(char* path)
{
	wchar_t wpath[MAXBUF * 2] = { 0 };

	if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, wpath)))
		path = NULL;
	else
		wcstombs(path, wpath, MAXBUF);
}

int
write_motd(const char* path, const char* motd)
{
	char newm[MAXMOTD];
	memset(newm, '\0', MAXMOTD);

	FILE* fp = fopen(path, "w");
	if (fp == NULL)
		return CMD_IOERR;

	mid(motd, 6, find_ch_index(motd, '"'), newm, strlen(motd));
	remove_first(newm, "\"");
	fprintf(fp, "%s", newm);

	fclose(fp);

	return CMD_OK;
}

int
read_motd(const char* path)
{
	FILE* stream;
	char line[MAXMOTD], * result = 0;
	memset(line, '\0;', sizeof(line));

	stream = fopen(path, "r");

	if ((result = fgets(line, MAXMOTD, stream)) != NULL)
		printf("%s\n", result);
	else
		return CMD_FILEEXST;
	fclose(stream);

	return CMD_OK;
}

const char*
get_keyvalue(const char* key, const char* def)
{
	config_setting_t* setting;
	char cfg_path[MAXBUF];

	memset(cfg_path, 0, sizeof(cfg_path));
	get_userdir(cfg_path);
	strcat(cfg_path, "\\.interp.ini");
	if (!file_exists(cfg_path))
		create_cfgfile(cfg_path);

	config_t cfg;
	config_init(&cfg);
	config_set_options(&cfg, (CONFIG_OPTION_SEMICOLON_SEPARATORS
		| CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
		| CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

	config_read_file(&cfg, cfg_path);
	setting = config_lookup(&cfg, key);
	const char* value = config_setting_get_string(setting);

	return value;
}

int
set_keyvalue(const char* pkey, const char* value)
{
	config_setting_t* setting;
	char cfg_path[MAXBUF];
	memset(cfg_path, 0, sizeof(cfg_path));

	get_userdir(cfg_path);
	strcat(cfg_path, "\\.interp.ini");
	config_t cfg;

	config_init(&cfg);
	config_set_options(&cfg, (CONFIG_OPTION_SEMICOLON_SEPARATORS
		| CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
		| CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

	config_read_file(&cfg, cfg_path);
	setting = config_lookup(&cfg, pkey);
	config_setting_set_string(setting, value);

	if (!config_write_file(&cfg, cfg_path)) {
		config_destroy(&cfg);
		return CMD_IOERR;
	}

	config_destroy(&cfg);
	return CMD_OK;
}

bool
file_exists(const char* filename)
{
	bool bExist = false;

	if(access(filename, F_OK) == 0)
		bExist = true;

	return bExist;
}