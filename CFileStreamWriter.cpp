#include "stdafx.h"
#include "CFileStreamWriter.h"


extern int g_cLocks;


// IUnknown
// ********

ULONG __stdcall CFileStreamWriter::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CFileStreamWriter::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CFileStreamWriter::QueryInterface(REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if(riid == IID_StreamWriter)
		*ppv = (StreamWriter*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();

	return S_OK;
}




CFileStreamWriter::CFileStreamWriter(BSTR fileName) : m_cRef(1)
{
	// Initialize class variables
	status = 0;

	// Open the file
	hFile = CreateFileW(fileName,		// lpFileName
						GENERIC_WRITE,	// dwDesired access
						0,				// dwShareMode
						NULL,			// lpSecurityAttributes
						CREATE_ALWAYS,	// dwCreationDisposition
						FILE_ATTRIBUTE_NORMAL |
						FILE_FLAG_SEQUENTIAL_SCAN,
										// dwFlagsAndAttributes
						NULL			// hTemplate
						);

	// Check if the file was opened successfully
	if (hFile == INVALID_HANDLE_VALUE)
		throw L"Could not open file for writing.";

	// Check for alternate error
	if (hFile == 0)
	{
		// Try to open the file using ANSI version of CreateFile

		// Allocate space for a temporary ASCII fileName string
		int stringLength = SysStringLen(fileName);
		char *tempString = new char[stringLength+1];
		tempString[stringLength] = 0;				// NULL terminate it
		// Convert the BSTR to ASCII
		WideCharToMultiByte(CP_ACP, 0, fileName, stringLength, tempString, stringLength, 0, 0);

		// Try to open the file with ANSI version of CreateFile
		hFile = CreateFileA(tempString,		// lpFileName
							GENERIC_WRITE,	// dwDesired access
							0,				// dwShareMode
							NULL,			// lpSecurityAttributes
							CREATE_ALWAYS,	// dwCreationDisposition
							FILE_ATTRIBUTE_NORMAL |
							FILE_FLAG_SEQUENTIAL_SCAN,
											// dwFlagsAndAttributes
							NULL			// hTemplate
						);

		// Check for errors
		if (hFile == INVALID_HANDLE_VALUE)
			throw L"Could not open file for writing.";
	}

	g_cLocks++;

}

CFileStreamWriter::~CFileStreamWriter()
{
	CloseHandle(hFile);

	g_cLocks--;
}


HRESULT CFileStreamWriter::Write(int numBytes, int pBuffer, int *numBytesWritten)
{
	BOOL bResult;
	unsigned long numberOfBytesWritten;

	// Read in the info
	bResult = WriteFile(hFile, (void*)pBuffer, numBytes, &numberOfBytesWritten, NULL);
	*numBytesWritten = numberOfBytesWritten;

	// Adjust the status of the stream
	if ((bResult == 0) || (*numBytesWritten < numBytes))
	{
		// An error occured or not all bytes were written
		status = 1;		// Nonzero denotes error
	}

	return S_OK;
}

HRESULT CFileStreamWriter::get_Status(int *status)
{
	*status = this->status;

	return S_OK;
}
