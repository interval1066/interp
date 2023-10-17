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
    DWORD cbData = 4;
    LPCSTR lpValueName = pKey = 0;
    DWORD dwDisposition = 0;

    BYTE Data[4];
    HKEY hKey = 0;
    HKEY phkResult = 0;

    HKEY v10 = 0;
    HKEY v11 = 0;

    if(!RegOpenKeyExA(HKEY_LOCAL_MACHINE, MAINKEY, 0, KEY_READ|KEY_WOW64_32KEY, &hKey)) {
    if(!RegCreateKeyExA(hKey, SUBKEY, 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, SUBKEY2, 0, "", 0, 0xF003Fu, 0, &v10, &dwDisposition)) {

        if(!RegCreateKeyExA(v10, VERKEY, 0, "", 0, 0xF003Fu, 0, &v11, &dwDisposition)) {
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
  return *(int*)Data;
}

void __fastcall
WriteWindowsRegistryString(const char* pKey, const char* pString)
{
  DWORD dwDisposition;
  HKEY hKey = 0;
  DWORD v2;

  HKEY phkResult = 0;
  HKEY v8 = 0;
  HKEY v9 = 0;

  if(!RegOpenKeyExA(HKEY_CURRENT_USER, MAINKEY, 0, 0x2001Fu, &hKey)) {
    if(!RegCreateKeyExA(hKey, SUBKEY, 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, SUBKEY2, 0, "", 0, 0xF003Fu, 0, &v8, &dwDisposition)) {

        if(!RegCreateKeyExA(v8, VERKEY, 0, "", 0, 0xF003Fu, 0, &v9, &dwDisposition)) {
          v2 = (DWORD)strlen(pString);
          RegSetValueExA(v9, pKey, 0, 1u, (const BYTE*)pString, v2 + 1);

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
ReadWindowsRegistryString(const char* pKeyName, char* pOutString, int uBufLen, const char* pDefaultValue)
{
  LSTATUS (__stdcall* v4)(HKEY);
  LSTATUS result;
  DWORD Type;

  LPCSTR lpValueName = NULL;
  DWORD cbData = uBufLen = 0;
  //LPBYTE Dest = (LPBYTE)pOutString;

  DWORD dwDisposition; 
  HKEY phkResult = 0;
  HKEY hKey = 0;

  HKEY v13 = 0;
  HKEY v14 = 0;
  v4 = RegCloseKey;

  if (RegOpenKeyExA(HKEY_CURRENT_USER, MAINKEY, 0, 0x2001Fu, &hKey)
    || RegCreateKeyExA(hKey, SUBKEY, 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)
    || RegCreateKeyExA(phkResult, SUBKEY2, 0, "", 0, 0xF003Fu, 0, &v13, &dwDisposition)

    || RegCreateKeyExA(v13, pKeyName, 0, "", 0, 0xF003Fu, 0, &v14, &dwDisposition))
    strncpy((char*)pOutString, pDefaultValue, uBufLen);
  else if (RegQueryValueExA(v14, pKeyName, 0, &Type, pOutString, &cbData)) {

    RegCloseKey(v14);
    v14 = 0;
    //result = (LSTATUS)strncpy((char*)Dest, pDefaultValue, uBufLen);
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
WriteWindowsRegistryInt(const char* pKey, int val)
{
  BYTE Data[4];
  DWORD dwDisposition;
  HKEY v8 = 0;

  HKEY hKey = 0;
  HKEY phkResult = 0;
  HKEY v7 = 0;

  *(int*)Data = val;

  if(!RegOpenKeyExA(HKEY_CURRENT_USER, MAINKEY, 0, 0x2001Fu, &hKey)) {
    if (!RegCreateKeyExA(hKey, SUBKEY, 0, "", 0, 0xF003Fu, 0, &phkResult, &dwDisposition)) {
      if(!RegCreateKeyExA(phkResult, SUBKEY2, 0, "", 0, 0xF003Fu, 0, &v7, &dwDisposition)) {

        if(!RegCreateKeyExA(v7, VERKEY, 0, "", 0, 0xF003Fu, 0, &v8, &dwDisposition)) {
          RegSetValueExA(v8, pKey, 0, 4, Data, 4);
          RegCloseKey(v8);
        }
        RegCloseKey(v7);
      }
      RegCloseKey(phkResult);
    }
    RegCloseKey(hKey);
  }
}
