#pragma once

#include "OP2Editor.h"
#include "CTileSetSource.h"


class CResourceManager : public IResourceManager, public ISupportErrorInfo
{
public:

	// IUnknown
	// ********

	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// IResource Manager
	// *****************

	// [propget]
	HRESULT STDMETHODCALLTYPE get_RootPath(
		/* [retval][out] */ BSTR __RPC_FAR *path);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_RootPath(
		/* [in] */ BSTR path);

	HRESULT STDMETHODCALLTYPE OpenStreamRead(
		/* [in] */ BSTR fileName,
		/* [retval][out] */ StreamReader __RPC_FAR *__RPC_FAR *stream);
	HRESULT STDMETHODCALLTYPE OpenStreamWrite(
		/* [in] */ BSTR fileName,
		/* [retval][out] */ StreamWriter __RPC_FAR *__RPC_FAR *stream);

	HRESULT STDMETHODCALLTYPE LoadMapFile(
		/* [in] */ BSTR fileName,
		/* [in] */ enum MapLoadSaveFormat loadFlags,
		/* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);
	HRESULT STDMETHODCALLTYPE LoadMap(
		/* [in] */ StreamReader __RPC_FAR *inStream,
		/* [in] */ enum MapLoadSaveFormat loadFlags,
		/* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *mapFile);
	HRESULT STDMETHODCALLTYPE CreateNewMap(
		/* [in] */ int width,
		/* [in] */ int height,
		/* [retval][out] */ MapFile __RPC_FAR *__RPC_FAR *newMap);

	HRESULT STDMETHODCALLTYPE LoadTileSetFile(
		/* [in] */ BSTR fileName,
		/* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
	HRESULT STDMETHODCALLTYPE LoadTileSet(
		/* [in] */ StreamReader __RPC_FAR *inStream,
		/* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);
	HRESULT STDMETHODCALLTYPE CreateTileSet(
		/* [in] */ int numTiles,
		/* [in] */ int bitDepth,
		/* [in] */ int width,
		/* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *newTileSet);

	HRESULT STDMETHODCALLTYPE LoadVolFile(
		/* [in] */ BSTR fileName,
		/* [in] */ int bAttachToStream,
		/* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);
	HRESULT STDMETHODCALLTYPE LoadVol(
		/* [in] */ SeekableStreamReader __RPC_FAR *inStream,
		/* [in] */ int bAttachToStream,
		/* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *volReader);
	HRESULT STDMETHODCALLTYPE CreateVolFile(
		/* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *volWriter);

	HRESULT STDMETHODCALLTYPE LoadClmFile(
		/* [in] */ BSTR fileName,
		/* [in] */ int bAttachToStream,
		/* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);
	HRESULT STDMETHODCALLTYPE LoadClm(
		/* [in] */ SeekableStreamReader __RPC_FAR *inStream,
		/* [in] */ int bAttachToStream,
		/* [retval][out] */ ArchiveReader __RPC_FAR *__RPC_FAR *clmReader);
	HRESULT STDMETHODCALLTYPE CreateClmFile(
		/* [retval][out] */ ArchiveWriter __RPC_FAR *__RPC_FAR *clmWriter);

	HRESULT STDMETHODCALLTYPE AddArchiveToSearch(
		/* [in] */ ArchiveReader __RPC_FAR *volReader);
	HRESULT STDMETHODCALLTYPE ClearSearchPath(void);


	// ISupportErrorInfo
	// *****************
	HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID riid);


	// Constructor/Destructor
	// **********************

	CResourceManager(BSTR gamePath);
	~CResourceManager();

private:
	ULONG m_cRef;		// COM object reference count

	struct LinkedListNode
	{
		LinkedListNode *next;
		ArchiveReader *archive;
	};

	// Class specific variables
	BSTR path;
	CTileSetSource *tileSetSource;
	// LinkedList
	LinkedListNode *head;
	LinkedListNode *tail;
};
