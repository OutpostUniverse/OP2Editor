
#include "stdafx.h"
#include "GlobalFunctions.h"



void PostErrorMsg(WCHAR *errorMsg)
{
	// Provide rich error information
    // Create generic error object.
    ICreateErrorInfo* pCreateErrorInfo;
    if (FAILED(CreateErrorInfo(&pCreateErrorInfo)))
		return;

    // Set rich error information.
	pCreateErrorInfo->SetDescription(errorMsg);
    //pCreateErrorInfo->SetGUID(IID_MapFile);

    // Exchange ICreateErrorInfo for IErrorInfo.
    IErrorInfo* pErrorInfo;
    pCreateErrorInfo->QueryInterface(IID_IErrorInfo, 
        (void**)&pErrorInfo);

    // Make the error information available to the client.
    SetErrorInfo(NULL, pErrorInfo);

    // Release the interface pointers.
    pErrorInfo->Release();
    pCreateErrorInfo->Release();
}


bool IsRelative(BSTR path)
{
	// Check if the first character is a "\"
	if (path[0] == L'\\')
		return false;	// Absolute path

	// Check for embedded ":"
	if (wcschr(path, L':') != NULL)
		return false;	// Absolute path

	// Relative path
	return true;
}


int RoundUpPowerOf2(int num)
{
	num = num - 1;
	num = num | (num >> 1);
	num = num | (num >> 2);
	num = num | (num >> 4);
	num = num | (num >> 8);
	num = num | (num >> 16);
	num += 1;

	return num;
}


int LogBase2(int num)
{
	int log = 31;
	int y;

	y = num <<16;  if (y != 0) {log = log -16;  num = y;}
	y = num << 8;  if (y != 0) {log = log - 8;  num = y;}
	y = num << 4;  if (y != 0) {log = log - 4;  num = y;}
	y = num << 2;  if (y != 0) {log = log - 2;  num = y;}
	y = num << 1;  if (y != 0) {log = log - 1;}

	return log;
}
