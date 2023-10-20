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
	wchar_t wpath[MAXBUF] = { 0 };

	if (FAILED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, wpath)))
		path = NULL;
	else
		wcstombs(path, wpath, MAXBUF);
}

int
write_motd(const char* path, const char* motd)
{
	return 0;
}

int
read_motd(const char* path)
{
	return 0;
}
const char*
get_keyvalue(const char* pkey, const char* pdef)
{
	_strset(str_data, 0);
	const DWORD dwFlags = RRF_RT_REG_EXPAND_SZ | RRF_NOEXPAND;
	DWORD size = 0;

	LSTATUS status = RegGetValueA(HKEY_CURRENT_USER, sk,
		str_data, dwFlags, NULL, NULL, &size);
	if (status != ERROR_SUCCESS)
		strcpy(str_data, pdef);

	return str_data;
}

int
set_keyvalue(const char* key, const char* value)
{
	return 0;
}

bool
file_exists(char* path)
{
	return false;
}
