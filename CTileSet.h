
#include "OP2Editor.h"


class CTileSet : public TileSet
{
public:
    // IUnknown
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);

	// ITileSet

    // [propget]
	HRESULT STDMETHODCALLTYPE get_NumTiles( 
            /* [retval][out] */ int __RPC_FAR *numTiles);
    // [propget]
	HRESULT STDMETHODCALLTYPE get_TileSize( 
            /* [retval][out] */ int __RPC_FAR *tileSize);
    // [propget]
	HRESULT STDMETHODCALLTYPE get_BitDepth( 
            /* [retval][out] */ int __RPC_FAR *bitDepth);
    // [propget]
	HRESULT STDMETHODCALLTYPE get_NumPaletteEntries( 
            /* [retval][out] */ int __RPC_FAR *numPaletteEntries);        
    // [propget]
	HRESULT STDMETHODCALLTYPE get_PaletteEntry( 
            /* [in] */ int index,
            /* [retval][out] */ int __RPC_FAR *palEntry); 
    // [propput]
	HRESULT STDMETHODCALLTYPE put_PaletteEntry( 
            /* [in] */ int index,
            /* [in] */ int palEntry);

	HRESULT STDMETHODCALLTYPE SetNumTiles( 
            /* [in] */ int numTiles);
    
	// Returns pixel data in native format (as stored in file)
    // [local]
	HRESULT STDMETHODCALLTYPE GetPixelData( 
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes);
	// Sets pixel data in native format (as stored in file)
    // [local]
	HRESULT STDMETHODCALLTYPE SetPixelData( 
            /* [in] */ int pBuffer,
            /* [in] */ int startOffset,
            /* [in] */ int numBytes);
    

    // [propget]	// **TODO** Remove
	HRESULT STDMETHODCALLTYPE get_MiniMapColors( 
            /* [in] */ int tileIndex,
            /* [retval][out] */ int __RPC_FAR *color);

	HRESULT STDMETHODCALLTYPE PasteTile( 
            /* [in] */ int destDC,
            /* [in] */ int pixelX,
            /* [in] */ int pixelY,
            /* [in] */ int tileNum);
        
    HRESULT STDMETHODCALLTYPE SaveTileSet( 
            /* [in] */ StreamWriter __RPC_FAR *stream,
            /* [in] */ enum TileSetSaveFormat saveFormat);


	// Class specific
	CTileSet(int numTiles = 1, int bitDepth = 8, int width = 32);	// Create a new empty tile set
	CTileSet(StreamReader *stream);		// Create a new tile set loaded from a stream
	~CTileSet();						// Release tile set resources

private:
	ULONG m_cRef;	// COM object reference count

	// Class specific structures
	// *************************
	#pragma pack(push, 1)	// Make sure structures are byte aligned
	// File section header tag
	struct SectionHeader
	{
		int tag;		// Section name: char tag[4];
		int size;		// Number of bytes in this section
	};
	// Header info loaded from tile set file
	struct HeaderInfo
	{
		int width;		// The width of the bitmap in pixels (Note: tiles are square)
		int height;		// Height of all tiles (stacked on top of each other)
		int bitDepth;	// Bit depth of the pixel data
		int flags;		// Tile set file flags
	};
	#pragma pack(pop)

	// Class specific functions
	// ************************
	int LoadTileSet(StreamReader *stream);
	int LoadBitmapFile(StreamReader *stream);
	int SaveBitmapFile(StreamWriter *stream);
	int SaveTileSet(StreamWriter *stream);
	void CalcMiniMapColors(int startTile, int endTile);	// **TODO** Remove
	int InitializeZoomBuffers();
	void CalcZoomPixelData(int startTile, int numTiles);
	void Refresh();
	void FreeMemory();

	// Class specific data
	// *******************
	HeaderInfo headInfo;

	int numberOfTiles;
	int sizeOfPixelData;
	int scanlineByteWidth;
	unsigned char *pixelData;
	RGBQUAD *miniMapColors;		// **TODO** phase this out
	BITMAPINFO zoomInfo;		// Info describing the zoomed pixel data format
	int numZoomLevels;
	char **zoomPixelData;

	BITMAPINFO *bmInfo;
	HDC	memDC;
	HBITMAP tileSet;
	HBITMAP originalBm;
};
