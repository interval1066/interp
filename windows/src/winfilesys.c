#include "winfilesys.h"

int 
find_cfgfile(const char* file_name, char* path_found, bool bUseDot)
{
	return 0;
}

int
create_cfgfile(const char* file_path)
{
	return 0;
}

void get_userdir(char* path)
{
}

int write_motd(char* path, const char* motd)
{
	return 0;
}

int read_motd(const char* path)
{
	return 0;
}
const char* get_value(const char* pkey)
{
	strset(str_data, 0);
	const DWORD dwFlags = RRF_RT_REG_EXPAND_SZ | RRF_NOEXPAND;
	DWORD size = 0;

	LSTATUS status = RegGetValueA(HKEY_CURRENT_USER, sk, str_data, dwFlags, NULL, NULL, &size);
	if (status != ERROR_SUCCESS)
		strcpy(str_data, "> ");

	return str_data;
}

int set_value(const char* key, char* value)
{
	return 0;
}

bool file_exists(char* path)
{
	return false;
}
