#include "utils/filesys.h"
#include "utils/config.h"

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 594 )
#pragma warning( disable : 4047 )
#pragma warning( disable : 4024 )
#endif


/**
 * @brief			find_cfgfile search for ini in a few predefined locations
 *
 * @details			make three attempts to locate the cfg file requested
 *					using three different strategies (/etc, $HOME, and
 *					the home for the current user using the passwd
 *					database), errors out with an integer code if
 *					finally unsuccessful. If the bUseDot is set the
 *					search will make the file name a dot file during
 *					search in the user directories
 *
 * @param			const string file_name: name of cfg file to search for
 * @param			string path_found: result of successful search
 * @param			boolean make it a dot file flag
 * @return			integer status code, path_found is NULLed if unsuccessful
 */
#ifndef _MSC_VER
int
find_cfgfile(const char* file_name, char* path_found, bool bUseDot)
{
    if(file_name == NULL && path_found == NULL)
        return CMD_ARGS;

    char search_this_path[MAXSIZE];
    char* sp = &search_this_path[0];
    strcpy(sp, "/etc");
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
#endif

/**
 * @brief			create_cfgfile create a new ini file
 *
 * @details			copies the passed parameter to a buffer to
 *                 	protect against file names larger than 256
 *                  chars.
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

#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif

    ini_table_s* config = ini_table_create();
    if(!ini_table_read_from_file(config, cfg_path)) {
        // create new table

        ini_table_create_entry(config, "Main", "prompt", "> ");
        ini_table_create_entry(config, "Main", "loglevel", "0");
        ini_table_create_entry(config, "Main", "admin", "false");
        ini_table_write_to_file(config, cfg_path);
    }

    ini_table_destroy(config);

    return CMD_OK;
}

#ifndef _MSC_VER
void
get_userdir(char* path)
{
    uid_t uid = getuid();
    struct passwd* pw = getpwuid(uid);
    strcpy(path, pw->pw_dir);
}
#else
void
get_userdir(char* path)
{
    wchar_t wpath[MAXBUF * 2] = { 0 };

    if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, wpath)))
        path = NULL;
    else
        wcstombs(path, wpath, MAXBUF);
}
#endif

int
write_motd(char* path, const char* motd)
{
    char newm[MAXMOTD];
    memset(newm, '\0', MAXMOTD);
    mid(motd, 6, find_ch_index(motd, '"'), newm, strlen(motd));

    remove_first(newm, "\"");
    FILE* fp = fopen(path, "w");
    if (fp == NULL) return CMD_ERR;

    fprintf(fp, "%s", newm);
    fclose(fp);

    return CMD_OK;
}

int
read_motd(const char* path)
{
    FILE* stream;
    char line[MAXMOTD];
    int errno;

    errno = CMD_OK;
    if((stream = fopen(path, "r")) != NULL) {
        if (NULL != fgets(&line, MAXMOTD, stream))
            errno = CMD_FILEEXST;
        fclose(stream);
    }
    return errno;
}

const char*
get_keyvalue(const char* key, const char* def)
{
    //struct config_setting_t const *setting;
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));

    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif

    if(!file_exists(cfg_path))
        create_cfgfile(cfg_path);

    return "";
}

int
set_keyvalue(const char* key, const char* value)
{
    char cfg_path[MAXBUF];
    memset(cfg_path, 0, sizeof(cfg_path));
    get_userdir(cfg_path);
#ifndef _MSC_VER
    strcat(cfg_path, "/.interp.ini");
#else
    strcat(cfg_path, "\\.interp.ini");
#endif

    return CMD_OK;
}

bool
file_exists(const char* filename)
{
  struct stat buffer;
  return (stat (filename, &buffer) == 0);
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

