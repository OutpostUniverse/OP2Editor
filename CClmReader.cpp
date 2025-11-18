
#include "stdafx.h"
#include "CClmReader.h"
#include "CMemoryStreamReader.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


const char CClmReader::tagClmFile[] = "OP2 Clump File Version 1.0\x01A";


ULONG __stdcall CClmReader::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CClmReader::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CClmReader::QueryInterface(REFIID riid, void** ppv)
{
    if(riid == IID_IUnknown)
        *ppv = (IUnknown*)this;
    else if(riid == IID_ArchiveReader)
        *ppv = (ArchiveReader*)this;
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();

    return S_OK;
}



// ArchiveReader
// *************

HRESULT CClmReader::get_NumFiles(int *numFiles)
{
	*numFiles = this->numFiles;

	return S_OK;
}

HRESULT CClmReader::get_FileName(int index, BSTR *fileName)
{
	int stringLength;

	// Cache string length
	for (stringLength = 0; stringLength < 8; stringLength++)
		if (indexTable[index].fileName[stringLength] == NULL) break;
	// Allocate space for the string
	SysReAllocStringLen(fileName, NULL, stringLength);
	// Convert the string to Unicode
	MultiByteToWideChar(CP_ACP, 0, indexTable[index].fileName,
						stringLength, *fileName, stringLength);

	return S_OK;
}

HRESULT CClmReader::OpenStreamRead(BSTR fileName, StreamReader **stream)
{
	int fileIndex;
	int numBytesRead;
	CMemoryStreamReader *memStream;
	HRESULT hr;
	LPVOID buffer;
	int bAttachToBuffer = 0;

	// Initialize returned stream pointer to NULL
	*stream = NULL;

	// Lookup the filename in the index
	fileIndex = GetFileIndex(fileName);
	// Check if the file was not found
	if (fileIndex == -1)
	{
		// File was not found
		return E_INVALIDARG;
	}

	// Cache the data buffer pointer
	buffer = dataBuffer[fileIndex];
	// Check if data hasn't been loaded yet
	if (buffer == NULL)
	{
		// Load the data from the stream
		// Allocate a buffer for this file
		buffer = new char[indexTable[fileIndex].size];

		// Seek to the start of the file
		attachedStream->Seek(streamStartOffset + indexTable[fileIndex].offset);
		// Read in the file data
		attachedStream->Read(indexTable[fileIndex].size, (int)dataBuffer[fileIndex], &numBytesRead);

		bAttachToBuffer = 1;
	}

	// Create a stream to read the data
	try
	{
		// **TODO** Create a new reader class that will load data
		// from the origianl CLM file. Would make rebuilding the
		// CLM file much less memory intensive.

		// Create a memory stream reading with the file contents
		memStream = new CMemoryStreamReader(indexTable[fileIndex].size,
											(char*)(dataBuffer[fileIndex]),
											bAttachToBuffer);
		if (memStream == NULL)
		{
			// Check if buffer is discardable
			if (bAttachToBuffer == 1)
				delete [] buffer;
			// Return error code
			return E_OUTOFMEMORY;
		}
	}
	catch(...)
	{
		// Check if buffer is discardable
		if (bAttachToBuffer == 1)
			delete [] buffer;
		// Return error code
		return E_FAIL;
	}

	hr = memStream->QueryInterface(IID_StreamReader, (void**)stream);
	memStream->Release();

	return hr;
}




// Class specific
// **************

CClmReader::CClmReader(SeekableStreamReader *inStream, int bAttachToStream) : m_cRef(1)
{
	// Initialize variables
	numFiles = 0;
	indexTable = NULL;
	dataBuffer = NULL;
	attachedStream = NULL;

	// Check if reader should attach to the stream
	if (bAttachToStream == 1)
	{
		attachedStream = inStream;
		inStream->AddRef();
	}


	// Load the Clm info from the stream
	if (LoadClm(inStream, bAttachToStream) != 0)
	{
		// Error loading Clm info
		FreeMemory();
		throw L"Error loading CLM info.";
	}

	g_cLocks++;
}

CClmReader::~CClmReader()
{
	g_cLocks--;

	FreeMemory();

	// Check if reader attached to a stream
	if (attachedStream != NULL)
		attachedStream->Release();
}


void CClmReader::FreeMemory()
{
	unsigned int i;

	// Check if the index table needs to be deleted
	if (indexTable != NULL)
		delete [] indexTable;				// Delete the index table
	// Check if the array of data buffer pointers needs to be deleted
	if (dataBuffer != NULL)
	{
		// Release each data buffer
		for (i = 0; i < numFiles; i++)
		{
			// Check if the data buffer exists
			if (dataBuffer[i] != NULL)
				delete [] dataBuffer[i];	// Delete the data buffer
		}

		// Delete the array of data buffer pointers
		delete [] dataBuffer;
	}

	// Reset variables
	indexTable = NULL;
	dataBuffer = NULL;
	numFiles = 0;
}


int CClmReader::GetFileIndex(BSTR fileName)
{
	int stringLength;
	char *tempString;
	unsigned int i;

	// Allocate space for a temporary ASCII fileName string
	stringLength = SysStringLen(fileName);
	tempString = new char[stringLength+1];
	tempString[stringLength] = 0;				// NULL terminate it
	// Convert the BSTR to ASCII
	WideCharToMultiByte(CP_ACP, 0, fileName, stringLength, tempString, stringLength, 0, 0);

	// **TODO** Improve this to a binary search? Or is that not general enough
	//          Outpost2 doesn't seem to require a sorted index

	// Perform a linear search of the index
	for (i = 0; i < numFiles; i++)
	{
		// Check if fileName matches this index entry
		if (strncmp(indexTable[i].fileName, tempString, 8) == 0)
		{
			// File names match. Return index
			delete [] tempString;
			return i;
		}
	}

	delete [] tempString;
	return -1;				// File not found
}

int CClmReader::LoadClm(SeekableStreamReader *inStream, int bAttachToStream)
{
	char buff[32];
	int numBytesRead;
	unsigned int i, j, maxOffset;

	try
	{
		// Record the starting stream position for later seeking
		// (Note: This allows CLM contents to be part of a larger stream)
		inStream->get_ReadOffset(&streamStartOffset);

		// Read header tag
		inStream->Read(32, (int)buff, &numBytesRead);
		// Check if header tag is invalid
		if (strncmp(buff, tagClmFile, 32) != 0)
			throw L"Format Error. Invalid Clump file header tag.";

		// Read WAVEFORMATEX structure
		inStream->Read(sizeof(waveFormat), (int)&waveFormat, &numBytesRead);
		// Check for format errors
		if (waveFormat.wFormatTag != WAVE_FORMAT_PCM)
			throw L"Format Error. Wave format is not encoded as WAVE_FORMAT_PCM.";
		if (waveFormat.nChannels != 1)
			throw L"Format Error. Wave format is not mono channel.";
		if (waveFormat.nBlockAlign != 2)
			throw L"Format Error. Wave format is not block aligned on a 2 byte boundary.";
		if (waveFormat.nSamplesPerSec != 22050)
			throw L"Format Error. Wave format is not 22050 samples per second.";

		// Pass over alignment bytes
		inStream->Read(2, (int)buff, &numBytesRead);

		// Read ??? **TODO** Find out what this DWORD means
		inStream->Read(4, (int)&unknown, &numBytesRead);

		// Read numFiles stored in CLM
		inStream->Read(4, (int)&numFiles, &numBytesRead);

		// Allocate space for CLM index table
		indexTable = new IndexEntry[numFiles];

		// Read CLM index table
		inStream->Read(numFiles*sizeof(IndexEntry), (int)indexTable, &numBytesRead);

		// Allocate space to hold all the file buffer pointers
		dataBuffer = new LPVOID[numFiles];
		memset(dataBuffer, 0, numFiles*sizeof(LPVOID));

		// Check if data needs to be loaded into memory
		if (bAttachToStream == 0)
		{
			// Data must be loaded into memory
			// Load each internal file
			for (i = 0; i < numFiles; i++)
			{
				// Allocate a buffer for this file
				dataBuffer[i] = new char[indexTable[i].size];

				// Seek to the start of the file
				inStream->Seek(streamStartOffset + indexTable[i].offset);
				// Read in the file data
				inStream->Read(indexTable[i].size, (int)dataBuffer[i], &numBytesRead);
			}
		}

		// Determine maximum offset of CLM data
		maxOffset = 0;
		j = 0;
		for (i = 0; i < numFiles; i++)
		{
			j = indexTable[i].offset + indexTable[i].size;
			if (j > maxOffset)
				maxOffset = j;
		}
		if (maxOffset < 0x3C + numFiles*sizeof(IndexEntry) + 1)
			maxOffset = 0x3C + numFiles*sizeof(IndexEntry) + 1;
		// Seek to end of CLM data
		inStream->Seek(streamStartOffset + maxOffset);
	}
	catch(WCHAR *errorMsg)
	{
		// Return a COM error message
		PostErrorMsg(errorMsg);
		return 1;	// Failed to load file
	}
	catch(...)
	{
		// Error loading Clm data
		return -1;	// Failed to load file
	}

	return 0;	// Success
}
