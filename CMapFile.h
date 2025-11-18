
#include "OP2Editor.h"
#include "CTileGroup.h"
//#include "CTileSetManager.h"


class CMapFile : public MapFile, public ISupportErrorInfo
{
public:
	// IUnknown
	// ********
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);


	// TileGroup
	// *********

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileWidth(
		/* [retval][out] */ int __RPC_FAR *tileWidth);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileHeight(
		/* [retval][out] */ int __RPC_FAR *tileHeight);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileSetManager(
		/* [retval][out] */ TileSetManager __RPC_FAR *__RPC_FAR *tileSetManager);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_MappingIndex(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *tileMappingIndex);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_MappingIndex(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int tileMappingIndex);

	HRESULT STDMETHODCALLTYPE Draw(
		/* [in] */ int destDC,
		/* [in] */ int sourcePixelX,
		/* [in] */ int sourcePixelY,
		/* [in] */ int pixelWidth,
		/* [in] */ int pixelHeight);


	// MapFile
	// ********

	// [propget]
	HRESULT STDMETHODCALLTYPE get_AroundTheWorld(
		/* [retval][out] */ int __RPC_FAR *bAroundTheWorld);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileData(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *tile);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TileData(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int newTile);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_CellType(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *cellType);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_CellType(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int newCellType);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_UnitIndex(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *unitIndex);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_UnitIndex(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int newUnitIndex);


	//[propget]
	HRESULT STDMETHODCALLTYPE get_Lava(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *lava);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_Lava(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int lava);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_LavaPossible(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *lavaPossible);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_LavaPossible(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int lavaPossible);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_Expand(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *expand);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_Expand(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int expand);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_Microbe(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *microbe);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_Microbe(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int microbe);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_WallOrBuilding(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [retval][out] */ int __RPC_FAR *wallOrBuilding);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_WallOrBuilding(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ int wallOrBuilding);


	HRESULT STDMETHODCALLTYPE Copy(
		/* [in] */ int tileX1,
		/* [in] */ int tileY1,
		/* [in] */ int tileX2,
		/* [in] */ int tileY2,
		/* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);
	HRESULT STDMETHODCALLTYPE Paste(
		/* [in] */ int tileX,
		/* [in] */ int tileY,
		/* [in] */ TileGroup __RPC_FAR *tileGroup);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumTileGroups(
		/* [retval][out] */ int __RPC_FAR *numTileGroups);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileGroup(
		/* [in] */ int tileGroupIndex,
		/* [retval][out] */ TileGroup __RPC_FAR *__RPC_FAR *tileGroup);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileGroupName(
		/* [in] */ int tileGroupIndex,
		/* [retval][out] */ BSTR __RPC_FAR *tileGroupName);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TileGroupName(
		/* [in] */ int tileGroupIndex,
		/* [in] */ BSTR tileGroupName);
	HRESULT STDMETHODCALLTYPE AddTileGroup(
		/* [in] */ TileGroup __RPC_FAR *newTileGroup);
	HRESULT STDMETHODCALLTYPE RemoveTileGroup(
		/* [in] */ int tileGroupIndex);

	HRESULT STDMETHODCALLTYPE SaveMap(
		/* [in] */ StreamWriter __RPC_FAR *stream,
		/* [in] */ enum MapLoadSaveFormat saveFlags,
		/* [retval][out] */ int __RPC_FAR *status);


	// ISupportErrorInfo
	// *****************
	HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID riid);


	// Class specific
	// **************
	CMapFile(TileSetSource *tileSetSource, int width, int height);
	CMapFile(TileSetSource *tileSetSource, StreamReader *stream, enum MapLoadSaveFormat loadFlags);
	~CMapFile();

private:
	ULONG m_cRef;

	// Class internal structures
	#pragma pack(push, 1)				// Make sure structures are byte aligned
	struct MapHeader
	{
		int tag;
		int unknown;
		int lgTileWidth;
		int tileHeight;
		int numTileSets;
	};
	struct ClippingRect
	{
		int x1;							// Left edge of map (x coordinate)
		int y1;							// Top edge of map (y coordinate)
		int x2;							// Rigth edge of map (x coordinate)
		int y2;							// Bottom edge of map (y coordinate)
	};
	#pragma pack(pop)
	struct TileGroupInfo
	{
		TileGroup *tileGroup;
		int nameLen;
		char *name;
	};

	// Private functions
	// *****************
	int LoadMap(StreamReader *stream, TileSetSource *tileSetSource, int loadFlags);
	void FreeMemory();

	// Private variables
	// *****************
	MapHeader mapHeadInfo;
	ClippingRect clipRect;
	int tileWidth;						// Cached width value (header contains lgTileWidth)
	int *tileData;						// Tile data array
	CTileSetManager *tileSetManager;	// Handles all tile sets for this map
	TileSetSource *tileSource;			// Source of all tile sets that need to be loaded
	int numTileGroups;					// Number of tile groups stored in map file
	TileGroupInfo *tileGroupInfo;		// Array of named tile groups
};
