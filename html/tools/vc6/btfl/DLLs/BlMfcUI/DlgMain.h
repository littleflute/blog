#if !defined(AFX_DLGMAIN_H__5881E530_36C1_47EC_B8AB_9F69118689E7__INCLUDED_)
#define AFX_DLGMAIN_H__5881E530_36C1_47EC_B8AB_9F69118689E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMain.h : header file
//
#include "Mmsystem.h"
#pragma comment(lib,"Winmm.lib")
/////////////////////////////////////////////////////////////////////////////
// CDlgMain dialog

#define		MY_VERSION		"BlMfcUI_V(0326)"
  
class CDlgMain : public CDialog    
{ 
	class CMyDll  
	{
	public:
		CMyDll(){
			m_hModule = LoadLibrary("B1Mng.dll");
		}
		~CMyDll(){
			if(m_hModule)
			{
				FreeLibrary (m_hModule);
				m_hModule = NULL;
			}
		} 
		BLSTATUS OnBlCallLibFun(HWND h,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = prCallLibFun(h,m,w,l);
			return r;
		}
	private: 
		HMODULE		m_hModule;

		
		
		BLSTATUS pvCallLibFun(HWND h,char *szFun,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE; 
			
			if(NULL != m_hModule)
			{
				FARPROC pFunc = GetProcAddress(m_hModule, szFun);
				if (pFunc ) {
					r = (* (OnBLAPI *)pFunc)(h,m,w,l);   
				}
			}
			else
			{
				r = BL_STATUS_NOT_FOUND_LIBARY;
			}
			return r;
		}
		BLSTATUS prCallLibFun(HWND h,UINT m,WPARAM w,LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE; 
			r = pvCallLibFun(h,"OnBlApi",m,w,l);
			return r;
		} 
	};
#define POS 5
#define TOP 30
	class CBtflStatusBarCtrl: public CStatusBarCtrl
	{
	public:
		CTime	m_startTime;
		CString m_strFPS;
		DWORD m_dwCount, m_dwTStart, m_dwTEnd;
		
		CBtflStatusBarCtrl(){
			m_dwCount = m_dwTStart = m_dwTEnd = 0;
		}
		~CBtflStatusBarCtrl(){}
		void xdMoveWindow(CRect &rc)
		{
			if(NULL==this->m_hWnd) return;
			MoveWindow(rc);
		}
		void OnXdInit(CWnd* pW)
		{
			m_startTime		= CTime::GetCurrentTime();
			CString strTime	= m_startTime.Format("%X");	
			strTime="程序启动时间 "+strTime;
			Create(WS_CHILD|WS_VISIBLE|SBT_OWNERDRAW, CRect(0,0,0,0), pW, 0); 
			
		    int strPartDim[4]= {120,270,330,-1}; //分割状态栏	     
			SetParts(4,strPartDim);
			
			SetText(MY_VERSION,0,0 );
			SetText(strTime,1,0); 
			
		}
		
		void ShowCurrentTime()
		{
			CTime t = CTime::GetCurrentTime();
			
			CTimeSpan span=t-m_startTime; 
			int iDay=span.GetDays(); 
			int iHour=span.GetTotalHours(); 
			int iMin=span.GetTotalMinutes();
			int iSec=span.GetTotalSeconds();
			
			CString strTime;
			strTime.Format("程序运行时间: %d-%d:%d:%d",iDay,iHour%24,iMin%60,iSec%60);
			SetText(strTime,1,0); 
			
		}

		void ShowFPS()
		{
			double   dwFPS;    
			if(m_dwTEnd-m_dwTStart>=1000)  {
				dwFPS=1000.0*m_dwCount/(m_dwTEnd-m_dwTStart);
				m_strFPS.Format("FPS:%.1f",dwFPS);
				m_dwCount = 0;
				m_dwTStart = m_dwTEnd = ::timeGetTime();  
			}
			else{
				m_dwTEnd=::timeGetTime();
				m_dwCount++;
			}
			SetText(m_strFPS,2,0); 
		}
		void CBtflStatusBarCtrl::ShowCoordinate(int x, int y, CWnd* pClientView)
		{
			CRect rc;
			pClientView->GetClientRect(&rc);
			int W=0;
			int H=0;
			if(BL_STATUS_OK == ((CMyStatic*)pClientView)->GetIMGRealSize(W, H))
			{  
				POINT pt;
				pt.x=x-POS;
				pt.y=y-TOP;
				if (rc.PtInRect(pt))
				{      
					int x1 = W * (x-POS)/rc.Width();
					int y1 = H * (y-TOP)/rc.Height();
					
					COLORREF rgb = ((CMyStatic*)pClientView)->MyGetPixel(x1,y1);
					int RV =  ((BYTE)((rgb)>>16));
					int GV =  ((BYTE)(((WORD)(rgb)) >> 8));
					int BV = ((BYTE)(rgb)); 
					
					CString strInfo;
					strInfo.Format("%d*%d, (%d,%d), R:%d,G:%d,B:%d", W, H, x1, y1,RV,GV,BV);
					SetText(strInfo, 3, 0 );
				}else{
					SetText("", 3, 0 );
				}
			}
		}
		
	};
 
	class CMyToolBar:public CToolBar
	{
	public:
		CMyToolBar(){}
		~CMyToolBar(){}
		void plInit(CWnd* pWnd,UINT id)
		{
			if(!Create(pWnd) || !LoadToolBar(IDR_TOOLBAR_MAIN))
			{
				TRACE0("Failed to Create Dialog Toolbar\n"); 
			}
			
			CRect rcClientOld; // 原客户区RECT
			CRect rcClientNew; // 加入TOOLBAR后的CLIENT RECT
			pWnd->GetClientRect(rcClientOld); // 
			// Called to reposition and resize control bars in the client area of a window
			// The reposQuery FLAG does not really traw the Toolbar. It only does the calculations.
			// And puts the new ClientRect values in rcClientNew so we can do the rest of the Math.
			//重新计算RECT大小
			pWnd->RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rcClientNew);
			
			// All of the Child Windows (Controls) now need to be moved so the Tollbar does not cover them up.
			//所有的子窗口将被移动，以免被TOOLBAR覆盖
			// Offest to move all child controls after adding Tollbar
			//计算移动的距离
			CPoint ptOffset(rcClientNew.left-rcClientOld.left,
				rcClientNew.top-rcClientOld.top);
			
			CRect rcChild;
			CWnd* pwndChild = pWnd->GetWindow(GW_CHILD); //得到子窗口
			while(pwndChild) // 处理所有子窗口
			{//移动所有子窗口
				pwndChild->GetWindowRect(rcChild);
				ScreenToClient(rcChild); 
				rcChild.OffsetRect(ptOffset); 
				//pwndChild->MoveWindow(rcChild,FALSE); //Jiapeng: comment out it.
				pwndChild = pwndChild->GetNextWindow();
			}
			
			CRect rcWindow;
			pWnd->GetWindowRect(rcWindow); // 得到对话框RECT
			rcWindow.right += rcClientOld.Width() - rcClientNew.Width(); // 修改对话框尺寸
			rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height(); 
			pWnd->MoveWindow(rcWindow,FALSE); // Redraw Window
			
			pWnd->RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
			
			CRect rcT;
			GetClientRect(rcT);
		}
	};
	class CMyStatic : public CStatic
	{
	public:
		CMyStatic():m_hMyB(NULL){
			bSelected = FALSE;
		}	
		~CMyStatic(){}
		void plUser1(WPARAM w, LPARAM l)
		{  
			CDC *pDC = GetDC();
			int n = (int)l;
			BYTE* pByte = (BYTE*)w;
		
			CRect rect(60,110,300,300);
			GetClientRect(&rect);
			ptShowBmp(pDC->m_hDC,pByte,n,&rect); 
			
			ReleaseDC(pDC);
		}
		void plDraw() 
		{
			static int n=0;
			n++;
			CDC *pDC = GetDC();
			CString s;
			s.Format("BlMfcUI Timer Test:: %d",n);
			pDC->TextOut(50,70,s);
			
			ReleaseDC(pDC);
		}
		void plMoveWnd(int x,int y,int dx,int dy,CWnd &w)
		{ 
			pvMoveWnd(x,y,dx,dy,w);
		}
		
		void plChangeCursor(int x, int y){
			pvChangeCursor(x, y);
		}
		
		BOOL plIsSelected(){
			return bSelected;
		}

		BLSTATUS CMyStatic::GetIMGRealSize(int &W, int &H)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
			if(NULL == m_hMyB)
			{
				r = BL_STATUS_PARAMETER_INVALID;
			}
			else
			{
				CBitmap m;
				m.FromHandle(m_hMyB);
				BITMAP btMap;
				GetObject(m_hMyB,sizeof(BITMAP),&btMap );
				
				W = btMap.bmWidth;
				H = btMap.bmHeight;
				r = BL_STATUS_OK; 
			}
			return r;
		}
		COLORREF  CMyStatic::MyGetPixel(int xPos, int yPos)
		{
			CBitmap m;
			m.FromHandle(m_hMyB);
			BITMAP btMap;
			GetObject( m_hMyB, sizeof(BITMAP), &btMap );
			int W = btMap.bmWidth;
			int H = btMap.bmHeight;
			
			BYTE *pBuffer = new BYTE [W*H*3];
			::memcpy(pBuffer,m_pBmpBits,W*H*3);
			
			//翻转图像数据
			BYTE *p = NULL, * q = NULL;	
			for (int i = 0; i < H/2; i++)
			{  
				p = pBuffer + i * W * 3;
				q = pBuffer + (H-i-1) * W * 3;
				for(int j = 0; j < W*3; j++)
				{
					BYTE temp = *(p + j);
					*(p+j) = *(q+j);
					*(q+j)=temp;
				}	
			}
			
			int PixelBytes=btMap.bmBitsPixel/8;//每一个像素占字节数
			int rgbV;
			for(int y=0;y<H;y++)
			{
				for(int x=0; x<W;x++)
				{
					rgbV=y*btMap.bmWidthBytes+x*PixelBytes;
					
					if (y==yPos && x==xPos)
					{
						int R = pBuffer[rgbV+0];
						int G = pBuffer[rgbV+1];
						int B = pBuffer[rgbV+2];
						delete[]pBuffer;
						return RGB(R,G,B);
						
					}
				}
			}
			delete[]pBuffer;
			return RGB(0,0,0);	
		}

		BOOL CMyStatic::IsPtInViewRect(int x, int y)
		{
			return pvIsHitMe(x,y);

			CRect rcView;
			GetClientRect(&rcView);
			
			POINT pt;
			pt.x=x-POS;
			pt.y=y-TOP;
			if (rcView.PtInRect(pt)){		
				return TRUE;
			}else
				return FALSE;
		}
		void CMyStatic::GetIMGPos(int x, int y, int &x1, int &y1)
		{
			//将设备坐标转换为图像坐标
			CRect rcView;
			GetClientRect(&rcView);

			int W, H;
			GetIMGRealSize(W,H);
			x1 = W * (x-POS)/rcView.Width();
			y1 = H * (y-TOP)/rcView.Height();
		}
		void CMyStatic::plGetImgXY(int x, int y, int &x1, int &y1)
		{ 
			CRect rcView;
			GetClientRect(&rcView);

			int W, H;
			GetIMGRealSize(W,H);
			CPoint p(x,y);
			GetParent()->ClientToScreen(&p);
			ScreenToClient(&p);
			x1 = W * (p.x)/rcView.Width();
			y1 = H * (p.y)/rcView.Height();
		}
	protected:
		BOOL bSelected;
	private:
		HBITMAP			m_hMyB;
		LPBYTE          m_pBmpBits;
		
		
		void ptShowBmp(HDC hDC,BYTE* pByte,int n, LPRECT pRect)
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
		void pvMoveWnd(int x,int y,int dx,int dy,CWnd &w)
		{
			CRect rc;
			GetWindowRect(&rc);
			
			if (x==rc.Width()+POS)
			{
				HCURSOR hCursor = (HCURSOR)AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);//IDC_SIZENWSE
				::SetCursor(hCursor);
			}
			MoveWindow(POS,TOP,x-POS,rc.Height());
			//w.MoveWindow(x,POS,115,115);
		}
		
		void pvChangeCursor(int x, int y)
		{
			if ( rule(x))
			{
				HCURSOR hCursor = (HCURSOR)AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
				::SetCursor(hCursor);
				bSelected = TRUE;
			}else{
				bSelected = FALSE;
			}
		}
		
		virtual BOOL rule(int x){
			CRect rc;
			GetWindowRect(&rc);
			if (x > rc.Width()+POS-1 && x < rc.Width()+POS+5)
				return TRUE;
			return FALSE;
		}
		BOOL CMyStatic::pvIsHitMe(int x, int y)
		{ 
			CRect rcMe;
			GetClientRect(&rcMe);
			CPoint p(x,y);
			ClientToScreen(rcMe);
			GetParent()->ClientToScreen(&p);
 
			if (rcMe.PtInRect(p))
			{		 
				return TRUE;
			}
			else
			{
				return FALSE;
			} 
		}
	};
	
	class CDeviceView : public CMyStatic{
	public:
		CDeviceView(){
			bSelected = FALSE;
		}	
		~CDeviceView(){}
		void plMoveWnd(int x,int y)
		{ 
			pvMoveWnd(x,y);
		}
		
	private:
		void pvMoveWnd(int x,int y)
		{
			CRect rc;
			GetWindowRect(&rc);
			GetParent()->ScreenToClient(&rc);
			
			if (x==rc.left)
			{
				HCURSOR hCursor = (HCURSOR)AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
				::SetCursor(hCursor);
			}
			int cx = rc.left -x;
			MoveWindow(x, TOP, rc.Width()+cx, rc.Height());
		}
		virtual BOOL rule(int x)
		{
			CRect rc;
			GetWindowRect(&rc);
			GetParent()->ScreenToClient(&rc); 
			
			if (x>rc.left-2 && x<rc.left+3)
				return TRUE;
			
			return FALSE;
		}
	};
	
	class CMyMsg
	{
	public:
		CMyMsg(CDlgMain *p):pParent(p){
			
			m_x		= 0;
			m_y		= 0;
			m_nDx	= 0;
			m_nDy	= 0;
			m_nMx	= 0;
			m_nMy	= 0;
		}
		~CMyMsg(){}
		void CMyMsg::pl2Do(UINT m, WPARAM w, LPARAM l)
		{
			pt2Do(m,w,l);
		}
	private:
		void CMyMsg::pvLBtnDown(HWND h,UINT m, WPARAM w, LPARAM l)
		{ 
			int x = (int)(short)LOWORD(l);
			int y = (int)(short)HIWORD(l); 
			m_nDx = x; 
			m_nDy = y;

			if (pParent->m_StaticClient.IsPtInViewRect(x,y))
			{
				int x1,y1;
				pParent->m_StaticClient.GetIMGPos(x,y,x1,y1);
				//给下层接口传递图像坐标(x1,y1)
				DWORD dwV=x1;
				dwV = dwV | (y1<<16);
				pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,m,w,dwV);
			}
			if (pParent->m_StaticDevice.IsPtInViewRect(x,y))
			{
				int x1,y1;
				pParent->m_StaticDevice.plGetImgXY(x,y,x1,y1);
				//给下层接口传递图像坐标(x1,y1)
				DWORD dwV=x1;
				dwV = dwV | (y1<<16);
				pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,m,BL_ID_B1_MNG,dwV);
			}
		}
		void CMyMsg::pvMouseMove(int i,int j) 
		{     
			if(0!=m_nDx) //Left button down
			{
				m_x -= (i-m_nDx);
				m_nDx = i;
				m_y -= (j-m_nDy);
				m_nDy = j;
				TRACE("lbt down: %d,%d\n",i,j);
				if (pParent->m_StaticClient.plIsSelected() && i>=POS+10)
				{
					pParent->m_StaticClient.plMoveWnd(i,j,300,300,pParent->m_StaticDevice);
					pParent->m_StaticDevice.plMoveWnd(i,j);
					TRACE("%d,%d\n",i,j);
				}
				
			}
			else
			{
				pParent->m_StaticClient.plChangeCursor(i,j);
				pParent->m_StaticDevice.plChangeCursor(i,j);
				TRACE("not lbt down: %d,%d\n",i,j);
			} 
			pParent->m_MyStatusBar.ShowCoordinate(i, j, &pParent->m_StaticClient);
		}
		
		void OnXdLBtnUp(int x,int y)
		{
			m_nDx	= 0;
			m_nDy	= 0;
		}
		
		CRect CMyMsg::ChangeSize(CWnd *pWnd, int newX, int newY)
		{
			if(pWnd)
			{
				CRect rect; 
				pWnd->GetWindowRect(&rect);
				pParent->ScreenToClient(&rect);
				
				rect.right=rect.right+(newX-m_rect.Width());
				rect.bottom=rect.bottom+(newY-m_rect.Height());
				pWnd->MoveWindow(rect);
				return rect;
			}else{
				return CRect(0,0,0,0);
			}
		}
	private:
		CDlgMain *pParent;
		int		m_x;
		int		m_y;
		int		m_nDx,m_nDy;
		int		m_nMx,m_nMy;
		CRect   m_rect; //Parent size
		void pt2Cmd(WPARAM w, LPARAM l)
		{
			switch (LOWORD (w))
			{
			case ID_TOOL_BTN_1:  
				pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,BL_WM_CMD_B0_2_B1_01,w,l);
				break;
			}
		}
		void pt2Do(UINT m, WPARAM w, LPARAM l)
		{
			int x = (int)(short)LOWORD(l);
			int y = (int)(short)HIWORD(l);
			switch(m)
			{ 
			case WM_COMMAND:
				{
					pt2Cmd(w,l);
				}
				break;  
			case BL_WM_B1_0XB101:
				Sleep(1);
				pParent->m_StaticClient.plUser1(w,l);  
                pParent->m_MyStatusBar.ShowFPS();
				break;
			case BL_WM_B0_0XB001: 
				pParent->m_StaticDevice.plUser1(w,l);
				break; 
				
			case WM_CLOSE:
			case BL_WM_B1_PRP_1:
			case WM_KEYDOWN:
			case WM_KEYUP: 
			case WM_DEADCHAR:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
			case WM_SYSCHAR:
			case WM_SYSDEADCHAR:
			case WM_CHAR:
				pParent->m_MyDll.OnBlCallLibFun(pParent->m_hWnd,m,w,l);
				break;
				
			case WM_LBUTTONDOWN:
				{
					pvLBtnDown(pParent->m_hWnd,m,w,l); 
				}
				break;
			case WM_LBUTTONUP:
				{
					OnXdLBtnUp(x,y);
				}
				break;
			case WM_MOUSEMOVE:
				{
					pvMouseMove(x,y);
				}
				break;
			case WM_SIZING:
				{
				}
				break;
			case  WM_PAINT:
				{
					pParent->m_StaticClient.Invalidate();
					pParent->m_StaticDevice.Invalidate();
				}break;
			case WM_SIZE:
				{
					CRect rt; 
					pParent->GetClientRect(&rt); 
					if (rt.Width()<=0) return;
					
					CRect newrc = ChangeSize(pParent->GetDlgItem(IDC_STATIC_CLIENT), rt.Width(), rt.Height());
					if (newrc.Width()>0)
					{
						CRect rcDevView; 
						pParent->GetDlgItem(IDC_STATIC_MSG)->GetWindowRect(&rcDevView);
						pParent->m_StaticDevice.MoveWindow(newrc.Width()+POS, TOP, rcDevView.Width(), rcDevView.Height()+rt.Height()-m_rect.Height());
					}
					
					m_rect=rt;
					rt.top = rt.bottom - 20; 
					pParent->m_MyStatusBar.xdMoveWindow(rt);
					
				}
				break;
			}
		}
	};
	// Construction
	public:
		CDlgMain(CWnd* pParent = NULL);   // standard constructor
		
		// Dialog Data
		//{{AFX_DATA(CDlgMain)
		enum { IDD = IDD_DLG_MAIN };
		CDeviceView		m_StaticDevice;
		CMyStatic		m_StaticClient;
		//}}AFX_DATA
		
		
		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CDlgMain)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
		virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
		
		// Implementation
	protected:
		
		// Generated message map functions
		//{{AFX_MSG(CDlgMain)
		virtual BOOL OnInitDialog();
		afx_msg void OnTimer(UINT nIDEvent);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
			
	public:
		CBtflStatusBarCtrl		m_MyStatusBar; 
		CMyToolBar				m_MyToolBar;
		CString					m_strTitle;
		 
		CMyDll					m_MyDll;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAIN_H__5881E530_36C1_47EC_B8AB_9F69118689E7__INCLUDED_)
