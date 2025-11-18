
#include "OP2Editor.h"


class CVolWriter : public ArchiveWriter
{
public:
	// IUnknown
	// ********
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);


	// ArchiveWriter
	// *************

	HRESULT STDMETHODCALLTYPE AddToArchive(
			/* [in] */ BSTR fileName,
			/* [in] */ SeekableStreamReader __RPC_FAR *inStream,
			/* [in] */ int reserved);
	HRESULT STDMETHODCALLTYPE WriteArchive(
			/* [in] */ StreamWriter __RPC_FAR *outStream);


	// Class specific
	// **************

	CVolWriter();
	~CVolWriter();

private:
	ULONG m_cRef;

	#pragma pack(push, 1)
	struct SectionHeader
	{
		int tag;						// Identifies this section with a 4 byte (ASCII) tag
		int sectionSize:31;				// Size of this section in bytes
		int alignment:1;				// Determines if section is to be treated as WORD or DWORD aligned
	};
	struct IndexEntry
	{
		int fileNameOffset;				// Offset to filename in string table
		int dataOffset;					// Offset in VOL file of this file's data
		int fileSize;					// Size of this file
		char encoding;					// Compression used to store the file
		char bUsed;						// Indicates if this IndexEntry is used
	};
	#pragma pack(pop)
	struct LinkedListNode
	{
		LinkedListNode *next;			// Next node in the linked list
		SeekableStreamReader *inStream;	// Input stream object for file data
		int startStreamOffset;			// Starting offset of data in this stream to store
		int fileNameLength;				// Length of filename, including the NULL terminator
		char *fileName;					// Internal archive filename
		IndexEntry indexEntry;			// Index entry for this file
	};

	LinkedListNode* SortIndex(LinkedListNode *list);

	// Linked list variables
	LinkedListNode *head;
	int numNodes;
	int stringTableSize;
	int maxBufferSize;
};
