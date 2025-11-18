
#include "stdafx.h"
#include "CMemoryStreamReader.h"


extern int g_cLocks;


// IUnknown
// ********

ULONG __stdcall CMemoryStreamReader::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CMemoryStreamReader::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CMemoryStreamReader::QueryInterface(REFIID riid, void** ppv)
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

HRESULT CMemoryStreamReader::Read(int numBytes, int pBuffer, int *numBytesRead)
{
	// Initialize returned number of bytes read to 0
	*numBytesRead = 0;

	// Check for read past end of stream
	if (readPtr >= bufferSize)
	{
		// Error. Read past end of stream
		streamStatus = 1;	// Error. Read past end of stream
		return E_FAIL;
	}
	// Default to number of bytes requested
	*numBytesRead = numBytes;
	// Check for partial read past end of stream
	if (readPtr + numBytes > bufferSize)
	{
		// Adjust number of bytes to read
		streamStatus = 1;	// Error. Read past end of stream
		*numBytesRead = bufferSize - readPtr;
	}

	// Perform a memory copy
	memcpy((void*)pBuffer, &streamBuffer[readPtr], *numBytesRead);

	// Update the read pointer
	readPtr += *numBytesRead;

	return S_OK;
}

HRESULT CMemoryStreamReader::get_Status(int *status)
{
	*status = streamStatus;

	return S_OK;
}


// SeekableStreamReader
// ********************

HRESULT CMemoryStreamReader::get_ReadOffset(int *readOffset)
{
	*readOffset = readPtr;

	return S_OK;
}

HRESULT CMemoryStreamReader::get_StreamSize(int *streamSize)
{
	*streamSize = bufferSize;

	return S_OK;
}

HRESULT CMemoryStreamReader::Seek(int offset)
{
	if (offset < bufferSize)
		readPtr = offset;

	return S_OK;
}


// Class specific
// **************

CMemoryStreamReader::CMemoryStreamReader(int streamLength, char *buffer, int bAttachToBuffer)
		: m_cRef(1)
{
	// Initialize variables
	streamStatus = 0;
	readPtr = 0;
	bufferSize = streamLength;

	if (bAttachToBuffer == 0)
	{
		// Allocate space for stream data
		streamBuffer = new char[bufferSize];
		// Copy the data into the buffer
		memcpy(streamBuffer, buffer, bufferSize);
	}
	else
		streamBuffer = buffer;

	g_cLocks++;
}

CMemoryStreamReader::~CMemoryStreamReader()
{
	delete [] streamBuffer;

	g_cLocks--;
}
