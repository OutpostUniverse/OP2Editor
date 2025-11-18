
#include "OP2Editor.h"


class CVolReader : public ArchiveReader
{
public:
	// IUnknown
	// ********
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);


	// ArchiveReader
	// *************

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumFiles(
		/* [retval][out] */ int __RPC_FAR *numFiles);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_FileName(
		/* [in] */ int index,
		/* [retval][out] */ BSTR __RPC_FAR *fileName);

	HRESULT STDMETHODCALLTYPE OpenStreamRead(
		/* [in] */ BSTR filename,
		/* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);


	// Class specific
	// **************
	CVolReader(SeekableStreamReader *inStream, int bAttachToStream);
	~CVolReader();

private:
	ULONG m_cRef;

	void FreeMemory();
	int LoadVol(SeekableStreamReader *inStream, int bAttachToStream);
	int GetFileIndex(BSTR fileName);

	#pragma pack(push, 1)
	struct IndexEntry
	{
		int fileNameOffset;				// Offset from the start of the string data
		int dataOffset;					// Offset from the start of the file to VBLK tag
		int fileSize;					// Size of packed data in archive
		char encoding;					// Form of compression used to store the file
		char boolUsed;					// Indicates if this index entry is used
	};
	struct SectionHeader
	{
		int tag;
		int sectionSize:31;
		int alignment:1;
	};
	#pragma pack(pop)

	unsigned int numFiles;					// Number of files stored in this Vol file
	unsigned int numIndexEntries;			// Number of index entries stored in Vol file (some may be empty)
	unsigned int actualStringDataLen;		// Actual used size of string section (up to and including last terminating NULL character)
	LPVOID stringBuffer;					// Buffer to hold all internal file names
	IndexEntry *indexTable;					// Pointer to index table array
	LPVOID *dataBuffer;						// Pointer to an array of pointers to data buffers
	int streamStartOffset;					// Start offset of vol data in stream
	SeekableStreamReader *attachedStream;	// Vol data input stream
};
