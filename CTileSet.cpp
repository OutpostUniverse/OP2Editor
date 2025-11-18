#include "stdafx.h"
#include "CTileSet.h"
#include "GlobalFunctions.h"


extern int g_cLocks;


// IUnknown
// ********

ULONG __stdcall CTileSet::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CTileSet::Release()
{
	if (--m_cRef != 0)
		return m_cRef;
	delete this;
	return 0;
}

HRESULT __stdcall CTileSet::QueryInterface(REFIID riid, void** ppv)
{
	if(riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if(riid == IID_TileSet)
		*ppv = (TileSet*)this;
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();

	return S_OK;
}


// ITileSet
// ********


HRESULT CTileSet::get_NumTiles(int *numTiles)
{
	*numTiles = numberOfTiles;

	return S_OK;
}

HRESULT CTileSet::get_TileSize(int *tileSize)
{
	*tileSize = headInfo.width;

	return S_OK;
}

HRESULT CTileSet::get_BitDepth(int *bitDepth)
{
	*bitDepth = headInfo.bitDepth;

	return S_OK;
}

HRESULT CTileSet::get_NumPaletteEntries(int *numPaletteEntries)
{
	*numPaletteEntries = bmInfo->bmiHeader.biClrUsed;

	return S_OK;
}

HRESULT CTileSet::get_PaletteEntry(int index, int *palEntry)
{
	// Error check the array bounds
	if ((index < 0) || (index >= 256))
	{
		PostErrorMsg(L"Invalid index value");
		return E_INVALIDARG;
	}

	*palEntry = *(int*)(&bmInfo->bmiColors[index]);

	return S_OK;
}

HRESULT CTileSet::put_PaletteEntry(int index, int palEntry)
{
	// Error check the array bounds
	if ((index < 0) || (index >= 256))
	{
		PostErrorMsg(L"Invalid index value");
		return E_INVALIDARG;
	}

	bmInfo->bmiColors[index] = *((RGBQUAD*)(&palEntry));
	SetDIBColorTable(memDC, index, 1, (RGBQUAD*)&palEntry);

	return S_OK;
}



HRESULT CTileSet::SetNumTiles(int newNumTiles)
{
	HBITMAP newTileSet;
	unsigned char *newPixelData;
	int newSizeOfPixelData;

	// Calculate new DIB dimensions
	headInfo.height = headInfo.width * newNumTiles;
	bmInfo->bmiHeader.biHeight = -headInfo.width * newNumTiles;
	newSizeOfPixelData = scanlineByteWidth*headInfo.width*newNumTiles;
	if (sizeOfPixelData > newSizeOfPixelData) sizeOfPixelData = newSizeOfPixelData;
	// Create a new DIB section
	newTileSet = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&newPixelData, NULL, 0);
	tileSet = (HBITMAP)SelectObject(memDC, originalBm);	// Unselect the old DIB section
	// Copy tile set pixel data to the new DIB section
	GdiFlush();
	memcpy(newPixelData, pixelData, sizeOfPixelData);
	// Blank out new pixels
	memset(newPixelData + sizeOfPixelData, 0, newSizeOfPixelData - sizeOfPixelData);
	// Replace the old DIB section
	DeleteObject(tileSet);									// Release the old DIB section
	originalBm = (HBITMAP)SelectObject(memDC, newTileSet);	// Select the new DIB section into the DC
	// Update class variables
	numberOfTiles = newNumTiles;
	sizeOfPixelData = newSizeOfPixelData;
	pixelData = newPixelData;
	tileSet = newTileSet;

	// **TODO** Update zoomPixelData and array size

	return S_OK;
}


// Copies internal data to a client specified buffer
HRESULT CTileSet::GetPixelData(int pBuffer, int startOffset, int numBytes)
{
	// Error check the arguments
	if (startOffset < 0)
	{
		PostErrorMsg(L"Must have positive value for startOffset");
		return E_INVALIDARG;
	}
	// **TODO** Improve error checking

	if (startOffset+numBytes <= sizeOfPixelData)	// Bounds check the memory copy
		memcpy((void*)pBuffer, pixelData+startOffset, numBytes);	// Copy the pixel data

	return S_OK;
}

// Copies data to the internal buffer from a client specified buffer
HRESULT CTileSet::SetPixelData(int pBuffer, int startOffset, int numBytes)
{
	// Error check the arguments
	if (startOffset < 0)
	{
		PostErrorMsg(L"Must have positive value for startOffset");
		return E_INVALIDARG;
	}
	// **TODO** Improve error checking

	if (startOffset+numBytes <= sizeOfPixelData)	// Bounds check the memory copy
		memcpy(pixelData+startOffset, (void*)pBuffer, numBytes);	// Copy the pixel data

	// Recalculate minimap colors
	int bytesPerTile = scanlineByteWidth * headInfo.width;	// Note: Assume square tiles
	//CalcMiniMapColors(startOffset/bytesPerTile, (startOffset+numBytes-1)/bytesPerTile);

	return S_OK;
}


// **TODO** Remove
HRESULT CTileSet::get_MiniMapColors(int tileIndex, int *color)
{
	*color = *(int*)&miniMapColors[tileIndex];

	return S_OK;
}


// Pastes the specified tile to the destination Device Context at the given coordinates
HRESULT CTileSet::PasteTile(int destDC, int pixelX, int pixelY, int tileNum)
{
	// Paste the tile to the destDC at given coordinates. Note: Tile are assumed
	// to be square, and stored in the bitmap as a column of tiles.
	BitBlt((HDC)destDC, pixelX, pixelY, headInfo.width, headInfo.width, memDC, 0, tileNum*headInfo.width, SRCCOPY);

	//SetDIBitsToDevice((HDC)destDC, pixelX, pixelY, headInfo.width, headInfo.width, 0, 0, 0, 32, &pixelData[tileNum*scanlineByteWidth*headInfo.width], bmInfo, DIB_RGB_COLORS);

	return S_OK;
}


HRESULT CTileSet::SaveTileSet(StreamWriter *stream, enum TileSetSaveFormat saveFormat)
{
	switch(saveFormat)
	{
	case Default:
		SaveTileSet(stream);
		break;
	case Bitmap:
		SaveBitmapFile(stream);
		break;
	default:
		// Unsupported format
		return E_INVALIDARG;
		break;
	}

	return S_OK;
}



// Private functions
// *****************


// Constructors
// ************

CTileSet::CTileSet(int numTiles, int bitDepth, int width) : m_cRef(1)
{
	// Initialize variables
	memDC = NULL;
	scanlineByteWidth = ((width*bitDepth + 31) & ~31) >> 3;		// DWORD aligned scanline size
	sizeOfPixelData = scanlineByteWidth * width * numTiles;		// Note: tiles are square
	numberOfTiles = numTiles;
	headInfo.bitDepth = bitDepth;
	headInfo.width = width;
	headInfo.height = width*numTiles;
	headInfo.flags = 8;		// **TODO** Find out what these flags mean
	miniMapColors = NULL;	// **TODO** Remove
	numZoomLevels = 0;
	zoomPixelData = NULL;

	// Allocate space for the bitmap info
	bmInfo = (BITMAPINFO*)new char[sizeof(*bmInfo)+sizeof(RGBQUAD)*256];
	if (bmInfo == NULL)
		throw L"Out of memory";

	// Clear bitmap info header
	memset(bmInfo, 0, sizeof(bmInfo->bmiHeader)+sizeof(RGBQUAD)*256);
	// Initialize fields
	bmInfo->bmiHeader.biSize = sizeof(bmInfo->bmiHeader);
	bmInfo->bmiHeader.biBitCount = bitDepth;
	bmInfo->bmiHeader.biWidth = width;
	bmInfo->bmiHeader.biHeight = -headInfo.height;
	bmInfo->bmiHeader.biPlanes = 1;
	if (bitDepth <= 8) bmInfo->bmiHeader.biClrUsed = 1 << bitDepth;

	// Create the DIB section to hold the bitmap pixel data
	tileSet = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&pixelData, NULL, 0);
	if (tileSet == NULL)
	{
		// Release the bitmap info structure
		delete [] bmInfo;

		throw L"Could not create DIB section";
	}

	// Initialize the bitmap pixel data
	GdiFlush();
	memset(pixelData, 0, sizeOfPixelData);

	Refresh();		// Update memory Device Context and reselect the DIB section


	// Allocate space for zoomed pixel data // **TODO**


	g_cLocks++;
}

CTileSet::CTileSet(StreamReader *stream) : m_cRef(1)
{
	// Initialize variables
	pixelData = NULL;
	memDC = NULL;
	sizeOfPixelData = 0;
	scanlineByteWidth = 0;
	tileSet = NULL;
	miniMapColors = NULL;
	numZoomLevels = 0;
	zoomPixelData = NULL;

	// Allocate space for bitmap info
	bmInfo = (BITMAPINFO*) new char[sizeof(*bmInfo) + sizeof(RGBQUAD)*256];

	// Load tile set from stream
	if (LoadTileSet(stream) != 0)
	{
		// Error loading tile set from stream
		FreeMemory();

		throw L"CTileSet: Error loading tile set data.";		// Return error
	}

	Refresh();		// Update memory Device Context and reselect the DIB section

	g_cLocks++;
}

// Destructor
// **********

CTileSet::~CTileSet()
{
	g_cLocks--;

	FreeMemory();
}

// Cleanup Function
// ****************

void CTileSet::FreeMemory()
{
	if (bmInfo != NULL)
		delete [] (char*)bmInfo;
	if (miniMapColors != NULL)
		delete [] miniMapColors;
	if (zoomPixelData != NULL)
		delete [] zoomPixelData;

	// Free drawing resources
	if (memDC != 0)
	{
		// Restore the original bitmap that DC was created with
		tileSet = (HBITMAP)SelectObject(memDC, originalBm);
		DeleteObject(tileSet);		// Delete the cached compatible bitmap
		DeleteDC(memDC);			// Free the memory DC
	}
	else if(tileSet != 0)
		DeleteObject(tileSet);		// Only the tileSet object existed
}


// TileSet Loading/Saving functions
// ********************************

// Returns 0 on success, and nonzero on failure
int CTileSet::LoadTileSet(StreamReader *stream)
{
	int numSectionsLeft = -2;
	int numSectionsLeftInner = -2;
	int numBytesRead;
	int status;
	unsigned int i, temp;
	SectionHeader sectHead;

	// Initialize bitmap drawing structures
	memset(&bmInfo->bmiHeader, 0, sizeof(bmInfo->bmiHeader));
	bmInfo->bmiHeader.biSize = sizeof(bmInfo->bmiHeader);
	bmInfo->bmiHeader.biPlanes = 1;
	bmInfo->bmiHeader.biCompression = BI_RGB;

	try
	{
		do
		{
			numSectionsLeft--;

			// Read in a section tag
			stream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
			// Check for errors reading
			stream->get_Status(&status);
			if (status)
				throw L"Read Error. Could not read section header.";	// Failed. Error reading stream.

			// Check for bitmap file header
			if ((sectHead.tag & 0xFFFF) == 'MB')	// BM
				return LoadBitmapFile(stream);

			// Determine how to process the following section
			switch(sectHead.tag)
			{
			case 'PMBP':	// PBMP
				// No special processing. Ignore tag.
				break;
			case 'LAPP':	// PPAL
				// Second level processing
				do
				{
					numSectionsLeftInner--;
					// Read in a section tag
					stream->Read(sizeof(sectHead), (int)&sectHead, &numBytesRead);
					// Check for read errors
					stream->get_Status(&status);
					if (status)
						throw L"Read Error. Could not read section header. (PPAL inner processing)";	// Failed. Read error.

					// Determine how to process the following section
					switch(sectHead.tag)
					{
					case 'LAPP':	// PPAL
						// No special processing
						break;
					case 'FFIR':	// RIFF
						// **TODO** implement
						break;
					case 'daeh':	// head
						// Check for format errors
						if (sectHead.size != 4)
						{
							OutputDebugStringW(L"Format Error. Palette head section doesn't have size 4.");
							// Format error. Section header following PPAL tag doesn't have size 4.
							throw L"Format Error. Palette head section doesn't have size 4.";	// Failed. Format error.
						}

						// Read number of sections left
						stream->Read(4, (int)&numSectionsLeftInner, &numBytesRead);
						// Check for read errors
						stream->get_Status(&status);
						if (status)
							throw L"Read Error. Could not read number of sections left. (PPAL inner processing)";	// Failed. Read error.

						break;
					case 'atad':	// data
						// Check for format errors
						// Check if palette data section already read
						if (bmInfo->bmiHeader.biClrUsed != 0)
						{
							// **Warning** Format error. Only one data section for palette allowed
							OutputDebugStringW(L"Format Error. Second palette data section found.");
						}
						// Check if palette data is the wrong size
						if (sectHead.size > 4*256)
						{
							OutputDebugStringW(L"Format error. Palette data section is too large.");
							throw L"Format Error. Palette data section is too large. (More than 256 entries)";	// Failed. Format error. Palette data should contain no more than 256 entries.
						}

						// Determine number of palette entries used (round down to RGBQUAD size)
						bmInfo->bmiHeader.biClrUsed = sectHead.size >> 2;

						// Read in the palette data
						stream->Read(sectHead.size, (int)&bmInfo->bmiColors, &numBytesRead);
						// Check for read errors
						stream->get_Status(&status);
						if (status)
							throw L"Read Error. Could not read in palette data.";	// Failed. Read error.

						// Adjust palette color component positions (RGB <-> BGR)
						for (i = 0; i < bmInfo->bmiHeader.biClrUsed; i++)
						{
							// Swap the Red and Blue components
							temp = bmInfo->bmiColors[i].rgbRed;
							bmInfo->bmiColors[i].rgbRed = bmInfo->bmiColors[i].rgbBlue;
							bmInfo->bmiColors[i].rgbBlue = temp;
						}

						break;
					case 'lpsp':	// pspl
						// **TODO** implement
						break;
					case 'lptp':	// ptpl
						// **TODO** implement
						break;
					default:
						// Unknown tag. Ignore.
						break;
					}
				} while (numSectionsLeftInner);
				break;
			case 'atad':	// data
				// Check for format errors
				// Check for multiple pixel data sections
				if (sizeOfPixelData != 0)
					throw L"Format Error. More than one pixel data section found.";	// Failed. More than one pixel data section was found.
				// Check for a valid bitmap width
				if (scanlineByteWidth == 0)
					throw L"Format Error. No valid bitmap width was specified before pixel data was found.";	// Failed. Format error. No valid bitmap width was specified before the pixel data.
				// Check for non integral tile size multiples
				if (sectHead.size != headInfo.height*scanlineByteWidth)
					throw L"Format Error. Non integral tile size multiple.";	// Failed. Format error. Pixel data size is not an integral multiple of the dimensions.

				// Record size of pixel data
				sizeOfPixelData = sectHead.size;

				// Create the DIB section to hold the bitmap pixel data
				tileSet = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&pixelData, NULL, 0);
				// Check for errors
				if (tileSet == NULL)
					throw L"Error. Failed to create a DIB section to store bitmap.";

				// Read in the pixel data
				GdiFlush();
				stream->Read(sectHead.size, (int)pixelData, &numBytesRead);
				// Check for read errors
				stream->get_Status(&status);
				if (status)
					throw L"Read Error. Could not read pixel data.";	// Failed. Read error.
				break;
			case 'daeh':	// head
				// Check for format errors
				if (sectHead.size != sizeof(headInfo)+4)
				{
					OutputDebugStringW(L"Format Error. PBMP head section has an invalid size.");
					// Failed! Format error. Section header info wrong size, will overflow buffer if too big.
					// Danger to Outpost2.exe. Possible exploit.
					throw L"Format Error. PBMP head section size is invalid. **Possible Exploit**";	// Failed. Format error.
				}

				// Read the number of section remaining
				stream->Read(4, (int)&numSectionsLeft, &numBytesRead);
				// Check for read errors
				stream->get_Status(&status);
				if (status)
					throw L"Read Error. Could not read number of sections left.";	// Failed. Read error.

				// Read in the header data
				stream->Read(sectHead.size-4, (int)&headInfo, &numBytesRead);
				// Check for read errors
				stream->get_Status(&status);
				if (status)
					throw L"Read Error. Could not read pixel header data.";	// Failed. Read error.

				// Calculate the number of bytes in each scanline
				scanlineByteWidth = ((headInfo.width * headInfo.bitDepth + 31) & ~31) >> 3;
				// Update bitmap header info
				bmInfo->bmiHeader.biBitCount = headInfo.bitDepth;
				bmInfo->bmiHeader.biWidth = headInfo.width;
				bmInfo->bmiHeader.biHeight = -headInfo.height;

				break;
			default:
				// Unknown tag. Ignore.
				break;
			}
		} while (numSectionsLeft);	// Loop while sections are still expected

		if (scanlineByteWidth*headInfo.width == 0)
			throw L"Format Error. Invalid dimensions given.";

		// Calculate number of tiles in tile set. Note: assumes tiles are square
		numberOfTiles = sizeOfPixelData / (scanlineByteWidth*headInfo.width);

		// **TODO** Update this, remove old code, add zoomPixelData code
		// Allocate space for minimap colors
		miniMapColors = new RGBQUAD[numberOfTiles];
		// Calcaulate the minimap colors
		CalcMiniMapColors(0, numberOfTiles-1);
	}
	catch(WCHAR *errorMsg)
	{
		PostErrorMsg(errorMsg);
		return 1;	// Error
	}
	catch(...)
	{
		return 1;	// Error
	}

	return 0;		// Success
}

int CTileSet::SaveTileSet(StreamWriter *stream)
{
	SectionHeader sectHead;
	int numBytesWritten;
	int numSectionsLeft;
	unsigned int i;
	RGBQUAD tempPal[256];
	RGBQUAD *srcPal, *destPal;

	// Write the file header "PBMP" section
	sectHead.tag = 'PMBP';		// PBMP tag
	sectHead.size = sizeof(sectHead)*4 + sizeOfPixelData + sizeof(headInfo) + 8 +
					bmInfo->bmiHeader.biClrUsed*sizeof(RGBQUAD);
	numSectionsLeft = 2;	// Number of sections (palette, and pixel data)
	// Check if palette section is needed
	if (bmInfo->bmiHeader.biClrUsed == 0)
	{
		numSectionsLeft = 1;						// No palette section needed
		// No headers for palette section needed
		sectHead.size = sizeof(sectHead) + sizeOfPixelData + sizeof(headInfo) + 4;
	}
	stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
	// Write the "head" section of the "PBMP" section
	sectHead.tag = 'daeh';		// head tag
	sectHead.size = sizeof(headInfo) + 4;
	stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
	stream->Write(4, (int)&numSectionsLeft, &numBytesWritten);
	stream->Write(sizeof(headInfo), (int)&headInfo, &numBytesWritten);

	// Check if a palette needs to be written
	if (bmInfo->bmiHeader.biClrUsed != 0)
	{
		// Write the Palette section
		sectHead.tag = 'LAPP';		// PPAL tag
		sectHead.size = bmInfo->bmiHeader.biClrUsed*sizeof(RGBQUAD) +
						sizeof(sectHead)*2 + 8;
		stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
		// Write the "head" section of the "PPAL" section
		sectHead.tag = 'daeh';		// head tag
		sectHead.size = 4;
		numSectionsLeft = 1;
		stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
		stream->Write(4, (int)&numSectionsLeft, &numBytesWritten);
		// Write the "data" section of the "PPAL" section
		sectHead.tag = 'atad';		// data tag
		sectHead.size = bmInfo->bmiHeader.biClrUsed*sizeof(RGBQUAD);
		stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
		// Convert palette to format used for storage
		for (i = 0; i < bmInfo->bmiHeader.biClrUsed; i++)
		{
			srcPal = &bmInfo->bmiColors[i];
			destPal = &tempPal[i];
			destPal->rgbRed = srcPal->rgbBlue;
			destPal->rgbGreen = srcPal->rgbGreen;
			destPal->rgbBlue = srcPal->rgbRed;
			destPal->rgbReserved = srcPal->rgbReserved;
		}
		stream->Write(bmInfo->bmiHeader.biClrUsed*sizeof(RGBQUAD),
						(int)&tempPal, &numBytesWritten);
	}

	// Write the "data" section of the "PBMP" section
	sectHead.tag = 'atad';		// data tag
	sectHead.size = sizeOfPixelData;
	stream->Write(sizeof(sectHead), (int)&sectHead, &numBytesWritten);
	stream->Write(sizeOfPixelData, (int)pixelData, &numBytesWritten);

	return 0;		// Success
}


// Bitmap loading/saving functions
// *******************************

int CTileSet::LoadBitmapFile(StreamReader *stream)
{
	BITMAPFILEHEADER bmFileHeader;
	int numBytesRead;

	// Skip over rest of the BITMAPFILEHEADER
	// Note: First 8 bytes of file were already read
	stream->Read(sizeof(bmFileHeader)-8, (int)&bmFileHeader+8, &numBytesRead);
	// Read the BITMAPINFOHEADER
	stream->Read(sizeof(bmInfo->bmiHeader), (int)&bmInfo->bmiHeader, &numBytesRead);
	// Determine if a palette needs to be read in
	if (bmInfo->bmiHeader.biBitCount <= 8)
	{
		if (bmInfo->bmiHeader.biClrUsed == 0)
			bmInfo->bmiHeader.biClrUsed = 1 << bmInfo->bmiHeader.biBitCount;
		// Read in the palette data
		stream->Read(sizeof(RGBQUAD)*bmInfo->bmiHeader.biClrUsed, (int)&bmInfo->bmiColors[0], &numBytesRead);
	}

	// Update header info
	headInfo.bitDepth = bmInfo->bmiHeader.biBitCount;
	headInfo.width = bmInfo->bmiHeader.biWidth;
	headInfo.height = bmInfo->bmiHeader.biHeight;
	if (headInfo.height < 0)
		headInfo.height = -headInfo.height;
	// Calculate the number of bytes in each scanline
	scanlineByteWidth = ((headInfo.width * headInfo.bitDepth + 31) & ~31) >> 3;
	// Calculate total bitmap size
	sizeOfPixelData = scanlineByteWidth * headInfo.height;
	// Create the DIB section to hold the bitmap pixel data
	tileSet = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&pixelData, NULL, 0);
	// Read in the pixel data
	stream->Read(sizeOfPixelData, (int)pixelData, &numBytesRead);

	// Calculate number of tiles in tile set. Note: assumes tiles are square
	numberOfTiles = sizeOfPixelData / (scanlineByteWidth*headInfo.width);

	// Allocate space for minimap colors
	miniMapColors = new RGBQUAD[numberOfTiles];
	// Calcaulate the minimap colors
	CalcMiniMapColors(0, numberOfTiles-1);

	return 0;		// Success
}

int CTileSet::SaveBitmapFile(StreamWriter *stream)
{
	BITMAPFILEHEADER bmFileHeader;
	int numBytesWritten;

	// Preapre the bitmap file header
	bmFileHeader.bfType = 'MB';		// "BM"
	bmFileHeader.bfSize = sizeof(bmFileHeader) + sizeof(bmInfo->bmiHeader) +
					sizeof(RGBQUAD)*bmInfo->bmiHeader.biClrUsed + sizeOfPixelData;
	bmFileHeader.bfReserved1 = 0;
	bmFileHeader.bfReserved2 = 0;
	bmFileHeader.bfOffBits = bmFileHeader.bfSize - sizeOfPixelData;
	// Write out the bitmap file header
	stream->Write(sizeof(bmFileHeader), (int)&bmFileHeader, &numBytesWritten);
	// Write out the BITMAPINFOHEADER
	stream->Write(sizeof(bmInfo->bmiHeader), (int)&bmInfo->bmiHeader, &numBytesWritten);
	// Write out the palette, if it exists
	if (bmInfo->bmiHeader.biBitCount <= 8)
	{
		// Write out the palette data
		stream->Write(sizeof(RGBQUAD)*bmInfo->bmiHeader.biClrUsed, (int)&bmInfo->bmiColors[0], &numBytesWritten);
	}
	// Write out the pixel data
	stream->Write(sizeOfPixelData, (int)pixelData, &numBytesWritten);

	return 0;		// Success
}

// **TODO** Remove
void CTileSet::CalcMiniMapColors(int startTile, int endTile)
{
	int tileByteSize = scanlineByteWidth*headInfo.width;	// Note: assume square tiles
	int tilePixelSize = headInfo.width*headInfo.width;
	int pixelDataOffset;
	RGBQUAD *rgbQuad;
	int red, green, blue;
	int tileNum, x, y;
	int temp;

	// Calculate minimap color of all tiles in given range
	for (tileNum = startTile; tileNum <= endTile; tileNum++)
	{
		// Initialize color components
		red = green = blue = 0;

		// Calculate the minimap color of this tile (sum over all pixels in tile)
		for (y = 0; y < headInfo.width; y++)	// Note: assume square tiles
		{
			for (x = 0; x < headInfo.width; x++)
			{
				// Add the color components of this pixel
				pixelDataOffset = tileNum*tileByteSize +
									y*scanlineByteWidth +
									((x*headInfo.bitDepth) >> 3);
				switch(headInfo.bitDepth)
				{
				case 8:
					temp = pixelData[pixelDataOffset];
					rgbQuad = &bmInfo->bmiColors[temp];

					// FIX: flip R and B colors around (they are stored backwards!)
					//red += rgbQuad->rgbRed;
					red += rgbQuad->rgbBlue;
					green += rgbQuad->rgbGreen;
					//blue += rgbQuad->rgbBlue;
					blue += rgbQuad->rgbRed;
					break;
				case 16: // Assume 5/5/5 for RGB components **TODO** test this code
					temp = *(short*)(pixelData+pixelDataOffset);
					blue += (temp & 0x1F) << 3;
					green += (temp & 0x3E0) >> 2;
					red += (temp & 0x7C00) >> 7;
					break;
				default:
					// Do nothing. Pixels will appear black
					break;
				}
			}
		}

		// Scale color components by the number of pixels in the tile
		red /= tilePixelSize;
		green /= tilePixelSize;
		blue /= tilePixelSize;
		// Store the tile minimap color
		rgbQuad = &miniMapColors[tileNum];
		rgbQuad->rgbRed = red;
		rgbQuad->rgbGreen = green;
		rgbQuad->rgbBlue = blue;
		rgbQuad->rgbReserved = 0;
	}
}


// Update the drawing cache. This will refresh the memory DC to match the screen (in case
// a mode change has occured) and reselect the bitmap for drawing.
void CTileSet::Refresh()
{
	// Check if a memory Device Context already exists
	if (memDC)
	{
		// Delete the old Device Context
		tileSet = (HBITMAP)SelectObject(memDC, originalBm);
		DeleteDC(memDC);
	}

	// Create a new memory Device Context and select the bitmap
	memDC = CreateCompatibleDC(NULL);	// NULL - makes DC compatible with current screen
	originalBm = (HBITMAP)SelectObject(memDC, tileSet);
}


int CTileSet::InitializeZoomBuffers()
{
	int i;
	int size;

	// Calculate size of largest zoom buffer
	numZoomLevels = LogBase2(headInfo.width);
	size = (1 << (numZoomLevels << 1)) * 3;

	// Allocate zoom buffer array
	zoomPixelData = new char*[numZoomLevels];
	if (zoomPixelData == NULL) return -1;	// Error (Out of memory)
	for (i = 0; i < numZoomLevels; i++)
	{
		// Allocate buffer space
		zoomPixelData[i] = new char[size];
		// Check for errors
		if (zoomPixelData[i] == NULL)
		{
			// Failed to allocate memory. Release what we've already obtained and abort
			for (i--; i >= 0; i--)
			{
				// Release the already obtained buffer
				delete [] zoomPixelData[i];
			}

			// Release the array of buffer pointers
			delete [] zoomPixelData;

			zoomPixelData = NULL;
			return -1;	// Error (Out of memory)
		}

		// Adjust size to allocate for next iteration
		size >>= 2;
	}

	// Initialize all the buffers
	CalcZoomPixelData(0, numberOfTiles);

	return 0; // Success
}

void CTileSet::CalcZoomPixelData(int startTile, int numTiles)
{
	int i;
	int startPixel;
	int numPixels;

	// Find the starting pixel to calculate zoom colors for
	startPixel = startTile * headInfo.width * headInfo.width;
	// Calculate the number of pixels we need to process at largest level
	numPixels = numTiles * headInfo.width * headInfo.width;

	// Copy data for the upper level
	switch(headInfo.bitDepth)
	{
	case 8:		// 8 bpp
		for (i = startPixel; i < numPixels; i++)
		{
			// Lookup the palette index of the pixel
		}

		break;
	default:	// **TODO** Handle more cases
		// Unhandled case. Abort.
		return;
	}

	// Recurse for lower levels
}
