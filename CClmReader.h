
#include "OP2Editor.h"


class CClmReader : public ArchiveReader
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
	CClmReader(SeekableStreamReader *inStream, int bAttachToStream);
	~CClmReader();

private:
	ULONG m_cRef;

	// Private constant used for Clm loading/saving
	static const char tagClmFile[];

	void FreeMemory();
	int LoadClm(SeekableStreamReader *inStream, int bAttachToStream);
	int GetFileIndex(BSTR fileName);

	struct IndexEntry
	{
		char fileName[8];
		int offset;
		int size;
	};

	WAVEFORMATEX waveFormat;				// Format of all stored sound data
	int unknown;							// Unknown **TODO** Find out meaning
	unsigned int numFiles;					// Number of wave files stored in the clump file
	IndexEntry *indexTable;					// Array of all index entries
	LPVOID *dataBuffer;						// Array of pointers to data buffers
	int streamStartOffset;					// Start offset of clm data in stream
	SeekableStreamReader *attachedStream;	// Clm data input stream
};
