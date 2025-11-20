#include "stdafx.h"
#include "CMapFile.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


// IUnknown functions
// ******************

ULONG __stdcall CMapFile::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CMapFile::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CMapFile::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)(MapFile*)this;
	else if (riid == IID_MapFile)
		*ppv = (MapFile*)this;
	else if (riid == IID_ISupportErrorInfo)
		*ppv = (ISupportErrorInfo*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();

	return S_OK;
}


// TileGroup functions
// *******************

HRESULT CMapFile::get_TileWidth(int *width)
{
	*width = tileWidth;

	return S_OK;
}

HRESULT CMapFile::get_TileHeight(int *height)
{
	*height = mapHeadInfo.tileHeight;

	return S_OK;
}


HRESULT CMapFile::get_TileSetManager(TileSetManager **tileSetManager)
{
	this->tileSetManager->QueryInterface(IID_TileSetManager, (void**)tileSetManager);

	return S_OK;
}


HRESULT CMapFile::get_MappingIndex(int tileX, int tileY, int *tileMappingIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Get the tile mapping index
	*tileMappingIndex = (tileData[tileOffset] & 0x0000FFE0) >> 5;

	return S_OK;
}

HRESULT CMapFile::put_MappingIndex(int tileX, int tileY, int tileMappingIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	// Check for invalid mapping index
	if ((tileMappingIndex & ~0x7FF) != 0)	// Only 11 bits allowed
		return E_INVALIDARG;
	// **TODO** Check if index is out of array bounds?

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the tile mapping index
	tileData[tileOffset] = (tileData[tileOffset] & 0xFFFF001F) | (tileMappingIndex << 5);

	return S_OK;
}


HRESULT CMapFile::Draw(int destDC, int sourcePixelX, int sourcePixelY, int pixelWidth, int pixelHeight)
{
	int startXTile = sourcePixelX >> 5;
	int startYTile = sourcePixelY >> 5;
	int endXTile = (sourcePixelX+pixelWidth+31) >> 5;
	int endYTile = (sourcePixelY+pixelHeight+31) >> 5;
	int x, y;
	int tileXUpper, tileXLower;
	int tileOffset;
	int tile;
	int tileIndex;
	TileSet *tileSet;
	CTileSetManager::TileSetTileMapping *tileMap;
	int destPixelX = -(sourcePixelX & 0x1F);
	int destPixelY = -(sourcePixelY & 0x1F);

	if (endYTile > mapHeadInfo.tileHeight)
		endYTile = mapHeadInfo.tileHeight;
	if (endXTile > tileWidth)
		endXTile = tileWidth;

	// Draw all tiles in visible range
	for (y = startYTile; y < endYTile; y++)
	{
		for (x = startXTile; x < endXTile; x++)
		{
			// Calculate the offset of the tile
			tileXUpper = x >> 5;
			tileXLower = x & 0x1F;
			tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + y) << 5) + tileXLower;
			// Load the tile data
			tile = tileData[tileOffset];
			// Get the tile index
			tileIndex = (tile & 0x0000FFE0) >> 5;

			// Make sure the tileIndex is in range
			if (tileIndex >= tileSetManager->numMappings)
				tileIndex = 0;
			// Get the tile mapping
			tileMap = &tileSetManager->mapping[tileIndex];
			// Paste the tile
			tileSet = tileSetManager->tileSetInfo[tileMap->tileSetIndex].tileSet;
			if (tileSet)
			{
				tileSet->PasteTile(destDC, destPixelX+((x-startXTile)*32), destPixelY+((y-startYTile)*32), tileMap->tileIndex);
			}
		}
	}

	return S_OK;
}


// MapFile functions
// *****************


HRESULT CMapFile::get_AroundTheWorld(int *bAroundTheWorld)
{
	*bAroundTheWorld = (mapHeadInfo.lgTileWidth >= 9);

	return S_OK;
}


HRESULT CMapFile::get_TileData(
	/* [in] */ int tileX,
	/* [in] */ int tileY,
	/* [retval][out] */ int __RPC_FAR *tile)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Get the tileData result value
	*tile = tileData[tileOffset];

	return S_OK;
}

HRESULT CMapFile::put_TileData(int tileX, int tileY, int newTile)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	tileData[tileOffset] = newTile;

	return S_OK;
}


HRESULT CMapFile::get_CellType(int tileX, int tileY, int *cellType)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Get the tileData result value
	*cellType = tileData[tileOffset] & 0x1F;

	return S_OK;
}

HRESULT CMapFile::put_CellType(int tileX, int tileY, int newCellType)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	// Check for invalid cell type
	if ((newCellType & ~0x1F) != 0)	// Only 5 bits allowed
		return E_INVALIDARG;

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	tileData[tileOffset] = (tileData[tileOffset] & 0xFFFFFFE0) | (newCellType & 0x1F);

	return S_OK;
}

HRESULT CMapFile::get_UnitIndex(int tileX, int tileY, int *unitIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Get the tileData result value
	*unitIndex = (tileData[tileOffset] >> 16) & 0x7FF;

	return S_OK;
}

HRESULT CMapFile::put_UnitIndex(int tileX, int tileY, int newUnitIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	// Check for invalid unit index
	if ((newUnitIndex & ~0x7FF) != 0)	// Only 11 bits allowed
		return E_INVALIDARG;

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	tileData[tileOffset] = (tileData[tileOffset] & 0xF800FFFF) | (newUnitIndex << 16);

	return S_OK;
}


// Bit flags
// *********

HRESULT CMapFile::get_Lava(int tileX, int tileY, int *lava)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Return the Lava presence bit
	*lava = (tileData[tileOffset] >> 27) & 0x1;
	return S_OK;
}

HRESULT CMapFile::put_Lava(int tileX, int tileY, int lava)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the Lava presence bit
	tileData[tileOffset] |= (lava & 0x1) << 27;
	return S_OK;
}

HRESULT CMapFile::get_LavaPossible(int tileX, int tileY, int *lavaPossible)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Return the LavaPossible bit
	*lavaPossible = (tileData[tileOffset] >> 28) & 0x1;
	return S_OK;
}

HRESULT CMapFile::put_LavaPossible(int tileX, int tileY, int lavaPossible)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the LavaPossible bit
	tileData[tileOffset] |= (lavaPossible & 0x1) << 28;
	return S_OK;
}

HRESULT CMapFile::get_Expand(int tileX, int tileY, int *expand)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Return the Lava/Microbe Expand presence bit
	*expand = (tileData[tileOffset] >> 29) & 0x1;
	return S_OK;
}

HRESULT CMapFile::put_Expand(int tileX, int tileY, int expand)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the Lava/Microbe Expand presence bit
	tileData[tileOffset] |= (expand & 0x1) << 29;
	return S_OK;
}

HRESULT CMapFile::get_Microbe(int tileX, int tileY, int *microbe)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Return the Microbe presence bit
	*microbe = (tileData[tileOffset] >> 30) & 0x1;
	return S_OK;
}

HRESULT CMapFile::put_Microbe(int tileX, int tileY, int microbe)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the Microbe presence bit
	tileData[tileOffset] |= (microbe & 0x1) << 30;
	return S_OK;
}

HRESULT CMapFile::get_WallOrBuilding(int tileX, int tileY, int *wallOrBuilding)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Return the Wall or Building presence bit (Non-moveable tile)
	*wallOrBuilding = (tileData[tileOffset] >> 31) & 0x1;
	return S_OK;
}

HRESULT CMapFile::put_WallOrBuilding(int tileX, int tileY, int wallOrBuilding)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= mapHeadInfo.tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	int tileXUpper = tileX >> 5;
	int tileXLower = tileX & 0x1F;
	int tileOffset = (((tileXUpper*mapHeadInfo.tileHeight) + tileY) << 5) + tileXLower;

	// Set the Wall or Building presence bit (Non-moveable tile)
	tileData[tileOffset] |= (wallOrBuilding & 0x1) << 31;
	return S_OK;
}


// Copy and Paste
// **************

HRESULT CMapFile::Copy(int tileX1, int tileY1, int tileX2, int tileY2, TileGroup **tileGroup)
{
	int copyTileWidth = tileX2 - tileX1 + 1;
	int copyTileHeight = tileY2 - tileY1 + 1;
	CTileGroup *copyTileGroup;
	TileSetManager *copyTileSetManager;

	// Create an object to hold the copied tile data
	*tileGroup = NULL;
	copyTileGroup = new CTileGroup(copyTileWidth, copyTileHeight, tileSource);
	// Check for errors creating object
	if (copyTileGroup == NULL)
		return E_OUTOFMEMORY;
	// Obtain the desired interface
	copyTileGroup->QueryInterface(IID_TileGroup, (void**)tileGroup);
	copyTileGroup->Release();
	// Check for errors
	if (*tileGroup == NULL)
		return E_FAIL;

	// Obtain the new tile group's tile set manager
	(*tileGroup)->get_TileSetManager(&copyTileSetManager);

	// Allocate space for compatibility maps
	// *************************************
	int *map;				// Compatibility map for mapping array
	int *tileSetMap;		// Compatibility map for tile set array
	int sourceMappings;		// Number of mapping entries in source tile set manager
	int destMappings;		// Current number of mapping entries in dest tile set manager
	int sourceTileSets;		// Number of tile sets in source tile set manager
	int destTileSets;		// Current number of tile sets in dest tile set manager
	// Initialize variables
	tileSetManager->get_NumMappings(&sourceMappings);
	destMappings = 0;
	tileSetManager->get_NumTileSets(&sourceTileSets);
	destTileSets = 0;

	// Allocate space for a compatibility map and tile set map
	map = new int[sourceMappings];
	tileSetMap = new int[sourceTileSets];
	// Check for memory allocation errors
	if ((map == NULL) || (tileSetMap == NULL))
	{
		// Failed to allocate memory. Cleanup and abort.
		if (map != NULL)
			delete [] map;
		if (tileSetMap != NULL)
			delete [] tileSetMap;
		copyTileSetManager->Release();
		(*tileGroup)->Release();

		return E_OUTOFMEMORY;

	}

	// Initialize all entries to unused
	memset(map, -1, sourceMappings*4);
	memset(tileSetMap, -1, sourceTileSets*4);

	// Translate and copy tile data
	// ****************************
	int x, y;
	int mappingIndex;
	int tileSetIndex;
	int tileSetTileIndex;
	int numTileReplacements;
	int cycleDelay;
	BSTR tileSetName;
	// Create the compatibilty map and copy data
	for (y = tileY1; y <= tileY2; y++)
	{
		for (x = tileX1; x <= tileX2; x++)
		{
			// Get the tile mapping index
			get_MappingIndex(x, y, &mappingIndex);
			// Check if compatibility map entry is not defined
			if (map[mappingIndex] == -1)
			{
				// Try to define this entry
				// Ensure a tile set mapping exists
				tileSetManager->get_TileSetIndex(mappingIndex, &tileSetIndex);
				// Check if tile set mapping is undefined
				if (tileSetMap[tileSetIndex] == -1)
				{
					// Get the tile set name
					tileSetName = NULL;
					tileSetManager->get_TileSetName(tileSetIndex, &tileSetName);
					// Load the tile set and obtain the index
					copyTileSetManager->AddTileSet(tileSetName, &tileSetMap[tileSetIndex]);
					// Free the tile set name string
					SysFreeString(tileSetName);
				}
				// Get the tile set tile index
				tileSetManager->get_TileSetTileIndex(mappingIndex, &tileSetTileIndex);
				// Fill in a new mapping entry
				copyTileSetManager->MapInTiles(tileSetMap[tileSetIndex], tileSetTileIndex, 1, &map[mappingIndex]);
				// Copy the animation properties
				tileSetManager->get_NumTileReplacements(mappingIndex, &numTileReplacements);
				tileSetManager->get_CycleDelay(mappingIndex, &cycleDelay);
				copyTileSetManager->put_NumTileReplacements(map[mappingIndex], numTileReplacements);
				copyTileSetManager->put_CycleDelay(map[mappingIndex], cycleDelay);
			}
			// Copy the tile data
			(*tileGroup)->put_MappingIndex(x-tileX1, y-tileY1, map[mappingIndex]);
		}
	}

	// Cleanup and exit
	delete [] map;
	delete [] tileSetMap;

	return S_OK;
}

HRESULT CMapFile::Paste(int tileX, int tileY, TileGroup *tileGroup)
{
	TileSetManager *sourceTileSetManager;
	int sourceTileSets;
	int sourceMappings;
	int *map;
	int *tileSetMap;
	bool *newTileSetMap;
	int tileSetIndex;
	int tileIndex;
	int numTileReplacements;
	int cycleDelay;
	int i, j, mappingIndex;
	int sourceWidth, sourceHeight;
	int numNewMappings;
	HRESULT retval;
	BSTR tileSetName = NULL;

	// Get the source TileSetManager
	tileGroup->get_TileSetManager(&sourceTileSetManager);
	// Get the number of tile sets and tile mappings from the source
	sourceTileSetManager->get_NumTileSets(&sourceTileSets);
	sourceTileSetManager->get_NumMappings(&sourceMappings);

	// Allocate space for a compatibility map and tile set map
	map = new int[sourceMappings];
	tileSetMap = new int[sourceTileSets];
	newTileSetMap = new bool[sourceTileSets];
	// Check for memory allocation errors
	if ((map == NULL) || (tileSetMap == NULL) || (newTileSetMap == NULL))
	{
		// Failed to allocate memory. Cleanup and abort.
		if (map != NULL)
			delete [] map;
		if (tileSetMap != NULL)
			delete [] tileSetMap;
		if (newTileSetMap != NULL)
			delete [] newTileSetMap;
		sourceTileSetManager->Release();

		return E_OUTOFMEMORY;

	}

	// Initialize all entries to unused
	memset(map, -1, sourceMappings*4);
	memset(tileSetMap, -1, sourceTileSets*4);
	memset(newTileSetMap, false, sourceTileSets*sizeof(bool));

	try
	{
		// Try to load all the tile sets and create a tile set mapping
		for (i = 0; i < sourceTileSets; i++)
		{
			// Get the tile set name
			sourceTileSetManager->get_TileSetName(i, &tileSetName);
			// Try to load the tile set
			retval = tileSetManager->AddTileSet(tileSetName, &tileSetMap[i]);
			// Check for errors loading the tile set
			if (FAILED(retval))
			{
				// Check if the error was not a duplicate tile set
				if (tileSetMap[i] < 0)
				{
					// Error loading tile set. Abort
					throw L"Could not load all needed tile sets for paste operation.";
				}
			}
			else
			{
				newTileSetMap[i] = true;	// A new tile set was successfully loaded
			}
		}

		// Create (initial) compatability map and count number of new mappings needed
		numNewMappings = 0;
		for (i = 0; i < sourceMappings; i++)
		{
			// Get the attributes for this mapping index
			sourceTileSetManager->get_TileSetIndex(i, &tileSetIndex);
			sourceTileSetManager->get_TileSetTileIndex(i, &tileIndex);
			sourceTileSetManager->get_NumTileReplacements(i, &numTileReplacements);
			sourceTileSetManager->get_CycleDelay(i, &cycleDelay);
			// Lookup index of dest mapping index
			tileSetManager->GetMappingIndex(tileSetMap[tileSetIndex], tileIndex, numTileReplacements, cycleDelay, &map[i]);
			// Check if a new mapping needs to be created
			if (map[i] < 0)
				numNewMappings++;		// A new mapping will be needed for this entry
		}

		// Check if there is not enough room for the new mappings
		if (tileSetManager->numMappings + numNewMappings >= 2048)
			throw L"Not enough free mapping entries to perform the paste operation.";

		// Add the needed mapping entries
		for (i = 0; i < sourceMappings; i++)
		{
			// Check if this entry still needs to be filled in
			if (map[i] < 0)
			{
				// Get the attributes for this mapping index
				sourceTileSetManager->get_TileSetIndex(i, &tileSetIndex);
				sourceTileSetManager->get_TileSetTileIndex(i, &tileIndex);
				sourceTileSetManager->get_NumTileReplacements(i, &numTileReplacements);
				sourceTileSetManager->get_CycleDelay(i, &cycleDelay);
				// Add a new mapping entry
				tileSetManager->MapInTiles(tileSetMap[tileSetIndex], tileIndex, 1, &map[i]);
				// Fill in the other entries
				tileSetManager->put_NumTileReplacements(map[i], numTileReplacements);
				tileSetManager->put_CycleDelay(map[i], cycleDelay);
			}
		}

		// Copy the tile data
		tileGroup->get_TileWidth(&sourceWidth);
		tileGroup->get_TileHeight(&sourceHeight);
		// Clip coordinates to destination map size
		if (tileX + sourceWidth >= tileWidth)
			sourceWidth = tileWidth - tileX;
		if (tileY + sourceHeight >= mapHeadInfo.tileHeight)
			sourceHeight = mapHeadInfo.tileHeight - tileY;
		for (j = 0; j < sourceHeight; j++)
		{
			for (i = 0; i < sourceWidth; i++)
			{
				// Get the mapping index
				tileGroup->get_MappingIndex(i, j, &mappingIndex);
				// Set the dest mapping index
				put_MappingIndex(tileX + i, tileY + j, map[mappingIndex]);
			}
		}
	}
	catch(WCHAR *errorMsg)
	{
		// Unload new tile sets
		for (i = 0; i < sourceTileSets; i++)
		{
			// Check if this tile set is new
			if (newTileSetMap[i] == true)
			{
				// Get the tile set name
				sourceTileSetManager->get_TileSetName(i, &tileSetName);
				// Unload the tile set
				tileSetManager->RemoveTileSet(tileSetName, &tileSetMap[i]);
			}
		}
		// Release memory
		SysFreeString(tileSetName);
		delete [] map;
		delete [] tileSetMap;
		delete [] newTileSetMap;
		sourceTileSetManager->Release();

		// Return a COM error message
		PostErrorMsg(errorMsg);
		return E_FAIL;				// Failed to complete paste operation
	}
	catch(...)
	{
		// Unexpected error
		return E_FAIL;
	}

	// Release memory
	SysFreeString(tileSetName);
	delete [] map;
	delete [] tileSetMap;
	delete [] newTileSetMap;
	sourceTileSetManager->Release();

	// Success
	return S_OK;
}


HRESULT CMapFile::get_NumTileGroups(int *numTileGroups)
{
	*numTileGroups = this->numTileGroups;

	return S_OK;
}

HRESULT CMapFile::get_TileGroup(int tileGroupIndex, TileGroup **tileGroup)
{
	*tileGroup = NULL;

	// Error check index range
	if ((tileGroupIndex < 0) || (tileGroupIndex >= numTileGroups))
		return E_INVALIDARG;

	*tileGroup = tileGroupInfo[tileGroupIndex].tileGroup;
	if (tileGroup != NULL)
		(*tileGroup)->AddRef();

	return S_OK;
}

HRESULT CMapFile::get_TileGroupName(int tileGroupIndex, BSTR *tileGroupName)
{
	// Error check index range
	if ((tileGroupIndex < 0) || (tileGroupIndex >= numTileGroups))
		return E_INVALIDARG;

	// Reallocate space for the returned string
	int nameLen = tileGroupInfo[tileGroupIndex].nameLen;
	SysReAllocStringLen(tileGroupName, NULL, nameLen);
	// Convert the name to unicode
	MultiByteToWideChar(
		CP_ACP,
		0,
		tileGroupInfo[tileGroupIndex].name,
		nameLen,
		*tileGroupName,
		nameLen
	);

	return S_OK;
}

HRESULT CMapFile::put_TileGroupName(int tileGroupIndex, BSTR tileGroupName)
{
	// Error check index range
	if ((tileGroupIndex < 0) || (tileGroupIndex >= numTileGroups))
		return E_INVALIDARG;

	// Get the length of the new name string
	int nameLen = SysStringLen(tileGroupName);
	// Allocate space for the name
	char *name = new char[nameLen+1];
	// Check for allocation errors
	if (name == NULL)
		return E_OUTOFMEMORY;

	// Convert the BSTR to ASCII
	WideCharToMultiByte(CP_ACP, 0, tileGroupName, nameLen, name, nameLen, 0, 0);
	// NULL terminate it
	name[nameLen] = 0;

	// Replace the string
	delete [] tileGroupInfo[tileGroupIndex].name;
	tileGroupInfo[tileGroupIndex].name = name;
	tileGroupInfo[tileGroupIndex].nameLen = nameLen;

	return S_OK;
}

// **TODO** This function needs to load tile sets into the map's tile set manager
// if needed and also create any needed mapping entries.
HRESULT CMapFile::AddTileGroup(TileGroup *newTileGroup)
{
	return E_NOTIMPL;

	TileGroupInfo *newTileGroupInfo;

	// Try to extend the TileGroupInfo array
	newTileGroupInfo = new TileGroupInfo[numTileGroups + 1];
	// Check for memory allocation errors
	if (newTileGroupInfo == NULL)
		return E_OUTOFMEMORY;

	// Copy the data to the new array
	memcpy(newTileGroupInfo, tileGroupInfo, sizeof(tileGroupInfo[0])*numTileGroups);
	// Release the old array
	delete [] tileGroupInfo;
	// Replace the array with the new one
	tileGroupInfo = newTileGroupInfo;

	// Store the tile group to the new entry
	tileGroupInfo[numTileGroups].nameLen = 0;
	tileGroupInfo[numTileGroups].name = NULL;
	tileGroupInfo[numTileGroups].tileGroup = newTileGroup;
	newTileGroup->AddRef();

	// Update number of tile groups
	numTileGroups++;

	return E_NOTIMPL;
}

HRESULT CMapFile::RemoveTileGroup(int tileGroupIndex)
{
	// Error check index range
	if ((tileGroupIndex < 0) || (tileGroupIndex >= numTileGroups))
		return E_INVALIDARG;

	// **TODO**

	return E_NOTIMPL;
}


int CMapFile::LoadMap(StreamReader *stream, TileSetSource *tileSetSource, int loadFlags)
{
	// **NOTE**: Changed the 'format errors' to just post an error rather than throw an exception.
	// Although they can cause problems, it shouldn't prevent the map from loading.
	int numBytesRead;
	int status;
	int temp;

	try
	{
		// Check if saved game header is to be loaded from the file
		if ((loadFlags & SavedGameHeader) == SavedGameHeader)
		{
			// Load a saved game file header **TODO**
		}

		// Load the .map file header
		stream->Read(sizeof(mapHeadInfo), (int)&mapHeadInfo, &numBytesRead);
		// Check for errors
		stream->get_Status(&status);
		if (status)
			throw L"Read error. Could not read map header data.";	// Failed. Error reading file.
		if (mapHeadInfo.tag < 0x1010)
			throw L"Format error: Invalid map header tag.";

		// Update map header fields
		// Round height up to nearest power of 2
		int &x = mapHeadInfo.tileHeight;
		x = x - 1;
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >>16);
		x++;
		tileWidth = 1 << mapHeadInfo.lgTileWidth;	// Calculate map width


		// Allocate space for tile data
		tileData = new int[tileWidth*mapHeadInfo.tileHeight];
		// Read in the tile data
		stream->Read(tileWidth*mapHeadInfo.tileHeight*4, (int)tileData, &numBytesRead);
		// Check for errors
		stream->get_Status(&status);
		if (status)
			throw L"Read error. Could not read map tile data.";		// Failed. Error reading file.

		// Read clipping rect
		stream->Read(sizeof(clipRect), (int)&clipRect, &numBytesRead);


		// Load Tile Set mapping info
		tileSetManager = new CTileSetManager(tileSetSource, mapHeadInfo.numTileSets, stream);


		// Read tag
		stream->Read(4, (int)&temp, &numBytesRead);
		// Check if tag matches the opening tag of the file
		if (temp != mapHeadInfo.tag)
			throw L"Format error: Tag did not match header tag.";

		// Check if Unit data is to be loaded from the file
		if ((loadFlags & Units) == Units)
		{
			// Load Unit data **TODO**
		}

		// Read tag
		stream->Read(4, (int)&temp, &numBytesRead);
		// Check if tag matches the opening tag of the file
		if (temp != mapHeadInfo.tag)
			throw L"Format error: Tag did not match header tag.";

		// Check if tile groups are to be loaded from the file
		if ((loadFlags & TileGroups) == TileGroups)
		{
			// Load tile groups from file
			// **************************
			int i;

			// Load the header data
			stream->Read(4, (int)&numTileGroups, &numBytesRead);
			stream->Read(4, (int)&temp, &numBytesRead);

			// Allocate space for the tile group info
			tileGroupInfo = new TileGroupInfo[numTileGroups];
			// Initialize the array
			memset(tileGroupInfo, 0, sizeof(tileGroupInfo[0])*numTileGroups);

			// Read all group info
			for (i = 0; i < numTileGroups; i++)
			{
				int width, height;
				int x, y;

				// Read the dimensions
				stream->Read(4, (int)&width, &numBytesRead);
				stream->Read(4, (int)&height, &numBytesRead);
				// Create a new TileGroup
				tileGroupInfo[i].tileGroup = new CTileGroup(width, height, tileSetManager);

				// Read in the tile data
				for (y = 0; y < height; y++)
				{
					for (x = 0; x < width; x++)
					{
						// Read in the mapping index
						stream->Read(4, (int)&temp, &numBytesRead);
						// Set the group's mapping index
						tileGroupInfo[i].tileGroup->put_MappingIndex(x, y, temp);
					}
				}

				// Read in the tile group name length
				stream->Read(4, (int)&tileGroupInfo[i].nameLen, &numBytesRead);
				// Allocate space for the name
				tileGroupInfo[i].name = new char[tileGroupInfo[i].nameLen+1];
				// Read in the tile group name
				stream->Read(tileGroupInfo[i].nameLen, (int)tileGroupInfo[i].name, &numBytesRead);
				// NULL terminate the name
				tileGroupInfo[i].name[tileGroupInfo[i].nameLen] = 0;
			}
		}
	}
	catch(WCHAR *errorMsg)
	{
		// Return a COM error message
		PostErrorMsg(errorMsg);
		return 1;	// Failed to load file
	}
	catch(...)
	{
		return 1;	// Failed to load file
	}

	return 0;	// Success
}


HRESULT CMapFile::SaveMap(StreamWriter *stream, enum MapLoadSaveFormat saveFlags, int *status)
{
	int numBytesWritten;

	// Check if flag to write saved game header is set
	if ((saveFlags & SavedGameHeader) == SavedGameHeader)
	{
		// Write a saved game header **TODO**
	}

	// Update number of tile sets in header structure
	tileSetManager->get_NumTileSets(&mapHeadInfo.numTileSets);
	// Write the .map file header
	stream->Write(sizeof(mapHeadInfo), (int)&mapHeadInfo, &numBytesWritten);

	// Write the tile data
	stream->Write(tileWidth*mapHeadInfo.tileHeight*4, (int)tileData, &numBytesWritten);

	// Write the clipping rect
	stream->Write(sizeof(clipRect), (int)&clipRect, &numBytesWritten);


	// Save the tile set info
	tileSetManager->Save(stream);

	// Write the tag from the header
	stream->Write(4, (int)&mapHeadInfo.tag, &numBytesWritten);

	// Check if Unit data is to be written to the stream
	if ((saveFlags & Units) == Units)
	{
		// Write Unit data to the file **TODO**
	}

	// Write the tag from the header
	stream->Write(4, (int)&mapHeadInfo.tag, &numBytesWritten);

	// Check if tile group data is to be written to the stream
	if ((saveFlags & TileGroups) == TileGroups)
	{
		// Save tile group info
		// ********************
		int i;
		int temp = 0;

		// Write the header
		stream->Write(4, (int)&numTileGroups, &numBytesWritten);
		stream->Write(4, (int)&temp, &numBytesWritten);

		// Write all the group info
		for (i = 0; i < numTileGroups; i++)
		{
			TileGroup *tg;
			int width, height;
			int x, y;

			// Get the tile group's dimensions
			tg = tileGroupInfo[i].tileGroup;
			tg->get_TileWidth(&width);
			tg->get_TileHeight(&height);

			// Write the tile group's dimensions
			stream->Write(4, (int)&width, &numBytesWritten);
			stream->Write(4, (int)&height, &numBytesWritten);

			// Write the tile group data
			for (y = 0; y < height; y++)
			{
				for (x = 0; x < width; x++)
				{
					// Get the mapping index
					tg->get_MappingIndex(x, y, &temp);
					// Store the mapping index
					stream->Write(4, (int)&temp, &numBytesWritten);
				}
			}

			// Write the tile group's name
			temp = tileGroupInfo[i].nameLen;
			stream->Write(4, (int)&temp, &numBytesWritten);
			stream->Write(temp, (int)tileGroupInfo[i].name, &numBytesWritten);
		}
	}

	*status = 0;	// Success
	return S_OK;	// Success
}


// ISupportErrorInfo
// *****************

HRESULT CMapFile::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (riid == IID_MapFile)
		return S_OK;
	else
		return S_FALSE;
}


// Constructors/Destructor
// ***********************

CMapFile::CMapFile(TileSetSource *tileSetSource, int width, int height) :
		m_cRef(1)
{
	// Round width up to the next power of 2
	width = RoundUpPowerOf2(width);
	// Round height up to the next power of 2
	height = RoundUpPowerOf2(height);

	// Check size is valid
	if (width < 16)// || width > 512)
		throw 0;	// Error
	if (height < 16)// || height > 256)
		throw 0;

	// Initialize variables
	// ********************

	// Misc variables
	tileWidth = width;
	tileData = NULL;
	tileSetManager = NULL;
	tileSource = tileSetSource;
	numTileGroups = 0;
	tileGroupInfo = NULL;

	// Initialize map header structure
	mapHeadInfo.tag = 0x00001011;
	mapHeadInfo.unknown = 0;
	mapHeadInfo.tileHeight = height;
	mapHeadInfo.numTileSets = 512;
	// Calculate the log (base 2) of the map width
	mapHeadInfo.lgTileWidth = LogBase2(tileWidth);

	// Initialize the clipping rectangle
	if (mapHeadInfo.lgTileWidth >= 9)
	{
		clipRect.x1 = -1;
		clipRect.y1 = 0;
		clipRect.x2 = 0x7FFFFFFF;
		clipRect.y2 = mapHeadInfo.tileHeight-2;
	}
	else
	{
		clipRect.x1 = 32;
		clipRect.y1 = 0;
		clipRect.x2 = tileWidth + 0x1F;
		clipRect.y2 = mapHeadInfo.tileHeight-2;
	}

	// Allocate space for data
	tileData = new int[tileWidth*mapHeadInfo.tileHeight];
	tileSetManager = new CTileSetManager(tileSetSource);

	// Clear tile data to 0
	memset(tileData, 0, tileWidth*mapHeadInfo.tileHeight);

	g_cLocks++;
}

CMapFile::CMapFile(
	TileSetSource *tileSetSource,
	StreamReader *stream,
	enum MapLoadSaveFormat loadFlags
) :
	m_cRef(1)
{
	// Initialize variables
	tileData = NULL;
	tileSetManager = NULL;
	tileSource = tileSetSource;
	numTileGroups = 0;
	tileGroupInfo = NULL;

	if (LoadMap(stream, tileSetSource, loadFlags) != 0)
	{
		// Error reading in map data
		FreeMemory();

		throw L"Error loading map data from stream.";
	}

	g_cLocks++;
}

CMapFile::~CMapFile()
{
	g_cLocks--;

	FreeMemory();
}

void CMapFile::FreeMemory()
{
	if (tileData != NULL)
		delete [] tileData;
	if (tileSetManager != NULL)
		tileSetManager->Release();
	if (tileGroupInfo != NULL)
	{
		int i;
		// Release each tile group
		for (i = 0; i < numTileGroups; i++)
		{
			if (tileGroupInfo[i].tileGroup != NULL)
				tileGroupInfo[i].tileGroup->Release();
			if (tileGroupInfo[i].name != NULL)
				delete [] tileGroupInfo[i].name;
		}

		// Release the tile group info array
		delete [] tileGroupInfo;
	}
}
