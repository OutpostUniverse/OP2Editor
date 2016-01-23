
#include "stdafx.h"
#include "CTileGroup.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


// IUnknown functions
// ******************

ULONG __stdcall CTileGroup::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CTileGroup::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CTileGroup::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown)
        *ppv = (IUnknown*)this;
    else if (riid == IID_TileGroup)
        *ppv = (TileGroup*)this;
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

HRESULT CTileGroup::get_TileWidth(int *width)
{
	*width = tileWidth;

	return S_OK;
}

HRESULT CTileGroup::get_TileHeight(int *height)
{
	*height = tileHeight;

	return S_OK;
}


HRESULT CTileGroup::get_TileSetManager(TileSetManager **tileSetManager)
{
	this->tileSetManager->QueryInterface(IID_TileSetManager, (void**)tileSetManager);

	return S_OK;
}


HRESULT CTileGroup::get_MappingIndex(int tileX, int tileY, int *tileMappingIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	// Get the tile mapping index
	*tileMappingIndex = tileData[tileY*tileWidth + tileX];

	return S_OK;
}

HRESULT CTileGroup::put_MappingIndex(int tileX, int tileY, int tileMappingIndex)
{
	// Error check array indicies
	if ((tileX < 0) || (tileX >= tileWidth) || (tileY < 0) || (tileY >= tileHeight))
	{
		PostErrorMsg(L"Invalid tile location");
		return E_INVALIDARG;
	}

	// Set the tile mapping index
	tileData[tileY*tileWidth + tileX] = tileMappingIndex;

	return S_OK;
}


HRESULT CTileGroup::Draw(int destDC, int sourcePixelX, int sourcePixelY, int pixelWidth, int pixelHeight)
{
	int startXTile = sourcePixelX >> 5;
	int startYTile = sourcePixelY >> 5;
	int endXTile = (sourcePixelX+pixelWidth+31) >> 5;
	int endYTile = (sourcePixelY+pixelHeight+31) >> 5;
	int x, y;
	int tileIndex;
	TileSet *tileSet;
	CTileSetManager::TileSetTileMapping *tileMap;
	int destPixelX = -(sourcePixelX & 0x1F);
	int destPixelY = -(sourcePixelY & 0x1F);

	if (endYTile > tileHeight)
		endYTile = tileHeight;
	if (endXTile > tileWidth)
		endXTile = tileWidth;

	// Draw all tiles in visible range
	for (y = startYTile; y < endYTile; y++)
	{
		for (x = startXTile; x < endXTile; x++)
		{
			// Load the tile mapping index
			tileIndex = tileData[y*tileWidth + x];

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



// Class specific
// **************

CTileGroup::CTileGroup(int tileWidth, int tileHeight, CTileSetManager *tileSetManager) : m_cRef(1)
{
	// Initialize variables
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->tileSetManager = tileSetManager;
	// Increment reference count of tile set manager object
	tileSetManager->AddRef();

	// Check for NULL tile set manager object pointer
	if (tileSetManager == NULL)
		throw L"Error: TileSetManager object pointer is NULL.";

	// Allocate space for data
	tileData = new int[tileWidth*tileHeight];

	// Increment module lock count
	g_cLocks++;
}

CTileGroup::CTileGroup(int tileWidth, int tileHeight, TileSetSource *tileSetSource) : m_cRef(1)
{
	// Initialize variables
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	// Allocate space for data
	tileData = new int[tileWidth*tileHeight];
	tileSetManager = new CTileSetManager(tileSetSource);

	// Increment module lock count
	g_cLocks++;
}

CTileGroup::~CTileGroup()
{
	if (tileData != NULL)
		delete [] tileData;
	if (tileSetManager != NULL)
		tileSetManager->Release();

	// Decrement module lock count
	g_cLocks--;
}
