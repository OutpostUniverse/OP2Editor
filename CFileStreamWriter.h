#pragma once

#include "OP2Editor.h"


class CFileStreamWriter : public StreamWriter
{
public:
	// IUnknown
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// IFileStreamWriter
	// [local]
	HRESULT STDMETHODCALLTYPE Write(
		/* [in] */ int numBytes,
		/* [in] */ int pBuffer,
		/* [retval][out] */ int __RPC_FAR *numBytesWritten);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_Status(
		/* [retval][out] */ int __RPC_FAR *status);

	// Class specific
	CFileStreamWriter(BSTR fileName);
	~CFileStreamWriter();

private:
	ULONG m_cRef;

	HANDLE hFile;	// Handle to opened file
	int status;		// Stream status code
};
