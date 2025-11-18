

class CTileSetManager : public TileSetManager, public ISupportErrorInfo
{
public:
	// IUnknown
	// ********
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);


	// ISupportErrorInfo
	// *****************
	HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID riid);


	// TileSetManager
	// **************

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumTileSets(
			/* [retval][out] */ int __RPC_FAR *numTileSets);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileSetName(
			/* [in] */ int index,
			/* [retval][out] */ BSTR __RPC_FAR *tileSetName);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileSet(
			/* [in] */ int index,
			/* [retval][out] */ TileSet __RPC_FAR *__RPC_FAR *tileSet);

	HRESULT STDMETHODCALLTYPE AddTileSet(
			/* [in] */ BSTR tileSetName,
			/* [retval][out] */ int __RPC_FAR *index);

	HRESULT STDMETHODCALLTYPE RemoveTileSet(
			/* [in] */ BSTR tileSetName,
			/* [retval][out] */ int __RPC_FAR *index);

	HRESULT STDMETHODCALLTYPE ReplaceTileSet(
			/* [in] */ int index,
			/* [in] */ BSTR tileSetName);

	HRESULT STDMETHODCALLTYPE MapInTiles(
			/* [in] */ int tileSetIndex,
			/* [in] */ int startTile,
			/* [in] */ int numTiles,
			/* [retval][out] */ int __RPC_FAR *mappingIndex);

	HRESULT STDMETHODCALLTYPE GetMappingIndex(
			/* [in] */ int tileSetIndex,
			/* [in] */ int tileIndex,
			/* [in] */ int numTileReplacements,
			/* [in] */ int cycleDelay,
			/* [retval][out] */ int __RPC_FAR *mappingIndex);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumMappings(
			/* [retval][out] */ int __RPC_FAR *numMappings);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileSetIndex(
			/* [in] */ int mappingIndex,
			/* [retval][out] */ int __RPC_FAR *tileSetIndex);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TileSetIndex(
			/* [in] */ int mappingIndex,
			/* [in] */ int tileSetIndex);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TileSetTileIndex(
			/* [in] */ int mappingIndex,
			/* [retval][out] */ int __RPC_FAR *tileSetTileIndex);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TileSetTileIndex(
			/* [in] */ int mappingIndex,
			/* [in] */ int tileSetTileIndex);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumTileReplacements(
			/* [in] */ int mappingIndex,
			/* [retval][out] */ int __RPC_FAR *numTileReplacements);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_NumTileReplacements(
			/* [in] */ int mappingIndex,
			/* [in] */ int numTileReplacements);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_CycleDelay(
			/* [in] */ int mappingIndex,
			/* [retval][out] */ int __RPC_FAR *cycleDelay);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_CycleDelay(
			/* [in] */ int mappingIndex,
			/* [in] */ int cycleDelay);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_NumTerrains(
			/* [retval][out] */ int __RPC_FAR *numTerrains);
	HRESULT STDMETHODCALLTYPE SetNumTerrains(
			/* [in] */ int numTerrains);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainStartTile(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *startMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainStartTile(
			/* [in] */ int terrainIndex,
			/* [in] */ int startMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainEndTile(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *endMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainEndTile(
			/* [in] */ int terrainIndex,
			/* [in] */ int endMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainDozed(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainDozed(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainRubble(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainRubble(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainTubeUnk(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainTubeUnk(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainLavaWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainLavaWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainMicrobeWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainMicrobeWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainNormalWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainNormalWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainDamagedWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainDamagedWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainRuinedWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainRuinedWall(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainLava(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainLava(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainFlat1(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainFlat1(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainFlat2(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainFlat2(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);
	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainFlat3(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainFlat3(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainTube(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainTube(
			/* [in] */ int terrainIndex,
			/* [in] */ enum TerrainTubeDirection direction,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainScorched(
			/* [in] */ int terrainIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainScorched(
			/* [in] */ int terrainIndex,
			/* [in] */ int dataMapping);

	// [propget]
	HRESULT STDMETHODCALLTYPE get_TerrainUnknown(
			/* [in] */ int terrainIndex,
			/* [in] */ int unkIndex,
			/* [retval][out] */ int __RPC_FAR *dataMapping);
	// [propput]
	HRESULT STDMETHODCALLTYPE put_TerrainUnknown(
			/* [in] */ int terrainIndex,
			/* [in] */ int unkIndex,
			/* [in] */ int dataMapping);

	// Class specific
	// **************
	CTileSetManager(TileSetSource *tileSetSource);
	CTileSetManager(TileSetSource *tileSetSource, int numTileSets, StreamReader *inStream);
	~CTileSetManager();

private:
	ULONG m_cRef;

	// Friend class for fast access to data needed to draw a view of the map
	friend class CMapFile;
	friend class CTileGroup;

	#pragma pack(push, 1)
	struct TileSetInfo
	{
		int numTiles;				// Number of tiles in this tile set
		int stringLength;			// Length of the tileSetName string
		char *tileSetName;			// File name of the tile set, as Outpost2 sees it
		BSTR wideTileSetName;		// BSTR copy of the tile set name (cached for use with COM)
		TileSet *tileSet;			// A pointer to a tile set object
	};
	struct TileSetTileMapping
	{
		short tileSetIndex;
		short tileIndex;
		short numTileReplacements;
		short cycleDelay;
	};
	struct TerrainTypeItemTable	// Holds sets of related tiles
								// LavaWalls/MicrobeWalls/NormalWalls/DamagedWalls/ReallyDamagedWalls/Tubes
	{
		short tile[0x10];		// tile for each direction facing
	};
	struct TerrainType
	{
		short firstTile;		// First tile index in this terrain type class
		short lastTile;			// Last tile index in this terrain type class
		short bulldozed;		// Index of the bulldozed tile
		short commonRubble;		// Index of the common rubble tile (4 common rubble tiles, followed by 4 rare rubble tiles)
		short tubeUnknown[6];	// **TODO** find out use of this (data is repeated below)
		TerrainTypeItemTable wall[5];	// Wall groups
		short lava;
		short flat1;
		short flat2;
		short flat3;
		TerrainTypeItemTable tube;		// Tube group
		short scorched;			// Scorched tile index (from vehicle explosion)

		short unknown[0x15];	// **TODO** find out
	};
	#pragma pack(pop)

	// Private functions
	// *****************
	int Save(StreamWriter *stream);
	int Load(StreamReader *stream);
	void FreeMemory();

	// Private variables
	// *****************
	TileSetSource *tileSource;		// Used to load tile sets

	int numTileSets;				// Number of loaded tile sets
	TileSetInfo *tileSetInfo;		// List of loaded tile sets
	int numMappings;				// Number of tile mappings in the tile mapping array
	TileSetTileMapping *mapping;	// Tile set tile mapping array
	int numTerrains;				// Number of terrain types in the terrain type array
	TerrainType	*terrain;			// Tarrain type array

	// Private constant used for tile set loading/saving
	static const char tagTileSet[];
};
