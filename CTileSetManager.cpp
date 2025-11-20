#include "stdafx.h"
#include "OP2Editor.h"
#include "CTileSetManager.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


const char CTileSetManager::tagTileSet[] = "TILE SET\x01A";


// IUnknown functions
// ******************

ULONG __stdcall CTileSetManager::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CTileSetManager::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CTileSetManager::QueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)(TileSetManager*)this;
	else if (riid == IID_TileSetManager)
		*ppv = (TileSetManager*)this;
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


// ISupportErrorInfo
// *****************

HRESULT CTileSetManager::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (riid == IID_TileSetManager)
		return S_OK;
	else
		return S_FALSE;
}


// TileSetManager
// **************

HRESULT CTileSetManager::get_NumTileSets(int *numTileSets)
{
	*numTileSets = this->numTileSets;

	return S_OK;
}

HRESULT CTileSetManager::get_TileSetName(int index, BSTR *tileSetName)
{
	// Error check array bounds
	if ((index < 0) || (index >= numTileSets))
	{
		PostErrorMsg(L"Invalid index value.");
		return E_INVALIDARG;
	}

	// Return a new copy of the string (replacing passed in string)
	SysReAllocString(tileSetName, tileSetInfo[index].wideTileSetName);

	return S_OK;
}

HRESULT CTileSetManager::get_TileSet(int index, TileSet **tileSet)
{
	// Return the tile set object (interface) pointer
	*tileSet = tileSetInfo[index].tileSet;
	if (*tileSet != NULL)
		(*tileSet)->AddRef();		// Increment the reference count

	return S_OK;
}

HRESULT CTileSetManager::AddTileSet(BSTR tileSetName, int *index)
{
	TileSetInfo *tileInfo;
	TileSet *tileSet;
	unsigned int lenString;
	int tileSetIndex;

	// Cache the tileSetName string length
	lenString = SysStringLen(tileSetName);
	*index = -1;

	// Check if tile set is already loaded
	for (tileSetIndex = 0; tileSetIndex < numTileSets; tileSetIndex++)
	{
		tileInfo = &tileSetInfo[tileSetIndex];		// Cache the tileSetInfo address

		// Check if input string matches this entry
		if ( (lenString == SysStringLen(tileInfo->wideTileSetName))
			&& (memcmp(tileSetName, tileInfo->wideTileSetName, lenString*2) == 0) )
		{
			// Tile set already loaded
			*index = tileSetIndex;

			PostErrorMsg(L"Tile set already loaded.");
			return E_FAIL;
		}
	}

	// Try to load the tile set
	tileSource->LoadTileSet(tileSetName, &tileSet);
	if (tileSet == NULL)
	{
		// Failed to load the tile set
		PostErrorMsg(L"Failed to load the tile set.");
		return E_FAIL;
	}

	// Find an empty tile set slot
	for (tileSetIndex = 0; tileSetIndex < numTileSets; tileSetIndex++)
	{
		if (tileSetInfo[tileSetIndex].stringLength == 0)
		{
			// Empty slot found. Add tile set here
			break;	// Fill in entries after the loop
		}
	}

	if (tileSetIndex >= numTileSets)
	{
		// No empty tile set slot found. Try to extend the tile set list.
		TileSetInfo *newInfo = new TileSetInfo[numTileSets+1];
		if (newInfo == NULL)
		{
			// Failed to allocate new space for tile mappings
			// Release the loaded tile set
			tileSource->UnloadTileSet(tileSetName);
			tileSet->Release();

			PostErrorMsg(L"Could not allocate space for new tile set array.");

			return E_FAIL;
		}
		// Copy the tile set info to the new array
		memcpy(newInfo, tileSetInfo, sizeof(*tileSetInfo)*numTileSets);
		// Release the old data
		delete [] tileSetInfo;
		// Update the pointer to the new array
		tileSetInfo = newInfo;
		// Increment number of tile sets in array
		numTileSets++;
	}

	// Fill in tile set info entry
	*index = tileSetIndex;
	tileInfo = &tileSetInfo[tileSetIndex];		// Cache pointer to entry
	// Store string length
	tileInfo->stringLength = lenString;
	// Allocate a new BSTR to cache the name
	tileInfo->wideTileSetName = SysAllocString(tileSetName);
	// Allocate a new char array to hold the tile set name
	tileInfo->tileSetName = new char[lenString+1];
	tileInfo->tileSetName[lenString] = 0;	// NULL terminate it
	// Convert the BSTR to ASCII
	WideCharToMultiByte(CP_ACP, 0, tileSetName, lenString, tileInfo->tileSetName, lenString, 0, 0);
	// Initialize tile set variables
	tileSet->get_NumTiles(&tileInfo->numTiles);
	tileInfo->tileSet = tileSet;

	// Return success
	return S_OK;
}

HRESULT CTileSetManager::RemoveTileSet(BSTR tileSetName, int *index)
{
	TileSetInfo *tileInfo;
	unsigned int lenString;
	int i;

	lenString = SysStringLen(tileSetName);	// Cache the tileSetName string length
	*index = -1;
	// Search for the input string in the array
	for (i = 0; i < numTileSets; i++)
	{
		tileInfo = &tileSetInfo[i];		// Cache the tileSetInfo address

		// Check if input string matches this entry
		if ( (lenString == SysStringLen(tileInfo->wideTileSetName))
			&& (memcmp(tileSetName, tileInfo->wideTileSetName, lenString*2) == 0) )
		{
			// Strings match. Delete this entry
			*index = i;
			// Release the tile set
			tileSource->UnloadTileSet(tileSetName);
			// Release the cached tile set name BSTR
			SysFreeString(tileInfo->wideTileSetName);
			tileInfo->wideTileSetName = NULL;
			// Free the ascii string
			delete [] tileInfo->tileSetName;
			tileInfo->tileSetName = NULL;
			// Reset all other variables
			tileInfo->stringLength = 0;
			tileInfo->numTiles = 0;
			tileInfo->tileSet->Release();
			tileInfo->tileSet = NULL;
			// Break out of the loop
			break;
		}
	}

	// **TODO** Clear out the mapping array elements which referred to this tile set

	return S_OK;
}

HRESULT CTileSetManager::ReplaceTileSet(int index, BSTR tileSetName)
{
	TileSet *tileSet;
	int numTiles;

	// Error check
	// ***********
	// Check for invalid index values
	if ((index < 0) || (index >= numTileSets))
	{
		PostErrorMsg(L"Invalid index value.");
		return E_INVALIDARG;
	}

	// Try to load the tile set
	tileSource->LoadTileSet(tileSetName, &tileSet);
	// Check for error loading the tile set
	if (tileSet == NULL)
	{
		// Failed to load the tile set
		PostErrorMsg(L"Failed to load the tile set.");
		return E_FAIL;
	}

	// Check if the tile set has the right number of tiles
	TileSetInfo &tileInfo = tileSetInfo[index];
	tileSet->get_NumTiles(&numTiles);
	if (numTiles != tileInfo.numTiles)
	{
		PostErrorMsg(L"Error replacing tile sets. Tile sets must have the same number of tiles.");
		return E_FAIL;
	}

	// Replace the tile sets
	// *********************
	// Remove the old tile set
	tileSource->UnloadTileSet(tileInfo.wideTileSetName);
	tileInfo.tileSet->Release();
	// Add the new tile set
	tileInfo.tileSet = tileSet;
	tileInfo.numTiles = numTiles;
	tileInfo.stringLength = SysStringLen(tileSetName);
	SysReAllocString(&tileInfo.wideTileSetName, tileSetName);
	// Allocate a new char array to hold the tile set name
	tileInfo.tileSetName = new char[tileInfo.stringLength+1];
	tileInfo.tileSetName[tileInfo.stringLength] = 0;	// NULL terminate it
	// Convert the BSTR to ASCII
	WideCharToMultiByte(CP_ACP, 0, tileSetName, tileInfo.stringLength, tileInfo.tileSetName, tileInfo.stringLength, 0, 0);

	return S_OK;
}

HRESULT CTileSetManager::MapInTiles(int tileSetIndex, int startTile, int numTiles, int *mappingIndex)
{
	// Initialize returned mapping index to invalid
	*mappingIndex = -1;

	// Error check
	// ***********
	// Make sure the specified tile set is valid
	if (tileSetIndex >= numTileSets)
	{
		PostErrorMsg(L"Invalid tile set specified.");
		return E_INVALIDARG;
	}
	// Check for an invalid tile range
	if ((startTile < 0) || (numTiles < 1))
	{
		PostErrorMsg(L"Invalid range. Value of startTile must be nonnegative (>=0) and value of numTiles must be positive (>0).");
		return E_INVALIDARG;
	}
	// Make sure the range of tiles is contained in the specified tile set (Note: comparison must be > here)
	if ((startTile + numTiles) > tileSetInfo[tileSetIndex].numTiles)
	{
		PostErrorMsg(L"Invaild range. The tile set does not contain those tiles.");
		return E_INVALIDARG;
	}
	// Check if there is room to add the new tile mapping entries
	if ((numMappings + numTiles) >= 2048)
	{
		PostErrorMsg(L"Only a maximum of 2048 tiles can be used.");
		return E_FAIL;
	}

	// Add in the new tile set mappings
	// ********************************
	// Allocate space for new mapping array
	TileSetTileMapping *newMapping = new TileSetTileMapping[numMappings + numTiles];
	// Check for allocation error
	if (newMapping == NULL)
	{
		PostErrorMsg(L"Could not allocate memory for new mapping array.");
		return E_FAIL;
	}

	// Copy the old array into the new one
	memcpy(newMapping, mapping, sizeof(mapping[0])*numMappings);
	// Release the old memory
	delete [] mapping;
	// Update the array pointer
	mapping = newMapping;

	// Initialize new entries
	int i;
	*mappingIndex = numMappings;
	for (i = 0; i < numTiles; i++)
	{
		mapping[numMappings+i].tileSetIndex = tileSetIndex;
		mapping[numMappings+i].tileIndex = startTile + i;
		mapping[numMappings+i].numTileReplacements = 0;
		mapping[numMappings+i].cycleDelay = 0;
	}
	// Update the number of mappings
	numMappings += numTiles;

	// Return success
	return S_OK;
}

// Note: Use -1 for don't care conditions on numTileReplacements and cycleDelay.
//		 Use -2 for a nonzero condition on numTileReplacements and cycleDelay.
HRESULT CTileSetManager::GetMappingIndex(int tileSetIndex, int tileIndex, int numTileReplacements, int cycleDelay, int *mappingIndex)
{
	int i;

	for (i = 0; i < numMappings; i++)
	{
		TileSetTileMapping &map = mapping[i];
		if ((map.tileSetIndex == tileSetIndex) && (map.tileIndex == tileIndex))
		{
			// TileSet and TileSetIndex match.
			// Check remaining parameters
			if ((numTileReplacements == -1) || (numTileReplacements == map.numTileReplacements) || ((numTileReplacements == -2) && (map.numTileReplacements != 0)))
			{
				if ((cycleDelay == -1) || (cycleDelay == map.cycleDelay) || ((cycleDelay == -2) && (map.cycleDelay != 0)))
				{
					// Match found
					*mappingIndex = i;

					return S_OK;
				}
			}
		}
	}

	// Entry not found
	*mappingIndex = -1;

	return S_OK;
}

HRESULT CTileSetManager::get_NumMappings(int *numMappings)
{
	*numMappings = this->numMappings;

	return S_OK;
}


HRESULT CTileSetManager::get_TileSetIndex(int mappingIndex, int *tileSetIndex)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	*tileSetIndex = mapping[mappingIndex].tileSetIndex;

	return S_OK;
}

HRESULT CTileSetManager::put_TileSetIndex(int mappingIndex, int tileSetIndex)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	mapping[mappingIndex].tileSetIndex = tileSetIndex;

	return S_OK;
}


HRESULT CTileSetManager::get_TileSetTileIndex(int mappingIndex, int *tileSetTileIndex)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	*tileSetTileIndex = mapping[mappingIndex].tileIndex;

	return S_OK;
}

HRESULT CTileSetManager::put_TileSetTileIndex(int mappingIndex, int tileSetTileIndex)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	mapping[mappingIndex].tileIndex = tileSetTileIndex;

	return S_OK;
}


HRESULT CTileSetManager::get_NumTileReplacements(int mappingIndex, int *numTileReplacements)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	*numTileReplacements = mapping[mappingIndex].numTileReplacements;

	return S_OK;
}

HRESULT CTileSetManager::put_NumTileReplacements(int mappingIndex, int numTileReplacements)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	mapping[mappingIndex].numTileReplacements = numTileReplacements;

	return S_OK;
}


HRESULT CTileSetManager::get_CycleDelay(int mappingIndex, int *cycleDelay)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	*cycleDelay = mapping[mappingIndex].cycleDelay;

	return S_OK;
}

HRESULT CTileSetManager::put_CycleDelay(int mappingIndex, int cycleDelay)
{
	if ((mappingIndex < 0) || (mappingIndex >= numMappings))
	{
		PostErrorMsg(L"Mapping index out of range.");
		return E_INVALIDARG;
	}

	mapping[mappingIndex].cycleDelay = cycleDelay;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_NumTerrains(int *numTerrains)
{
	*numTerrains = this->numTerrains;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::SetNumTerrains(int numTerrains)
{
	if (numTerrains < 1)
	{
		PostErrorMsg(L"There must be at least one terrain type in a map.");
		return E_INVALIDARG;
	}

	// Allocate space for new terrain array
	TerrainType *newTerrain = new TerrainType[numTerrains];
	// Check for allocation error
	if (newTerrain == NULL)
	{
		PostErrorMsg(L"Could not allocate memory for new terrain array.");
		return E_FAIL;
	}
	// Zero it
	memset(newTerrain, 0, sizeof(terrain[0])*numTerrains);

	// Copy the old array into the new one
	if (numTerrains < this->numTerrains)
		memcpy(newTerrain, terrain, sizeof(terrain[0])*numTerrains);
	else
		memcpy(newTerrain, terrain, sizeof(terrain[0])*this->numTerrains);

	// Release the old memory
	delete [] terrain;
	// Update the array pointer & numTerrains var
	terrain = newTerrain;
	this->numTerrains = numTerrains;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainStartTile(int terrainIndex, int *startMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*startMapping = terrain[terrainIndex].firstTile;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainStartTile(int terrainIndex, int startMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].firstTile = startMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainEndTile(int terrainIndex, int *endMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*endMapping = terrain[terrainIndex].lastTile;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainEndTile(int terrainIndex, int endMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].lastTile = endMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainDozed(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].bulldozed;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainDozed(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].bulldozed = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainRubble(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].commonRubble;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainRubble(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].commonRubble = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainTubeUnk(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 5)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].tubeUnknown[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainTubeUnk(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 5)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].tubeUnknown[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainLavaWall(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].wall[0].tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainLavaWall(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].wall[0].tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainMicrobeWall(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].wall[1].tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainMicrobeWall(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].wall[1].tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainNormalWall(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].wall[2].tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainNormalWall(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].wall[2].tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainDamagedWall(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].wall[3].tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainDamagedWall(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].wall[3].tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainRuinedWall(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].wall[4].tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainRuinedWall(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].wall[4].tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainLava(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].lava;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainLava(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].lava = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainFlat1(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].flat1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainFlat1(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].flat1 = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainFlat2(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].flat2;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainFlat2(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].flat2 = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainFlat3(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].flat3;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainFlat3(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].flat3 = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainTube(int terrainIndex, enum TerrainTubeDirection direction, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].tube.tile[direction];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainTube(int terrainIndex, enum TerrainTubeDirection direction, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (direction < 0 || direction > 15)
	{
		PostErrorMsg(L"Invalid direction.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].tube.tile[direction] = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainScorched(int terrainIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].scorched;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainScorched(int terrainIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].scorched = dataMapping;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::get_TerrainUnknown(int terrainIndex, int unkIndex, int *dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (unkIndex < 0x0 || unkIndex > 0x14)
	{
		PostErrorMsg(L"Invalid unkIndex.");
		return E_INVALIDARG;
	}

	*dataMapping = terrain[terrainIndex].unknown[unkIndex];
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CTileSetManager::put_TerrainUnknown(int terrainIndex, int unkIndex, int dataMapping)
{
	if (terrainIndex < 0 || terrainIndex > numTerrains)
	{
		PostErrorMsg(L"Invalid terrain ID.");
		return E_INVALIDARG;
	}
	if (unkIndex < 0x0 || unkIndex > 0x14)
	{
		PostErrorMsg(L"Invalid unkIndex.");
		return E_INVALIDARG;
	}

	terrain[terrainIndex].unknown[unkIndex] = dataMapping;
	return S_OK;
}


// Constructor/Destructor
// **********************

CTileSetManager::CTileSetManager(TileSetSource *tileSetSource) :
	m_cRef(1), tileSource(tileSetSource)
{
	// Initialize variables
	numTileSets = 512;
	numMappings = 0;
	mapping = NULL;
	numTerrains = 0;
	terrain = NULL;

	// Allocate memory for the tile sets and clear it out
	tileSetInfo = new TileSetInfo[numTileSets];
	memset(tileSetInfo, 0, sizeof(*tileSetInfo)*numTileSets);

	// Increment module lock count
	g_cLocks++;
}

CTileSetManager::CTileSetManager(TileSetSource *tileSetSource, int numTileSets, StreamReader *inStream) :
	m_cRef(1), tileSource(tileSetSource)
{
	// Initialize variables
	this->numTileSets = numTileSets;
	tileSetInfo = NULL;
	numMappings = 0;
	mapping = NULL;
	numTerrains = 0;
	terrain = NULL;

	if (Load(inStream) != 0)
	{
		// Error reading in data
		FreeMemory();

		// Don't throw anything, let the Load method pass it down
		//throw L"CTileSetManager: Error loading tile set data";
	}

	// Increment module lock count
	g_cLocks++;
}

CTileSetManager::~CTileSetManager()
{
	// Decrement module lock count
	g_cLocks--;

	// Free memory
	FreeMemory();
}


// Class specific
// **************

void CTileSetManager::FreeMemory()
{
	int i;
	TileSetInfo *tileSet;

	if (mapping)
		delete [] mapping;
	if (terrain)
		delete [] terrain;

	if (tileSetInfo)
	{
		// Free all the string data
		for (i = 0; i < numTileSets; i++)
		{
			tileSet = &tileSetInfo[i];
			if (tileSet->wideTileSetName)
			{
				// Unload tile set
				tileSource->UnloadTileSet(tileSetInfo[i].wideTileSetName);
				// Free the memory for the BSTR
				SysFreeString(tileSetInfo[i].wideTileSetName);
			}
			if (tileSet->tileSetName)
			{
				// Free the memory for the string
				delete [] tileSetInfo[i].tileSetName;
			}
			if (tileSet->tileSet)
			{
				tileSet->tileSet->Release();
			}
		}

		delete [] tileSetInfo;
	}
}


int CTileSetManager::Save(StreamWriter *stream)
{
	int i;
	int numBytesWritten;

	// Write the tile set file list
	for (i = 0; i < numTileSets; i++)
	{
		// Write the length of the string
		stream->Write(4, (int)&tileSetInfo[i].stringLength, &numBytesWritten);
		if (tileSetInfo[i].stringLength)
		{
			// String exists. Write it.
			stream->Write(tileSetInfo[i].stringLength, (int)tileSetInfo[i].tileSetName, &numBytesWritten);
			// Write the number of tiles in this tile set
			stream->Write(4, (int)&tileSetInfo[i].numTiles, &numBytesWritten);
		}
	}

	// Write the Tile Set info
	// Write the section tag "TILE SET", 0x1A, 0
	stream->Write(0xA, (int)tagTileSet, &numBytesWritten);
	// Write the number of tile set mappings
	stream->Write(4, (int)&numMappings, &numBytesWritten);
	// Write the tile set tile mappings
	stream->Write(sizeof(*mapping)*numMappings, (int)mapping, &numBytesWritten);
	// Write the number of terrain types
	stream->Write(4, (int)&numTerrains, &numBytesWritten);
	// Write the terrain type info
	stream->Write(sizeof(*terrain)*numTerrains, (int)terrain, &numBytesWritten);

	return 0;
}


int CTileSetManager::Load(StreamReader *stream)
{
	char buff[64];			// Used to read the "TILE SET" tag
	TileSetInfo *tileSet;
	int numBytesRead;
	int i, temp;

	try
	{
		// Allocate space for the tile set info
		tileSetInfo = new TileSetInfo[numTileSets];
		// Load Tile Set file list
		for (i = 0; i < numTileSets; i++)
		{
			// Cache the tileSet address
			tileSet = &tileSetInfo[i];

			// Read the length of the string
			stream->Read(4, (int)&temp, &numBytesRead);
			// Initialize struct variables
			tileSet->stringLength = temp;		// Store the string length
			tileSet->tileSetName = NULL;		// NULL string pointer
			tileSet->wideTileSetName = NULL;	// NULL string pointer
			tileSet->numTiles = 0;				// No loaded tiles in this tile set
			tileSet->tileSet = NULL;			// NULL ITileSet pointer

			// If string length > 0 then read other fields
			if (temp > 0)
			{
				// String exists.
				// Allocate space for string
				tileSet->tileSetName = new char[temp+1];
				if (tileSet->tileSetName == NULL)
					throw L"Out of memory error. Could not allocate space for tile set name strings.";	// Error. Out of memory

				tileSet->tileSetName[temp] = 0;	// NULL terminate the string
				// Read the string
				stream->Read(temp, (int)tileSet->tileSetName, &numBytesRead);
				// Allocate space for a BSTR to hold the name
				tileSetInfo[i].wideTileSetName = SysAllocStringLen(NULL, temp);
				// Convert the name to unicode
				MultiByteToWideChar(
					CP_ACP,
					0,
					tileSetInfo[i].tileSetName,
					temp,
					tileSetInfo[i].wideTileSetName,
					temp
				);
				// Load the associated tile set
				tileSource->LoadTileSet(tileSetInfo[i].wideTileSetName, &tileSet->tileSet);
				// Make sure the tile set was found
				if (tileSet->tileSet == NULL)
					throw L"Error loading map data. Tile set could not be loaded.";

				// Read the number of tiles stored in this tile set
				stream->Read(4, (int)&tileSet->numTiles, &numBytesRead);
			}
		}


		// Load Tile Set mapping info
		// Read the string "TILE SET", 0x1A, 0
		stream->Read(0xA, (int)buff, &numBytesRead);
		if (strncmp(buff, tagTileSet, 0xA))
			throw L"Format error. Could not find \"TILE SET\" tag.";	// Failed. Format Error.
		// Read the number of tile set tile mappings
		stream->Read(4, (int)&numMappings, &numBytesRead);
		// Allocate space for the tile set tile mappings
		mapping = new TileSetTileMapping[numMappings];
		// Read the tile set tile mapping info
		stream->Read(sizeof(mapping[0])*numMappings, (int)mapping, &numBytesRead);
		// Read the number of terrain types
		stream->Read(4, (int)&numTerrains, &numBytesRead);
		// Allocate space for terrain type info
		terrain = new TerrainType[numTerrains];
		// Read the terrain type info
		stream->Read(sizeof(*terrain)*numTerrains, (int)terrain, &numBytesRead);
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

	return 0;
}
