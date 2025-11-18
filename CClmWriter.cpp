
#include "stdafx.h"
#include "CClmWriter.h"


extern int g_cLocks;


const char CClmWriter::tagClmFile[32] = "OP2 Clump File Version 1.0\x01A";


ULONG __stdcall CClmWriter::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CClmWriter::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CClmWriter::QueryInterface(REFIID riid, void** ppv)
{
    if(riid == IID_IUnknown)
        *ppv = (IUnknown*)this;
    else if(riid == IID_ArchiveWriter)
        *ppv = (ArchiveWriter*)this;
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();

    return S_OK;
}



// ArchiveWriter
// *************

HRESULT CClmWriter::AddToArchive(BSTR fileName, SeekableStreamReader *inStream, int reserved)
{
	LinkedListNode *newNode;
	int stringLength;

	// Check for invalid parameters
	if (reserved != 0)
		return E_INVALIDARG;
	if (inStream == NULL)
		return E_INVALIDARG;
	stringLength = SysStringLen(fileName);			// Cache the string length
	if (stringLength > 8)
		return E_INVALIDARG;

	// Create a new linked list node to hold the data
	newNode = new LinkedListNode;
	memset(newNode->indexEntry.fileName, 0, 8);		// NULL pad the string/initialize
	// Convert the filename from UNICODE to ASCII
	WideCharToMultiByte(CP_ACP, 0, fileName, stringLength, newNode->indexEntry.fileName, stringLength, 0, 0);
	// Store the stream pointer
	newNode->inStream = inStream;
	inStream->AddRef();
	// Store the starting stream offset and data size
	inStream->get_ReadOffset(&newNode->streamStartOffset);
	inStream->get_StreamSize(&newNode->indexEntry.dataSize);
	newNode->indexEntry.dataSize -= newNode->streamStartOffset;	// Adjust for start of data

	// Store the new node to the linked list
	newNode->next = head;
	head = newNode;
	numNodes++;

	// Update max data size
	if (newNode->indexEntry.dataSize > maxDataSize)
		maxDataSize = newNode->indexEntry.dataSize;

	return S_OK;
}

HRESULT CClmWriter::WriteArchive(StreamWriter *outStream)
{
	WAVEFORMATEX waveFormat;
	int temp = 0;				// Used for NULL padding
	int offset;
	int numBytesWritten;
	LinkedListNode *current;
	char *buffer = NULL;

	// Sort the index
	head = SortIndex(head);

	// Prepare WAVEFORMATEX structure
	// ******************************
	waveFormat.cbSize = sizeof(WAVEFORMATEX);
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = 1;
	waveFormat.nSamplesPerSec = 22050;
	waveFormat.nAvgBytesPerSec = 44100;
	waveFormat.nBlockAlign = 2;
	waveFormat.wBitsPerSample = 16;

	// Create a write buffer
	buffer = new char[maxDataSize];
	if (buffer == NULL)
		return E_OUTOFMEMORY;

	// Begin writing the CLM file contents
	// ***********************************

	// Write out the header
	// ********************
	// Write the header tag
	outStream->Write(32, (int)tagClmFile, &numBytesWritten);
	// Write the WAVEFORMATEX structure
	outStream->Write(sizeof(WAVEFORMATEX), (int)&waveFormat, &numBytesWritten);
	// Pad with NULL bytes
	outStream->Write(2, (int)&temp, &numBytesWritten);
	// Write unknown DWORD **TODO** Find out what this DWORD means
	outStream->Write(4, (int)&unknown, &numBytesWritten);
	// Write out the number of files stored in archive
	outStream->Write(4, (int)&numNodes, &numBytesWritten);

	// Write out the index table
	// *************************
	// Calculate the starting data offset
	offset = 32 + sizeof(WAVEFORMATEX) + 2 + 4 + 4 + numNodes*sizeof(IndexEntry);
	current = head;
	while (current)
	{
		// Store the offset to the data
		current->indexEntry.dataOffset = offset;
		// Update the current data offset
		offset += (current->indexEntry.dataSize + 3) & ~3;
		// Write out the index entry
		outStream->Write(sizeof(IndexEntry), (int)&current->indexEntry, &numBytesWritten);
		// Process next node
		current = current->next;
	}

	// Write out the file data
	// ***********************
	current = head;
	while (current)
	{
		// Seek to the start of the file data
		current->inStream->Seek(current->streamStartOffset);
		// Read in the file data
		current->inStream->Read(current->indexEntry.dataSize, (int)buffer, &numBytesWritten);
		// Write out the file data
		outStream->Write(current->indexEntry.dataSize, (int)buffer, &numBytesWritten);
		// Pad with NULL bytes
		outStream->Write(-current->indexEntry.dataSize & 3, (int)&temp, &numBytesWritten);
		// Proccess next node
		current = current->next;
	}

	// Release the write buffer
	delete [] buffer;

	return S_OK;
}


// Class specific
// **************

CClmWriter::CClmWriter() : m_cRef(1)
{
	// Initialize variables
	head = NULL;
	numNodes = 0;
	unknown = 65536;
	maxDataSize = 0;

	g_cLocks++;
}

CClmWriter::~CClmWriter()
{
	LinkedListNode *current, *next;

	// Delete the linked list
	current = head;
	while (current)
	{
		next = current->next;			// Read the pointer to the next node
		current->inStream->Release();	// Release the input stream for this node
		delete current;					// Release this node
		current = next;					// Process next node
	}

	g_cLocks--;
}


// Performs a Merge Sort on the linked list
CClmWriter::LinkedListNode* CClmWriter::SortIndex(LinkedListNode *list)
{
	struct Tape
	{
		LinkedListNode *head;
		LinkedListNode *tail;
		int count;
	};

	Tape tape[4];
	LinkedListNode *current, *next;
	int destTape, sourceTape;
	int blockSize;
	int blockCount[2];

	// Initialize tapes
	tape[0].head = NULL;
	tape[0].tail = NULL;
	tape[0].count = 0;
	tape[1].head = NULL;
	tape[1].tail = NULL;
	tape[1].count = 0;
	// Break list into two
	destTape = 0;
	for (current = list; current != NULL; destTape ^= 1)
	{
		// Cache the next node in the list
		next = current->next;
		// Add the node to the tape
		if (tape[destTape].head == NULL)
			tape[destTape].head = current;
		else
			tape[destTape].tail->next = current;
		tape[destTape].tail = current;
		tape[destTape].count++;
		// Process next node
		current = next;
	}
	// Note: The tail nodes will have invalid next pointers at this point

	// Merge tapes using successively larger blocks in sorted order and split output
	for (blockSize = 1; tape[1].count != 0; blockSize <<= 1)
	{
		// Initialize new tapes
		tape[2].head = NULL;
		tape[2].tail = NULL;
		tape[2].count = 0;
		tape[3].head = NULL;
		tape[3].tail = NULL;
		tape[3].count = 0;

		// Merge all blocks on two tapes and split the output
		for (destTape = 2; (tape[0].count != 0) || (tape[1].count != 0); destTape ^= 1)
		{
			// Merge a block from each tape
			blockCount[0] = blockCount[1] = blockSize;
			if (blockCount[0] > tape[0].count)
				blockCount[0] = tape[0].count;
			if (blockCount[1] > tape[1].count)
				blockCount[1] = tape[1].count;
			for ( ; blockCount[0] | blockCount[1]; )
			{
				// Check for empty tapes
				if (blockCount[0] == 0)
					sourceTape = 1;			// Node must come from tape[1]
				else if (blockCount[1] == 0)
					sourceTape = 0;			// Node must come from tape[0]
				// Check for proper sorted order
				else if (strcmp(tape[0].head->indexEntry.fileName, tape[1].head->indexEntry.fileName) < 0)
					sourceTape = 0;			// Node on tape[0] comes before
				else
					sourceTape = 1;			// Node on tape[1] comes before

				// Move the node from the source tape to the dest tape
				// Extract the node from the source tape
				blockCount[sourceTape]--;
				next = tape[sourceTape].head;
				tape[sourceTape].head = tape[sourceTape].head->next;
				tape[sourceTape].count--;
				// Add the node to the dest tape
				if (tape[destTape].tail == NULL)
					tape[destTape].head = next;
				else
					tape[destTape].tail->next = next;
				tape[destTape].tail = next;
				next->next = NULL;
				tape[destTape].count++;
			}
		}

		// Swap tapes for next round
		tape[0] = tape[2];
		tape[1] = tape[3];
	}

	// Return the first element of the sorted list
	return tape[0].head;
}
