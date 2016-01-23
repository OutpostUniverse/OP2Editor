

#include "OP2Editor.h"
#include "CTileSetManager.h"


class CTileGroup : public TileGroup
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

			
	// ISupportErrorInfo
	// *****************
	HRESULT STDMETHODCALLTYPE InterfaceSupportsErrorInfo(REFIID riid);


	// Class specific
	// **************
	CTileGroup(int tileWidth, int tileHeight, CTileSetManager *tileSetManager);
	CTileGroup(int tileWidth, int tileHeight, TileSetSource *tileSetSource);
	~CTileGroup();

private:
	ULONG m_cRef;

	// Private variables
	// *****************
	int tileWidth;						// Width of this tile group
	int tileHeight;						// Height of this tile group
	int *tileData;						// Array of mapping indexes
	CTileSetManager *tileSetManager;	// TileSetManager for this tile group
};
