#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "Registry.h"

int __fastcall
ReadWindowsRegistryInt(const char *pKey, int uDefValue)
{
  DWORD cbData;
  LPCSTR lpValueName;
  DWORD dwDisposition;

  BYTE Data[4];
  HKEY hKey;
  HKEY phkResult;

  HKEY v10;
  HKEY v11;
  lpValueName = pKey;

  v11 = 0;
  v10 = 0;
  hKey = 0;

  phkResult = 0;
  cbData = 4;

  if(!RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE", 0, KEY_READ|KEY_WOW64_32KEY, &hKey)) {
    if(!RegCreateKeyExA(hKey, "New World Computing", 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, "Might and Magic VII", 0, "", 0, 0xF003Fu, 0, &v10, &dwDisposition)) {
        if(!RegCreateKeyExA(v10, "1.0", 0, "", 0, 0xF003Fu, 0, &v11, &dwDisposition)) {
			LSTATUS status;
          if(status = RegQueryValueExA(v11, lpValueName, 0, 0, Data, &cbData)) {
			  status;			  
			  GetLastError();

            *(int*)Data = uDefValue;
            RegSetValueExA(v11, lpValueName, 0, 4u, Data, 4u);
          }
          RegCloseKey(v11);
        }
        RegCloseKey(v10);
      }
      RegCloseKey(phkResult);
    }
    RegCloseKey(hKey);
  }
  return *(int *)Data;
}

void __fastcall
WriteWindowsRegistryString(const char *pKey, const char *pString)
{
  DWORD v2;
  const char* lpValueName;
  const char* Str;

  DWORD dwDisposition;
  HKEY hKey;
  HKEY phkResult;

  HKEY v8;
  HKEY v9;

  Str = pString;
  lpValueName = pKey;
  v9 = 0;

  v8 = 0;
  hKey = 0;
  phkResult = 0;

  if(!RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE", 0, 0x2001Fu, &hKey)) {
    if(!RegCreateKeyExA(hKey, "New World Computing", 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, "Might and Magic VII", 0, "", 0, 0xF003Fu, 0, &v8, &dwDisposition)) {

        if(!RegCreateKeyExA(v8, "1.0", 0, "", 0, 0xF003Fu, 0, &v9, &dwDisposition)) {
          v2 = (DWORD)strlen(Str);
          RegSetValueExA(v9, lpValueName, 0, 1u, (const BYTE *)Str, v2 + 1);

          RegCloseKey(v9);
        }
        RegCloseKey(v8);
      }
      RegCloseKey(phkResult);
    }
    RegCloseKey(hKey);
  }
}

void __fastcall
ReadWindowsRegistryString(const char *pKeyName, char *pOutString, int uBufLen, const char *pDefaultValue)
{
  LSTATUS (__stdcall *v4)(HKEY);
  LSTATUS result;
  DWORD Type;

  LPCSTR lpValueName;
  DWORD cbData;
  LPBYTE Dest;

  DWORD dwDisposition;
  HKEY phkResult;
  HKEY hKey;

  HKEY v13;
  HKEY v14;

  cbData = uBufLen;
  Dest = (LPBYTE)pOutString;
  lpValueName = pKeyName;

  v14 = 0;
  v13 = 0;
  hKey = 0;

  phkResult = 0;
  v4 = RegCloseKey;

  if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE", 0, 0x2001Fu, &hKey)
    || RegCreateKeyExA(hKey, "New World Computing", 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)
    || RegCreateKeyExA(phkResult, "Might and Magic VII", 0, "", 0, 0xF003Fu, 0, &v13, &dwDisposition)

    || RegCreateKeyExA(v13, "1.0", 0, "", 0, 0xF003Fu, 0, &v14, &dwDisposition))
    result = (LSTATUS)strncpy((char *)Dest, pDefaultValue, uBufLen);
  else if (RegQueryValueExA(v14, lpValueName, 0, &Type, Dest, &cbData)) {

    RegCloseKey(v14);
    v14 = 0;
    result = (LSTATUS)strncpy((char *)Dest, pDefaultValue, uBufLen);
  }
  else {
    v4 = RegCloseKey;
    RegCloseKey(v14);
    v14 = 0;

    RegCloseKey(v13);
    v13 = 0;
    RegCloseKey(phkResult);

    phkResult = 0;
    result = RegCloseKey(hKey);
    hKey = 0;
  }
  if(v14)
    result = v4(v14);
  if(v13)
    result = v4(v13);
  if(hKey)
    result = v4(hKey);
  if(phkResult)
    result = v4(phkResult);
}

void __fastcall
WriteWindowsRegistryInt(const char *pKey, int val)
{
  const char *lpValueName;
  BYTE Data[4];
  DWORD dwDisposition;

  HKEY hKey;
  HKEY phkResult;
  HKEY v7;

  HKEY v8;

  *(int*)Data = val;
  lpValueName = pKey;
  v8 = 0;

  v7 = 0;
  hKey = 0;
  phkResult = 0;

  if(!RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE", 0, 0x2001Fu, &hKey)) {
    if (!RegCreateKeyExA(hKey, "New World Computing", 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, "Might and Magic VII", 0, "", 0, 0xF003Fu, 0, &v7, &dwDisposition)) {

        if(!RegCreateKeyExA(v7, "1.0", 0, "", 0, 0xF003Fu, 0, &v8, &dwDisposition)) {
          RegSetValueExA(v8, lpValueName, 0, 4, Data, 4);
          RegCloseKey(v8);
        }
        RegCloseKey(v7);
      }
      RegCloseKey(phkResult);
    }
    RegCloseKey(hKey);
  }
}
