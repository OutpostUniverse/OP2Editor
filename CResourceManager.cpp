
#include "stdafx.h"
#include "CResourceManager.h"
#include "CFileStreamReader.h"
#include "CFileStreamWriter.h"
#include "CVolReader.h"
#include "CVolWriter.h"
#include "CClmReader.h"
#include "CClmWriter.h"
#include "CMapFile.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


ULONG __stdcall CResourceManager::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CResourceManager::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CResourceManager::QueryInterface(REFIID riid, void** ppv)
{
    if (riid == IID_IUnknown)
        *ppv = (IUnknown*)(ResourceManager*)this;
    else if (riid == IID_IResourceManager)
        *ppv = (IResourceManager*)this;
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





CResourceManager::CResourceManager(BSTR gamePath) : m_cRef(1)
{
	// Initilize linked list of archives in search path
	head = NULL;
	tail = NULL;
	int stringLength;

	// Cache string length
	stringLength = SysStringLen(gamePath);
	// Add a trailing "\" if none exists
	if ((stringLength > 0) && (gamePath[stringLength-1] != L'\\'))
	{
		// Allocate space for string + "\"
		path = SysAllocStringLen(NULL, stringLength+1);
		// Copy the string
		memcpy(path, gamePath, stringLength*2);
		// Append a trailing "\"
		path[stringLength] = L'\\';
	}
	else
	{
		// Save the path to the game folder
		path = SysAllocString(gamePath);
	}

	// Create a new tile set source object
	tileSetSource = new CTileSetSource(this);

	g_cLocks++;
}

CResourceManager::~CResourceManager()
{
	LinkedListNode *current, *next;

	g_cLocks--;

	// Unload all archives in search path and delete linked list nodes
	current = head;
	while (current)
	{
		current->archive->Release();
		next = current->next;
		delete current;
		current = next;
	}

	// Free the tile set source object
	tileSetSource->Release();
	// Free the game path BSTR
	SysFreeString(path);
}



HRESULT CResourceManager::get_RootPath(BSTR *path)
{
	SysReAllocString(path, this->path);

	return S_OK;
}

HRESULT CResourceManager::put_RootPath(BSTR newPath)
{
	int stringLength;

	// Cache string length
	stringLength = SysStringLen(newPath);
	// Add a trailing "\" if none exists
	if ((stringLength > 0) && (newPath[stringLength-1] != L'\\'))
	{
		// Allocate space for string + "\"
		SysReAllocStringLen(&path, NULL, stringLength+1);
		// Copy the string
		memcpy(path, newPath, stringLength*2);
		// Append a trailing "\"
		path[stringLength] = L'\\';
	}
	else
	{
		// Save the path to the game folder
		SysReAllocString(&path, newPath);
	}

	// Replace the resource sources
	delete tileSetSource;
	tileSetSource = new CTileSetSource(this);

	return S_OK;
}





HRESULT CResourceManager::OpenStreamRead(
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamReader **stream)
{
	int lenFileName = SysStringLen(fileName);
	int lenPath = SysStringLen(path);
	BSTR pathAndFile = NULL;
	// Initialize returned stream pointer to NULL
	*stream = NULL;

	// Check if relative path given
	if (IsRelative(fileName))
	{
		// Form the full path name rooted at the desired directory
		pathAndFile = SysAllocStringLen(NULL, lenFileName + lenPath);
		memcpy(pathAndFile, path, lenPath*2);
		memcpy((char*)pathAndFile + (lenPath * 2), fileName, lenFileName*2);
	}
	else
	{
		// Absolute path. Copy the string
		pathAndFile = SysAllocString(fileName);
	}

	// Check if file exists in directory rooted at the game path
	try
	{
		*stream = new CFileStreamReader(pathAndFile);
	}
	catch(...)
	{
	}

	// Release the path string (Not needed for searching archives)
	SysFreeString(pathAndFile);

	if (*stream)
	{
		// Stream successfully opened
		return S_OK;
	}
	// Failed to open a file. Search the loaded vol files for this resource.
	LinkedListNode *current = head;
	while (current)
	{
		// Try to open the stream from each archive
		// Note: Don't use full path. Only resource name.
		current->archive->OpenStreamRead(fileName, stream);
		// Check if successful
		if (*stream != NULL)
		{
			// Stream opened successfully
			return S_OK;
		}
		current = current->next;
	}


	// Could not find resource.
	PostErrorMsg(L"Could not find resource.");
	return E_FAIL;
}

HRESULT CResourceManager::OpenStreamWrite(
            /* [in] */ BSTR fileName,
            /* [retval][out] */ StreamWriter **stream)
{
	int lenFileName = SysStringLen(fileName);
	int lenPath = SysStringLen(path);
	BSTR pathAndFile = NULL;

	// Initialize returned stream pointer to NULL
	*stream = NULL;

	// Check if relative path given
	if (IsRelative(fileName))
	{
		// Form the full path name rooted at the desired directory
		pathAndFile = SysAllocStringLen(NULL, lenFileName + lenPath);
		memcpy(pathAndFile, path, lenPath*2);
		memcpy((char*)pathAndFile + (lenPath * 2), fileName, lenFileName*2);
	}
	else
	{
		// Absolute path. Copy the string
		pathAndFile = SysAllocString(fileName);
	}

	// Try to open the file for writing
	try
	{
		*stream = new CFileStreamWriter(pathAndFile);
		if (stream == NULL)
		{
			SysFreeString(pathAndFile);
			PostErrorMsg(L"Failed to create stream writer.");
			return E_OUTOFMEMORY;
		}
	}
	catch(...)
	{
	}

	if (*stream)
	{
		// Stream successfully opened
		SysFreeString(pathAndFile);
		return S_OK;
	}

	// **Possible future expansion**
	// See if an existing archive file can accept the new data

	// Could not open the file for writing
	SysFreeString(pathAndFile);

	PostErrorMsg(L"Failed to create stream writer.");
	return E_FAIL;
}




HRESULT CResourceManager::LoadMapFile(BSTR fileName, enum MapLoadSaveFormat loadFlags, MapFile **mapFile)
{
	StreamReader *inStream;

	// Initialize returned mapFile pointer to NULL
	*mapFile = NULL;

	// Try to open the file as a stream
	OpenStreamRead(fileName, &inStream);
	// Check if a stream was constructed
	if (inStream == NULL)
	{
		// Failed to open the file as a stream
		return E_INVALIDARG;
	}

	// Read in the map data
	HRESULT hr = LoadMap(inStream, loadFlags, mapFile);

	// Release the input stream
	inStream->Release();

	return hr;
}

HRESULT CResourceManager::LoadMap(StreamReader *inStream, enum MapLoadSaveFormat loadFlags, MapFile **mapFile)
{
	CMapFile *pMapFile;

	// Initialize returned mapFile pointer to NULL
	*mapFile = NULL;

	try
	{
		pMapFile = new CMapFile(tileSetSource, inStream, loadFlags);
		if (pMapFile == 0) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Error constructing object
		return E_FAIL;
	}

	HRESULT hr = pMapFile->QueryInterface(IID_MapFile, (void**)mapFile);
	pMapFile->Release();

	return hr;
}

HRESULT CResourceManager::CreateNewMap(int width, int height, MapFile** newMap)
{
	CMapFile *pMapFile;

	// Initialize returned mapFile pointer to NULL
	*newMap = NULL;

	try
	{
		pMapFile = new CMapFile(tileSetSource, width, height);
		if (pMapFile == 0) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Error constructing object
		return E_FAIL;
	}

	HRESULT hr = pMapFile->QueryInterface(IID_MapFile, (void**)newMap);
	pMapFile->Release();

	return hr;
}




HRESULT CResourceManager::LoadTileSetFile(BSTR fileName, TileSet **tileSet)
{
	StreamReader *inStream;

	// Initialize returned tileSet pointer to NULL
	*tileSet = NULL;

	// Try to open the file as a stream
	OpenStreamRead(fileName, &inStream);
	// Check if a stream was constructed
	if (inStream == NULL)
	{
		// Failed to open the file as a stream
		return E_FAIL;
	}

	// Read in the tile set data
	HRESULT hr = LoadTileSet(inStream, tileSet);

	// Release the input stream
	inStream->Release();

	return hr;
}

HRESULT CResourceManager::LoadTileSet(StreamReader *stream, TileSet **tileSet)
{
	CTileSet *pTileSet;

	// Initialize returned tileSet pointer to NULL
	*tileSet = NULL;

	try
	{
		pTileSet = new CTileSet(stream);
		if (pTileSet == 0) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Error constructing object
		return E_FAIL;
	}

	HRESULT hr = pTileSet->QueryInterface(IID_TileSet, (void**)tileSet);
	pTileSet->Release();

	return hr;
}

HRESULT CResourceManager::CreateTileSet(int numTiles, int bitDepth, int width, TileSet **newTileSet)
{
	CTileSet *pTileSet;

	// Initialize returned tileSet pointer to NULL
	*newTileSet = NULL;

	try
	{
		pTileSet = new CTileSet(numTiles, bitDepth, width);
		if (pTileSet == 0) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Error constructing object
		return E_FAIL;
	}

	HRESULT hr = pTileSet->QueryInterface(IID_TileSet, (void**)newTileSet);
	pTileSet->Release();

	return hr;
}




HRESULT CResourceManager::LoadVolFile(BSTR fileName, int bAttachToStream, ArchiveReader **volReader)
{
	StreamReader *inStream;
	SeekableStreamReader *inSeekStream;

	// Initialize returned ArchiveReader to NULL
	*volReader = NULL;

	// Try to open the file as a stream
	OpenStreamRead(fileName, &inStream);
	// Check if a stream was constructed
	if (inStream == NULL)
	{
		// Failed to open the file as a stream
		return E_FAIL;
	}

	// Obtain the SeekableStreamReader interface
	inStream->QueryInterface(IID_SeekableStreamReader, (void**)&inSeekStream);
	inStream->Release();
	// Check if the interface was obtained
	if (inSeekStream == NULL)
	{
		// Failed to obtain a SeekableStreamReader interface
		return E_FAIL;
	}

	// Read in the vol data
	HRESULT hr = LoadVol(inSeekStream, bAttachToStream, volReader);

	// Release the stream
	inSeekStream->Release();

	return hr;
}

HRESULT CResourceManager::LoadVol(SeekableStreamReader *inStream, int bAttachToStream, ArchiveReader **volReader)
{
	CVolReader *pVolReader;

	// Initialize returned ArchiveReader to NULL
	*volReader = NULL;

	// Try to create a VOL reader
	try
	{
		pVolReader = new CVolReader(inStream, bAttachToStream);
		if (pVolReader == NULL) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		return E_FAIL;
	}

	// Obtain the ArchiveReader interface
	HRESULT hr = pVolReader->QueryInterface(IID_ArchiveReader, (void**)volReader);
	pVolReader->Release();

	return hr;
}

HRESULT CResourceManager::CreateVolFile(ArchiveWriter **volWriter)
{
	CVolWriter *pVolWriter;

	// Initialize returned ArchiveWriter to NULL
	*volWriter = NULL;

	try
	{
		pVolWriter = new CVolWriter();
		if (pVolWriter == NULL) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Failed to create CVolWriter object
		return E_FAIL;
	}

	// Obtain the ArchiveWriter interface
	HRESULT hr = pVolWriter->QueryInterface(IID_ArchiveWriter, (void**)volWriter);
	pVolWriter->Release();

	return hr;
}


HRESULT CResourceManager::LoadClmFile(BSTR fileName, int bAttachToStream, ArchiveReader **clmReader)
{
	StreamReader *inStream;
	SeekableStreamReader *inSeekStream;

	// Initialize returned ArchiveReader to NULL
	*clmReader = NULL;

	// Try to open the file as a stream
	OpenStreamRead(fileName, &inStream);
	// Check if a stream was constructed
	if (inStream == NULL)
	{
		// Failed to open the file as a stream
		PostErrorMsg(L"Error. Could not open stream.");
		return E_FAIL;
	}

	// Obtain the SeekableStreamReader interface
	inStream->QueryInterface(IID_SeekableStreamReader, (void**)&inSeekStream);
	inStream->Release();
	// Check if the interface was obtained
	if (inSeekStream == NULL)
	{
		// Failed to obtain a SeekableStreamReader interface
		PostErrorMsg(L"Error. Stream was not seekable.");
		return E_FAIL;
	}

	// Read in the vol data
	HRESULT hr = LoadClm(inSeekStream, bAttachToStream, clmReader);

	// Release the stream
	inSeekStream->Release();

	return hr;
}

HRESULT CResourceManager::LoadClm(SeekableStreamReader *inStream, int bAttachToStream, ArchiveReader **clmReader)
{
	CClmReader *pClmReader;

	// Initialize returned ArchiveReader to NULL
	*clmReader = NULL;

	// Try to create a CLM reader
	try
	{
		pClmReader = new CClmReader(inStream, bAttachToStream);
		if (pClmReader == NULL) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		return E_FAIL;
	}

	// Obtain the ArchiveReader interface
	HRESULT hr = pClmReader->QueryInterface(IID_ArchiveReader, (void**)clmReader);
	pClmReader->Release();

	return hr;
}

HRESULT CResourceManager::CreateClmFile(ArchiveWriter **clmWriter)
{
	CClmWriter *pClmWriter;

	// Initialize returned ArchiveWriter to NULL
	*clmWriter = NULL;

	try
	{
		pClmWriter = new CClmWriter();
		if (pClmWriter == NULL) return E_OUTOFMEMORY;
	}
	catch(...)
	{
		// Failed to create CVolWriter object
		return E_FAIL;
	}

	// Obtain the ArchiveWriter interface
	HRESULT hr = pClmWriter->QueryInterface(IID_ArchiveWriter, (void**)clmWriter);
	pClmWriter->Release();

	return hr;
}


HRESULT CResourceManager::AddArchiveToSearch(ArchiveReader *volReader)
{
	LinkedListNode *newNode;

	// Create a new linked list node
	newNode = new LinkedListNode;
	newNode->next = NULL;
	newNode->archive = volReader;
	// Increment the reference count
	volReader->AddRef();

	// Check if list is empty
	if (head == NULL)
		head = newNode;
	// Add archive to tail of linked list
	if (tail != NULL)
		tail->next = newNode;
	// Update tail of linked list
	tail = newNode;

	return S_OK;
}

HRESULT CResourceManager::ClearSearchPath()
{
	LinkedListNode *current, *next;

	// Clear linked list of archives in search path
	current = head;
	while (current)
	{
		current->archive->Release();	// Release the archive
		next = current->next;			// Get the next linked list node
		delete current;					// Release the current linked list node
		current = next;					// Process next node
	}

	head = NULL;
	tail = NULL;

	return S_OK;
}




// ISupportErrorInfo
// *****************

HRESULT CResourceManager::InterfaceSupportsErrorInfo(REFIID riid)
{
	if (riid == IID_IResourceManager)
		return S_OK;
	else
		return S_FALSE;
}
