#pragma once

#include "OP2Editor.h"


class CMemoryStreamReader : public SeekableStreamReader
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

	CMemoryStreamReader(int streamLength, char *buffer, int bAttachToBuffer);
	~CMemoryStreamReader();

private:
	ULONG m_cRef;

	int streamStatus;
	int readPtr;
	int bufferSize;
	char *streamBuffer;
};
