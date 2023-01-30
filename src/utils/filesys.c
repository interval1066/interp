#include <filesys.h>
#include <libconfig.h>
#include <sys/stat.h>

/**
 * @brief			find_cfgfile search for ini in a few predefined locations
 *
 * @details			make three attempts to locate the cfg file requested
 *						using three different strategies (/etc, $HOME, and
 *						the home for the current user using the passwd
 *						ddatabase), errors out with an integer code if
 *						finally unsuccessful. If the bUseDot is set the
 *						search will make the file name a dot file during
 *						search in the user directories
 *
 * @param			const string file_name: name of cfg file to search for
 * @param			string path_found: result of successful search
 * @param			boolean make it a dot file flag
 * @return			integer status code, path_found is NULLed if unsuccessful
 */
int
find_cfgfile(const char* file_name, char* path_found, bool bUseDot)
{
	if(file_name == NULL && path_found == NULL)
		return CMD_ARGS;

	char search_this_path[MAXSIZE];
	char* sp = &search_this_path[0];
	// Search /etc first for a plain,
	// un-decorated (no dot prefix)
    // file_name
    memset(sp, 0, strlen(search_this_path));
	sp = strcpy(search_this_path, "/etc");
	sp = strcat(search_this_path, "/");

	sp = strcat(sp, file_name);

	if(access(sp, F_OK) != -1 ) {
		strcpy(path_found, sp);
		return CMD_OK;
	}
   // then try for whatever is in $HOME,
   // if bUseDot == true prefix the file
   // name with a dot.
	char* homedir = getenv("HOME");
	if(homedir != NULL) {
		memset(sp, 0, strlen(search_this_path));

		strcpy(sp, homedir);
		strcat(sp, "/");
		if(bUseDot) strcat(sp, ".");

		strcat(sp, file_name);
		if(access(sp, F_OK) != -1 ) {
			strcpy(path_found, sp);

			return CMD_OK;
		}
	}
	// Finally try the user's directory as
	// specified in the passwd data base
	uid_t uid = getuid();
	struct passwd* pw = getpwuid(uid);
	if(pw != NULL) {

		memset(sp, 0, strlen(search_this_path));
		strcpy(sp, pw->pw_dir);
		strcat(sp, "/");

		if(bUseDot) strcat(sp, ".");
		strcat(sp, file_name);
		if(access(search_this_path, F_OK) != -1 ) {

			strcpy(path_found, sp);
			return CMD_OK;
		}
	}
	// nothing worked, set the result string
	// param to null and return an error code
    strcpy(path_found, "\0");

	return CMD_FILENF;
}

/**
 * @brief			create_cfgfile create a new ini file
 *
 * @details			copies the passed parameter to a buffer to
 *						protect against file names larger than 256
 *						chars.
 *
 * @param			const char* the full path of the new file
 * @return			integer status code
 */
int
create_cfgfile(const char* file_path)
{
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));
    get_userdir(cfg_path);

    strcat(cfg_path, "/.interp.ini");
    config_t cfg;
    config_setting_t *root, *setting;

    config_init(&cfg);
    config_set_options(&cfg,
                       (CONFIG_OPTION_FSYNC
                        | CONFIG_OPTION_SEMICOLON_SEPARATORS
                        | CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
                        | CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

    root = config_root_setting(&cfg);

    setting = config_setting_get_member(root, "prompt");

    if(!setting)
        setting = config_setting_add(root, "prompt", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, "> ");

    if(! config_write_file(&cfg, cfg_path)) {
        config_destroy(&cfg);
        return CMD_IOERR;
    }

    config_destroy(&cfg);
    return CMD_OK;
}

void
get_userdir(char* path)
{
	uid_t uid = getuid();
	struct passwd* pw = getpwuid(uid);
	strcpy(path, pw->pw_dir);
}

int
write_motd(char* path, const char* motd)
{
	char newm[MAXMOTD];
	memset(newm, '\0', MAXMOTD);

	FILE* fp = fopen(path, "w");
	if (fp == NULL)
		return CMD_ERR;

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
    char line[MAXMOTD], * result;

    stream = fopen(path, "r");

    if ((result = fgets(line, MAXMOTD, stream)) != NULL)
       printf("%s", result);

    fclose(stream);

    return CMD_OK;
}

const char*
get_value(const char* key)
{
    config_setting_t *setting;
    char cfg_path[MAXBUF];

    memset(cfg_path, 0, sizeof(cfg_path));
    get_userdir(cfg_path);
    strcat(cfg_path, "/.interp.ini");

    config_t cfg;
    config_init(&cfg);
    config_set_options(&cfg, (CONFIG_OPTION_FSYNC
        | CONFIG_OPTION_SEMICOLON_SEPARATORS
        | CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
        | CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

    config_read_file(&cfg, cfg_path);
    setting = config_lookup(&cfg, key);
    const char* value = config_setting_get_string(setting);

    return value;
}

int
set_value(const char* key, const char* value)
{
    config_setting_t *setting;
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));

    get_userdir(cfg_path);
    strcat(cfg_path, "/.interp.ini");
    config_t cfg;

    config_init(&cfg);
    config_set_options(&cfg, (CONFIG_OPTION_FSYNC
        | CONFIG_OPTION_SEMICOLON_SEPARATORS
        | CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS
        | CONFIG_OPTION_OPEN_BRACE_ON_SEPARATE_LINE));

    config_read_file(&cfg, cfg_path);
    setting = config_lookup(&cfg, key);
    config_setting_set_string (setting, value);

    if(!config_write_file(&cfg, cfg_path)) {
        config_destroy(&cfg);
        return CMD_IOERR;
    }

    config_destroy(&cfg);
    return CMD_OK;
}

/*int
write_config(config_t* cfg, char* cfg_file)
{

}*/
