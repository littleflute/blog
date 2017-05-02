~~~ C++
class CXdBmp{
	#pragma warning (disable : 4183)
	public:
		CXdBmp::CXdBmp(){
			strcpy(m_szV,"V0.0.1");
		}
		CXdBmp::~CXdBmp(){}
		HBITMAP CXdBmp::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)
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
		char m_szV[16];
	};
~~~
