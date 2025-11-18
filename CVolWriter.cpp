
#include "stdafx.h"
#include "CVolWriter.h"


extern int g_cLocks;


ULONG __stdcall CVolWriter::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CVolWriter::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CVolWriter::QueryInterface(REFIID riid, void** ppv)
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

HRESULT CVolWriter::AddToArchive(BSTR fileName, SeekableStreamReader *inStream, int reserved)
{
	LinkedListNode *newNode;
	int stringLength;

	// Check for invalid parameters
	if (fileName == NULL)
		return E_INVALIDARG;
	if (inStream == NULL)
		return E_INVALIDARG;
	if (reserved != 0)
		return E_INVALIDARG;

	// Create a new linked list node to hold the data
	newNode = new LinkedListNode;
	// Allocate space to store the filename
	stringLength = SysStringLen(fileName);
	newNode->fileNameLength = stringLength+1;		// Store the string length
	newNode->fileName = new char[stringLength+1];	// Allocate space for filename string
	newNode->fileName[stringLength] = 0;			// NULL terminate the string
	// Convert the filename from UNICODE to ASCII
	WideCharToMultiByte(CP_ACP, 0, fileName, stringLength, newNode->fileName, stringLength, 0, 0);
	// Store the stream pointer
	newNode->inStream = inStream;
	inStream->AddRef();
	// Store the encoding method
	newNode->indexEntry.encoding = reserved;
	newNode->indexEntry.bUsed = 1;
	// Get the stream starting offset and size
	inStream->get_ReadOffset(&newNode->startStreamOffset);
	inStream->get_StreamSize(&newNode->indexEntry.fileSize);
	newNode->indexEntry.fileSize -= newNode->startStreamOffset;	// Adjust for unstored data

	// Store the new node to the linked list
	newNode->next = head;
	head = newNode;
	numNodes++;

	// Update running counts of string table size and max buffer size
	stringTableSize += stringLength+1;
	if (newNode->indexEntry.fileSize > maxBufferSize)
		maxBufferSize = newNode->indexEntry.fileSize;

	return S_OK;
}

HRESULT CVolWriter::WriteArchive(StreamWriter *outStream)
{
	SectionHeader sectHead;
	int totalHeaderSize;
	int stringSectionSize;
	int indexSectionSize;
	int temp = 0;			// Used to write alignment bytes
	int numBytesWritten;
	int bufferSize;
	char *buffer;			// Write buffer
	int offset;
	LinkedListNode *current;

	// Sort the index
	head = SortIndex(head);

	// Calculate section sizes and allocate buffer space
	// *************************************************
	stringSectionSize = (stringTableSize + 4 + 3) & ~3;
	indexSectionSize = (numNodes*sizeof(IndexEntry) + 3) & ~3;
	totalHeaderSize = stringSectionSize + indexSectionSize + 3*sizeof(SectionHeader);
	// Calculate needed buffer size
	bufferSize = maxBufferSize;
	if (stringTableSize > bufferSize)
		bufferSize = stringTableSize;
	// Allocate space for the write buffer
	buffer = new char[bufferSize];

	// Prepare the string table
	offset = 0;
	current = head;
	while (current)
	{
		current->indexEntry.fileNameOffset = offset;	// Store filename offset
		// Copy the filename to the string buffer
		memcpy(&buffer[offset], current->fileName, current->fileNameLength);
		offset += current->fileNameLength;				// Update the string offset
		current = current->next;						// Process next node
	}


	// Begin writing the VOL file contents
	// ***********************************

	// "VOL " section
	// **************
	sectHead.tag = ' LOV';		// "VOL "
	sectHead.sectionSize = totalHeaderSize;
	sectHead.alignment = 1;
	outStream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);

	// "volh" section
	sectHead.tag = 'hlov';		// "volh"
	sectHead.sectionSize = 0;
	outStream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);

	// "vols" section
	sectHead.tag = 'slov';		// "vols"
	sectHead.sectionSize = stringSectionSize;
	outStream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
	outStream->Write(4, (int)&stringTableSize, &numBytesWritten);
	// Write out the string table
	outStream->Write(stringTableSize, (int)buffer, &numBytesWritten);
	// Pad section with NULL bytes
	outStream->Write(stringSectionSize - stringTableSize - 4, (int)&temp, &numBytesWritten);

	// "voli" section
	sectHead.tag = 'ilov';		// "voli"
	sectHead.sectionSize = numNodes * sizeof(IndexEntry);
	outStream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
	// Write out the index table
	offset = totalHeaderSize + sizeof(SectionHeader);
	current = head;
	while (current)
	{
		// Store the data offset
		current->indexEntry.dataOffset = offset;
		// Update offset for next file
		offset += sizeof(SectionHeader) + ((current->indexEntry.fileSize + 3) & ~3);
		// Write out the index table
		outStream->Write(sizeof(IndexEntry), (int)&current->indexEntry, &numBytesWritten);
		current = current->next;					// Process next node
	}
	// Pad the section with NULL bytes
	outStream->Write(indexSectionSize - numNodes*sizeof(IndexEntry), (int)&temp, &numBytesWritten);

	// Data section
	// ************
	sectHead.tag = 'KLBV';	// "VBLK"
	current = head;
	while (current)
	{
		// Write out the file data section header
		sectHead.sectionSize = current->indexEntry.fileSize;
		outStream->Write(sizeof(SectionHeader), (int)&sectHead, &numBytesWritten);
		// Seek to the beginning of the file data
		current->inStream->Seek(current->startStreamOffset);
		// Read in the file data
		current->inStream->Read(sectHead.sectionSize, (int)buffer, &numBytesWritten);
		// Write out the file data to the archive
		outStream->Write(sectHead.sectionSize, (int)buffer, &numBytesWritten);
		// Pad the section with NULL bytes
		outStream->Write(-sectHead.sectionSize & 3, (int)&temp, &numBytesWritten);
		// Process next file
		current = current->next;
	}

	// Release the write buffer
	delete [] buffer;

	return S_OK;
}


// Class specific
// **************

CVolWriter::CVolWriter() : m_cRef(1)
{
	// Initialize variables
	head = NULL;
	numNodes = 0;
	stringTableSize = 0;
	maxBufferSize = 0;

	g_cLocks++;
}

CVolWriter::~CVolWriter()
{
	LinkedListNode *current, *next;

	// Delete the linked list
	current = head;
	while(current)
	{
		next = current->next;			// Read the pointer to the next node
		delete [] current->fileName;	// Release the filename memory for this node
		current->inStream->Release();	// Release the input stream for this node
		delete current;					// Release this node
		current = next;					// Process next node
	}

	g_cLocks--;
}


// Performs a Merge Sort on the linked list
CVolWriter::LinkedListNode* CVolWriter::SortIndex(LinkedListNode *list)
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
				else if (strcmp(tape[0].head->fileName, tape[1].head->fileName) < 0)
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
