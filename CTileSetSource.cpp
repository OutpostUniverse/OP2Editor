
#include "stdafx.h"
#include "CTileSetSource.h"


extern int g_cLocks;


ULONG __stdcall CTileSetSource::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CTileSetSource::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CTileSetSource::QueryInterface(REFIID riid, void** ppv)
{
    if(riid == IID_IUnknown)
        *ppv = (IUnknown*)this;
    else if(riid == IID_TileSetSource)
        *ppv = (TileSetSource*)this;
    else
    {
        *ppv = NULL;
        return E_NOINTERFACE;
    }
    AddRef();

    return S_OK;
}




CTileSetSource::CTileSetSource(IResourceManager *resourceManager) : m_cRef(1)
{
	head = NULL;	// Initialize linked list of loaded files to empty

	resManager = resourceManager;	// CTileSetSource is owned by IResourceManager
									// so the reference count should not be incremented
									// (Don't want circular references)

	g_cLocks++;
}

CTileSetSource::~CTileSetSource()
{
	LinkedListNode *current, *next;

	g_cLocks--;

	current = head;
	// Traverse each node
	while (current)
	{
		// Get the next node in the list
		next = current->next;

		// Free the tile set
		current->tileSet->Release();
		// Free the tile set name BSTR
		SysFreeString(current->tileSetName);

		// Delete the current node
		delete current;
		current = next;
	}
}


// TileSetSource functions
// ***********************


HRESULT CTileSetSource::LoadTileSet(BSTR tileSetName, TileSet **tileSet)
{
	LinkedListNode *current;
	StreamReader *stream;
	TileSet *newTileSet;
	LinkedListNode *newNode;
	BSTR tempName;
	unsigned int lenString;
	HRESULT hr;

	*tileSet = NULL;	// Initialize return pointer to NULL

	// Cache string length
	lenString = SysStringLen(tileSetName);
	current = head;
	// Search linked list for already loaded copy
	while (current)
	{
		// Check if tile set names match
		if ( (lenString == SysStringLen(current->tileSetName))
			&& (memcmp(tileSetName, current->tileSetName, lenString*2) == 0) )
		{
			// Update the count
			current->loadedCount++;
			// Return a copy of the tile set
			*tileSet = current->tileSet;
			(*tileSet)->AddRef();

			return S_OK;
		}

		// process next node in list
		current = current->next;
	}

	// Add the ".bmp" extension
	tempName = SysAllocStringLen(NULL, lenString+4);
	memcpy(tempName, tileSetName, lenString*2);
	memcpy((char*)tempName + lenString*2, L".bmp", 8);

	// Tile set not found in list. Try to find the file
	resManager->OpenStreamRead(tempName, &stream);
	SysFreeString(tempName);
	// Check if the resource could not be opened
	if (stream == NULL)
		return E_FAIL;

	try
	{
		// Resource was found and opened. Read in the tile set
		newTileSet = (TileSet*) new CTileSet(stream);
	}
	catch(...)
	{
		// Error loading tile set from stream
		stream->Release();
		return E_FAIL;
	}

	// Release the stream
	stream->Release();
	// Check if the object was constructed properly
	if (newTileSet == NULL)
		return E_OUTOFMEMORY;

	// Create a new linked list node
	newNode = new LinkedListNode;
	if (newNode == NULL)
	{
		newTileSet->Release();
		return E_OUTOFMEMORY;
	}
	hr = newTileSet->QueryInterface(IID_TileSet, (void**)&newNode->tileSet);
	if (FAILED(hr))
	{
		delete newNode;
		newTileSet->Release();
		return hr;
	}
	newNode->loadedCount = 1;
	newNode->tileSetName = SysAllocString(tileSetName);
	// Add the tile set to the linked list
	newNode->next = head;
	head = newNode;

	// Return a copy of the tile set
	(*tileSet) = newNode->tileSet;

	return hr;
}

HRESULT CTileSetSource::UnloadTileSet(BSTR tileSetName)
{
	LinkedListNode *current;

	// Find the node in the linked list
	current = head;
	while (current)
	{
		// Check if tile set names match
		if ( (SysStringLen(tileSetName) == SysStringLen(current->tileSetName))
			&& (memcmp(tileSetName, current->tileSetName, SysStringByteLen(tileSetName)) == 0) )
		{
			// Decrement the count
			current->loadedCount--;

			// Note: Don't free the tile set here since it may likely be loaded again soon 
			// **TODO** Handle this possible optimization
			if (current->loadedCount == 0)
			{
				// Unload the tile set and remove the node from the linked list
				//current->tileSet->Release();
			}

			return S_OK;
		}

		// process next node in list
		current = current->next;
	}

	// Node not found. Ignore.
	return S_OK;
}
