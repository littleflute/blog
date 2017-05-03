[V0.0.7](https://github.com/littleflute/blog/edit/master/docs/2017/04/30/index.md)

[show me](https://littleflute.github.io/blog/docs/2017/04/30/)
<script src="../../../../js/xdhead.js"></script>

~~~ C++
//File: XdBmp.h
/*
2017.05.04 2:10 AM bjt
littleflute
*/
class CXdBmp
{
#pragma warning (disable : 4183)
public:
	CXdBmp::CXdBmp():m_hMyB(NULL){
		strcpy(m_szV,"V0.0.2");
	}
	CXdBmp::~CXdBmp(){}
	
	void drawByByteData(HDC hDC,BYTE* pByte,int n, LPRECT pRect)
	{   
		HBITMAP	&h = m_hMyB;
		if(NULL==h)
		{
			h = ptCreateDIBSection(n,n,24,0); 
		}
		::memcpy(m_pBmpBits,pByte,n*n*3);
		if(h)
			BOOL b = ptDrawDIBSectionOnDC(hDC,h,pRect);
	}
	HBITMAP CXdBmp::getScreenToBmp(LPRECT lpRect,BOOL bSave)
	{
		HDC       hScrDC, hMemDC;      
		HBITMAP    hBitmap, hOldBitmap;   
		int       nX, nY, nX2, nY2;      
		int       nWidth, nHeight;
		
		if (IsRectEmpty(lpRect))
			return NULL;
		hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
		
		hMemDC = CreateCompatibleDC(hScrDC);
		nX = lpRect->left;
		nY = lpRect->top;
		nX2 = lpRect->right;
		nY2 = lpRect->bottom;
		//获取屏幕分辩率
		int xScreen = ::GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		if (nX < 0)
			nX = 0;
		if (nY < 0)
			nY = 0;
		if (nX2 > xScreen)
			nX2 = xScreen;
		if (nY2 > yScreen)
			nY2 = yScreen;
		nWidth = nX2 - nX;
		nHeight = nY2 - nY;
		hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY);
		
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		
		if(bSave)
		{				 
			save(hMemDC,hBitmap,"d:\\xd\\xd1.bmp");
		} 
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		return hBitmap;
	}
	HBITMAP CXdBmp::draw2File(LPRECT lpRect,BOOL bSave)
	{
		HDC       hScrDC, hMemDC;      
		HBITMAP    hBitmap, hOldBitmap;   
		int       nX, nY, nX2, nY2;      
		int       nWidth, nHeight;
		
		if (IsRectEmpty(lpRect))
			return NULL;
		hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
		
		hMemDC = CreateCompatibleDC(hScrDC);
		nX = lpRect->left;
		nY = lpRect->top;
		nX2 = lpRect->right;
		nY2 = lpRect->bottom;
		//获取屏幕分辩率
		int xScreen = ::GetSystemMetrics(SM_CXSCREEN);
		int yScreen = GetSystemMetrics(SM_CYSCREEN);
		if (nX < 0)
			nX = 0;
		if (nY < 0)
			nY = 0;
		if (nX2 > xScreen)
			nX2 = xScreen;
		if (nY2 > yScreen)
			nY2 = yScreen;
		nWidth = nX2 - nX;
		nHeight = nY2 - nY;
		hBitmap = CreateCompatibleBitmap(hScrDC, nWidth, nHeight);
		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
		
		::Rectangle(hMemDC,10,10,300,300);
		::TextOut(hMemDC,100,100,"xd drawing test",16);
		::TextOut(hMemDC,100,200,m_szV,strlen(m_szV));
		
		hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
		
		
		if(bSave)
		{				 
			save(hMemDC,hBitmap,"d:\\xd\\3.bmp");
		} 
		DeleteDC(hScrDC);
		DeleteDC(hMemDC);
		return hBitmap;
	}
	private:
		int CXdBmp::save(HDC hDC,HBITMAP hBmp,char* filePath)
		{
			HBITMAP				hBitmap = hBmp;
			
			int					iBits;
			WORD				wBitCount;
			DWORD				dwPaletteSize=0, dwBmBitsSize=0, dwDIBSize=0, dwWritten=0;
			BITMAP				Bitmap; 
			BITMAPFILEHEADER	bmfHdr; 
			BITMAPINFOHEADER	bi; 
			LPBITMAPINFOHEADER	lpbi; 
			HANDLE				fh, hDib, hPal,hOldPal=NULL;
			
			iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
			
			if (iBits <= 1)  wBitCount = 1;
			else if (iBits <= 4)  wBitCount = 4;
			else if (iBits <= 8)  wBitCount = 8;
			else      wBitCount = 24;
			
			GetObject(hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap);
			bi.biSize   = sizeof(BITMAPINFOHEADER);
			bi.biWidth   = Bitmap.bmWidth;
			bi.biHeight   = Bitmap.bmHeight;
			bi.biPlanes   = 1;
			bi.biBitCount  = wBitCount;
			bi.biCompression = BI_RGB;
			bi.biSizeImage  = 0;
			bi.biXPelsPerMeter = 0;
			bi.biYPelsPerMeter = 0;
			bi.biClrImportant = 0;
			bi.biClrUsed  = 0;
			
			dwBmBitsSize = ((Bitmap.bmWidth * wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;
			
			hDib = GlobalAlloc(GHND,dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
			lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
			*lpbi = bi;
			
			hPal = GetStockObject(DEFAULT_PALETTE);
			if (hPal)
			{
				hDC = ::GetDC(NULL);
				hOldPal = ::SelectPalette(hDC, (HPALETTE)hPal, FALSE);
				RealizePalette(hDC);
			}
			
			GetDIBits(hDC, hBitmap, 0, (UINT) Bitmap.bmHeight,
				(LPSTR)lpbi + sizeof(BITMAPINFOHEADER) + dwPaletteSize, 
				(BITMAPINFO *)lpbi, DIB_RGB_COLORS);
			
			if (hOldPal)
			{
				::SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
				RealizePalette(hDC);
				::ReleaseDC(NULL, hDC);
			}
			
			fh = CreateFile(filePath, GENERIC_WRITE,0, NULL, CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
			
			if (fh == INVALID_HANDLE_VALUE)  
				return 	0;
			
			bmfHdr.bfType = 0x4D42; // "BM"
			dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize; 
			bmfHdr.bfSize = dwDIBSize;
			bmfHdr.bfReserved1 = 0;
			bmfHdr.bfReserved2 = 0;
			bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;
			
			WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
			WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
			
			GlobalUnlock(hDib);
			GlobalFree(hDib);
			CloseHandle(fh); 
			return 1;
		}
		
		BOOL ptDrawDIBSectionOnDC( HDC hDC, HBITMAP hBitmap, LPRECT pxdRect )
		{
			DIBSECTION  ds;
			HPALETTE    hPal, hOldPal;
			BOOL        bRes;
			
			GetObject( hBitmap, sizeof(DIBSECTION), &ds );
			if( GetDeviceCaps( hDC, RASTERCAPS ) & RC_PALETTE )
			{   // if it's a palette device, select and realize a palette
				// as a background palette (won't cause a problem is the
				// palette was not selected in the foreground in the main app
				hPal = ptCreatePaletteForDIBSection( hBitmap );
				hOldPal = SelectPalette( hDC, hPal, TRUE );
				RealizePalette( hDC );
			}
			if( GetDeviceCaps( hDC, TECHNOLOGY ) == DT_RASDISPLAY )
			{ // going to the screen, use StretchBlt()
				HDC hMemDC;
				HBITMAP hOldBitmap;
				
				hMemDC = CreateCompatibleDC( hDC  );
				hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );
				bRes = StretchBlt( hDC, pxdRect->left, pxdRect->top, 
					pxdRect->right-pxdRect->left, pxdRect->bottom-pxdRect->top, 
					hMemDC, 0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, SRCCOPY );
				SelectObject( hMemDC, hOldBitmap );
				DeleteDC( hMemDC );
			}
			else
			{ // going to the printer, use StretchDIBits()
				LPBITMAPINFO    pbmi;
				
				// if the printer is palettized, 
				pbmi = ptGetBITMAPINFOForDIBSection( hBitmap );
				bRes = (GDI_ERROR != StretchDIBits( hDC, pxdRect->left, pxdRect->top, 
					pxdRect->right-pxdRect->left, pxdRect->bottom-pxdRect->top,
					0, 0, ds.dsBm.bmWidth, ds.dsBm.bmHeight, ds.dsBm.bmBits, 
					pbmi, DIB_RGB_COLORS, SRCCOPY ));
				free( pbmi );
			}
			if( GetDeviceCaps( hDC, RASTERCAPS ) & RC_PALETTE )
			{
				SelectPalette( hDC, hOldPal, TRUE );
				DeleteObject( hPal );
			}
			return bRes;
		}
		
		HPALETTE ptCreatePaletteForDIBSection( HBITMAP hBitmap )
		{
			BITMAP      bm;
			HPALETTE    hPalette;
			
			// Get the color depth of the DIBSection
			GetObject( hBitmap, sizeof(BITMAP), &bm );
			// If the DIBSection is 256 color or less, it has a color table
			if( ( bm.bmBitsPixel * bm.bmPlanes ) <= 8 )
			{
				HDC             hMemDC;
				HBITMAP         hOldBitmap;
				RGBQUAD         rgb[256];
				LPLOGPALETTE    pLogPal;
				WORD            i;
				int             nColors;
				
				// Find out how many colors are in the color table
				nColors = 1 << ( bm.bmBitsPixel * bm.bmPlanes );
				// Create a memory DC and select the DIBSection into it
				hMemDC = CreateCompatibleDC( NULL );
				hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );
				// Get the DIBSection's color table
				GetDIBColorTable( hMemDC, 0, nColors, rgb );
				// Create a palette from the color table
				pLogPal = (LOGPALETTE*)malloc( sizeof(LOGPALETTE) + (nColors*sizeof(PALETTEENTRY)) );
				pLogPal->palVersion = 0x300;
				pLogPal->palNumEntries = nColors;
				for(i=0;i<nColors;i++)
				{
					pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
					pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
					pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
					pLogPal->palPalEntry[i].peFlags = 0;
				}
				hPalette = CreatePalette( pLogPal );
				// Clean up
				free( pLogPal );
				SelectObject( hMemDC, hOldBitmap );
				DeleteDC( hMemDC );
			}
			else   // It has no color table, so make one up
			{
				hPalette = ptCreateSpectrumPalette();
			}
			return hPalette;
		}
		HPALETTE ptCreateSpectrumPalette( void ) 
		{                 
			HPALETTE hPal;
			LPLOGPALETTE lplgPal;
			BYTE red, green, blue;
			int i; 
			
			lplgPal = (LPLOGPALETTE)GlobalAlloc( GPTR, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256 ); 
			if (!lplgPal)
				return NULL;
			
			lplgPal->palVersion = 0x300;
			lplgPal->palNumEntries = 256;
			
			red = green = blue = 0;
			for (i = 0; i < 256; i++) {
				lplgPal->palPalEntry[i].peRed   = red;
				lplgPal->palPalEntry[i].peGreen = green;
				lplgPal->palPalEntry[i].peBlue  = blue;
				lplgPal->palPalEntry[i].peFlags = (BYTE)0;
				
				if (!(red += 32))
					if (!(green += 32))
						blue += 64;
			}
			hPal = CreatePalette(lplgPal);
			GlobalFree(lplgPal);
			return hPal;
		}
		
		LPBITMAPINFO ptGetBITMAPINFOForDIBSection( HBITMAP hBitmap )
		{
			LPBITMAPINFO    pbmi;
			DIBSECTION      ds;
			LPRGBQUAD       prgb;
			
			GetObject( hBitmap, sizeof(DIBSECTION), &ds );
			// load the header and the bitmasks if present
			// per function comments above, we allocate space for a color 
			// table even if it is not needed 
			if( ds.dsBmih.biCompression == BI_BITFIELDS )
			{   // has a bitmask - be sure to allocate for and copy them
				pbmi = (BITMAPINFO*)malloc( sizeof(BITMAPINFOHEADER) + (3*sizeof(DWORD)) + (256*sizeof(RGBQUAD)) );
				CopyMemory( &(pbmi->bmiHeader), &(ds.dsBmih), sizeof(BITMAPINFOHEADER) + (3*sizeof(DWORD)) );
				prgb = (LPRGBQUAD)&(pbmi->bmiColors[3]);
			}
			else
			{   // no bitmask - just the header and color table
				pbmi = (BITMAPINFO*)malloc( sizeof(BITMAPINFOHEADER) + (256*sizeof(RGBQUAD)) );
				CopyMemory( &(pbmi->bmiHeader), &(ds.dsBmih), sizeof(BITMAPINFOHEADER) );
				prgb = pbmi->bmiColors;
			}
			// at this point, prgb points to the color table, even 
			// if bitmasks are present
			
			// Now for the color table
			if( ( ds.dsBm.bmBitsPixel * ds.dsBm.bmPlanes ) <= 8 )
			{   // the DIBSection is 256 color or less (has color table)
				HDC             hMemDC;
				HBITMAP         hOldBitmap;
				hMemDC = CreateCompatibleDC( NULL );
				hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );
				GetDIBColorTable( hMemDC, 0, 1<<(ds.dsBm.bmBitsPixel*ds.dsBm.bmPlanes), prgb );
				SelectObject( hMemDC, hOldBitmap );
				DeleteDC( hMemDC );
			}
			else
			{   // the DIBSection is >8bpp (has no color table) so make one up
				HPALETTE        hPal;
				PALETTEENTRY    pe[256];
				int             i;
				
				// where are we going to get the colors? from a spectrum palette
				hPal = ptCreateSpectrumPalette();
				GetPaletteEntries( hPal, 0, 256, pe );
				for(i=0;i<256;i++)
				{
					prgb[i].rgbRed = pe[i].peRed;
					prgb[i].rgbGreen = pe[i].peGreen;
					prgb[i].rgbBlue = pe[i].peBlue;
					prgb[i].rgbReserved = 0;
				}
				DeleteObject( hPal );
				pbmi->bmiHeader.biClrUsed = 256;
			}
			return pbmi;
		} 
		
		
		HBITMAP ptCreateDIBSection( DWORD dwX, DWORD dwY, WORD wBits, BOOL Monochrome )
		{
			HBITMAP         hBitmap;
			int             nInfoSize;
			LPBITMAPINFO    pbmi;
			HDC             hRefDC;
			
			nInfoSize = sizeof( BITMAPINFOHEADER );
			if( wBits <= 8 )
				nInfoSize += sizeof(RGBQUAD) * (1 << wBits);
			if( ( wBits == 16 ) || ( wBits == 32 ) )
				nInfoSize += 3 * sizeof(DWORD);
			
			// Create the header big enough to contain color table and bitmasks if needed
			pbmi = (LPBITMAPINFO)malloc( nInfoSize );
			ZeroMemory( pbmi, nInfoSize );
			pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			pbmi->bmiHeader.biWidth = dwX;
			pbmi->bmiHeader.biHeight = dwY;
			pbmi->bmiHeader.biPlanes = 1; 
			pbmi->bmiHeader.biBitCount = wBits;
			pbmi->bmiHeader.biCompression = BI_RGB; // override below for 16 and 32bpp
			
			switch( wBits )
			{
			case 24:
				// 24bpp requires no special handling
				break;
			case 16:
				{   // if it's 16bpp, fill in the masks and override the compression
					// these are the default masks - you could change them if needed
					LPDWORD pMasks = (LPDWORD)(pbmi->bmiColors);
					pMasks[0] = 0x00007c00;
					pMasks[1] = 0x000003e0;
					pMasks[2] = 0x0000001f;
					pbmi->bmiHeader.biCompression = BI_BITFIELDS;
				}
				break;
			case 32:
				{   // if it's 32bpp, fill in the masks and override the compression
					// these are the default masks - you could change them if needed
					LPDWORD pMasks = (LPDWORD)(pbmi->bmiColors);
					pMasks[0] = 0x00ff0000;
					pMasks[1] = 0x0000ff00;
					pMasks[2] = 0x000000ff;
					pbmi->bmiHeader.biCompression = BI_BITFIELDS; 
				}
				break;
			case 8:  
				{
					if(Monochrome)
					{
						int             i;
						for(i=0;i<256;i++)
						{
							pbmi->bmiColors[i].rgbRed = i;
							pbmi->bmiColors[i].rgbGreen = i;
							pbmi->bmiColors[i].rgbBlue = i;
							pbmi->bmiColors[i].rgbReserved = 0;
						}
						pbmi->bmiHeader.biClrUsed = 256;
					}
					else
					{
						HPALETTE        hPal;
						PALETTEENTRY    pe[256];
						int             i;
						// at this point, prgb points to the color table, even 
						// if bitmasks are present
						hPal = ptCreateSpectrumPalette();
						GetPaletteEntries( hPal, 0, 256, pe );
						for(i=0;i<256;i++)
						{
							pbmi->bmiColors[i].rgbRed = pe[i].peRed;
							pbmi->bmiColors[i].rgbGreen = pe[i].peGreen;
							pbmi->bmiColors[i].rgbBlue = pe[i].peBlue;
							pbmi->bmiColors[i].rgbReserved = 0;
						}
						DeleteObject( hPal );
						pbmi->bmiHeader.biClrUsed = 256;
					}
				}
				break;
			case 4:
				{   // Use a default 16 color table for 4bpp DIBSections
					RGBTRIPLE       rgb[16] = { { 0x00, 0x00, 0x00 }, // black 
					{ 0x80, 0x00, 0x00 }, // dark red 
					{ 0x00, 0x80, 0x00 }, // dark green 
					{ 0x80, 0x80, 0x00 }, // dark yellow 
					{ 0x00, 0x00, 0x80 }, // dark blue 
					{ 0x80, 0x00, 0x80 }, // dark magenta 
					{ 0x00, 0x80, 0x80 }, // dark cyan 
					{ 0xC0, 0xC0, 0xC0 }, // light gray 
					//  { 0xC0, 0xDC, 0xC0 }, // money green 
					//  { 0xA6, 0xCA, 0xF0 }, // sky blue 
					//  { 0xFF, 0xFB, 0xF0 }, // cream 
					//  { 0xA0, 0xA0, 0xA4 }, // light gray 
					{ 0x80, 0x80, 0x80 }, // medium gray 
					{ 0xFF, 0x00, 0x00 }, // red 
					{ 0x00, 0xFF, 0x00 }, // green 
					{ 0xFF, 0xFF, 0x00 }, // yellow 
					{ 0x00, 0x00, 0xFF }, // blue 
					{ 0xFF, 0x00, 0xFF }, // magenta 
					{ 0x00, 0xFF, 0xFF }, // cyan 
					{ 0xFF, 0xFF, 0xFF } }; // white 
					int i;
					
					for(i=0;i<16;i++)
					{
						pbmi->bmiColors[i].rgbRed = rgb[i].rgbtRed;
						pbmi->bmiColors[i].rgbGreen = rgb[i].rgbtGreen;
						pbmi->bmiColors[i].rgbBlue = rgb[i].rgbtBlue;
						pbmi->bmiColors[i].rgbReserved = 0;
					}
					pbmi->bmiHeader.biClrUsed = 16;
				}
				break;
			case 1: // BW
				pbmi->bmiColors[0].rgbRed = pbmi->bmiColors[0].rgbGreen = pbmi->bmiColors[0].rgbBlue = 0;
				pbmi->bmiColors[1].rgbRed = pbmi->bmiColors[1].rgbGreen = pbmi->bmiColors[1].rgbBlue = 255;
				pbmi->bmiColors[0].rgbReserved = pbmi->bmiColors[1].rgbReserved = 0;
				break;
			}
			hRefDC = ::GetDC( NULL );
			hBitmap = CreateDIBSection( hRefDC, pbmi, DIB_RGB_COLORS, (void**)&m_pBmpBits, NULL, 0 );
			nInfoSize = GetLastError();
			::ReleaseDC( NULL, hRefDC );
			free( pbmi );
			if( hBitmap == NULL )
			{
				TCHAR   szTemp[64];
				wsprintf( szTemp, "Error %d", nInfoSize );
				::MessageBox( NULL, szTemp, "Error", MB_OK );
			}
			return hBitmap;
		}
		
		
		char			m_szV[16];
		HBITMAP			m_hMyB;
		LPBYTE          m_pBmpBits;
	};
~~~




