
#include "OP2Editor.h"


class CClmWriter : public ArchiveWriter
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

	CClmWriter();
	~CClmWriter();

private:
	ULONG m_cRef;

	// Private constant used for Clm loading/saving
	static const char tagClmFile[32];

	#pragma pack(push, 1)
	struct IndexEntry
	{
		char fileName[8];				// Internal archive filename
		int dataOffset;					// Offset to data
		int dataSize;					// Size of data
	};
	#pragma pack(pop)
	struct LinkedListNode
	{
		LinkedListNode *next;			// Next node in the linked list
		SeekableStreamReader *inStream;	// Input stream object for file data
		IndexEntry indexEntry;			// Index entry to save in the index section
		int streamStartOffset;			// Starting offset of data in stream to store
	};

	LinkedListNode* SortIndex(LinkedListNode *list);

	// Linked list variables
	LinkedListNode *head;
	int numNodes;
	int unknown;						// **TODO** Find out what this DWORD means
	int maxDataSize;
};


