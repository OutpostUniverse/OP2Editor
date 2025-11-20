// OP2Editor.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL,
//      run nmake -f OP2Editorps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "OP2Editor.h"

#include "OP2Editor_i.c"

#include "CFileStreamReader.h"
#include "CFileStreamWriter.h"
#include "CResourceManager.h"
#include "CResourceManagerFactory.h"


int g_cLocks = 0;
HINSTANCE g_hInstance = NULL;


// DLL Entry Point
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInstance;
		DisableThreadLibraryCalls(hInstance);
	}

	return TRUE;    // ok
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	if (g_cLocks == 0)
		return S_OK;
	else
		return S_FALSE;
}

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if(rclsid != CLSID_ResourceManager)
		return CLASS_E_CLASSNOTAVAILABLE;

	CResourceManagerFactory *pFactory = new CResourceManagerFactory();
	if(pFactory == NULL)
		return E_OUTOFMEMORY;

	// riid is probably IID_IClassFactory.
	HRESULT hr = pFactory->QueryInterface(riid, ppv);
	pFactory->Release();    // Just in case QueryInterface fails
	return hr;
}

// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	HKEY hSubKey;
	TCHAR path[MAX_PATH];
	DWORD creationDisposition;
	int pathLen;
	int retVal;

	pathLen = GetModuleFileName(g_hInstance, path, MAX_PATH);
	retVal = RegCreateKeyEx(HKEY_CLASSES_ROOT,
				TEXT("CLSID\\{C8DE4CDE-4554-4fe9-8688-A90D91EBCA0B}\\InprocServer32"),
				0,
				TEXT(""),
				REG_OPTION_NON_VOLATILE,
				KEY_ALL_ACCESS,
				NULL,
				&hSubKey,
				&creationDisposition);
	if (retVal != ERROR_SUCCESS)
		return HRESULT_FROM_WIN32(retVal);
	retVal = RegSetValueEx(hSubKey, TEXT(""), 0, REG_SZ, (BYTE*)path, pathLen);
	RegCloseKey(hSubKey);

	return HRESULT_FROM_WIN32(retVal);
}

// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	int retVal;

	retVal = RegDeleteKey(HKEY_CLASSES_ROOT,
						TEXT("CLSID\\{C8DE4CDE-4554-4fe9-8688-A90D91EBCA0B}\\InprocServer32"));
	retVal = RegDeleteKey(HKEY_CLASSES_ROOT,
						TEXT("CLSID\\{C8DE4CDE-4554-4fe9-8688-A90D91EBCA0B}"));

	return HRESULT_FROM_WIN32(retVal);
}
