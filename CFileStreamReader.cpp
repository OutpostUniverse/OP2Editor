
#include "stdafx.h"
#include "CFileStreamReader.h"


extern int g_cLocks;


// IUnknown
// ********

ULONG __stdcall CFileStreamReader::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CFileStreamReader::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CFileStreamReader::QueryInterface(REFIID riid, void** ppv)
{
    if(riid == IID_IUnknown)
        *ppv = (IUnknown*)this;
    else if(riid == IID_StreamReader)
        *ppv = (StreamReader*)this;
    else if(riid == IID_SeekableStreamReader)
        *ppv = (SeekableStreamReader*)this;
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();

    return S_OK;
}



// StreamReader
// ************

HRESULT CFileStreamReader::Read(int numBytes, int pBuffer, int *numBytesRead)
{
	BOOL bResult;
	unsigned long numberOfBytesRead;

	// Read in the info
	bResult = ReadFile(hFile, (void*)pBuffer, numBytes, &numberOfBytesRead, NULL);
	*numBytesRead = numberOfBytesRead;

	// Adjust the status of the stream
	if ((bResult == 0) || (*numBytesRead < numBytes))
	{
		if (bResult == 0)
			OutputDebugStringW(L"Error. ReadFile error.");
		else if (*numBytesRead < numBytes)
			OutputDebugStringW(L"End of file reached.");
		// An error occured or a read past EOF occured
		status = 1;		// Nonzero denotes error
	}

	return S_OK;
}

HRESULT CFileStreamReader::get_Status(int *status)
{
	*status = this->status;

	return S_OK;
}

// SeekableStreamReader
// ********************

HRESULT CFileStreamReader::get_ReadOffset(int *readOffset)
{
	*readOffset = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

	return S_OK;
}

HRESULT CFileStreamReader::get_StreamSize(int *streamSize)
{
	*streamSize = GetFileSize(hFile, NULL);

	return S_OK;
}

HRESULT CFileStreamReader::Seek(int offset)
{
	if (SetFilePointer(hFile, offset, NULL, FILE_BEGIN) == -1)
	{
		// Seek error.
		status = 1;	// Error

		return E_FAIL;
	}

	return S_OK;
}




// Class specific
// **************

CFileStreamReader::CFileStreamReader(BSTR fileName) : m_cRef(1)
{
	// Initialize class variables
	status = 0;

	// Open the file
	hFile = CreateFileW(fileName,		// lpFileName
						GENERIC_READ,	// dwDesired access
						FILE_SHARE_READ,// dwShareMode
						NULL,			// lpSecurityAttributes
						OPEN_EXISTING,	// dwCreationDisposition
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
							GENERIC_READ,	// dwDesired access
							FILE_SHARE_READ,// dwShareMode
							NULL,			// lpSecurityAttributes
							OPEN_EXISTING,	// dwCreationDisposition
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

CFileStreamReader::~CFileStreamReader()
{
	CloseHandle(hFile);

	g_cLocks--;
}
