
#include "OP2Editor.h"


class CFileStreamReader : public SeekableStreamReader
{
public:

    // IUnknown
	// ********

    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// StreamReader
	// ************
	
	// [local]
    HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ int numBytes,
            /* [in] */ int pBuffer,
            /* [retval][out] */ int __RPC_FAR *numBytesRead);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ int __RPC_FAR *status);


	// SeekableStreamReader
	// ********************

    // [propget]
	HRESULT STDMETHODCALLTYPE get_ReadOffset( 
            /* [retval][out] */ int __RPC_FAR *readOffset);    
    // [propget]
	HRESULT STDMETHODCALLTYPE get_StreamSize( 
            /* [retval][out] */ int __RPC_FAR *streamSize);
    HRESULT STDMETHODCALLTYPE Seek( 
            /* [in] */ int offset);


	// Class specific
	// **************

	CFileStreamReader(BSTR fileName);
	~CFileStreamReader();

private:
	ULONG m_cRef;

	HANDLE hFile;	// Handle to opened file
	int status;		// Stream status code
};
