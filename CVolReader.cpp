#include "stdafx.h"
#include "CVolReader.h"
#include "CMemoryStreamReader.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


ULONG __stdcall CVolReader::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CVolReader::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CVolReader::QueryInterface(REFIID riid, void** ppv)
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

HRESULT CVolReader::get_NumFiles(int *numFiles)
{
	*numFiles = this->numFiles;

	return S_OK;
}

HRESULT CVolReader::get_FileName(int index, BSTR *fileName)
{
	char *string;
	int stringLength;

	// Cache string address
	string = (char*)stringBuffer + indexTable[index].fileNameOffset;
	stringLength = strlen(string);
	// Allocate space for the string
	SysReAllocStringLen(fileName, NULL, stringLength);
	// Convert the string to Unicode
	MultiByteToWideChar(
		CP_ACP,
		0,
		string,
		stringLength,
		*fileName,
		stringLength
	);

	return S_OK;
}

HRESULT CVolReader::OpenStreamRead(BSTR fileName, StreamReader **stream)
{
	int fileIndex;
	HRESULT hr;
	int bAttachToBuffer = 0;
	LPVOID buffer;

	// Initialize returned stream pointer to NULL
	*stream = NULL;

	// Lookup the filename in the index
	fileIndex = GetFileIndex(fileName);
	// Check if the file was not found
	if (fileIndex == -1)
	{
		// File was not found
		PostErrorMsg(L"File not found in archive.");
		return E_INVALIDARG;
	}

	// Store a pointer to the data buffer
	buffer = dataBuffer[fileIndex];
	// Check if data is loaded into memory
	if (buffer == NULL)
	{
		// Data is not loaded into memory.
		// Check if attached stream does not exist
		if (attachedStream == NULL)
		{
			// No data source. Failed.
			PostErrorMsg(L"No data source.");
			return E_FAIL;
		}

		// Load the data from the stream
		// *****************************
		SectionHeader sectHead;
		int numBytesRead;

		// Seek to begining of internal file data
		attachedStream->Seek(streamStartOffset + indexTable[fileIndex].dataOffset);
		// Read the "VBLK" section header
		attachedStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
		if (sectHead.tag != 'KLBV')		// "VBLK"
		{
			PostErrorMsg(L"Invalid format. VBLK not found.");
			return E_FAIL;	// Error. Format error.
		}
		//if (sectHead.sectionSize != indexTable[fileIndex].fileSize)
		//	return 1;	// Error. Format error.

		// Allocate space for the file data
		buffer = new char[sectHead.sectionSize];
		// Read the file data
		attachedStream->Read(sectHead.sectionSize, (int)buffer, &numBytesRead);

		// Mark the buffer as discardable
		bAttachToBuffer = 1;
	}

	try
	{
		// Determine which type of stream reader to construct to read the file
		switch(indexTable[fileIndex].encoding)
		{
		case 0:		// Raw uncompressed data
			// Copy the data into a memory stream
			CMemoryStreamReader *rawStream;

			rawStream = new CMemoryStreamReader(
				indexTable[fileIndex].fileSize,
				(char*)buffer,
				bAttachToBuffer
			);
			if (rawStream == NULL)
			{
				if (bAttachToBuffer == 1)
					delete [] buffer;	// Delete discardable buffer
				PostErrorMsg(L"Could not create memory stream reader. Out of memory.");
				return E_OUTOFMEMORY;
			}

			hr = rawStream->QueryInterface(IID_StreamReader, (void**)stream);
			rawStream->Release();

			return hr;
			break;

		case 1:		// Unknown **TODO** Find out
			break;
		case 2:		// Unknown **TODO** Find out
			break;
		case 3:		// AdaptiveHuffman+RepeatedBlocks
			// **TODO** Implement
			break;
		default:
			// **TODO** Implement
			break;
		}
	}
	catch(...)
	{
		// Failed to create a StreamReader object
		// Check if buffer is discardable
		if (bAttachToBuffer == 1)
			delete [] buffer;
		PostErrorMsg(L"Could not create memory stream reader.");
		return E_FAIL;
	}

	// Failed to open the stream
	if (bAttachToBuffer == 1)
		delete [] buffer;		// Release the discardable buffer

	PostErrorMsg(L"Could not open stream.");
	return E_FAIL;
}


// Class specific
// **************

CVolReader::CVolReader(SeekableStreamReader *inStream, int bAttachToStream) : m_cRef(1)
{
	numFiles = 0;
	stringBuffer = NULL;
	indexTable = NULL;
	dataBuffer = NULL;
	streamStartOffset = 0;

	// Check if stream is to be attached or loaded completely
	if (bAttachToStream)
	{
		attachedStream = inStream;	// Record attached stream
		inStream->AddRef();
	}
	else
		attachedStream = NULL;		// No attached stream

	if (LoadVol(inStream, bAttachToStream) != 0)
	{
		// Error loading file
		FreeMemory();

		throw 0;	// Abort object construction
	}

	g_cLocks++;
}

CVolReader::~CVolReader()
{
	FreeMemory();

	g_cLocks--;

	// Check if an attached stream exists
	if (attachedStream)
	{
		// Release attached stream
		attachedStream->Release();
	}
}


void CVolReader::FreeMemory()
{
	unsigned int i;

	if (stringBuffer != NULL)
		delete [] stringBuffer;
	if (indexTable != NULL)
		delete [] indexTable;
	if (dataBuffer != NULL)
	{
		for (i = 0; i < numFiles; i++)
		{
			// Check if file data is buffered in memory
			if (dataBuffer[i] != NULL)
				delete [] dataBuffer[i];	// Delete buffered memory
		}

		// Delete list of memory buffers
		delete [] dataBuffer;
	}

	// Reset variables
	stringBuffer = NULL;
	indexTable = NULL;
	dataBuffer = NULL;
	numFiles = 0;
}

// - Reads in VOL file data from the input stream.
// - Returns 0 if successful and nonzero if an error occured.
// - Memory cleanup after errors is not supported by this function
// so if an error is detected, FreeMemory should be called after
// this function returns. Note that this requires memory pointers
// to be initialized to NULL before calling LoadVol.
// - bAttachToStream will cause only the index to be read from the
// stream since the stream will later be available when loading
// internal archive file data.
int CVolReader::LoadVol(SeekableStreamReader *inStream, int bAttachToStream)
{
	SectionHeader sectHead;
	int numBytesRead;
	unsigned int totalHeaderSize;
	unsigned int stringTableSize;
	unsigned int indexTableSize;
	unsigned int maxOffset;
	unsigned int i, j;

	try{
		// Record the starting stream position for later seeking
		// (Note: This allows VOL contents to be part of a larger stream)
		inStream->get_ReadOffset(&streamStartOffset);

		// Read the "VOL " section
		inStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
		if (sectHead.tag != ' LOV')		// "Vol "
			throw L"Format error. 'VOL ' tag not found.";
		totalHeaderSize = sectHead.sectionSize;
		// Read the "volh" section
		inStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
		if (sectHead.tag != 'hlov')		// "volh"
			throw L"Format error. 'volh' tag not found";
		if (sectHead.sectionSize != 0)
			throw L"Format error. 'volh' section size is not 0.";

		// Read the "vols" section
		inStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
		if (sectHead.tag != 'slov')		// "vols"
			throw L"Format error. 'vols' section not found.";
		stringTableSize = sectHead.sectionSize - 4;
		// Read the actual size of the string data
		inStream->Read(4, (int)&actualStringDataLen, &numBytesRead);
		if (actualStringDataLen > stringTableSize)
			throw L"Format error. String data exceeds string section size.";
		// Allocate space for the string table
		stringBuffer = new char[stringTableSize];
		// Read the string table
		inStream->Read(stringTableSize, (int)stringBuffer, &numBytesRead);

		// Read the "voli" section
		inStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
		if (sectHead.tag != 'ilov')		// "voli"
			throw L"Format error. 'voli' tag not found.";
		indexTableSize = sectHead.sectionSize;
		//if (totalHeaderSize != stringTableSize + 4 + indexTableSize + sizeof(sectHead)*3)
		//	return 1;	// Error. Format error.
		// Calculate number of index entries stored in Vol file (round up)
		numIndexEntries = (sectHead.sectionSize + sizeof(IndexEntry) - 1) / sizeof(IndexEntry);
		// Allocate space for the index table
		indexTable = new IndexEntry[numIndexEntries];
		// Read in the index table
		inStream->Read(sectHead.sectionSize, (int)indexTable, &numBytesRead);
		// Fnid the number of used entries
		numFiles = sectHead.sectionSize / sizeof(IndexEntry);
		while ((numFiles > 0) && (indexTable[numFiles-1].boolUsed != 1))
			numFiles--;

		// Allocate space for data buffer pointers
		dataBuffer = new LPVOID[numFiles];
		memset(dataBuffer, 0, numFiles*4);

		// Read in file data blocks
		for (i = 0; i < numFiles; i++)
		{
			// Seek to begining of internal file data
			inStream->Seek(streamStartOffset + indexTable[i].dataOffset);
			// Read the "VBLK" section header
			inStream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
			if (sectHead.tag != 'KLBV')		// "VBLK"
				throw L"Format error. 'VBLK' tag not found at data offset";
			//if (sectHead.sectionSize != indexTable[i].fileSize)
			//	return 1;	// Error. Format error.

			if (!bAttachToStream)
			{
				// Allocate space for the file data
				dataBuffer[i] = new char[sectHead.sectionSize];
				// Read the file data
				inStream->Read(sectHead.sectionSize, (int)dataBuffer[i], &numBytesRead);
			}
		}

		// Determine maximum offset of VOL data
		maxOffset = 0;
		j = 0;
		for (i = 0; i < numFiles; i++)
		{
			j = indexTable[i].dataOffset + indexTable[i].fileSize;
			if (j > maxOffset)
				maxOffset = j;
		}
		if (maxOffset < totalHeaderSize + sizeof(sectHead) + 1)
			maxOffset = totalHeaderSize + sizeof(sectHead) + 1;
		// Seek to end of VOL data
		inStream->Seek(streamStartOffset + maxOffset);
	}
	catch(WCHAR *errorMsg)
	{
		PostErrorMsg(errorMsg);
		return -1;		// Error
	}
	catch(...)
	{
		return -1;		// Error
	}


	return 0;	// Success
}


int CVolReader::GetFileIndex(BSTR fileName)
{
	int startIndex, endIndex, middleIndex;
	int result;
	int stringLength;
	char *tempString;

	// Allocate space for a temporary ASCII fileName string
	stringLength = SysStringLen(fileName);
	tempString = new char[stringLength+1];
	tempString[stringLength] = 0;				// NULL terminate it
	// Convert the BSTR to ASCII
	WideCharToMultiByte(CP_ACP, 0, fileName, stringLength, tempString, stringLength, 0, 0);

	// Search index for file
	startIndex = 0;
	endIndex = numFiles - 1;
	while (startIndex <= endIndex)
	{
		// Get the midpoint
		middleIndex = (startIndex + endIndex) >> 1;
		// Check if strings match
		result = strncmp(
			(char*)stringBuffer + indexTable[middleIndex].fileNameOffset,
			tempString,
			stringLength
		);
		if (result == 0)
		{
			// String match
			delete [] tempString;
			return middleIndex;
		}
		if (result < 0)
		{
			// Search top half of index table
			startIndex = middleIndex + 1;
		}
		else	// result > 0
		{
			// Search bottom half of index table
			endIndex = middleIndex - 1;
		}
	}

	// File not found
	delete [] tempString;
	return -1;
}
