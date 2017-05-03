// BlXAU.h : main header file for the DLL
//

#if !defined(AFX_BLXAU_H__FF5B609A_BF33_476E_A89F_8EBE8259FB6C__INCLUDED_)
#define AFX_BLXAU_H__FF5B609A_BF33_476E_A89F_8EBE8259FB6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "wininet.h"
#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib ")  

//#include <algorithm>
//#include <vector>
//using std::vector;
/////////////////////////////////////////////////////////////////////////////
//  
//
#include "MyPrpDlg.h"

#include <math.h>

#define IDM_ALIGN_LEFT                  40003
#define IDM_ALIGN_RIGHT                 40004
#define IDM_ALIGN_CENTER                40005
#define IDM_ALIGN_JUSTIFIED             40006
#define EZ_ATTR_BOLD          1
#define EZ_ATTR_ITALIC        2
#define EZ_ATTR_UNDERLINE     4
#define EZ_ATTR_STRIKEOUT     8


#define MY_VERSION		"V:0096"   

class CLfDC{
	class CXdGDI
	{
	private:
		HFONT xdCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
			int iDeciPtWidth, int iAttributes, BOOL fLogRes){
			FLOAT      cxDpi, cyDpi ;
			HFONT      hFont ;
			LOGFONT    lf ;
			POINT      pt ;
			TEXTMETRIC tm ;
			
			SaveDC (hdc) ;
			
			SetGraphicsMode (hdc, GM_ADVANCED) ;
			ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
			SetViewportOrgEx (hdc, 0, 0, NULL) ;
			SetWindowOrgEx   (hdc, 0, 0, NULL) ;
			
			if (fLogRes)
			{
				cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
				cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
			}
			else
			{
				cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
					GetDeviceCaps (hdc, HORZSIZE)) ;
				
				cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
					GetDeviceCaps (hdc, VERTSIZE)) ;
			}
			
			pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
			pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
			
			DPtoLP (hdc, &pt, 1) ;
			
			lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
			lf.lfWidth          = 0 ;
			lf.lfEscapement     = 0 ;
			lf.lfOrientation    = 0 ;
			lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
			lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
			lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
			lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
			lf.lfCharSet        = DEFAULT_CHARSET ;
			lf.lfOutPrecision   = 0 ;
			lf.lfClipPrecision  = 0 ;
			lf.lfQuality        = 0 ;
			lf.lfPitchAndFamily = 0 ;
			
			lstrcpy (lf.lfFaceName, szFaceName) ;
			
			hFont = CreateFontIndirect (&lf) ;
			
			if (iDeciPtWidth != 0)
			{
				hFont = (HFONT) SelectObject (hdc, hFont) ;
				
				GetTextMetrics (hdc, &tm) ;
				
				DeleteObject (SelectObject (hdc, hFont)) ;
				
				lf.lfWidth = (int) (tm.tmAveCharWidth *
					fabs (pt.x) / fabs (pt.y) + 0.5) ;
				
				hFont = CreateFontIndirect (&lf) ;
			}
			
			RestoreDC (hdc, -1) ;
			return hFont ;
		}
		
	public:
		void OnXdCreate2DData(IN int x, IN int y,IN int w, IN int h,
			OUT BYTE *pData,bool bClr)
		{ 
			OnDrawRect(x,y,w,h,RGB(0,0,255));
		}
		
		void OnDrawFillFontText(char *szString,int cxArea, int cyArea){
			HDC &hdc = m_hDC; 
			HFONT        hFont ;
			SIZE         size ;
			
			hFont = xdCreateFont (hdc, TEXT ("Times New Roman"), 1440, 0, 0, TRUE) ;
			
			SelectObject (hdc, hFont) ;
			SetBkMode (hdc, TRANSPARENT) ;
			
			GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;
			
			BeginPath (hdc) ;
			TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
				szString, lstrlen (szString)) ;
			EndPath (hdc) ;
			
			SelectObject (hdc, CreateHatchBrush (HS_DIAGCROSS, RGB (255, 0, 0))) ;
			SetBkColor (hdc, RGB (0, 0, 255)) ;
			SetBkMode (hdc, OPAQUE) ;
			
			StrokeAndFillPath (hdc) ;
			
			DeleteObject (SelectObject (hdc, GetStockObject (WHITE_BRUSH))) ;
			SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
			DeleteObject (hFont) ;
			
		}
		void OnJustify (PTSTR pText, RECT * prc, int iAlign)
		{
			HDC &hdc = m_hDC;
			
			int   xStart, yStart, cSpaceChars ;
			PTSTR pBegin, pEnd ;
			SIZE  size ;
			
			yStart = prc->top ;
			do                            // for each text line
			{
				cSpaceChars = 0 ;        // initialize number of spaces in line
				
				while (*pText == ' ')    // skip over leading spaces
					pText++ ;
				
				pBegin = pText ;         // set pointer to char at beginning of line
				
				do                       // until the line is known
				{
					pEnd = pText ;      // set pointer to char at end of line
					
					// skip to next space 
					
					while (*pText != '\0' && *pText++ != ' ') ;
					
					if (*pText == '\0')
						break ;
					
					// after each space encountered, calculate extents
					
					cSpaceChars++ ;
					GetTextExtentPoint32(hdc, pBegin, pText - pBegin - 1, &size) ;
				}
				while (size.cx < (prc->right - prc->left)) ;
				
				cSpaceChars-- ;               // discount last space at end of line
				
				while (*(pEnd - 1) == ' ')    // eliminate trailing spaces
				{
					pEnd-- ;
					cSpaceChars-- ;
				}
				
				// if end of text and no space characters, set pEnd to end
				
				if (*pText == '\0' || cSpaceChars <= 0)
					pEnd = pText ;
				
				GetTextExtentPoint32 (hdc, pBegin, pEnd - pBegin, &size) ;
				
				switch (iAlign)               // use alignment for xStart
				{
				case IDM_ALIGN_LEFT:
					xStart = prc->left ;
					break ;
					
				case IDM_ALIGN_RIGHT:
					xStart = prc->right - size.cx ;
					break ;
					
				case IDM_ALIGN_CENTER:
					xStart = (prc->right + prc->left - size.cx) / 2 ;
					break ;
					
				case IDM_ALIGN_JUSTIFIED:
					if (*pText != '\0' && cSpaceChars > 0)
						SetTextJustification (hdc,
						prc->right - prc->left - size.cx,
						cSpaceChars) ;
					xStart = prc->left ;
					break ;
				}
				// display the text
				
				TextOut (hdc, xStart, yStart, pBegin, pEnd - pBegin) ;
				
				// prepare for next line
				
				SetTextJustification (hdc, 0, 0) ;
				yStart += size.cy ;
				pText = pEnd ;
			}
			while (*pText && yStart < prc->bottom - size.cy) ;
		}
		void OnDrawRuler(RECT * prc){
			static int iRuleSize [16] = { 360, 72, 144, 72, 216, 72, 144, 72,
				288, 72, 144, 72, 216, 72, 144, 72 } ;
			HDC &hdc = m_hDC;
			
			int        i, j ;
			POINT      ptClient ;
			
			SaveDC (hdc) ;
			
			// Set Logical Twips mapping mode
			
			SetMapMode (hdc, MM_ANISOTROPIC) ;
			SetWindowExtEx (hdc, 1440, 1440, NULL) ;
			SetViewportExtEx (hdc, GetDeviceCaps (hdc, LOGPIXELSX),
				GetDeviceCaps (hdc, LOGPIXELSY), NULL) ;
			
			// Move the origin to a half inch from upper left
			
			SetWindowOrgEx (hdc, -720, -720, NULL) ;
			
			// Find the right margin (quarter inch from right)
			
			ptClient.x = prc->right ;
			ptClient.y = prc->bottom ;
			DPtoLP (hdc, &ptClient, 1) ;
			ptClient.x -= 360 ;
			
			// Draw the rulers
			
			MoveToEx (hdc, 0,          -360, NULL) ;
			LineTo   (hdc, ptClient.x, -360) ;
			MoveToEx (hdc, -360,          0, NULL) ;
			LineTo   (hdc, -360, ptClient.y) ;
			
			for (i = 0, j = 0 ; i <= ptClient.x ; i += 1440 / 16, j++)
			{
				MoveToEx (hdc, i, -360, NULL) ;
				LineTo   (hdc, i, -360 - iRuleSize [j % 16]) ;
			}
			
			for (i = 0, j = 0 ; i <= ptClient.y ; i += 1440 / 16, j++)
			{
				MoveToEx (hdc, -360, i, NULL) ;
				LineTo   (hdc, -360 - iRuleSize [j % 16], i) ;
			}
			
			RestoreDC (hdc, -1) ;
			
		}
		void OnDrawText(int x,int y,char *sz,COLORREF rgb)
		{
			if(NULL==m_hDC) return;
			HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
			HBRUSH  hOldBrush = (HBRUSH)SelectObject(m_hDC,hBrush); 
			
			TextOut (m_hDC, x, y, sz,25) ;
			
			SelectObject(m_hDC,hOldBrush);
			DeleteObject(hBrush);
			
			
		}
		void OnDrawRect(int x,int y,int w,int h,COLORREF rgb)
		{
			if(NULL==m_hDC) return;
			HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
			HBRUSH  hOldBrush = (HBRUSH)SelectObject(m_hDC,hBrush);
			
			::Rectangle(m_hDC,x,y,w,h);
			
			SelectObject(m_hDC,hOldBrush);
			DeleteObject(hBrush);
			
		}
		void SetRECT(RECT &r,int x,int y,int w,int h){
			r.left		= x;
			r.top		= y;
			r.right		= w;
			r.bottom	= h;
		}
		
		
		
		CXdGDI(HDC &hDC)
		{
			m_hDC = hDC;
		} 
		
		CXdGDI()
		{
			m_hDC = NULL;
		}
		virtual ~CXdGDI()
		{
		}
		
private:
	HDC		m_hDC;
};
public: 
	void plLine(int x1,int y1,int x2,int y2,LOGPEN &p)
	{ 	
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return; 
		HPEN	hPen		= (HPEN)CreatePenIndirect(&p);
		HBRUSH  hOldPen		= (HBRUSH)SelectObject(hDC,hPen);
		
		MoveToEx (hDC,x1,y1, NULL) ;
		::LineTo(hDC,x2,y2);
		
		SelectObject(hDC,hOldPen);
		DeleteObject(hPen); 
	}
	void plRect(int x,int y,int w,int h,bool bPen,LOGPEN &p,bool bBrush,LOGBRUSH &b)
	{ 	
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return;
		HBRUSH  hBrush		= (HBRUSH)CreateBrushIndirect(&b);
		HBRUSH  hOldBrush	= (HBRUSH)SelectObject(hDC,hBrush);
		
		if (bBrush)
			hOldBrush		= (HBRUSH)SelectObject(hDC,hBrush);
		else
		{
			hOldBrush		= (HBRUSH)SelectObject(hDC,GetStockObject(NULL_BRUSH));
		}
		
		HPEN	hPen		= (HPEN)CreatePenIndirect(&p);
		HBRUSH  hOldPen		= (HBRUSH)SelectObject(hDC,hPen);
		
		::Rectangle(hDC,x,y,x+w,y+h);
		
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush); 
		SelectObject(hDC,hOldPen);
		DeleteObject(hPen);  
		
	}
	
	void plUpsidedown24Rgb(BYTE *p,int w,int h){
		BYTE *pNew = new BYTE[w*h*3];
		memset(pNew,255,w*h*3);
		//*
		BYTE *pI = p;
		BYTE *pN = pNew + w * 3* (h-1);
		for(int i = 0; i < h; i++)
		{
			memcpy(pN,pI,w*3);
			pI += w*3;
			pN -= w*3;
		}
		//*/
		memcpy(p,pNew,w*h*3); 
		delete []pNew;
	}
	void OnXd_DrawG1()
	{
		HDC		&hDC = m_hMemDC;  
		xdPaintRoutine (hDC, 300,300);
	}
	void OnXd_DrawG()
	{
		
		HDC		&hDC = m_hMemDC;  
		
		CXdGDI d(hDC);
		RECT	rc;
		rc.left		= 0;
		rc.top		= 0;
		rc.right	= 300;
		rc.bottom	= 300;
		d.OnDrawRuler(&rc);
		
		static BYTE		bitsHello1 []   = { 0x51, 0x77, 0x10, 0x00,
			0x57, 0x77, 0x50, 0x00, 
			0x13, 0x77, 0x50, 0x00,
			0x57, 0x77, 0x50, 0x00,
			0x51, 0x11, 0x10, 0x00 
		} ;
		static BITMAP	bitmapHello1     = { 0, 20, 5, 4, 1, 1 } ;
		
		static BYTE		bitsG []		= { 0xff, 0x1f, //1 0x1f, 0x00,
			0xff, 0x1f, //2 0x50, 0x00, 
			0xfe, 0x4f, //3 0x50, 0x00,
			0xfe, 0x1f, //4 0x50, 0x00,
			0xfe, 0x1f, //5 0x10, 0x00 
			
		} ;
		static BITMAP	bmpG     = { 0, 16, 40, 2, 1, 1 } ;
		
		
		
		static HBITMAP	hBitmap ;
		static int		cxClient, cyClient, cxSource, cySource ;
		bmpG.bmBits				= bitsG ; 
		hBitmap							= CreateBitmapIndirect (&bmpG) ;  
		cxSource						= bmpG.bmWidth ;
		cySource						= bmpG.bmHeight ;
		HDC hdcMem						= CreateCompatibleDC (hDC) ;
		cxClient						= cxSource;//800;
		cyClient						= cxSource;//600;
		
		
		SelectObject (hdcMem, hBitmap) ; 
		
		for (int y = 0 ; y < cyClient ; y += cySource)
			for (int x = 0 ; x < cxClient ; x += cxSource)
			{
				BitBlt (hDC, 300, 300, cxSource, cySource, hdcMem, 0, 0, SRCCOPY) ;
			}
			
			DeleteDC (hdcMem) ; 
	}
	void OnXddrawMusicStr(int x,int y,char *sz,int nBkMode)
	{
		HDC		&hDC = m_hMemDC;
		xdMusicstring(hDC,x,y,sz,nBkMode);
	}
	void OnXdDrawStr(int x,int y,char* sz)
	{
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return;
		
		HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(RGB(255,0,0));
		HBRUSH  hOldBrush = (HBRUSH)SelectObject(hDC,hBrush); 
		
		TextOut (hDC, x, y, sz,strlen(sz)) ;
		
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}
	
	void OnXdGetData(int w, int h, BYTE *pData)
	{
		BYTE *p = pData;
		BITMAP csBitmap;
		HBITMAP		&hB = m_hBmp;
		
		int nRetValue = GetObject(hB, sizeof(csBitmap), &csBitmap);
		unsigned long nBpp, nWBmp, nHBmp;
		
		if (nRetValue) {
			nWBmp   = (long)csBitmap.bmWidth;
			nHBmp	= (long)csBitmap.bmHeight;
			nBpp    = (long)csBitmap.bmBitsPixel;
			long sz = csBitmap.bmWidth*csBitmap.bmHeight*(csBitmap.bmBitsPixel>>3);
			csBitmap.bmBits = (void *) new BYTE[ sz ];
			GetBitmapBits((HBITMAP)hB, sz, csBitmap.bmBits ); 
		} 
		else 
		{ 
			return ;
		}
		
		if ( nBpp == 32 )
		{
			for ( unsigned long y = 0; y < nHBmp; y ++ )
			{
				for ( unsigned long x = 0; x < nWBmp; x ++ ) 
				{
					RGBQUAD * rgb = ((RGBQUAD *) ((char*)(csBitmap.bmBits) 
						+ csBitmap.bmWidthBytes*y + x*sizeof(DWORD)) ); 
					p[ 0 ]	= rgb->rgbBlue;
					p[ 1 ]	= rgb->rgbGreen;
					p[ 2 ]	= rgb->rgbRed;
					p+=3;
				}
				p+=(w-nWBmp)*3;
			}
		} 
		else if ( nBpp == 24 )
		{
			for ( unsigned long y = 0; y < nHBmp; y ++ ) 
			{
				for ( unsigned long x = 0; x < nWBmp; x ++ )
				{ 
					RGBTRIPLE rgbi = *((RGBTRIPLE *) ((char*)(csBitmap.bmBits)
						+ csBitmap.bmWidthBytes*y + x*3) );
					
					RGBQUAD rgbq;
					rgbq.rgbRed = rgbi.rgbtRed;
					rgbq.rgbGreen = rgbi.rgbtGreen;
					rgbq.rgbBlue = rgbi.rgbtBlue;
					
					p[ (nHBmp - 1 - y)*nWBmp + x ]		= rgbq.rgbBlue;
					p[ (nHBmp - 1 - y)*nWBmp + x + 1 ]	= rgbq.rgbGreen;
					p[ (nHBmp - 1 - y)*nWBmp + x + 2 ]	= rgbq.rgbRed;
				}
			}
		}  
		if(csBitmap.bmBits) delete []csBitmap.bmBits;
	}
	
	void OnXdDrawRect(int x, int y, int w, int h, COLORREF rgb) 
	{
		HDC		&hDC = m_hMemDC;
		if(NULL==hDC) return;
		HBRUSH  hBrush  = (HBRUSH)CreateSolidBrush(rgb);
		HBRUSH  hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		
		::Rectangle(hDC,x,y,x+w,y+h);
		
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush); 
	}
	CLfDC()
	{
		m_nWMax			= 300;
		m_nHMax			= 300;
		m_hScreenDC		= ::GetDC(NULL);//CreateDC("DISPLAY", NULL, NULL, NULL);
		m_hMemDC 		= CreateCompatibleDC(m_hScreenDC);
		m_hBmp			= CreateCompatibleBitmap(m_hScreenDC, m_nWMax, m_nHMax);
		m_hOldBmp		= (HBITMAP) SelectObject(m_hMemDC, m_hBmp);
		
		m_pBits			= new BYTE[m_nWMax*m_nHMax*3];
		
	}
	virtual ~CLfDC()
	{
		SelectObject(m_hMemDC, m_hOldBmp); 
		DeleteObject(m_hBmp);
		DeleteDC(m_hMemDC);  
		::ReleaseDC(NULL, m_hScreenDC);
		delete []m_pBits;
	}
	void plInitDraw()
	{
		OnXdDrawRect(0,0,m_nWMax,m_nHMax,RGB(123,123,123)); 
	}
	HDC plGetDC()
	{
		return m_hMemDC;
	}
private:  
	HDC					m_hScreenDC;
	HDC					m_hMemDC;
	HBITMAP				m_hBmp; 
	HBITMAP				m_hOldBmp;
	BYTE				*m_pBits;
	int				m_nWMax;
	int				m_nHMax; 
	void xdMusicstring(HDC hdc,int x,int y,char *sz,int nBkMode)
	{
		HFONT        hFont ;
		SIZE         size ;
		
		hFont = xdEzCreateFont (hdc, TEXT ("akvo"), 400, 0, 0, TRUE) ;
		
		SelectObject (hdc, hFont) ;
		
		GetTextExtentPoint32 (hdc, sz, lstrlen (sz), &size) ;
		
		int nMode = SetBkMode (hdc, nBkMode) ; 
		TextOut (hdc, x, y,	sz, lstrlen (sz)) ; 
		SetBkMode (hdc, nMode) ;
		
		SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
		DeleteObject (hFont) ;
	}
	
	void xdPaintRoutine (HDC hdc, int cxArea, int cyArea)
	{
		static TCHAR szString [] = TEXT ("abc:()") ;
		HFONT        hFont ;
		SIZE         size ;
		
		hFont = xdEzCreateFont (hdc, TEXT ("akvo"), 800, 0, 0, TRUE) ;
		
		SelectObject (hdc, hFont) ;
		
		GetTextExtentPoint32 (hdc, szString, lstrlen (szString), &size) ;
		
		BeginPath (hdc) ;
		TextOut (hdc, (cxArea - size.cx) / 2, (cyArea - size.cy) / 2,
			szString, lstrlen (szString)) ;
		EndPath (hdc) ;
		
		StrokePath (hdc) ;
		
		SelectObject (hdc, GetStockObject (SYSTEM_FONT)) ;
		DeleteObject (hFont) ;
	}
	void ref1()
	{
		HDC hdc=::GetDC(NULL);
		HDC memdc=CreateCompatibleDC(hdc);
		RECT rc;
		BITMAP bmpXD;
		HBITMAP holdbmp,hbmp=NULL;
		//	LoadBitmap(hInstDVBRes,MAKEINTRESOURCE(IDB_CLOCK));//从资源加载位图
		holdbmp=(HBITMAP)SelectObject(memdc,hbmp);//这里把hbmp的位图选择到兼容DC memdc,之后这个兼容DC就拥有和
		//hbmp同样大小的绘图区域,注意超出位图返回的GDI输出都是无效的.
		GetObject(hbmp,sizeof(BITMAP),&bmpXD);//这里获取位图的大小信息,事实上也是兼容DC绘图输出的范围
		SetRect(&rc,0,0,bmpXD.bmWidth,bmpXD.bmHeight);
		DrawText(memdc,"Center Line Text", -1,&rc,DT_VCENTER|DT_SINGLELINE|DT_CENTER);//在兼容DC中间位置输出字符串
		//这样以来我们就相当于把hbmp这个位图加上了文字标注,我们可以把这个增加了文字标注的位图保存起来.一个简单的图像处理基本就OK了.
		SelectObject(memdc,holdbmp);//复原兼容DC数据.
		DeleteDC(memdc);
		::ReleaseDC(NULL, hdc);
		
	}
	
	HFONT xdEzCreateFont (HDC hdc, TCHAR * szFaceName, int iDeciPtHeight,
		int iDeciPtWidth, int iAttributes, BOOL fLogRes)
	{
		FLOAT      cxDpi, cyDpi ;
		HFONT      hFont ;
		LOGFONT    lf ;
		POINT      pt ;
		TEXTMETRIC tm ;
		
		SaveDC (hdc) ;
		
		SetGraphicsMode (hdc, GM_ADVANCED) ;
		ModifyWorldTransform (hdc, NULL, MWT_IDENTITY) ;
		SetViewportOrgEx (hdc, 0, 0, NULL) ;
		SetWindowOrgEx   (hdc, 0, 0, NULL) ;
		
		if (fLogRes)
		{
			cxDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSX) ;
			cyDpi = (FLOAT) GetDeviceCaps (hdc, LOGPIXELSY) ;
		}
		else
		{
			cxDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, HORZRES) /
				GetDeviceCaps (hdc, HORZSIZE)) ;
			
			cyDpi = (FLOAT) (25.4 * GetDeviceCaps (hdc, VERTRES) /
				GetDeviceCaps (hdc, VERTSIZE)) ;
		}
		
		pt.x = (int) (iDeciPtWidth  * cxDpi / 72) ;
		pt.y = (int) (iDeciPtHeight * cyDpi / 72) ;
		
		DPtoLP (hdc, &pt, 1) ;
		
		lf.lfHeight         = - (int) (fabs (pt.y) / 10.0 + 0.5) ;
		lf.lfWidth          = 0 ;
		lf.lfEscapement     = 0 ;
		lf.lfOrientation    = 0 ;
		lf.lfWeight         = iAttributes & EZ_ATTR_BOLD      ? 700 : 0 ;
		lf.lfItalic         = iAttributes & EZ_ATTR_ITALIC    ?   1 : 0 ;
		lf.lfUnderline      = iAttributes & EZ_ATTR_UNDERLINE ?   1 : 0 ;
		lf.lfStrikeOut      = iAttributes & EZ_ATTR_STRIKEOUT ?   1 : 0 ;
		lf.lfCharSet        = DEFAULT_CHARSET ;
		lf.lfOutPrecision   = 0 ;
		lf.lfClipPrecision  = 0 ;
		lf.lfQuality        = 0 ;
		lf.lfPitchAndFamily = 0 ;
		
		lstrcpy (lf.lfFaceName, szFaceName) ;
		
		hFont = CreateFontIndirect (&lf) ;
		
		if (iDeciPtWidth != 0)
		{
			hFont = (HFONT) SelectObject (hdc, hFont) ;
			
			GetTextMetrics (hdc, &tm) ;
			
			DeleteObject (SelectObject (hdc, hFont)) ;
			
			lf.lfWidth = (int) (tm.tmAveCharWidth *
				fabs (pt.x) / fabs (pt.y) + 0.5) ;
			
			hFont = CreateFontIndirect (&lf) ;
		}
		
		RestoreDC (hdc, -1) ;
		return hFont;
	}
};


typedef struct  {
	long	lDate;
	int		h;
	int		m;
	int		s; 
}UPDATATIME,*PUPDATATIME;

class CXdKLine  
{
public: 
	CString		m_strHTML;
	UPDATATIME	m_udt;
	float CXdKLine::GetClose()
	{
		return m_fClose;
	}
	
	float CXdKLine::GetHigh()
	{
		return m_fHigh;
	}
	float CXdKLine::GetLow()
	{
		return m_fLow;
	} 
	bool CXdKLine::IsUp()
	{
		bool bRet = true;
		if(m_fClose > m_fOpen) 
		{
			bRet = true;     
		}
		else
		{
			bRet = false;
		}
		
		return bRet;
	}
	float CXdKLine::GetOpen()
	{
		return m_fOpen;
	}
	
	float GetSell();
	float GetPreClose();
	float GetAvg();
	CString GetUpdateTime();
	int GetDataFromHTML();
	void GetXY(int &x, int &y);
	void SetXY(int x,int y);
	void SetY(float y0,float y1);
	void setR(float r);
	float BodyWidth();
	CXdKLine(float o,float h,float l,float c){
		m_fOpen = o;
		m_fClose = c;
		m_fHigh = h;
		m_fLow = l;
		
		m_iDy = 400;
		m_fY0 = 42000.0;
		m_fY1 = 40000.0;
	}
	CXdKLine(){}
	virtual ~CXdKLine(){}
	
	void PaintMe (HDC hdc, int x, int iDx);
	void Paint5M (HDC hdc, int x, int iDx);
	
private:
	int Cal_K_2_Y(float f);
	HBRUSH GetBrush();
	HPEN  GetPen();
	float	m_fOpen;
	float	m_fClose;
	float	m_fHigh;
	float	m_fLow;
	float	m_fSell;
	float	m_fPreClose;
	float	m_fAvg;
	float	m_fR; 
	float	m_fY0;
	float	m_fY1;
	int		m_iDy;
	int		m_iX;
	int		m_iY;
};
class CGet_Data
{
public: 
	void FineAll(); 
	CString CGet_Data::plGetStrHtml()
	{
		CString strRet;
		strRet.Format("%s",m_lpszBufRawHtml);
		return strRet;	
	}
	void fn_CopyFile1_to_File2(CString file1,CString open_method1,CString file2,CString open_method2);
	void fn_Write_to_File(CString filename,CString str);
	int fn_Get_RB_Num();
	CString RBData2Str();
	bool fn_Save_OldData_2_File();
	bool fn_Save_RBData_2_File(CString strFileName,int nMode);
	CString fn_GetRBLogFileName();
	void fn_Update_RB_Date_2_File();
	bool fn_Parse_RB_Data();
	
	void CGet_Data::fn_MyNewBuf(DWORD dwSize)
	{
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
		m_lpszBufRawHtml=new char[dwSize+1];
		memset(m_lpszBufRawHtml,0,dwSize+1);
	}
	
	void CGet_Data::fn_ParseURL(CString &strUrl)
	{
		if(strUrl.IsEmpty())
		{
			return;
		}
		//去掉"http://"
		CString strTemp=strUrl.Mid(7);
		
		//检查主机的路径
		int nSlash=strTemp.Find("/");
		if (nSlash!=-1)  //如等于-1，就是没找到
		{
			m_strServer=strTemp.Left(nSlash);//取‘/’左边的服务器地址
			m_strPath=strTemp.Mid(nSlash);
		}
		else
			m_strServer=strTemp;
		
		
	}

	bool fn_From_URL(CString str)
	{
		m_lpszBufRawHtml=NULL;
		bool bRet = TRUE;
		CString strUrl = str;
		//判断地址是否有效,如为空或开头7个字符不是“http://"
		if(strUrl.IsEmpty()||strUrl.Left(7)!="http://")
		{
			AfxMessageBox("Sorry,It is a invalid address!");
			bRet = FALSE;
			goto EXIT;
		}
		//解析地址，得到server名字和文件路径
		fn_ParseURL(strUrl);
		//第一步:初始化internet DLL,这是第一个被调用的函数
		HINTERNET hSession;
		hSession = ::InternetOpen("Raw HTML Reader",PRE_CONFIG_INTERNET_ACCESS,
			"",INTERNET_INVALID_PORT_NUMBER,0);
		
		//判断会话句柄是否有效
		if(hSession==NULL)
		{
			AfxMessageBox("Internet session initalization failed!");
			bRet = FALSE;
			goto EXIT;
		}
		//第二步：初始化HTTP session
		HINTERNET	hConnect;
		hConnect = ::InternetConnect(hSession,//当前internet会话句柄
			m_strServer,//server name
			INTERNET_INVALID_PORT_NUMBER,
			NULL,//"",//user name
			"",//password
			INTERNET_SERVICE_HTTP,//Type of service to access
			0,
			0);
		//判断连接句柄是否有效
		if(hConnect==NULL)
		{
			AfxMessageBox("Internet connect initalization failed!");
			//关闭会话句柄
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		//第三步：打开一个HTTP请求句柄
		HINTERNET hHttpFile;
		hHttpFile = ::HttpOpenRequest(hConnect,
										  "GET",
										  m_strPath,
										  HTTP_VERSION,
										  NULL,
										  0,
										  INTERNET_FLAG_DONT_CACHE,
										  0);
		//判断连接句柄是否有效
		//判断会话句柄是否有效
		if(hHttpFile==NULL)
		{
			AfxMessageBox("Http request failed!");
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
			bRet = FALSE;
			goto EXIT;
		}
		
		
		
		//第四步：发出请求
		BOOL bSendRequest;
		bSendRequest = ::HttpSendRequest(hHttpFile,
									   NULL,
									   0,
									   0,
									   0);
		if(bSendRequest)
		{
			//得到文件的大小
			char achQueryBuf[16];
			DWORD dwFileSize;
			DWORD dwQueryBufLen=sizeof(achQueryBuf);
			BOOL bQuery=::HttpQueryInfo(hHttpFile,
				HTTP_QUERY_CONTENT_LENGTH,
				achQueryBuf,
				&dwQueryBufLen,
				NULL);
			if(bQuery)
			{
				//查找成功，指出需要存放文件的内存大小???????
				dwFileSize=(DWORD)atol(achQueryBuf);
			}
			else
			{
				//失败，猜出一个最大文件数
				return false;
				dwFileSize=10*1024;
			}
			
			//分配一个缓冲区给文件数据
			//	 m_lpszBufRawHtml=new char[dwFileSize+1];
			fn_MyNewBuf(dwFileSize);
			//读文件
			DWORD dwBytesRead;
			BOOL bRead = ::InternetReadFile(hHttpFile,
				m_lpszBufRawHtml,
				dwFileSize+1,
				&dwBytesRead);
			
			// 关闭INTERNET句柄
			VERIFY(::InternetCloseHandle(hHttpFile));
			VERIFY(::InternetCloseHandle(hConnect));
			VERIFY(::InternetCloseHandle(hSession));
		}
		else{
			bRet = FALSE; //网络不通
		}
		
EXIT:
		return bRet;
}
	void fn_From_File();
	CGet_Data()
	{ 
		m_lpszBufRawHtml = NULL;
	}

	virtual		~CGet_Data()
	{ 
		if(NULL != m_lpszBufRawHtml)
		{
			delete []m_lpszBufRawHtml;
			m_lpszBufRawHtml = NULL;
		}
	}
	char		*m_lpszBufRawHtml;
	
	CString		m_strServer;
	CString		m_strPath;
	int			nLine;
	int			(*p_Ball)[9];
private:
	void vv_Fun_Fine_All();
	static UINT  v_Thread_Fun_FineAll(LPVOID pParam);
};
class CMyLib 
{
#define		BLVV		virtual void
	class CMyView
	{
		class O
		{
		public:
			O():x(40),y(40),w(5),h(5),
				m_bCtrl(false),m_bEdit(false),
				pNext(NULL),m_nOs(0)
				//v(m_VectorSet)
			{
				m_str					= "";
				m_bPen					= true;
				m_logpen.lopnStyle		= PS_INSIDEFRAME;
				m_logpen.lopnWidth.x	= 1;
				m_logpen.lopnWidth.y	= 2;
				m_logpen.lopnColor		= RGB(0, 0, 255);
				
				m_pPen.lopnStyle		= PS_INSIDEFRAME;
				m_pPen.lopnWidth.x		= 1;
				m_pPen.lopnWidth.y		= 2;
				m_pPen.lopnColor		= RGB(0, 255, 0);
				
				m_fPen.lopnStyle		= PS_INSIDEFRAME;
				m_fPen.lopnWidth.x		= 1;
				m_fPen.lopnWidth.y		= 2;
				m_fPen.lopnColor		= RGB(255, 0, 0);
				
				m_nPen.lopnStyle		= PS_INSIDEFRAME;
				m_nPen.lopnWidth.x		= 1;
				m_nPen.lopnWidth.y		= 2;
				m_nPen.lopnColor		= RGB(188, 222, 58);
				
				
				m_bBrush				= false;
				m_logbrush.lbStyle		= BS_SOLID;
				m_logbrush.lbColor		= RGB(22, 55, 255);
				m_logbrush.lbHatch		= HS_HORIZONTAL;
				
			}
			~O()
			{
				for (int i=0;i<m_nOs;i++){// vi = v.begin(); vi != v.end(); ++ vi){
					if ( m_pOs[i]){//*vi ){ 
						delete (m_pOs[i]);//*vi);
					}
				} 
			//	v.clear();
				m_nOs = 0;
			}
			void pl_OnInit(int x1,int y1,int w1,int h1,O *o)
			{
				x		= x1;
				y		= y1;
				w		= w1;
				h		= h1;
				pNext	= o;
			}
			bool plIsRemoved()
			{
				bool b1 = (NULL==pNext);
				bool b2 = (NULL==pForward);
				return (b1&&b2); 
			}
			void plMoveAllAfterMe(int dx,int dy)
			{
				if(pNext) 
				{
					pNext->plMoveAllAfterMe(dx,dy);
					pNext->x += dx;
					pNext->y += dy;
				} 
			}
			BLVV plChar(WPARAM wP,LPARAM lP)
			{
				if(pNext) pNext->plChar(wP,lP);
				if(!m_bEdit) return;
				switch(wP)
				{
				case '\b': 
					{  
						ptBackSpace();
						return; 
					}
					break; 
				} 
				char sz[155];
				sprintf(sz,"%s",m_str.GetBuffer(m_str.GetLength()));
				char szNew[155];
				sprintf(szNew,"%s%c",sz,wP); 
				m_str = szNew;
			}  
			void plKeyup(WPARAM wP,LPARAM lP)
			{
				if(pNext) pNext->plKeyup(wP,lP);
				pvCtrlUp(wP,lP);
			}
			void plKeydown(WPARAM wP,LPARAM lP)
			{ 
				if(pNext) pNext->plKeydown(wP,lP);
				pvCtrlDown(wP,lP);
				if(!m_bEdit) return;
				long b = 0x20000000 & lP; // Alt 是否按下
				
				switch(wP)
				{    
				case 46: 
					pvDeleteMe();
					break;
				case 37:  
					b?(w -= 5):( x -= 5); 
					break;
				case 38: 
					b?(h -= 5):( y -= 5); 
					break;
				case 39: 
					b?(w += 5):( x += 5); 
					break;
				case 40: 
					b?(h += 5):( y += 5); 
					break;
				}
			}
			BLVV plDraw(CLfDC &l)
			{ 	   
				bool &bNDraw = m_bEdit; 
				if(bNDraw)
				{
					l.OnXdDrawRect(x-3,y-3,6,6,RGB(255,255,0));
					m_logpen.lopnColor = RGB(255, 0, 255);	 
				} 
				else
				{
					m_logpen.lopnColor = RGB(0, 0, 255);	
				}
				if(m_bCtrl)
				{
					l.OnXdDrawRect(x+w-3,y-3,6,6,RGB(0,255,255));
				}
				else
				{
				}
				l.plRect(x,y,w,h,m_bPen,m_logpen,m_bBrush,m_logbrush);
				l.OnXdDrawStr(x,y,m_str.GetBuffer(m_str.GetLength()));
			}
			CString							m_str;
			int								x,y,w,h;
			bool							m_bCtrl;
			bool							m_bEdit;
			bool							m_bPen;
			LOGPEN							m_logpen;
			bool							m_bBrush;
			LOGBRUSH						m_logbrush;
			LOGPEN							m_fPen,m_nPen,m_pPen;
			
			O								*pParent;
			O								*pForward;
			O								*pNext;
//			std::vector<O *>				m_VectorSet,&v;
//			std::vector<O *>::iterator		vi;
			O *								m_pOs[100];
			int								m_nOs;
			CBlDebug		d;  
		private:
			
			void pvDeleteMe()
			{
				if(pNext)
				{
					pNext->pForward = pForward;
				}
				pForward->pNext = pNext;
				pNext = NULL;
				pForward = NULL;
				//std::vector<O *>::iterator &i = pParent->vi;
				//std::vector<O *>		&a = pParent->v;

				
				for (int i=0;i<m_nOs;i++)// i = a.begin(); i < a.end(); ++ i)
				{
					if (m_pOs[i])// *i )
					{  
						bool b1 = (NULL==m_pOs[i]->pNext);//(NULL==(*(*i)).pNext);
						bool b2 = (NULL==m_pOs[i]->pForward);//(NULL==(*(*i)).pForward);
						if(b1&&b2)
						{
							//	a.erase(i);
							//	delete(*i); 
						} 
					}
				}
			}
			void pvCtrlDown(WPARAM w,LPARAM l)
			{
				if(17==w) m_bCtrl = true;   
			}
			void pvCtrlUp(WPARAM w,LPARAM l)
			{
				if(17==w) m_bCtrl = false;   
			}
		protected:
			void ptBackSpace()
			{
				char sz[155]; 
				sprintf(sz,"%s",m_str.GetBuffer(m_str.GetLength()));
				int n = strlen(sz);
				sz[n-1] = '\0';
				m_str = sz;
			}
		};
		
		class CNote :public O
		{
		public:
			CNote(O *p,O *f,O *n)
			{ 
				O::O();
				pParent		= p;
				pForward	= f;
				pNext		= n;
			} 
			~CNote(){}
			void plDraw(CLfDC &l)
			{ 	
				O::plDraw(l); 
				int nY = y+20;
				l.OnXdDrawStr(x,nY,m_str.GetBuffer(m_str.GetLength()));
				l.OnXdDrawRect(x,nY,w,h,RGB(255,0,255));
				pvDraw2Parent(l);
				pvDraw2Forward(l); 
				pvDraw2Next(l); 
				
				pvDraw_1_Note(l);
			} 
			void plChar(WPARAM wP,LPARAM lP)
			{ 
				O::plChar(wP,lP);
				pv2Char(wP,lP);
			}
			bool pl_OnHit(int i,int j,CString &s)
			{
				bool &bNote = m_bEdit;
				CPoint p(i,j);
				CRect r(x,y,x+w,y+h);
				if(r.PtInRect(p))
				{  
					s.Format("Note: x=%d",x); 
					bNote = true; 
					return true;
				}
				else
				{ 
					if(m_bCtrl)
					{
						TRACE("ctrl=%d\n",m_bCtrl);
					}
					else
					{
						bNote = false;
					}
					return false;
				} 
			}
		private:  
			void pvDraw_1_Note(CLfDC &l)
			{
				CString &s = m_str;
				char sz[155];
				sprintf(sz,"%s",s.GetBuffer(s.GetLength()));
				
				int d = 0;
				int nDY = 7;
				switch(sz[1])
				{
				case 'C':
					d = -12;
					break;
				case 'D':
					d = -7;
					break;
				case 'E':
					d = 0;
					break;
				case 'F':
					d = 5;
					break;
				case 'G':
					d = 12;
					break;
				case 'A':
					d = 18;
					break;
				case 'B':
					d = 24;
					break;
				case 'c':
					d = 32;
					break;
				case 'd':
					d = 38;
					break;
				case 'e':
					d = 45;
					break;
				case 'f':
					d = 50;
					break;
				}
				int nX = x + 8;
				int nY = y - d;
				char szNote[2];
				sprintf(szNote,"%c",sz[0]);
				l.OnXddrawMusicStr(nX,nY,szNote,0);
				
			} 
			void pvDraw2Parent(CLfDC &l)
			{  
				l.plLine(x,y,pParent->x,pParent->y+pParent->h,m_pPen); 
			}
			void pvDraw2Forward(CLfDC &l)
			{  
				if(pForward)
				{
					l.plLine(x,y,pForward->x+pForward->w,pForward->y,m_fPen); 
				}
			}
			void pvDraw2Next(CLfDC &l)
			{
				if(NULL==pNext)
				{
					l.plLine(x+w,y+h,x+w+5,y+h,m_nPen); 
				}
				else
				{ 
					l.plLine(x+w,y+h,pNext->x,pNext->y+pNext->h,m_nPen); 
				}
			}
			void pv2Char(WPARAM wP, LPARAM lP)
			{ 
				if(!m_bEdit) return;
				if(' ' == wP)
				{
					pvInSertAfterMe();
					ptBackSpace();
				} 
			}
			void pvInSertAfterMe()
			{
				CNote *pN = new CNote(pParent,this,pNext);
				pN->pl_OnInit(x+25,y+15,w,h,this->pNext);
				
				if(pNext)
					pNext->pForward = pN;
				this->pNext= pN;
				//pParent->v.push_back(pN);  
				pParent->m_pOs[m_nOs] = pN;
				m_nOs++;
				plMoveAllAfterMe(25,0);
			}
			void x_bottom___(){}
			
		};
		class CBeat : public O
		{
			
		public:
			CBeat() {}
			~CBeat(){}
			void pl_Init(int x1,int y1,int w1,int h1)
			{ 
				CNote *pN1 = new CNote(this,this,NULL);
				//v.push_back(pN1);
				m_pOs[m_nOs] = pN1;
				m_nOs++;
				O::pl_OnInit(x1,y1,w1,h1,pN1);
				int nDX = 20;
				CNote *pN2 = new CNote(this,pN1,NULL);
			//	v.push_back(pN2);
				m_pOs[m_nOs] = pN2;
				m_nOs++;
				pN1->pl_OnInit(x+5,y+5,15,15,pN2);
				pN2->pl_OnInit(x+5+nDX,y+5,15,15,NULL);
			}
			void plChar(WPARAM wP,LPARAM lP)
			{  
				O::plChar(wP,lP);
				pvChar(wP,lP);
			}
			void plOn_Draw(CLfDC &l)
			{
				//		l.OnXdDrawRect(x,y,w,h,RGB(255,0,0)); 
				O::plDraw(l); 
				for ( int i=0;i<m_nOs;i++){//vi = v.begin(); vi < v.end(); ++ vi){
					if ( m_pOs[i]){//*vi ){ 
						O &n = *m_pOs[i];//(*(*vi));
						if(!n.plIsRemoved())
							n.plDraw(l);
					}
				}				
			}
			bool plOn2Hit(int i,int j,CString &s)
			{  
				bool &bBeat = m_bEdit;
				
				bool b = false;
				for (int idx=0;idx<m_nOs;idx++){// vi = v.begin(); vi < v.end(); ++ vi){
					if ( m_pOs[idx])//*vi )
					{ 
						bool bI = ((CNote*)m_pOs[idx])->pl_OnHit(i,j,s);//((CNote*)(*vi))->pl_OnHit(i,j,s);
						b = b||bI;
					}
				}
				if(b) 
				{
					bBeat = false; 
					return true;
				}
				CPoint p(i,j);
				CRect r(x,y,x+w,y+h);
				if(r.PtInRect(p))
				{  
					s.Format("Beat:%d",x);
					bBeat =true; 
					return true;
				}
				else
				{ 
					bBeat = false; 
					return false;
				} 
			}
		private:  	 
			void pvChar(WPARAM wP,LPARAM lP)
			{ 
				//d.plMsgBox("beat char");
				
			}
			
			int			v_bottom__________;
			
		};
		class CBar : public O
		{
			
		public:
			CBar(){}
			~CBar(){}
			void plOn_Init(int x1,int y1,int w1,int h1)
			{ 
				O::pl_OnInit(x1,y1,w1,h1,&beat); 
				beat.pl_Init(x+5,y+5,w-20,h-20);
			}
			void plOn_Char(WPARAM w)
			{ 
			}
			bool plOnHit(int i,int j,CString &s)
			{
				bool &bBar = m_bEdit;
				if(beat.plOn2Hit(i,j,s)) 
				{
					bBar = false;
					return true;
				}
				CPoint p(i,j);
				CRect r(x,y,x+w,y+h);
				if(r.PtInRect(p))
				{  
					s.Format("BAR: X=%d",x);
					bBar = true; 
					return true;
				}
				else
				{ 
					bBar = false;
					return false;
				} 
			}
			void plOnDraw(CLfDC &l)
			{
				//	l.OnXdDrawRect(x,y,w,h,RGB(66,255,123));
				
				O::plDraw(l);
				beat.plOn_Draw(l);
			}
		private: 
			CBeat		beat;
			int			v_bottom__________;
		};
		class CLine : public O
		{
			
		public:
			CLine() 
			{
				strL = "):::::";
			}
			~CLine(){} 
			void pl2Init(int x1,int y1,int w1,int h1)
			{
				O::pl_OnInit(x1,y1,w1,h1,&b); 
				b.plOn_Init(x+5,y+5,w-30,h-30);
			}
			void plChar(WPARAM wP,LPARAM lP)
			{  
				//d.plMsgBox("line");
				O::plChar(wP,lP);
			}
			void pl_Draw(CLfDC &l)
			{
				l.OnXdDrawRect(x,y,w,h,RGB(55,123,12));
				l.OnXddrawMusicStr(x,y,strL.GetBuffer(strL.GetLength()),0);
				
				//	m_bBrush = true;
				O::plDraw(l);
				b.plOnDraw(l);
			}
			bool pl2Hit(int i,int j,CString &s)
			{
				bool &bLine = m_bEdit;
				if(b.plOnHit(i,j,s))
				{
					bLine = false;
					return true;
				}
				CPoint p(i,j);
				CRect r(x,y,x+w,y+h);
				if(r.PtInRect(p))
				{  
					s.Format("Line: x=%d",x);
					bLine = true;
					return true;
				}
				else
				{ 
					bLine = false;
					return false;
				}
			}
		private: 
			CBar		b;
			CString		strL;
			int			v_bottom____________;
		};
		class CPage : public O
		{
			
		public:
			CPage() 
			{ 
				m_nBtnX			= 220;
				m_nBtnY			= 250;
				m_nBtnSelected	= 0;
			}
			~CPage(){}
			
			void plInit(int x1,int y1,int w1,int h1)
			{ 
				O::pl_OnInit(x1,y1,w1,h1,&m_line);  
				
				m_line.pl2Init(x+10,y+10,w-40,h-40);
			} 
			bool plHit(int i,int j,CString &s)
			{
//				printf("BlXAU.dll: %d,%d\n",i,j);
				pvHitToolBar(i,j);
				if(m_line.pl2Hit(i,j,s))
				{
					return true;
				}
				CPoint p(i,j);
				CRect r(x,y,x+w,y+h);
				
				if(r.PtInRect(p))
				{
					
					s.Format("Page: x=%d",x);
					return true;
				}
				else
				{
					s = "s:";
					return false;
				}
			}
			void pl2Draw(CLfDC &l)
			{
				pv2DrawMyBackGround(l);
				l.OnXdDrawRect(x,y,w,h,RGB(11,22,33));
				m_line.pl_Draw(l);
				
				
				pv2DrawToolBar(l);				
			}
		private: 
			void pv2DrawMyBackGround(CLfDC &l)
			{
				l.OnXdDrawRect(0,0,300,300,RGB(0xf0,0xff,0xff));
			}
			void pv2DrawToolBar(CLfDC &l)
			{
				l.OnXdDrawRect(m_nBtnX,m_nBtnY,30,30,RGB(0x00,0xff,0xff));
				if(m_nBtnSelected)
				{
					l.OnXdDrawRect(m_nBtnX+5,m_nBtnY+5,20,20,RGB(0xa0,0x11,0x22));
				}

			}
			bool pvHitToolBar(int i,int j)
			{
				bool b = false;
				CPoint p(i,j);
				CRect r(m_nBtnX,m_nBtnY,m_nBtnX+30,m_nBtnY+30);
				
				if(r.PtInRect(p))
				{ 
					m_nBtnSelected = 1;
					b = true;
				}
				else
				{
					m_nBtnSelected = 0;
				}

				return b;
			}
			CLine		m_line;

			int			m_nBtnCount;
			int			m_nBtnSelected;
			int			m_nBtnX,m_nBtnY;
		}; 
		class CMyFun
		{
		public:  
			CMyFun():x(30),y(250),w(200),h(40){
				s = "s:";
			}
			void plLBtnDow(WPARAM w,LPARAM l,CPage &p)
			{
				int x1 = (int)(short)LOWORD(l);
				int y1 = (int)(short)HIWORD(l);  
				p.plHit(x1,y1,s); 
				
			}
			void plShowSelectObjPrp(CLfDC &l)
			{
				l.OnXdDrawRect(x,y,w,h,RGB(255,0,100));
				l.OnXdDrawStr(x+10,y+10,s.GetBuffer(s.GetLength()));
			}
		private:
			CBlDebug		d; 
			int				x,y,w,h;
			CString			s;
		};
		public:
			CMyView():m_pMyLib(NULL),m_nTime(1),m_nTestNum(0),m_fSell(0.0),m_nCount(0)
			{
				m_pPrpDlg = NULL;
				sprintf(m_szDir,"[.]"); 				
			}
			~CMyView(){
				CMyPrpDlg * &p = m_pPrpDlg;
				if (p)
				{ 
					delete[]p;
					p=NULL;
				}
			}
			void Init(CMyLib*p)
			{
				m_pMyLib = p;
				page.plInit(30,30,250,180);
			}
		private:
			void prPrpChanged(UINT m, WPARAM w, LPARAM l)
			{
				switch(w)
				{
				case 1001:
					{
						m_nTime = l; 
					}
					break;
				}
			}
			void prShowDlgPrp()
			{
				CMyPrpDlg * &p = m_pPrpDlg;
				if (p==NULL)
				{		
					p = new CMyPrpDlg(NULL); 
					p->Create(IDD_DLG_PRP,NULL);//创建对话框
					p->ShowWindow(SW_SHOW);    //显示对话框
					p->plSetParam(m_pMyLib->GetHWnd());
					
				}
				else
				{
					p->ShowWindow(SW_SHOW);    //显示对话框
				} 
			}
		public:
			BLSTATUS CMyView::pl2OnMsg(UINT m, WPARAM w, LPARAM l)
			{
				BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
				switch(m)
				{
				case BL_WM_INIT:
					{
						BL_LPARAM_CONTEXT* p = (BL_LPARAM_CONTEXT*)l;
						m_pMyLib->plMsgInit(*p);
					}
					break;
				case BL_WM_B1_PRP_1:
					{
						prPrpChanged(m,w,l);
					}
					break;
				case BL_WM_CMD_B0_2_B1_01:
					{ 
						prShowDlgPrp();
					}
					break;
				case WM_LBUTTONDOWN:
					{
						f.plLBtnDow(w,l,page);
					}
					break;
				case WM_KEYUP: 
				case WM_SYSKEYUP:
					prKeyup(w,l);
					break;
				case WM_KEYDOWN:
				case WM_DEADCHAR:
				case WM_SYSKEYDOWN:
				case WM_SYSCHAR:
				case WM_SYSDEADCHAR: 
					{ 
						prKeydown(w,l);  
					}
					break;
				case WM_CHAR:
					{ 
						prChar(w,l);   
					}
					break;
				}
				return r;
			}
		private:
			CMyLib*				m_pMyLib; 
			CLfDC				l;
			CMyFun				f;		
			CMyPrpDlg			*m_pPrpDlg; 
			CBlDebug			d;  
			CPage				page;
			
			char				m_szDir[255];
			int					m_nTime;
			
			void prKeyup(WPARAM w,LPARAM l)
			{
				page.plKeyup(w,l); 
				TRACE("ku\n");
			}
			void prKeydown(WPARAM w,LPARAM l)
			{
				page.plKeydown(w,l); 
				TRACE("kd\n");
			}
		//	vector<CXdKLine>			m_vKlines;
		//	std::vector<CXdKLine>::iterator	iter;
			CXdKLine					m_VA[1000];
			int							m_nVA;
			void prChar(WPARAM wP,LPARAM lP)
			{  
				page.plChar(wP,lP);
				switch(wP)
				{
				case '\b': 
					{
						char sz[1000];
						prGetDir(sz);
						int n = strlen(sz);
						sz[n-1] = '\0';
						prSetDir(sz);
						
						return; 
					}
					break;
				case 39:
					d.plMsgBox("39");
					break;
				}
				char sz[1000];
				prGetDir(sz);
				char szNew[1000];
				sprintf(szNew,"%s%c",sz,wP);
				prSetDir(szNew);
				
			}
		public:
			int		m_nTestNum;
			float	m_fSell;
			int		m_nCount;
			int plGetSleepTime()
			{
				return m_nTime;
			}
			void CMyView::plCreateBmp24Bytes(int w,int h,BYTE *pB)
			{
				pvCreateBmpData(w,h,pB);
			}
			void CMyView::plNewKDatas()
			{ 
				int n = m_nVA;//m_vKlines.size();
				
				if(n<1){ 
					char s[250]={0};
					pvGetModulePath(s);
					char szPath[250]={0};
					sprintf(szPath,"%s/%s",s,"Data/HXCUA_60M.txt");
					pvOpenFile(szPath);
				} 

				CString strWholeDayXAU = pvUpdateWholeDayXAU(m_nCount);
				CString strXAU = pvUpdateXAU(m_fSell);
				m_nTestNum++;
			}
		private:
			CString CMyView::pvUpdateXAU(float &fSell)
			{
				CString strRet = "XAU: ";
				CGet_Data	d;
				CString str  = "http://api.baidao.com/api/hq/npdata.do?ids=201";
				BOOL b = d.fn_From_URL(str); 
				if(!b)
				{
					return strRet;
				}
				else
				{
					strRet = d.plGetStrHtml();
//					printf("xdTest:: %s\n",strRet.GetBuffer(strRet.GetLength()));

					CString strHtml = strRet;
					CString strRight; 

					
					//  卖出价 sell 值 
					strRight=strHtml.Right(strHtml.GetLength()-strHtml.Find("sell")); 
					sscanf(strRight.GetBuffer(strRight.GetLength()),"sell\":%f",&fSell); 
				 
					return strRet;
				}
			}
		private:
			CString CMyView::pvUpdateWholeDayXAU(int &nCount)
			{
				CString strRet = "WholedayXAU: ";
				CGet_Data	d;
				CString str  = "http://api.baidao.com/api/hq/mtdata.do?quotationType=201&id=201&JSONP=?&ran=";
				BOOL b = d.fn_From_URL(str); 
				if(!b)
				{
					return strRet;
				}
				else
				{
					strRet = d.plGetStrHtml();
					CString strHtml = strRet;
					CString strRight;  
					// Get count  
					strRight=strHtml.Right(strHtml.GetLength()-strHtml.Find("count")); 
					sscanf(strRight.GetBuffer(strRight.GetLength()),"count\":%d",&nCount); 
					
					pvGetOHLCFromJSONTxt(strHtml);
				 
					return strRet;
				}
			}
			void CMyView::pvGetOHLCFromJSONTxt(CString &strJSONTxt)
			{
				CStringList sl;
				CString &s = strJSONTxt;
				CString r;  
				r=s.Right(s.GetLength()-s.Find("open")); 
				r.SetAt(0,'e');
				int n = 0;
				CString sOHLC; 
				int nIdxOpen = 1;
				while(r.GetLength()>1 && !(-1==nIdxOpen)) //至少有一个 open
				{
					n++; 
					CString sNext = r;
					nIdxOpen = sNext.Find("open"); 
					sOHLC = sNext.Left(nIdxOpen);
					r = sNext.Right(sNext.GetLength()-nIdxOpen);  
					r.SetAt(0,'e');
					if(1==n ||
						2==n ||
						100==n||
						1160==n||
						1161==n)
					{
						printf("n = %d: %s\n",n,sOHLC.GetBuffer(sOHLC.GetLength()));
					}  
				}
				printf("n = %d: %s\n",n,sOHLC.GetBuffer(sOHLC.GetLength()));
					
			}
		private:
			void CMyView::pvGetModulePath(OUT char *szPath)
			{
				char szFilePath[296]; 
				memset(szFilePath,0,296); 
				::GetModuleFileName(NULL,szFilePath,296);
				PathRemoveFileSpec(szFilePath);
				strcpy(szPath,szFilePath);
				
			}
			void CMyView::pvOpenFile(char *szFN)
			{ 
				CStdioFile file;
				
				if (!file.Open(szFN, CFile::modeRead))
				{
					::AfxMessageBox(_T("文件打开失败。"));
					return;
				}
				
				CString strText = _T("");
				int n=0;
				while (file.ReadString(strText))
				{
					n++;  
					CString s;
					s.Format("%d : ",n);
					s+=strText;
					
					if(n>2)
					{
						int a[4];
						char strTmp[100]="\0";
						sscanf(strText,"%s %s	%d %d %d %d",strTmp,strTmp,
							&a[0],&a[1],&a[2],&a[3]); 
						CXdKLine x(a[0],a[1],a[2],a[3]);
						
						//m_vKlines.push_back(x);
						m_VA[m_nVA] = x;
						m_nVA++;
					}  
				}
				
				file.Close();
			}
			
			void CMyView::pvDrawKlines(HDC hdc,int w,int h)
			{ 	
				int n = m_nVA;//m_vKlines.size();
				
				if(n<1){ 
					return;
				} 
				CRect r(0,0,w,h);
				int iDx = (r.Width()-20)/(min(500,n)+8);
				int x1 = 10;
				int y0 = 100,y1=120;
				float fKMin = v_GetHighMax();
				float fKMax = v_GetLowMin();
				LOGBRUSH lb ;     
				HBRUSH hBrush = NULL ;	 
				hBrush = CreateSolidBrush(RGB(0,0,0));
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc,hBrush);
				
				Rectangle(hdc,r.left+10,r.top+10,r.right-10,r.bottom-10);  
				hOldBrush = (HBRUSH)SelectObject(hdc,hBrush);
				
				
				for(int i=0;i<m_nVA;i++)//iter=m_vKlines.begin();iter!=m_vKlines.end();++iter)
				{
					
					y0 = v_Get_K_2_Y(m_VA[i].GetOpen(),//iter->GetOpen(),
						fKMin,fKMax,r.top+80,r.bottom-150);
					y1 = v_Get_K_2_Y(m_VA[i].GetClose(),//iter->GetClose(),
						fKMin,fKMax,r.top+80,r.bottom-150);
					HPEN hPen;
					lb.lbStyle = BS_SOLID ;
					lb.lbHatch = 0 ;   
					if(m_VA[i].IsUp())//iter->IsUp())
					{
						hBrush = CreateSolidBrush(RGB(255,0,0));
						lb.lbColor = RGB (0xFF,0,0); 
					}
					else
					{
						hBrush = CreateSolidBrush(RGB(0x54,0xff,0xff)); 
						lb.lbColor = RGB (0x54,0xff,0xff);
					}
					hPen =  ExtCreatePen (PS_SOLID, 1, &lb, 0, NULL) ;
					HPEN hOldPen = (HPEN)SelectObject(hdc,hPen);
					hOldBrush = (HBRUSH)SelectObject(hdc,hBrush);
					Rectangle(hdc,x1,y0,x1+iDx,y1); 
					
					
					int iYHight = v_Get_K_2_Y(m_VA[i].GetHigh(),//iter->GetHigh(),
						fKMin,fKMax,r.top+80,r.bottom-150);
					int iYLow = v_Get_K_2_Y(m_VA[i].GetLow(),//iter->GetLow(),
						fKMin,fKMax,r.top+80,r.bottom-150);
					MoveToEx(hdc,x1+iDx/2,iYHight,NULL);
					LineTo(hdc,x1+iDx/2,iYLow);
					if(y0==y1)
					{
						MoveToEx(hdc,x1,y0,NULL);
						LineTo(hdc,x1+iDx,y0);
					}
					x1 += iDx*(1.2); 
					
					SelectObject(hdc,hOldBrush); DeleteObject (hBrush) ;  
					SelectObject(hdc,hOldPen); DeleteObject (hPen) ; 
				} 
				
			}
			
			int v_Get_K_2_Y( float fK,float fMin, float fMax,int iMin,int iMax)
			{
				return iMin + (fK - fMin)*(iMax-iMin)/(fMax-fMin);
			} 
			float v_GetLowMin()
			{
				
				float fRet = 0.0;
				//vector<float> vF;
				float fA[1000];
				for(int i=0;i<m_nVA;i++)//std::vector<CXdKLine>::iterator iter=m_vKlines.begin();iter!=m_vKlines.end();++iter)
				{
					//vF.push_back(iter->GetHigh());
					fA[i] = m_VA[i].GetHigh();
				}  
			//	int	pos = (int) (  std::min_element(vF.begin(),vF.end()) - vF.begin() );
			//	fRet = vF[pos];
				return fRet;	
			}
			
			float v_GetHighMax()
			{	
				float fRet = 0.0;
				/*
				vector<float> vF;
				for(iter=m_vKlines.begin();iter!=m_vKlines.end();++iter)
				{
					vF.push_back(iter->GetHigh());
				}  
				int	pos = (int) ( std::max_element(vF.begin(),vF.end()) - vF.begin() );
				fRet = vF[pos];
				
				  */
				return fRet;	
			}
			
			void CMyView::pvCreateBmpData(int w, int h, BYTE *pDat)
			{
				static int i=0;
				i++;
				char	szDir[255];
				prGetDir(szDir); 
				float	fSell	= m_fSell;
				int		nCount	= m_nCount; 
				 
				char s[1115];
				sprintf(s,"i = %03d (%.2f) (%s):%s [Sleep(%d)]",
					i,fSell,
					MY_VERSION, 
					szDir,m_nTime); 
				l.plInitDraw();
				page.pl2Draw(l);

				l.OnXdDrawStr(11,210,s); 
				char s2[1000];
				sprintf(s2,"WholdeDay: count = %d m_nTestNum = %d",nCount,m_nTestNum);
				l.OnXdDrawStr(11,230,s2); 
				l.OnXdDrawRect(5,255,5,5,RGB(255,220,0));
				 
				l.OnXdDrawRect(200,50,30,30,RGB(255,220,0));
				
				f.plShowSelectObjPrp(l);
				pvDrawKlines(l.plGetDC(),300,200);
				l.OnXdGetData(300,300,pDat);
				
				l.plUpsidedown24Rgb(pDat,300,300);
			}
		private:
			void prSetDir(char* sz)
			{
				sprintf(m_szDir,"%s",sz);
			} 
			void prGetDir(char* sz)
			{
				sprintf(sz,"%s",m_szDir); 
			}
			
	};
	
	
	class CMyThread: public CBlThread
	{
	public:
		CMyThread():m_lpSnapProc(NULL),m_pSnapParam(NULL){}
		~CMyThread(){}
		void plRun(void *p)
		{
			pvCreate(pv2CreateBmpDataFun,p);
			pvCreate(pvGetJSONFun,p);
		}
		void plSetCallBackFun(BL_CBP_PROC f,void *p)
		{
			m_lpSnapProc = f;
			m_pSnapParam = p;
		}
	private:
		
		BL_CBP_PROC		m_lpSnapProc;
		void*			m_pSnapParam;
		
		static DWORD WINAPI	CMyThread::pvGetJSONFun(void *p1)
		{
			DWORD dwR = 0;
			CMyLib*  pL = (CMyLib*) p1; 
			 
			while(1)    
			{  
				Sleep(1000);
				pL->plGetMyView()->plNewKDatas();
			}
			return dwR;
		}
		static DWORD WINAPI	CMyThread::pv2CreateBmpDataFun(void *p1)
		{
			DWORD dwR = 0;
			CMyLib*  pL = (CMyLib*) p1; 
			
			static n=300;
			static BYTE bt[300*300*3]; 
			int i = 0;
			while(1)    
			{  
				i++;
				Sleep(pL->plGetMyView()->plGetSleepTime());
				pL->plGetMyView()->plCreateBmp24Bytes(300,300,bt);  

				BL_CB_INF inf;
				inf.pParam		= bt;
				inf.pCaller		= pL->plGetMyThread()->m_pSnapParam;
				BL_CBP_PROC	f	= pL->plGetMyThread()->m_lpSnapProc;
				if(NULL!= f) 
				{
					f(&inf);
				}
			} 
			return dwR;
		} 
		
	};
	public:
		CMyLib(HWND h):m_hWnd(h){
			m_myThread.plRun(this);
			m_myView.Init(this);
			
		}
		~CMyLib(){}
		
		HWND GetHWnd() 
		{
			return m_hWnd;
		}
		BLSTATUS plMsgInit(BL_LPARAM_CONTEXT &c)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
			
			if(0!=strcmp(c.szVerify,"BEAUTIFULLOVER"))
			{   
				r = BL_STATUS_PARAMETER_INVALID;
			}
			else
			{
				m_myThread.plSetCallBackFun(c.LPARAM.CallBack.pFun,c.LPARAM.CallBack.pParam);
				r = BL_STATUS_OK;
			}
			return r;
		}
		CMyView* plGetMyView() 
		{
			return &m_myView;
		}
		CMyThread* plGetMyThread()
		{ 
			return &m_myThread;
		}
		BLSTATUS pl2Do(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			BLSTATUS r = pv2Do(h,m,w,l);
			return r;
		}
	private:
		HWND						m_hWnd;
		CMyThread					m_myThread; 
		CMyView						m_myView;
		
		BLSTATUS pv2Do(HWND h,UINT m, WPARAM w, LPARAM l)
		{
			BLSTATUS r = BL_STATUS_NOT_SUPPORT_INTERFACE;
			if(NULL==m_hWnd)
			{
				m_hWnd = h;
			}  
			if(h)
			{
				m_myView.pl2OnMsg(m,w,l);
			}  
			return r;
		}
};

class CBlXAUApp : public CWinApp
{
public:
	CBlXAUApp();
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlXAUApp)
	//}}AFX_VIRTUAL
	
	//{{AFX_MSG(CBlXAUApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLXAU_H__FF5B609A_BF33_476E_A89F_8EBE8259FB6C__INCLUDED_)
