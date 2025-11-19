#pragma once

#include "OP2Editor.h"
#include "CTileSet.h"

class CTileSetSource : public TileSetSource
{
public:
	// IUnknown
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// TileSetSource
	HRESULT STDMETHODCALLTYPE LoadTileSet(
		/* [in] */ BSTR tileSetName,
		/* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);

	HRESULT STDMETHODCALLTYPE UnloadTileSet(
		/* [in] */ BSTR __RPC_FAR tileSetName);


	// Class specific functions
	CTileSetSource(IResourceManager *resourceManager);
	~CTileSetSource();

private:
	ULONG m_cRef;	// COM object reference count

	// Class internal structures
	struct LinkedListNode
	{
		LinkedListNode *next;
		TileSet *tileSet;
		BSTR tileSetName;
		int loadedCount;
	};

	// Class specific variables
	LinkedListNode *head;
	IResourceManager *resManager;	// Resource manager used to find and open tile set files
};
